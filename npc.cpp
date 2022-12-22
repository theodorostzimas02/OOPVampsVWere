#include <cstdlib>
#include "entity.hpp"
#include "npc.hpp"

        NPC::NPC(){
            Potions = rand() % 3;
            Power_Lvl = (rand() % 3) + 1;
            Defence_Lvl = (rand() % 2) + 1;
        }

        short int NPC::getPower_Lvl(){
            return Power_Lvl;
        }

        short int NPC::getCurrentHP(){
            return CurrentHP;
        }
        
        short int NPC::getPotions(){
            return Potions;
        }

        short int NPC::getCapHP() {
            return CapHP;
        }
        
        void NPC::MAXCurrentHP() {
            CurrentHP=CapHP;   
        }

        void NPC::Heal(NPC* target)
        {
            target->CurrentHP++;
            Potions--;
        }

        void NPC::Attack(NPC* target)
        {
            target->CurrentHP=target->CurrentHP-(this->Power_Lvl - target->Defence_Lvl);
            if (target->Defence_Lvl > 0) target->Defence_Lvl--;
        }
