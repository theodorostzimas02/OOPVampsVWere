#include <iostream>
#include <cstdlib>
#include <vector>
#include "entity.hpp"
#include "npc.hpp"
#include "vampwere.hpp"
#include "avatar.hpp"
#include "map.hpp"

extern int n,m;

using namespace std;


// Αρχικοποίηση του Map με τα εμπόδια και το επιπλέον φίλτρο επούλωσης
Map::Map(){
    this->Grid = new char*[n];
    for (int i=0;i<n;i++)
        this->Grid[i] = new char[m];

    for (int i=0;i<n;i++){
        for(int j=0;j<m;j++){
            this->Grid[i][j] = '-';
        } 
    }

    int limit = rand() % (n * m / 12) + 1;

    for (int i = 0; i < limit; i++){
        int ObsN = rand() % n, ObsM = rand() % n;
        if (this->Grid[ObsN][ObsM] == '-')
            (rand() % 2) ? this->Grid[ObsN][ObsM] = 'S' : this->Grid[ObsN][ObsM] = 'T'; // Τυχαία επιλογή μεταξύ δέντρου ή νερού
    }

    Grid[rand() % n][rand() % m] = 'P';
}

// Ανανέωση της θέσης του Avatar στο Map
void Map::UpdateAvatar(int y, int x, Avatar* obj){
    Grid[y][x]='-';
    Grid[obj->getY()][obj->getX()]=obj->getID();
}

// Αναδρομική συνάρτηση εύρεσης και αρχικοποίησης συντεταγμένων των NPC και του Avatar
void Map::SetCoordinates(Entity* Obj)
{
    // Εύρεση καινούργιων συντεταγμένων για το NPC ή το Avatar
    int y = rand() % n;
    int x = rand() % m;

    if (this->Grid[y][x] == '-')
    {
        // Έλεγχος για τον αποκλεισμό των NPC και του Avatar από terrain (γη, νερό, γιατρικό, όρια του map), κατά την αρχή του παιχνιδιού
        char* array = new char;
        array = Scan(y, x);
                
        int i = 0;
        if (Obj->getID() == 'w' || Obj->getID() == 'W' || Obj->getID() == 'V')
        {
            for (i = 1; i <= 7; i+=2){
                if (array[i] != 'E' && array[i] != 'S' && array[i] != 'T' && array[i] != 'P') break;
                if (i == 3) i--;
            }
        }

        else if (Obj->getID() == 'v')
        {
            for (i = 0; i < 8; i++)
            {
                if (array[i] != 'E' && array[i] != 'S' && array[i] != 'T' && array[i] != 'P') break;
            }
        }

        if (i == 8 || i == 9)
        {
            SetCoordinates(Obj);
            delete[] array;
            return;
        }

        // Αρχικοποίηση των συντεταγμένων του NPC ή του Avatar
        Obj->SetYX(y, x);
        Grid[y][x]=Obj->getID();
        delete[] array;
        return;
    }
    else SetCoordinates(Obj);
}

// Αρχικοποίηση των NPC και τοποθέτητσή τους στο vector της αντίστοιχης ομάδας
void Map::SpawnEntities(){
    int NumOfNPC=(rand() % (n*m/15))+1;
    for (int i = 0; i < NumOfNPC; i++)
    {
        objvecV.push_back(new Vampire);
        SetCoordinates(objvecV.at(i));
    }
    for (int i = 0; i < NumOfNPC; i++)
    {   
        objvecW.push_back(new Werewolf);
        SetCoordinates(objvecW.at(i));
    }
}

//H scan επιστρεφει array char για τις θέσεις γύρω από μία θέση για κάθε αντικείμενο
char* Map::Scan(int y, int x)
{
    // Το NearPositions[] περιλαμβάνει το max 3*3 πλαίσιο του Grid, εκτός της θέσης με την οποία καλείται, με την σειρά: από πάνω αριστερά έως κάτω δεξιά
    char* NearPositions=new char[8];
    int NP_index=0;
    for (int i = y - 1; i <= y + 1; i++)
    {
        for (int j = x - 1; j <= x + 1; j++)
        {
            if (i < 0 || i > n - 1 || j < 0 || j > m - 1)
            {
                NearPositions[NP_index] = 'E'; // Empty, εκτός πίνακα "Grid"
                NP_index++;
                continue;
            }

            if (i == y && j == x)
                continue;

            NearPositions[NP_index] = Grid[i][j];
            NP_index++;
        }
    }
    return NearPositions;
}

int Map::Iterate(vector<NPC*> objvec, NPC* Target)
{
    int i;
    for (i = 0; i < objvec.size(); i++)
    {
        if (Target == objvec.at(i)) break;
    }
    return i;
}

// Επιστροφή των NPC από το κατάλληλο vector
NPC* Map::GetNPC(vector<NPC*> objvec,int &x,int &y,short int block){
    // Αντιστοίχιση των συντεταγμένων του array σε συντεταγμένες του χάρτη
    switch (block) {
        case 0:
            x--;
            y--;
            break;
                    
        case 1:
            y--;
            break;

        case 2:
            x++;
            y--;
            break;
                    
        case 3:
            x--;
            break;
                    
        case 4:
            x++;
            break;
                    
        case 5:
            y++;
            x--;
            break;
                    
        case 6:
            y++;
            break;

        case 7:
            y++;
            x++;  
            break;
    }
            
    // Αναζήτηση του NPC στο vector του
    int i;
    for (i=0;i<objvec.size();i++) {
        if (objvec.at(i)->getX() == x && objvec.at(i)->getY() == y) {
             break;
        }    
    }
    return objvec.at(i);
}

// Συνάρτηση που αποφασίζει την ενέργεια που θα εκτελέσει ένα NPC σε έναν γύρο, με βαση τις θέσεις γύρω του (ενδεχομένως αναδρομική)
void Map::Action(NPC* protagonist)
{
    char* array = new char;
    array = Scan(protagonist->getY(), protagonist->getX());

    short int block = rand() % 8;

    // Η θέση που επιλέγεται δεν μπορεί προσπελαστεί από το NPC, οπότε, αυτό θα μείνει ακίνητο
    if (array[block] == 'E' || array[block] == 'S' || array[block] == 'T' || array[block] == 'P' || array[block] == 'W' || array[block] == 'V') {
        delete[] array; 
        return;
    }
            
    int x1 = protagonist->getX();
    int y1 = protagonist->getY();
    NPC* Target;

    // Η θέση που επιλέγεται περιέχει σύμμαχο (NPC της ίδιας ομάδας)
    if (array[block] == protagonist->getID()) {
        if (protagonist->getID() == 'w'){
            Target = GetNPC(objvecW, x1, y1, block);
        } 
        else {
            Target = GetNPC(objvecV, x1, y1, block);
        }
        // Αν το NPC έχει γιατρικό και το επίπεδο υγείας του συμμάχου δεν είναι πλήρες, τότε το NPC θα αναπληρώσει ένα επίπεδο υγείας του συμμάχου του, με κόστος ενος γιατρικού του
        if (protagonist->getPotions() > 0 && Target->getCurrentHP() < Target->getCapHP()){
            protagonist->Heal(Target);
        }

        // Αν δεν ικανοποιούνται οι απαραίτητες συνθήκες για την Heal(), τότε το NPC μένει ακίνητο
        delete[] array;
        return;
    }

    // Η θέση που επιλέγεται περιέχει εχθρό
    if (array[block] != protagonist->getID() && array[block] != '-') {
        if (protagonist->getID() == 'w') {
            Target = GetNPC(objvecV, x1, y1, block);
        }    
        else {
            Target = GetNPC(objvecW, x1, y1, block);
        }
        // Αν το επίπεδο δύναμης του εχθρού είναι μικρότερο, τότε επιτίθεται
        if (protagonist->getPower_Lvl() >= Target->getPower_Lvl())
        {
            protagonist->Attack(Target);
                    
            // Αν ο εχθρός πεθάνει, διαγράφεται από το αντίστοιχο vector
            if (Target->getCurrentHP() <= 0)
            {
                int TargetIndex;
            
                if (Target->getID() == 'w') {
                    TargetIndex = Iterate(objvecW,Target);
                    Grid[y1][x1] = '-';
                    objvecW.erase(objvecW.begin()+TargetIndex);
                }
                else {
                    TargetIndex = Iterate(objvecV,Target);
                    Grid[y1][x1] = '-';
                    objvecV.erase(objvecV.begin()+TargetIndex);
                }
            }
        }
        else Action(protagonist);

        delete[] array;
        return;       
    }

    // Στην περίπτωση που ένα werewolf NPC πάρει διαγώνια, άδεια θέση, κάνει εκ νέου κίνηση
    if ((block == 0 || block == 2 || block == 5 || block == 7 ) && protagonist->getID() == 'w') {
        delete[] array;
        Action(protagonist);
        return;
    }

    // Αν η θέση που επιλεχθεί είναι άδεια, τότε το NPC κινείται σε αυτή
    else if (array[block] == '-') {
        Grid[protagonist->getY()][protagonist->getX()] = '-';
        protagonist->Move(block);
        Grid[protagonist->getY()][protagonist->getX()] = protagonist->getID();
    }

    delete[] array;
}

// Εκτύπωση του Map
void Map::print(){
    for (int i=0;i<n;i++){
        for (int j=0;j<m;j++){
            cout << this->Grid[i][j];
        }
        cout << endl;
    }
}

Map::~Map(){
    for (int i=0;i<n;i++){
        delete [] this->Grid[i];
    }
    delete[] this->Grid; 
}
