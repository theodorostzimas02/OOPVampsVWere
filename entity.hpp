#pragma once

class Entity{

    protected:
        int x, y;
        short int Potions;
        char ID;

    public:
        // Η Move() χειρίζεται την κίνηση ενος NPC ή του Avatar μεσα στον χάρτη και παίρνει ως όρισμα το index ενος array από την Scan() παρακάτω
        virtual void Move(short int MoveN);

        virtual void Heal();

        int getX();
        
        int getY();

        void SetYX(int y,int x);

        char getID();
};