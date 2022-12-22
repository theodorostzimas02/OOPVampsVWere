#pragma once
#include "entity.hpp"

class NPC : public Entity {

    protected:
        short int CapHP = 10;
        short int CurrentHP = CapHP;
        short int Power_Lvl;
        short int Defence_Lvl;

    public:
        NPC();

        short int getPower_Lvl();

        short int getCurrentHP();
        
        short int getPotions();
        
        short int getCapHP();
        
        void MAXCurrentHP();

        void Heal(NPC* target);

        void Attack(NPC* target);

};