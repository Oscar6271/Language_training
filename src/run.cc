#include "../headers/run.h"
#include "../headers/library.h"

#include <cstdlib>
#include <limits>
#include <random>
#include <iostream>

using namespace std;

vector<string> wrong_answers{}, wrong_translations{};

bool firstRound{true}, cleared{false};
int wrongCount{};

void compare(string & userInput, int randomIndex, 
    vector<string> & phrases, vector<string> & translations)
{    
    string correctAnswer = translations.at(randomIndex);

    clean_string(userInput);

    to_lower(userInput);
    to_lower(correctAnswer);

    if(userInput != correctAnswer)
    {
        cout << "Fel svar!\n" 
             << phrases.at(randomIndex) << " = " 
             << translations.at(randomIndex) << "\n\n"; 

        wrong_answers.push_back(phrases.at(randomIndex));
        wrong_translations.push_back(translations.at(randomIndex));
    }
    else
    {
        cout << "Rätt!\n\n";
    }
}

void check_empty(vector<string> & phrases, vector<string> & translation, 
    string redo_message)
{
    if(phrases.empty())
    {
        if(firstRound)
        {
            wrongCount += wrong_answers.size();
            firstRound = false;
        }

        phrases = std::move(wrong_answers);
        translation = std::move(wrong_translations);

        if(!phrases.empty())
        {            
            if(!cleared)
            {
                cout << "\033[2J\033[H";
                cleared = true;
            }

            cout << "_______________________________\n" << redo_message << "\n\n";
        }
    }
}

long int random(int max)
{
    random_device r;
    default_random_engine e1(r());
    uniform_int_distribution<int> uniform_dist(0, max);
    
    return uniform_dist(e1);
}

int run(vector<string> & phrases, vector<string> & translation, 
    bool clear, string const& redo_message)
{
    string userInput;

    while(!phrases.empty())
    {
        long int randomIndex{random(phrases.size() - 1)};
        cout << phrases.at(randomIndex) << ": ";

        getline(cin, userInput);

        compare(userInput, randomIndex, phrases, translation);

        phrases.erase(phrases.begin() + randomIndex);
        translation.erase(translation.begin() + randomIndex);        

        check_empty(phrases, translation, redo_message);
    }

    return wrongCount;
}