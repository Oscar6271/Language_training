#pragma once

#include <string>

std::string to_lower(std::string const& word);

void clean_string(std::string & s);

void trim_white_space(std::string & phrase, std::string & translation);

void clear_terminal(bool clear);