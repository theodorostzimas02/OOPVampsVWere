#pragma once
#include <vector>
#include "entity.hpp"
#include "npc.hpp"


class Avatar : public Entity {
    
    public:
        Avatar(char Team_Sup);
    
        short int getPotion();

        void IncrPotions();

        void Move(short int MoveNum);
        
        void Heal(std::vector<NPC*> NPCvec);
        
};