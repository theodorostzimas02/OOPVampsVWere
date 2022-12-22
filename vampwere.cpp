

#include "vampwere.hpp"
#include "npc.hpp"
#include "entity.hpp"

Vampire::Vampire() { ID = 'v';}

void Vampire::Move(short int MoveN){
    switch (MoveN)
    {
        case 0:    // Κινείται διαγώνια αριστερά και πάνω
            this->y--;
            this->x--;
            break;
        
        case 1:     // Κινείται πάνω
            this->y--;
            break;
            
        case 2:    // Κινείται διαγώνια δεξιά και πάνω
            this->y--;
            this->x++;
            break;   
        case 3:    // Κινείται αριστερά
            this->x--;
            break;
        case 4:    // Κινείται δεξιά
            this->x++;
            break;
        case 5:    // Κινείται διαγώνια αριστερά και κάτω
            this->y++;
            this->x--;
            break;
        case 6:    // Κινείται κάτω
            this->y++;
            break;   
        case 7:    // Κινείται διαγώνια δεξιά και κάτω
            this->y++;
            this->x++;
            break;
    }
}

Werewolf::Werewolf() { ID = 'w'; }

void Werewolf::Move(short int MoveN){
    switch (MoveN)
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
