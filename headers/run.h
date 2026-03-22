#pragma once

#include <string>
#include <vector>

void compare(std::string & userInput, int randomIndex,
    std::vector<std::string> & phrases, std::vector<std::string> & translations);

void check_empty(std::vector<std::string> & phrases, std::vector<std::string> & translation,
    std::string redo_message);

long int random(int max);

int run(std::vector<std::string> & phrases, std::vector<std::string> & translation,
    bool clear, std::string const& redo_message);