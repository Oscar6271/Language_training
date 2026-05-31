#include "../headers/library.h"

#include <algorithm>
#include <cwctype>

using namespace std;

string to_lower(string const& word)
{
    string temp_word{word};
    
    transform(word.begin(), word.end(), temp_word.begin(),
             [](unsigned char c)
             {
                return tolower(c);
             });
    return temp_word;
}

void clean_string(string & s)
{
    while (!s.empty() && (s.back() == L'\r' || s.back() == L'\n')) {
        s.pop_back();
    }

    std::replace_if(s.begin(), s.end(), [](wchar_t c) {
        return std::iswspace(c) && c != L' ';
    }, L' ');
}

void trim_white_space(string & phrase)
{
    phrase.erase(0, phrase.find_first_not_of(" \t"));
    phrase.erase(phrase.find_last_not_of(" \t") + 1);

    clean_string(phrase);
}

void clear_terminal(bool clear)
{
    if(clear)
    {
        system("clear");
    }
}

bool end_of_file(size_t pos, int seperator, size_t max_seperator)
{
    return pos == string::npos && seperator == max_seperator;
}

void ignore_explanation(string & word)
{
    auto start = word.find('(');

    if(start != string::npos)
    {
        word = word.substr(0, start);
        trim_white_space(word);
    }

}