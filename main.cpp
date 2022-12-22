#include <iostream>
#include <cstdlib>
#include <time.h>
#include <vector>
#include <windows.h>
#include "game.hpp"

using namespace std;
int n,m;



int main() {
    // Προετοιμασίαα του παιχνιδιού
    srand((unsigned int)time(NULL));
    char Sup;
    cout << "Enter Grid Size n: " << endl;
    cin >> n;
    cout << "Enter Grid Size m: " << endl;
    cin >> m;
    cout << "Enter either W to support team Werewolves or V to support team Vampires: " << endl;
    cin >> Sup;
    bool inputValid = false;
    while (!inputValid) {
        try {
            if (Sup != 'W' && Sup != 'V') {
                throw invalid_argument("Please enter a proper character");
            }
            inputValid = true;
        }
        catch (const invalid_argument& e) {
            cout << e.what() << endl;
            cin >> Sup;
        }
    }
    system("cls"); 
    
    Game newGame(Sup);
    
    newGame.MainLoop();
    
    return 0;
}