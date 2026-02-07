#include <iostream>
#include <string>
#include "sputnik.hpp"


void printSplit(std::string title, std::string text, char delimeter) {
    std::vector<std::string_view> splits = Sputnik::splitString(text, delimeter);
    std::cout << "=== Split: " << title << " ===" << std::endl;
    std::cout << "Delimeter " << delimeter << std::endl;
    std::cout << "Text: " << std::endl << text << std::endl << "---" << std::endl;
    for (std::string_view split: splits) {
        std::cout << split << std::endl;
    }
    std::cout << "=== End of Split ===" << std::endl;
}

void testStringSplit() {
    printSplit("Semicolon", "a;b;c", ';');
    printSplit("End line", "a\nb\nc\n\r\n\r", '\n');
}

void testSputnikFileRead() {
    std::cout << "Test reading a file named \"KitchenSink.spk\"" << std::endl;

    Sputnik::File *sputnikFile = new Sputnik::File();
    Sputnik::ParseStatus fileStatus = sputnikFile->parseFile("samples/KitchenSink.spk");


    std::cout << fileStatus.success << std::endl;
}

int main() {
    testStringSplit();
    testSputnikFileRead();

    return 0;
}