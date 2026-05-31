#include "../headers/setup.h"
#include "../headers/library.h"

#include <fstream>
#include <iostream>
#include <sstream>
#include <algorithm>
#include <iomanip>
#include <cstdlib>

using namespace std;

vector<string> commands{"print", "swedish", "clear", "no_clear", "-f", "-file", "file"};

vector<char> seperators{':', ','};

void split_string(vector<string> & phrases, vector<string> & translations, 
    auto pos, bool const write_in_swedish, string const& line)
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

    trim_white_space(phrase);
    trim_white_space(translation);

    phrases.push_back(phrase);
    translations.push_back(translation);
}

string make_filePath(string const& folder, string const& fileName)
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

    return filePath;
}

pair<string, string> readfile(string const& fileName, string const& folder,
    bool write_in_swedish, vector<string> & phrases, 
    vector<string> & translations)
{
    ifstream file{make_filePath(folder, fileName)};
 
    string line, message{"Skriv översättningen för ordet som skrivs ut"}, redo_message{"Träna på dom ord du hade fel på"};

    if(!file.is_open())
    {
        throw invalid_argument("Filen finns inte!");
    }

    int current_seperator = 0;
    while(getline(file, line))
    {
split_string:
        auto pos = line.find(seperators.at(current_seperator));
        
        if(pos != string::npos)
        {
            split_string(phrases, translations, pos, write_in_swedish, line);
        }
        else if(end_of_file(pos, current_seperator, seperators.size()))
        {
            message = line;
            if(getline(file, line))
            {
                redo_message = line;
            }
        }
        else
        {
            current_seperator++;
            goto split_string;
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
    string command{}, folder{}, fileName{};
    bool printFile{false}, write_in_swedish{false}, fileChoosen{false};

    // kommandon medans man kör ./a.out
    for(int i{1}; i < argc; i++)
    {
        command = match_any(string(argv[i]));

        if(command == "" && !fileChoosen)
        {
            folder = string(argv[i]); 
        }
        else if(command == "no_clear")
        {
            clear = false;
        }
        else if(command == "print")
        {
            printFile = true;
        }
        else if(command == "swedish")
        {
            write_in_swedish = true;
        }
        else if(command == "-f" || command == "-file" || command == "file")
        {
            string path{string(argv[i + 1])};

            auto pos = path.find('/');

            if(pos != string::npos)
            {
                folder = path.substr(0, pos);
                fileName = path.substr(pos + 1);
            }

            fileChoosen = true;
        }
    }

    if(!fileChoosen)
    {
        checkCommands(fileName, write_in_swedish, printFile, folder);
    }

    clear_terminal(clear);
    messages = readfile(fileName, folder, write_in_swedish, phrases, translation);
    
    if(printFile)
    {
        printfile(phrases, translation);
    }

    return messages;
}

void printfile(vector<string> const& phrases, vector<string> const& translation)
{
    for(size_t i = 0; i < phrases.size(); i++)
    {
        cout << left << setw(20) << phrases.at(i)
             << right << translation.at(i) << "\n"
             << "￣￣￣￣￣￣￣￣￣￣￣￣￣￣￣￣￣\n";
    }
}

void checkCommands(string & fileName, bool & write_in_swedish, bool & printFile, string const& folder)
{
    string input{};

    cout << "Välj fil och valfria kommandon\n\n";
    string command = "ls " + folder;
    system(command.c_str());
    cout << "\n\n";

    getline(cin, input);
    istringstream inputStream{input};

    // commandon när programmet har startat
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
}