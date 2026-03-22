#include "../headers/setup.h"
#include "../headers/run.h"
#include "../headers/library.h"

#include <iostream>

using namespace std;

// skriver ut hexadecimala ASCII koden för varje tecken
void debug_string(string const& s) 
{
    cout << "[";
    for (unsigned char c : s) 
    {
        cout << hex << (int)c << " ";
    }
    cout << "]\n";
}

int main(int argc, char* argv[])
{
    vector<string> phrases{}, translation{};
    string instruction{}, redo_message{};
    pair<string, string> messages{};
    
    bool clear{true};   

    try
    {
        messages = initialize(argc, argv, phrases, translation, clear);
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
        return EXIT_FAILURE;
    }

    instruction = messages.first;
    redo_message = messages.second;

    int wordCount = phrases.size();
    
    cout << instruction << "\n\n";

    int wrongCount = run(phrases, translation, clear, redo_message);

    clear_terminal(clear);

    cout << "Klar!\nTotalt hade du " << wrongCount << " fel av " << wordCount << " ord\n";
    
    return 0;
}