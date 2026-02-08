#include <string>
#include <map>
#include <vector>
#include <fstream>

#ifndef SPUTNIK_H
#define SPUTNIK_H

namespace Sputnik {
    /// @brief A set of values and objects related to each other.
    /// think of it like a "namespace" in C++, which I was originally
    /// going to call it but decided on "sector" to avoid conflicts
    /// with the reserved keyword "namespace".
    class Sector {
    public:
        Sector();
        ~Sector();

        std::map<std::string, std::map<std::string, std::string>> sections = {};
        std::multimap<std::string, std::map<std::string, std::string>> objects = {};
        
        std::string value(std::string key);
        std::vector<std::string> valueAsArray(std::string key);
    };

    struct ParseStatus {
        // flag if the parse was a success
        bool success = true;
        // if not a success, not the line and error message
        // line number of -1 means the error wasn't line specific
        int lineNumber = -1;
        // the error message
        std::string errorMessage = "";
    };

    class File {
    private:
        void clear();
    public:
        File();
        ~File();

        std::map<std::string, Sector> sectors = {};

        ParseStatus parseText(std::string text);
        ParseStatus parseFile(std::string fileName);

        Sector root();
        Sector sector(std::string key);
    };

    enum class LineState {
        AtRoot,
        InSection,
        InObject
    };

    std::vector<std::string_view> splitString(std::string_view text, char delimeter);
}

// String ops
std::vector<std::string_view> Sputnik::splitString(std::string_view text, char delimeter)
{
    std::vector<std::string_view> result; 
    auto left = text.begin(); 

    for (auto it = left; it != text.end(); ++it) 
    { 
        if (*it == delimeter) 
        { 
            result.emplace_back(&*left, it - left); 
            left = it + 1; 
        } 
    } 
    
    if (left != text.end()) {
        result.emplace_back(&*left, text.end() - left); 
    }

    return result; 
}


// SECTOR
Sputnik::Sector::Sector() {

}

Sputnik::Sector::~Sector() {

}

// FILE
Sputnik::File::File() {

}

Sputnik::File::~File() {

}

void Sputnik::File::clear() {
    // Clear the sectors
    this->sectors.clear();
    // Add in root sector
    Sputnik::Sector *rootSector = new Sputnik::Sector();
    this->sectors.insert({"root", *rootSector});
}

Sputnik::ParseStatus Sputnik::File::parseText(std::string text) {
    Sputnik::ParseStatus status;
    return status;
}

Sputnik::ParseStatus Sputnik::File::parseFile(std::string fileName) {
    Sputnik::ParseStatus status;
    std::ifstream file(fileName);

    if (file.is_open()) {
        // File opened, so clear (reset all values) this Sputnik file
        this->clear();
        
        // Loop by line
        std::string line;
        // Variables to keep track of state that spans multiple lines
        Sputnik::LineState lineState = Sputnik::LineState::AtRoot;
        std::map<std::string, std::string> *currentSectionOrObject = nullptr;

        while (std::getline(file, line)) {
            //std::cout << line << std::endl;
            bool sectionStart = line.starts_with(':');
            bool objectStart = line.starts_with('@');
            if (sectionStart || objectStart) { // sections and objects share a lot of logic
                std::string sectionOrObjectName(line.begin()+1, line.end());

                // Check if a sector is specified in the name. If not, the sector defaults to root.
                std::vector<std::string_view> sectorSplit = Sputnik::splitString(sectionOrObjectName, '>');
                std::string sectorName = "root";
                if (sectorSplit.size() > 1) {
                    sectorName = std::string(sectorSplit[0]);
                }

                // Get the sector
                Sputnik::Sector sector = this->sectors[sectorName];

                if (sectionStart) {
                    lineState = Sputnik::LineState::InSection;
                    currentSectionOrObject = &sector.sections[sectionOrObjectName]; 
                } else {
                    lineState = Sputnik::LineState::InObject;
                    // replace this with creating and inserting a new object
                    currentSectionOrObject = &sector.objects[sectionOrObjectName]; 
                }

                std::cout << sectionOrObjectName << std::endl;
            } else if (line.starts_with(';')) { // comment
                // do nothing
            } else if (line.find("=") != std::string::npos) { // key=value line
                // todo: get key and value
            }
        }

        file.close();
    }


    return status;
}

#endif 