#include <iostream>
#include <cstdlib>
#include <time.h>
#include <vector>
#include <windows.h>

using namespace std;

int n,m;

class Entity{

    protected:
        int x, y;
        short int Potions;
        char ID;

    public:
        virtual void Move(){
            return;
        };

        virtual void Heal(){
            return;
        };

        int getX(){
            return x;
        }
        int getY(){
            return y;
        }

        void SetXY(int x,int y){
            this->x=x;
            this->y=y;
        }

        char getID(){
            return ID;
        }
};

class NPC : public Entity {

    protected:
        short int CapHP = 10;
        short int CurrentHP = CapHP;
        short int Power_Lvl;
        short int Defence_Lvl;

    public:
        NPC(){
            Potions = rand() % 3;
            Power_Lvl = (rand() % 3) + 1;
            Defence_Lvl = (rand() % 2) + 1;
        }

        virtual void Move(int &x, int &y, short int MoveN){
            return;
        }

        short int getPower_Lvl(){
            return Power_Lvl;
        }

        short int getCurrentHP(){
            return CurrentHP;
        }
        
        short int getPotions(){
            return Potions;
        }

        short int getCapHP() {
            return CapHP;
        }
        
        void MAXCurrentHP() {
            CurrentHP=CapHP;   
        }

        void Heal(NPC* target)
        {
            target->CurrentHP++;
            Potions--;
        }

        void Attack(NPC* target)
        {
            target->CurrentHP=target->CurrentHP-(target->Defence_Lvl - Power_Lvl);
        }

};

class Avatar : public Entity {
    
    public:
        Avatar(char Team_Sup){
            ID = Team_Sup;
            Potions=1;
        }
    
        short int getPotion(){
            return Potions;
        }

        void Move(char* Array,bool *k) {

            if (GetAsyncKeyState(VK_UP) && (*k == 0))
            {
                if (Array[1] == '-' || Array[1] == 'P'){
                    if (Array[1] == 'P')
                        Potions++;
                    x--;
                    *k=1;
                }
            }
            else if (GetAsyncKeyState(VK_UP)) {
                *k = 0;
            }

            if (GetAsyncKeyState(VK_LEFT) && (*k == 0))
            {
                if (Array[3] == '-' || Array[3] == 'P'){
                    if (Array[3] == 'P')
                        Potions++;
                    x--;
                   *k=1;
                }
            }
            else if (GetAsyncKeyState(VK_LEFT))
            {
                *k = 0;
            }

            if (GetAsyncKeyState(VK_RIGHT) && (*k==0)) {
                if (Array[5] == '-' || Array[5] == 'P'){
                    if (Array[5] == 'P')
                        Potions++;
                    x++;
                    *k=1;
                }
            }
            else if (GetAsyncKeyState(VK_RIGHT)) {
                *k=0;
            }

            if (GetAsyncKeyState(VK_DOWN) && (*k==0)) {
                if (Array[7] == '-' || Array[7] == 'P'){
                    if (Array[7] == 'P')
                        Potions++;
                    x--;
                    *k=1;
                }
             
            }
            else if (GetAsyncKeyState(VK_DOWN))
            {
                *k=0;
            }
        }
        void Heal(vector<NPC*> NPCvec)
        {
            if (Potions == 0) {
                cout << "You don't have enough potions for this action." << endl;
                Sleep(1000);
            }
            else {
                for (int i=0; i<NPCvec.size(); i++){
                    NPCvec.at(i)->MAXCurrentHP();
                }
                Potions--;
            }    
        }
        
};    



class Vampire : public NPC {
    public:
        Vampire() { ID = 'v'; }

        void Move(int &x, int &y, short int MoveN){
            switch (MoveN)
            {
                case 0:     // Μένει ακίνητο
	                break;

                case 1:     // Κινείται πάνω
                    this->y--;
                    break;

                case 2:    // Κινείται κάτω
                    this->y++;
                    break;

                case 3:    // Κινείται αριστερά
                    this->x--;
                    break;

                case 4:    // Κινείται δεξιά
                    this->x++;
                    break;

                case 5:    // Κινείται διαγώνια αριστερά και πάνω
                    this->y--;
                    this->x--;
                    break;

                case 6:    // Κινείται διαγώνια δεξιά και πάνω
                    this->y--;
                    this->x++;
                    break;

                case 7:    // Κινείται διαγώνια αριστερά και κάτω
                    this->y++;
                    this->x--;
                    break;

                case 8:    // Κινείται διαγώνια δεξιά και κάτω
                    this->y++;
                    this->x++;
                    break;
            }
        }
};

class Werewolf : public NPC {
    private:
        int num;
    public:
        Werewolf() { ID = 'w';}

        void Move(int &x, int &y, short int MoveN){
            switch (MoveN)
            {
            case 0:         // Μένει ακίνητο
                break;
            case 1:         // Κινείται πάνω
                this->y--;
                break;
            case 2:         // Κινείται κάτω
                this->y++;
                break;
            case 3:         // Κινείται αριστερα
                this->x--;
                break;
            case 4:          // Κινείται δεξιά
                this->x++;
                break;    
            }
        }
};

class Map{
    private:
        char **Grid;
    public: // S T P

        vector<NPC*> objvecV;
        vector<NPC*> objvecW;

        Map(){
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

        void SetCoordinates(Entity* Obj)
        {
            int x = rand() % n;
            int y = rand() % m;
            while(1)
            {
                if (this->Grid[x][y] == '-')
                {
                    // Έλεγχος για τον αποκλεισμό των NPC και του Avatar από terrain (γη, νερό, γιατρικό, όρια του map), κατά την αρχή του παιχνιδιού
                    char* array = new char;
                    array = Scan(x, y);

                    int i = 0;
                    if (Obj->getID() == 'w' || Obj->getID() == 'W' || Obj->getID() == 'V')
                    {
                        for (i = 1; i < 8; i+=2){
                            if (array[i] != 'E' && array[i] != 'S' && array[i] != 'T' && array[i] != 'P') break;
                        }
                        
                        delete[] array;
                    }

                    else if (Obj->getID() == 'v')
                    {
                        for (i = 0; i < 8; i++)
                        {
                            if (array[i] != 'E' && array[i] != 'S' && array[i] != 'T' && array[i] != 'P') break;
                        }
                        
                        delete[] array;
                    }
                    if (i == 9 && (Obj->getID() == 'w' || Obj->getID() == 'W' || Obj->getID() == 'V') || i == 8 && Obj->getID() == 'v') break;

                    // Αρχικοποίηση των συντεταγμένων του NPC ή του Avatar
                    Obj->SetXY(x, y);
                    Grid[x][y]=Obj->getID();
                    return;
                }

                // Εύρεση καινούργιων συντεταγμένων για το NPC ή το Avatar
                x = rand() % n;
                y = rand() % m;
            }
        }

        void SpawnEntities(){
            int NumOfNPC=rand() % (n*m/15);
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

        //H scan επιστρεφει array bool για τις θέσεις γύρω από μία θέση για κάθε αντικείμενο

        char* Scan(int x, int y)
        {
            // Το NearPositions[] περιλαμβάνει το max 3*3 πλαίσιο του Grid, εκτός της θέσης με την οποία καλείται, με την σειρά: από πάνω αριστερά έως κάτω δεξιά
            char* NearPositions=new char[8];
            int NP_index=0;
            for (int j = y - 1; j <= y + 1; j++)
            {
                for (int i = x - 1; i <= x + 1; i++)
                {
                    if (i < 0 || i > n - 1 || j < 0 || j > m - 1)
                    {
                        NearPositions[NP_index] = 'E'; //empty, εκτός πίνακα "Grid"
                        NP_index++;
                        continue;
                    }

                    if (i == x && j == y)
                        continue;

                    NearPositions[NP_index] = Grid[i][j];
                    NP_index++;
                }
            }
            return NearPositions; // NearPositions[περιττού αριθμού] = πάνω, κάτω, δεξιά, αριστερά
        }

        int Iterate(vector<NPC*> objvec, NPC* Target)
        {
            for (int i; i < objvec.size(); i++)
            {
                if (Target == objvec.at(i))
                   return i;
            }
        }

        NPC* GetNPC(vector<NPC*> objvec,int &x,int &y,short int block){
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
            
            for (int i=0;i<objvec.size();i++) {
                if (objvec.at(i)->getX() == x && objvec.at(i)->getX() == y) return objvec.at(i);
            }
        }
        
        void Action(NPC* protagonist)
        {
            char* array = new char;
            array = Scan(protagonist->getX(), protagonist->getY());

            short int block = rand() % 8;

            if (array[block] == 'E' || array[block] == 'S' || array[block] == 'T' || array[block] == 'P' || array[block] == 'W' || array[block] == 'V') {
                return;
            }
            
            int x1 = protagonist->getX();
            int y1 = protagonist->getY();
            NPC* Target= new NPC;

            if (array[block] == protagonist->getID()) {
                if (protagonist->getID() == 'w') Target = GetNPC(objvecW, x1, y1, block);
                else Target = GetNPC(objvecV, x1, y1, block);
                
                if (protagonist->getPotions() > 0 && Target->getCurrentHP() < Target->getCapHP()){
                    protagonist->Heal(Target);
                    
                    delete Target;
                    delete[] array;
                    return;
                }
            }

            if (array[block] != protagonist->getID() && array[block] != '-') {
                if (protagonist->getID() == 'w') Target = GetNPC(objvecV, x1, y1, block);
                else Target = GetNPC(objvecW, x1, y1, block);
                
                if (protagonist->getPower_Lvl() >= Target->getPower_Lvl())
                {
                    protagonist->Attack(Target);
                    if (Target->getCurrentHP() <= 0)
                    {
                        int TargetIndex;
            
                        if (Target->getID() == 'w') {
                            TargetIndex = Iterate(objvecW,Target);
                            delete objvecW.at(TargetIndex);
                            objvecW.erase(objvecW.begin()+TargetIndex);
                        }    
                        else {
                            TargetIndex = Iterate(objvecV,Target);
                            delete objvecV.at(TargetIndex);
                            objvecW.erase(objvecV.begin()+TargetIndex);
                        }
                    }
                    
                    delete Target;
                    delete[] array;
                    return;
                }
                /*else
                {
                    protagonist->Move();
                    return;
                }*/
            }

            //if (array[block] == '-') protagonist->Move();
            
            /*if (block % 2 != 0 && protagonist->getID() == "w" ) {
                
            }
            
                    // Attack cases
                    if (

                    //heal case
            */
            
            delete Target;
            delete[] array;
        }

        void print(){
            for (int j=0;j<m;j++){
                for (int i=0;i<n;i++){
                    cout << this->Grid[i][j];
                }
                cout << endl;
            }
        }

        ~Map(){
            for (int i=0;i<n;i++){
                delete [] this->Grid[i];
            }
            delete[] this->Grid; 
        }
};

class Game{
    public:
        void Input(bool *k,Map newMap,Avatar Player)
        {
            Player.Move(newMap.Scan(Player.getX(), Player.getY()), k);
        }
};



int main() {
    srand(time(0));
    n=20;
    m=20;

    //Werewolf lykaki;
    //Vampire drakoulas;
      /* for (int i=0;i<5;i++){
        cout << "Vampire original location" << endl;
        int VampX=drakoulas.getX();
        cout <<"X:" << VampX << endl;
        int VampY=drakoulas.getY();
        cout <<"Y:" << VampY << endl;
        drakoulas.Move(VampX, VampY);
        cout << "Vampire final location" << endl;
        VampX=drakoulas.getX();
        cout <<"X:" << VampX << endl;
        VampY=drakoulas.getY();
        cout <<"Y:" << VampY << endl;
        cout << "Werewolf original location" << endl;
        int WereX=lykaki.getX();
        cout <<"X:" << WereX << endl;
        int WereY=lykaki.getY();
        cout <<"Y:" << WereY << endl;
        lykaki.Move(WereX,WereY);
        cout << "Werewolf final location" << endl;
        WereX=lykaki.getX();
        cout <<"X:" << WereX << endl;
        WereY=lykaki.getY();
        cout << "Y:" << WereY << endl;
    } */

    Map newMap;
    Game newGame;
    Avatar Player('W'); // Το Avatar εισάγεται στο map πριν τα NPC, ώστε να μην εμποδίσει τις κινήσεις του
    newMap.SetCoordinates(&Player);

    newMap.SpawnEntities();
    newMap.print();
    return 0;
}


// Γύρος: κάθε αντικείμενο εκτελεί μόνο μία ενέργεια. Δυνατές ενέργειες: μένει ακίνητο, αλλάζει θέση, επουλώνει πληγές συμμάχου, επιτίθεται σε αντίπαλο