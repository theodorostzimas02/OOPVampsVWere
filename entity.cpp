#include "entity.hpp"

// Η Move() χειρίζεται την κίνηση ενος NPC ή του Avatar μεσα στον χάρτη και παίρνει ως όρισμα το index ενος array από την Scan() παρακάτω
void Entity::Move(short int MoveN){
    return;
}

void Entity::Heal(){
    return;
}

int Entity::getX(){
    return x;
}

int Entity::getY(){
    return y;
}

void Entity::SetYX(int y,int x){
    this->x=x;
    this->y=y;
}

char Entity::getID(){
    return ID;
}
