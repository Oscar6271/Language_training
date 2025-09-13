#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <cstdlib>

using namespace std;

string to_lower(string & word)
{
    transform(word.begin(), word.end(), word.begin(),
             [](unsigned char c)
             {
                return tolower(c);
             });
    return word;
}

void readfile(string const& fileName, string const& language_to_write_in,
                            vector<string> & phrases, vector<string> & translations)
{
    ifstream file{fileName};
    string phrase{};

    while(getline(file, phrase, ':'))
    {
        string translation{};
        file >> translation;

        if(!phrase.empty())
        {
            phrases.push_back(phrase.substr(0, phrase.size() - 1));
            translations.push_back(translation);
        }
    }

}

int main(int argc, char* argv[])
{
    vector<string> phrases, translation;

    if(argc >= 3)
    {
        readfile(argv[1], argv[2], phrases, translation);
    }
    else 
    {
        readfile(argv[1], "not_swedish", phrases, translation);
    }

    cout << "Skriv översättningen för ordet som skrivs ut\n";

    while(true)
    {
        int randomIndex{rand() % (int) phrases.size()};
        cout << phrases.at(randomIndex) << ": ";

        string userInput{};
        cin >> userInput;

        if(userInput != translation.at(randomIndex))
        {
            cout << "Fel svar!" << phrases.at(randomIndex) 
                 << " = " << translation.at(randomIndex) << '\n'; 
        }
        else
        {
            cout << "Rätt!"
        }
    }
    
    return 0;
}