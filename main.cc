#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <cstdlib>
#include <limits>

using namespace std;

vector<string> wrong_answers{}, wrong_translations{};

string to_lower(string & word)
{
    transform(word.begin(), word.end(), word.begin(),
             [](unsigned char c)
             {
                return tolower(c);
             });
    return word;
}

void trim_white_space(string & phrase, string & translation)
{
    phrase.erase(0, phrase.find_first_not_of(" \t"));
    phrase.erase(phrase.find_last_not_of(" \t") + 1);
    translation.erase(0, translation.find_first_not_of(" \t"));
    translation.erase(translation.find_last_not_of(" \t") + 1);
}

void readfile(string const& fileName, string const& language_to_write_in,
                            vector<string> & phrases, vector<string> & translations)
{
    ifstream file{fileName};
    string line;

    while(getline(file, line))
    {
        auto pos = line.find(':');
        if(pos != string::npos)
        {
            string phrase, translation;

            if(language_to_write_in != "spanish")
            {
                translation = line.substr(0, pos);
                phrase = line.substr(pos + 1);
            }
            else
            {
                phrase = line.substr(0, pos);
                translation = line.substr(pos + 1);
            }

            trim_white_space(phrase, translation);

            phrases.push_back(phrase);
            translations.push_back(translation);
        }
    }
}

void compare(string userInput, int randomIndex, 
             vector<string> & phrases, vector<string> & translations)
{
    if(userInput != translations.at(randomIndex))
    {
        cout << "Fel svar!\n" << phrases.at(randomIndex) 
                << " = " << translations.at(randomIndex) << "\n\n"; 

        wrong_answers.push_back(phrases.at(randomIndex)),
        wrong_translations.push_back(translations.at(randomIndex));
    }
    else
    {
        cout << "Rätt!\n\n";
    }
}

int main(int argc, char* argv[])
{
    vector<string> phrases, translation;
    string userInput{};

    if(argc >= 3)
    {
        readfile(argv[1], argv[2], phrases, translation);
    }
    else 
    {
        readfile(argv[1], "spanish", phrases, translation);
    }

    cout << "Skriv översättningen för ordet som skrivs ut\n\n";

    while(!phrases.empty())
    {
        int randomIndex{rand() % (int) phrases.size()};
        cout << phrases.at(randomIndex) << ": ";

        cin >> userInput;

        compare(userInput, randomIndex, phrases, translation);

        phrases.erase(phrases.begin() + randomIndex);
        translation.erase(translation.begin() + randomIndex);

        if(phrases.empty())
        {
            phrases = std::move(wrong_answers);
            translation = std::move(wrong_translations);

            if(!phrases.empty())
            {
                cout << "Träna på dom ord du hade fel på\n";
            }
        }
    }

    cout << "Klar!\n";
    
    return 0;
}