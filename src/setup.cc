#include "../headers/setup.h"
#include "../headers/library.h"

#include <fstream>
#include <iostream>
#include <sstream>
#include <algorithm>
#include <iomanip>
#include <cstdlib>

using namespace std;

vector<string> commands{"print", "swedish", "clear", "no_clear"};

pair<string, string> readfile(string const& fileName, string const& folder,
    bool write_in_swedish, vector<string> & phrases, 
    vector<string> & translations)
{
    string filePath{folder + '/' + fileName};

    if(fileName.size() <= 3)
    {
        filePath += ".txt";
    }
    else if(fileName.substr(fileName.size() - 4) != ".txt")
    {
        filePath += ".txt";
    }

    ifstream file{filePath};
    string line, message{"Skriv översättningen för ordet som skrivs ut"}, redo_message{"Träna på dom ord du hade fel på"};

    if(!file.is_open())
    {
        throw invalid_argument("Filen finns inte!");
    }

    while(getline(file, line))
    {
        auto pos = line.find(':');
        if(pos != string::npos)
        {
            string phrase, translation;

            if(!write_in_swedish)
            {
                phrase = line.substr(0, pos);
                translation = line.substr(pos + 1);
            }
            else
            {
                translation = line.substr(0, pos);
                phrase = line.substr(pos + 1);
            }

            trim_white_space(phrase, translation);

            phrases.push_back(phrase);
            translations.push_back(translation);
        }
        else
        {
            message = line;
            if(getline(file, line))
            {
                redo_message = line;
            }
        }
    }
    file.close();

    return make_pair(message, redo_message);
}

string match_any(string const& command)
{
    string temp_command = to_lower(command);

    for(string const& allowed_command : commands)
    {
        if(allowed_command == temp_command)
        {
            return allowed_command;
        }
    }
    return {};
}

pair<string, string> initialize(int argc, char* argv[], vector<string> & phrases, 
    vector<string> & translation, bool clear)
{
    pair<string, string> messages{};
    string input{}, command{}, folder{"."}, fileName{};
    bool printFile{false}, write_in_swedish{false};

    for(int i{1}; i < argc; i++)
    {
        command = match_any(string(argv[i]));

        if(command == "")
        {
            folder = string(argv[i]); 
        }
        else if(command == "no_clear")
        {
            clear = false;
        }
    }

    cout << "Välj fil och valfria kommandon\n\n";
    command = "ls " + folder;
    system(command.c_str());
    cout << "\n\n";

    getline(cin, input);
    istringstream inputStream{input};

    while(inputStream >> command)
    {
        string matched_command = match_any(command);

        if(matched_command == "")
        {
            fileName = command;
        }
        else if(matched_command == "swedish")
        {
            write_in_swedish = true;
        }
        else if(matched_command == "print")
        {
            printFile = true;
        }
    }

    clear_terminal(clear);
    messages = readfile(fileName, folder, write_in_swedish, phrases, translation);
    
    if(printFile)
    {
        printfile(fileName, phrases, translation);
    }

    return messages;
}

void printfile(string const& fileName, vector<string> const& phrases, 
    vector<string> const& translation)
{
    for(size_t i = 0; i < phrases.size(); i++)
    {
        cout << left << setw(20) << phrases.at(i)
             << right << translation.at(i) << "\n"
             << "￣￣￣￣￣￣￣￣￣￣￣￣￣￣￣￣￣\n";
    }
}