#include <iostream>
#include <windows.h>
#include <vector>
#include "avatar.hpp"
#include "entity.hpp"
#include "npc.hpp"

using namespace std;

        Avatar::Avatar(char Team_Sup){
            ID = Team_Sup;
            Potions=1;
        }
    
        short int Avatar::getPotion(){
            return Potions;
        }

        void Avatar::IncrPotions(){
            Potions++;
        }

        void Avatar::Move(short int MoveNum) {
            switch (MoveNum)
            {
            case 1:         // Κινείται πάνω
                this->y--;
                break;
            case 3:         // Κινείται αριστερά
                this->x--;
                break;
            case 4:          // Κινείται δεξιά
                this->x++;
                break;
            case 6:         // Κινείται κάτω
                this->y++;
                break;
            }
        }
        
        void Avatar::Heal(vector<NPC*> NPCvec)
        {
            if (Potions == 0) {
                cout << "You don't have enough potions for this action." << endl;
                Sleep(1000);
                system("cls"); 
            }
            else {
                for (int i=0; i<NPCvec.size(); i++){
                    NPCvec.at(i)->MAXCurrentHP();
                }
                Potions--;
                cout << "You healed your team." << endl;
                Sleep(1000);
                system("cls");
            }    
        }
        
