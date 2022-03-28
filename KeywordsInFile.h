#include <string>
#include <ostream>
#include <fstream>
#include <iostream>
#include <vector>
#include <unordered_map>
#pragma once

class KeywordsInFile
{
    public:
    KeywordsInFile(std::string filename_with_keywords,std::string filename_with_text); //Our constructor. This prevents the creation of a default
    KeywordsInFile() = delete; //This will further prevent the intialization of a default.
    //Although the above parameters already do this, this just further prevents it from ever being recognized anyway
    bool KeywordFound(std::string keyword); //The function to search to for a keyword
    int KeywordInLine(std::string keyword, int line_number); //will return a the frequency of a word based on line number
    int TotalOccurrences(std::string keyword); //returns the total occurrence of the keywords
    friend std::ostream &operator<<(std::ostream &result, KeywordsInFile &object); //our nonmember function to print our keywords from our map

    private:
    std::unordered_map <std::string, int> keyword_map; //Our main map
    std::unordered_map <std::string,int> keyword_line; //the map to store the second file
    std::vector <std::unordered_map<std::string,int>> vector_data; //This will be our vector 
};