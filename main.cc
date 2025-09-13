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
            string phrase = line.substr(0, pos);
            string translation = line.substr(pos + 1);

            // ta bort whitespace runt orden
            phrase.erase(0, phrase.find_first_not_of(" \t"));
            phrase.erase(phrase.find_last_not_of(" \t") + 1);
            translation.erase(0, translation.find_first_not_of(" \t"));
            translation.erase(translation.find_last_not_of(" \t") + 1);

            phrases.push_back(phrase);
            translations.push_back(translation);
        }
    }
}

bool compare(string userInput, int randomIndex, 
             vector<string> & phrases, vector<string> & translations,
             bool push_back = true)
{
    bool correct{};
    if(userInput != translations.at(randomIndex))
    {
        cout << "Fel svar!\n" << phrases.at(randomIndex) 
                << " = " << translations.at(randomIndex) << "\n\n"; 

        if(push_back)
        {
            wrong_answers.push_back(phrases.at(randomIndex)),
            wrong_translations.push_back(translations.at(randomIndex));
        }
        correct = false;
    }
    else
    {
        cout << "Rätt!\n\n";
        correct = true;
    }

    return correct;
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
        readfile(argv[1], "not_swedish", phrases, translation);
    }

    cout << "Skriv översättningen för ordet som skrivs ut\n\n";

    while(true)
    {
        int randomIndex{rand() % (int) phrases.size()};
        cout << phrases.at(randomIndex) << ": ";

        cin >> userInput;

        compare(userInput, randomIndex, phrases, translation);

        phrases.erase(phrases.begin() + randomIndex);
        translation.erase(translation.begin() + randomIndex);

        if(phrases.empty())
        {
            break;
        }
    }

    cout << "Träna på dom ord du hade fel på\n";

    while(!wrong_answers.empty())
    {
        int randomIndex{rand() % (int) wrong_answers.size()};
        cout << wrong_answers.at(randomIndex) << ": ";

        cin >> userInput;

        bool correct = compare(userInput, randomIndex, wrong_answers, wrong_translations, false);

        if(correct)
        {
            wrong_answers.erase(wrong_answers.begin() + randomIndex);
            wrong_translations.erase(wrong_translations.begin() + randomIndex);
        }
    }

    cout << "Klar!\n";
    
    return 0;
}