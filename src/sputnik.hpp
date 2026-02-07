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
    private:
        std::map<std::string, std::string> _values = {};
        std::multimap<std::string, std::string> _objects = {};
    public:
        Sector();
        ~Sector();

        std::map<std::string, std::string> values();
        std::multimap<std::string, std::string> objects();
        
        std::string value(std::string key);
        std::vector<std::string> valueAsArray(std::string key);

        std::string object(std::string key);
        std::vector<std::string> objectAsArray(std::string key);
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
        std::map<std::string, Sector> _sectors = {};
        void invalidate();
    public:
        File();
        ~File();

        std::map<std::string, Sector> sectors();

        ParseStatus parseText(std::string text);
        ParseStatus parseFile(std::string fileName);

        Sector root();
        Sector sector(std::string key);
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

std::map<std::string, std::string> Sputnik::Sector::values() {
    return this->_values;
}

std::multimap<std::string, std::string> Sputnik::Sector::objects() {
    return this->_objects;
}

// FILE
Sputnik::File::File() {

}

Sputnik::File::~File() {

}

void Sputnik::File::invalidate() {
    this->_sectors.clear();
}

Sputnik::ParseStatus Sputnik::File::parseText(std::string text) {
    Sputnik::ParseStatus status;
    return status;
}

Sputnik::ParseStatus Sputnik::File::parseFile(std::string fileName) {
    Sputnik::ParseStatus status;
    std::ifstream file(fileName);

    if (file.is_open()) {
        // File opened, so invalidate (reset all values) this Sputnik file
        std::string line;
        
        // read file line my line
        while (std::getline(file, line)) {
            //std::cout << line << std::endl;

            if (line.starts_with(':')) {
                std::string sectionName(line.begin()+1, line.end());
                std::cout << sectionName << std::endl;
            }
        }

        file.close();
    }


    return status;
}


std::map<std::string, Sputnik::Sector> Sputnik::File::sectors() {
    return this->_sectors;
}

#endif 