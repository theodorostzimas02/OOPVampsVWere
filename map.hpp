#pragma once

#include <vector>
#include "npc.hpp"
#include "avatar.hpp"
#include "entity.hpp"


class Map{
    private:
        char **Grid;
    public: 
        std::vector<NPC*> objvecV;
        std::vector<NPC*> objvecW;

        // Αρχικοποίηση του Map με τα εμπόδια και το επιπλέον φίλτρο επούλωσης
        Map();
        
        // Ανανέωση της θέσης του Avatar στο Map
        void UpdateAvatar(int y, int x, Avatar* obj);

        // Αναδρομική συνάρτηση εύρεσης και αρχικοποίησης συντεταγμένων των NPC και του Avatar
        void SetCoordinates(Entity* Obj);

        // Αρχικοποίηση των NPC και τοποθέτητσή τους στο vector της αντίστοιχης ομάδας
        void SpawnEntities();

        //H scan επιστρεφει array char για τις θέσεις γύρω από μία θέση για κάθε αντικείμενο
        char* Scan(int y, int x);

        int Iterate(std::vector<NPC*> objvec, NPC* Target);

        // Επιστροφή των NPC από το κατάλληλο vector
        NPC* GetNPC(std::vector<NPC*> objvec,int &x,int &y,short int block);
        
        // Συνάρτηση που αποφασίζει την ενέργεια που θα εκτελέσει ένα NPC σε έναν γύρο, με βαση τις θέσεις γύρω του (ενδεχομένως αναδρομική)
        void Action(NPC* protagonist);

        // Εκτύπωση του Map
        void print();

        ~Map();
};