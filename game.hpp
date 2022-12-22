#pragma once
#include "map.hpp"
#include "avatar.hpp"

class Game{
    private:
        Map newMap;
        Avatar Player;
        bool DaylightCycle=0;

    public:
        // Αρχικοποίηση του παιχνιδιού
        Game(char Supp); 
        
        // Εκτελεί μία ενέργεια για κάθε NPC - Σηματοδοτεί το πέρας ενος γύρου
        void Update();
        
        // Παύση του παιχνιδιού
        void PauseGame();

        // Έξοδος από το παιχνίδι
        void ExitGame();
        
        // Συνάρτηση που ελέγχει την είσοδο του πληκτρολογίου για τον χειρισμο του παιχνιδιού και του Avatar
        void Input();

        // Αλλαγή από μέρα σε νύχτα και αντίστροφα
        void ChangeDayTime();

        void MainLoop();
};