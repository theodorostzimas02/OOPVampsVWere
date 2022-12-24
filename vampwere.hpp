#pragma once
#include "npc.hpp"
#include "entity.hpp"

class Vampire : public NPC {
    public:
        Vampire();

        void Move(short int MoveN);
};

class Werewolf : public NPC {
    public:
        Werewolf();

        void Move(short int MoveN);
};