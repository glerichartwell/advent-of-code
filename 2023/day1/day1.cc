/**
 * @file day1.cc
 * @author Eric Hartwell
 * @date 2023
 * 
 * This file contains the solutions for Day 1
 * 
*/

#include <iostream>
#include <fstream>
#include <string>
#include <cctype>
#include <map>

using namespace std;

/**
 * @returns the sum required to get the first gold star for day one as described at https://adventofcode.com/2023/day/1
*/
int partOne() {
    
    ifstream inputFile;
    inputFile.open("input.txt");
    
    int sum = 0;
    string line;
    while (getline(inputFile, line)) {
        int tens = -1;
        int ones = 10;
        for (int i = 0, j = line.length() - 1; i < line.length(); i++, j--) {
            if (isdigit(line[i]) && tens == -1) {
                tens = (line[i] - '0') * 10;
            }
            if (isdigit(line[j]) && ones == 10) {
                ones = line[j] - '0';
            }
        }
        sum += tens + ones;
    }

    inputFile.close();
    return sum;
}

int partTwo() {
    map<string, int> wordNumbers {
        {"one", 1}, 
        {"two", 2}, 
        {"three", 3}, 
        {"four", 4}, 
        {"five", 5}, 
        {"six", 6}, 
        {"seven", 7}, 
        {"eight", 8}, 
        {"nine", 9}
    };

    ifstream inputFile;
    inputFile.open("input.txt");
    
    int sum = 0;
    string line;
    while (getline(inputFile, line)) {
        int tens = -1;
        int ones = 10;
        int indexI = 0;
        int indexJ = line.length() - 1;
        for (int i = 0, j = line.length() - 1; i < line.length(); i++, j--) {
            if (isdigit(line[i]) && tens == -1) {
                tens = (line[i] - '0') * 10;
                indexI = i;
            }
            if (isdigit(line[j]) && ones == 10) {
                ones = line[j] - '0';
                indexJ = j;
            }
        }
        for (auto word: wordNumbers) {
            size_t foundBefore = line.find(word.first);
            size_t foundAfter = line.rfind(word.first);
            if (foundBefore != string::npos && foundBefore < indexI) {
                indexI = foundBefore;
                tens = wordNumbers[word.first] * 10;
            } 
            if (foundAfter != string::npos && foundAfter > indexJ) {
                indexJ = foundAfter;
                ones = wordNumbers[word.first];
            }

        }
        sum += tens + ones;
    }
    inputFile.close();
    return sum;
}

int main() {
    int partOneSum = partOne();
    cout << "Day 1 Part 1: " << partOneSum << "\n\n";
    int partTwoSum = partTwo();
    cout << "Day 1 Part 2: " << partTwoSum << '\n';
    return 0;
}