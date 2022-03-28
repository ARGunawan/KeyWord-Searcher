#include <iostream>
#include <ostream>
#include <fstream>
#include <vector>
#include <string>
#include <unordered_map>
#include "KeywordsInFile.h"

//Our Constructor:
//Will read through both files one at a time and search for alphabet symbols. Any non alphabet symbols will be considered as a delimiter.
KeywordsInFile::KeywordsInFile(std::string filename_with_keywords,std::string filename_with_text)
{
    std::fstream Files; //variable to read and write files. (But in this case just to read)
    Files.open(filename_with_keywords); //Opens the text file for keywords
    if(Files.fail())    //Closes file if it fails to open
    {
        exit(1);
    }
    else    
    {
        std::string lines_; //create a string to measure the files 
        std::string temporary_string; //temp string
        while(getline(Files,lines_))    //while the file is being read
        {
            std::string different_temporary_string = ""; //set as our value for anything that is empty
            for(int i = 0;i < lines_.length()+1;i++) //Reads through the file and adds 1 to the length to prevent it from missing edge cases
            {
                 if((lines_[i] >= 'a' && lines_[i] <= 'z') || (lines_[i] >= 'A' && lines_[i] <= 'Z')) //Checks if something is alphanumeric
                {
                    temporary_string += lines_[i];  //the temp string is added by the string charcaters
                }
                else if(temporary_string.length() != 0) //If it is not empty
                {
                    keyword_map.insert({temporary_string,0}); //insert it into the map
                    temporary_string = ""; //set temp back to empty 
                }
            }
        }   
    }
    Files.close(); //closes the file

    Files.open(filename_with_text); //Opens the file with text
    if(Files.fail()) //another fail condition 
    {
        exit(1);
    }
    else
    {
        //Declaring these variables outside of the else will lead to redeclaration
        std::string lines_; //same variables shoudl be declared within the else to prevent confusion 
        std::string temporary_string; 
        vector_data.push_back({}); //We create a variable to push our vector back into the map
        while(getline(Files, lines_))
        {
           for(int i = 0;i < lines_.length()+1; i++) //Use the same for loop as the above
           {
               if((lines_[i] >= 'a' && lines_[i] <= 'z') || (lines_[i] >= 'A' && lines_[i] <= 'Z')) //Will again check for any alpha
               {
                   temporary_string += lines_[i]; 
               }
               //otherwise if is it not in the map or the string is not empty
               else if(keyword_map.count(temporary_string) > 0 && temporary_string != "") 
               {
                   if(keyword_line.count(temporary_string) > 0) //if it is larger than zero
                   {
                       keyword_line.at(temporary_string)++; //use at function to locate and increment 
                       keyword_map.at(temporary_string)++; //use at function locate and  increment 
                       temporary_string = ""; //set temp back to empty 
                   }
                   else
                   {
                       keyword_line.insert({temporary_string,1}); //inserts our value into the map
                       keyword_map.at(temporary_string)++; //then use at to locate and increment
                       temporary_string = ""; //set temp back to empty 
                   }
               }
                else
                 {
                     temporary_string = ""; //otherwise it is just empty
                 }
           }
           vector_data.push_back(keyword_line); //push our vector into our map
           keyword_line.clear(); //clear 
        }
    }
    Files.close(); //again close this second file being read
}

//KeywordFound function:
//Will check if the keyword specified in the conditions are found within the files. 
bool KeywordsInFile::KeywordFound(std::string keyword) 
{
    if(keyword_map.count(keyword) > 0 ) //If keyword is found within the map
    {
        if(keyword_map.at(keyword) > 0) //if it is in the map
        {
            return true; //return true
        }
        else
        {
            return false; //otherwise return false
        }
    }
    else
    {
        return false; //return false if it is not there at all
    }
}

//KeywordinLine Function:
//Will designate the number of occurrences found in the file on a specified keyword. This is essentially our frequency as it checks
//for each word appearing more than once on a specific line.
int KeywordsInFile::KeywordInLine(std::string keyword,int line_number)
{
    if(line_number > 0 && line_number <= vector_data.size()) //If the word exists and it is not out of range from the vector
    {
        if(vector_data[line_number].count(keyword) > 0) //if it shows up more than once
        {
            return vector_data[line_number].at(keyword); //return the line number to show the frequency 
        }
        else
        {
            return false; //otherwise returns nothing if it is not found again 
        }
    }
    else
    {
        return false; //returns nothing if is not found in the text again
    }
}

//TotalOccurrences Function
//Gives the total amount of times the keyword was found in the text. While keywordinline showed the frequency next to the word itself, 
//this will show the complete total times it has appeared
int KeywordsInFile::TotalOccurrences(std::string keyword)
{
    return keyword_map[keyword]; //returns the total amount of times it has appeared in the text within our map
}


//Overload Operator
//Our friend function that behaves a nonmember. This function needs to be referenced to prevent referencing and return issues. This function
//uses ostream to give the output of the object within our map and uses it to print each keyword out.
std::ostream &operator<<(std::ostream &result, KeywordsInFile &object)
{
    for(const auto x :object.keyword_map) //while this object is in our map
    {
        result <<  x.first << ":" << x.second << std::endl; //Print the result and object using the map traversal
    }
    return result; //return the result to prevent referencing errors
}
