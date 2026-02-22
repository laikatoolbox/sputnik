#include <iostream>
#include <string>
#include <assert.h>

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

void testSanitize() {
    // test sanitizing
    std::string text = ":, =, ;, \r, \n, @, >, <, $";
    Sputnik::sanitize(text);
    assert(text == "$cl, $eq, $sc, $r, $n, $at, $gt, $lt, $dl");
    
    // test desanitizing
    Sputnik::desanitize(text);
    assert(text == ":, =, ;, \r, \n, @, >, <, $");
    
    std::cout << "Sanitize/Desanitize test passed" << std::endl;
} 

void testStringSplit() {
    printSplit("Semicolon", "a;b;c", ';');
    printSplit("End line", "a\nb\nc\n\r\n\r", '\n');
    
    std::cout << "String split test passed" << std::endl;
}

void testKitchenSink() {
    std::cout << "Test reading a file named \"KitchenSink.spk\"" << std::endl;

    Sputnik::File *spkFile = new Sputnik::File();
    Sputnik::ParseStatus spkStatus = spkFile->parseFile("../samples/KitchenSink.spk");

    // sanity test: uncomment this and it should fail
    //assert(false);

    // File parsed successfully
    assert(spkStatus.success);

    // We should only have 2 sectors:
    // the default "root" sector and a sector called "root 2"
    assert(spkFile->sectors.size() == 2);
    assert(spkFile->sectors.contains("root"));
    assert(spkFile->sectors.contains("sector 2"));

    // Test getting a value from a defined sector and section
    std::string sector2FavoriteColor = spkFile->value("color", "favorites", "sector 2");
    assert(sector2FavoriteColor == "blue");

    // Test getting a value the default sector root
    // The intial value is green, but a later value sets it to red, overwriting it
    std::string rootFavoriteColor = spkFile->value("color", "favorites");
    assert(rootFavoriteColor == "red");

    // Test that the section key=values are merging correctly
    // Both animal and food should be populated 
    std::string rootFavoriteAnimal = spkFile->value("animal", "favorites");
    std::string rootFavoriteFood = spkFile->value("food", "favorites");
    assert(rootFavoriteAnimal == "cat");
    assert(rootFavoriteFood == "pizza");
    
    // Test that section and sector names are desanitized correctly
    std::string valueWithEscapedCharactersNewLine = spkFile->value("\n", ":>;@");
    std::string valueWithEscapedCharactersDollar = spkFile->value("$@", ":>;@");    
    assert(valueWithEscapedCharactersNewLine == ";");
    assert(valueWithEscapedCharactersDollar == "\r\n@\r\n");

    // Test objects
    auto circles = spkFile->objectsNamed("circle");
    // We should have two circles
    assert(circles.size() == 2);
    // test values for the first circle
    auto circle1 = circles[0];
    assert(circle1["x"] == "0");
    assert(circle1["y"] == "10");
    assert(circle1["width"] == "100");
    assert(circle1["height"] == "100");
    assert(circle1["fill"] == "black");
    // test values for the second circle
    auto circle2 = circles[1];
    assert(circle2["x"] == "90");
    assert(circle2["y"] == "90");
    assert(circle2["width"] == "9000");
    assert(circle2["height"] == "650");

    std::cout << "Kitchen sink test passed" << std::endl;
}

int main() {
    testStringSplit();
    testSanitize();
    testKitchenSink();

    return 0;
}