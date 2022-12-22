#include <iostream>
#include <windows.h>
#include <vector>
#include "entity.hpp"
#include "avatar.hpp"
#include "map.hpp"
#include "game.hpp"

using namespace std;

Game::Game(char Supp) : Player(Supp)
{
    newMap.SetCoordinates(&Player);
    newMap.SpawnEntities();
}     

void Game::Update(){
            for (int i=0;i<newMap.objvecW.size();i++){
                newMap.Action(newMap.objvecW.at(i));
            }
            for (int i=0;i<newMap.objvecV.size();i++){
                newMap.Action(newMap.objvecV.at(i));
            }
            
        };

void Game::PauseGame(){
            cout << "Active Werewolves: " << newMap.objvecW.size() << endl;
            cout << "Active Vampires: " << newMap.objvecV.size() << endl;
            cout << "Potions: " << Player.getPotion() << endl;
            system("pause");
        }        

void Game::ExitGame(){
            cout << "Thanks for Playing. Goodbye" << endl;
            Sleep(2000);
            exit(0);
        }        

void Game::Input()
        {
            // Όταν πατηθεί το πλήκτρο P, τότε καλείται η συνάρτηση PauseGame για παύση του παιχνιδιού
            if (GetAsyncKeyState(0x50)){ 
                //k=1;
                PauseGame();
                system("cls"); 
            }

            // Όταν πατηθεί το πλήκτρο E, τότε καλείται η συνάρτηση ExitGame για έξοδο από το παιχνίδι
            if (GetAsyncKeyState(0x45))
            {
                ExitGame();
            }

            // Όταν πατηθεί το πλήκτρο H, τότε γίνεται επούλωση όλων των μελών της ομάδας που υποστηρίζει ο παίκτης   
            if (GetAsyncKeyState(0x48)){
                if ((DaylightCycle == 0) && (Player.getID()=='V')){
                    Player.Heal(newMap.objvecV);
                    return;
                }  

                else if ((DaylightCycle == 1) && (Player.getID()=='W')){
                    Player.Heal(newMap.objvecW);
                    return;
                }
                
                else {
                    cout << "You can not heal your team right now" << endl;
                    Sleep(1000);
                    system("cls"); 
                    return;
                }
            }
            
            // Κίνηση Avatar
            char* array = new char[8];
            array = newMap.Scan(Player.getY(),Player.getX());

            if (GetAsyncKeyState(VK_UP)){   // Πάνω βελος
                if (array[1] == '-' || array[1] == 'P') {
                    if (array[1] == 'P') Player.IncrPotions();
                    int PrevY=Player.getY();
                    int PrevX=Player.getX();
                    Player.Move(1);
                    newMap.UpdateAvatar(PrevY,PrevX,&Player);
                    delete[] array;
                    return;
                }
            }

            if (GetAsyncKeyState(VK_DOWN)){ // Κάτω βελος
                if (array[6] == '-' || array[6] == 'P') {
                    if (array[6] == 'P') Player.IncrPotions();
                    int PrevY=Player.getY();
                    int PrevX=Player.getX();
                    Player.Move(6);
                    newMap.UpdateAvatar(PrevY,PrevX,&Player);
                    delete[] array;
                    return;
                }
            }

            if (GetAsyncKeyState(VK_LEFT)){ // Αριστερό βελος
                if (array[3] == '-' || array[3] == 'P') {
                    if (array[3] == 'P') Player.IncrPotions();
                    int PrevY=Player.getY();
                    int PrevX=Player.getX();
                    Player.Move(3);
                    newMap.UpdateAvatar(PrevY,PrevX,&Player);
                    delete[] array;
                    return;
                }
            }

            if (GetAsyncKeyState(VK_RIGHT)){    // Δεξι βελος
                if (array[4] == '-' || array[4] == 'P') {
                    if (array[4] == 'P') Player.IncrPotions();
                    int PrevY=Player.getY();
                    int PrevX=Player.getX();
                    Player.Move(4);
                    newMap.UpdateAvatar(PrevY,PrevX,&Player);
                    delete[] array;
                    return;
                }
            }

            else
            {
                delete[] array;
            }
        }
void Game::ChangeDayTime()
        {
            if (DaylightCycle == 0) DaylightCycle = 1; // Όταν DaylightCycle = 1, τότε είναι νυχτα
            else DaylightCycle = 0;                    // Όταν DaylightCycle = 1, τότε είναι μερα
        }        
void Game::MainLoop(){
            for(int l = 0; 1 ; l++)
            {
                // Διαχείριση της εναλλαγής της μέρας σε νυχτα
                if (l == 10)
                {
                    ChangeDayTime();
                    l = 0;
                }
 
                newMap.print();
                cout << endl;
                DaylightCycle? cout << "Night" << endl : cout << "Day" << endl ;
                Sleep(1000);
                system("cls"); 
                Input();
                Update();

                // Συνθήκη ολοκλήρωσης του παιχνιδιού
                if (newMap.objvecV.size() == 0 || newMap.objvecW.size() == 0){
                    cout << "Game Over" << endl;

                    if (newMap.objvecV.size() == 0) cout << "Werewolves Won" << endl;
                    else cout << "Vampires Won" << endl;

                    Sleep(2000);
                    ExitGame();
                }
            }
        }        
