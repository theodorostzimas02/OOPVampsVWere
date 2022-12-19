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

        void SetYX(int y,int x){
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

        // Η Move() του καθε NPC χειρίζεται την κίνησή του μεσα στον χάρτη και παίρνει ως όρισμα το index ενος array από την Scan() παρακάτω
        virtual void Move(short int MoveN){
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
            target->CurrentHP=target->CurrentHP-(this->Power_Lvl - target->Defence_Lvl);
            if (target->Defence_Lvl > 0) target->Defence_Lvl--;
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

        void Move(short int MoveN){
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
};

class Werewolf : public NPC {
    private:
        int num;
    public:
        Werewolf() { ID = 'w';}

        void Move(short int MoveN){
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

        void SetCoordinates(Entity* Obj) //εδώ γίνεται το λάθος 
        {
            int y = rand() % n;
            int x = rand() % m;
            while(1)
            {
                if (this->Grid[y][x] == '-')
                {
                    // Έλεγχος για τον αποκλεισμό των NPC και του Avatar από terrain (γη, νερό, γιατρικό, όρια του map), κατά την αρχή του παιχνιδιού
                    char* array = new char;
                    array = Scan(y, x);

                   /* int i = 0;
                    if (Obj->getID() == 'w' || Obj->getID() == 'W' || Obj->getID() == 'V')
                    {
                        for (i = 0; i < 7; i+=2){
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
                    if (i == 9 && (Obj->getID() == 'w' || Obj->getID() == 'W' || Obj->getID() == 'V') || i == 8 && Obj->getID() == 'v') break;*/

                    // Αρχικοποίηση των συντεταγμένων του NPC ή του Avatar
                    Obj->SetYX(y, x);
                    Grid[y][x]=Obj->getID();
                    delete [] array;
                    return;
                }

                // Εύρεση καινούργιων συντεταγμένων για το NPC ή το Avatar
                y = rand() % n;
                x = rand() % m;
            }
        }

        void SpawnEntities(){
            int NumOfNPC=rand() % (n*m/15);
            for (int i = 0; i < NumOfNPC; i++)
            {
                objvecV.push_back(new Vampire);
                SetCoordinates(objvecV.at(i));
                cout<<objvecV.at(i)->getID()<<endl;
            }
            for (int i = 0; i < NumOfNPC; i++)
            {   
                objvecW.push_back(new Werewolf);
                SetCoordinates(objvecW.at(i));
                cout<<objvecW.at(i)->getID()<<endl;
            }
        }

        //H scan επιστρεφει array bool για τις θέσεις γύρω από μία θέση για κάθε αντικείμενο

        char* Scan(int y, int x)
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
                        NearPositions[NP_index] = 'E'; //empty, εκτός πίνακα "Grid"
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

        int Iterate(vector<NPC*> objvec, NPC* Target)
        {
            int i;
            for (i = 0; i < objvec.size(); i++)
            {
                if (Target == objvec.at(i)) break;
            }
            cout << i << endl;
            return i;
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
            
            int i;
            for (i=0;i<objvec.size();i++) { //to tsekara kai den exei provlhma, kanonika to gyrnaei. sthn heal kai sthn attack yparxei provlhma
                if (objvec.at(i)->getX() == x && objvec.at(i)->getY() == y) {
                     break;
                }    
            }
            return objvec.at(i);
        }
        
        void Action(NPC* protagonist)
        {
            char* array = new char;
            array = Scan(protagonist->getY(), protagonist->getX());
            for (int i=0;i<8;i++){
                cout << array[i] << endl;
            }

            short int block = rand() % 8;
            cout << "block :" << array[block] << endl;
            cout << "id " << protagonist->getID() << endl;
            

            // Η θέση που επιλέγεται δεν μπορεί προσπελαστεί από το NPC, οπότε, αυτό θα μείνει ακίνητο
            if (array[block] == 'E' || array[block] == 'S' || array[block] == 'T' || array[block] == 'P' || array[block] == 'W' || array[block] == 'V') {
                cout << "MENEI STASIMO" << endl;
                delete[] array; //EDW EXEI BUG! Diagrafetai to id tou protagonist alla oxi sto idio, sto vector ! 
                return;
            }
            
            int x1 = protagonist->getX();
            int y1 = protagonist->getY();
            NPC* Target = new NPC;

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
                cout << Target->getID()<<endl;

                // Αν δεν ικανοποιούνται οι απαραίτητες συνθήκες για την Heal(), τότε το NPC μένει ακίνητο
                delete[] array;
                //delete Target;
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
                      
                delete[] array;
                //delete Target;
                return;       
            }

            // Στην περίπτωση που ένα werewolf NPC πάρει διαγώνια, άδεια θέση, μένει ακίνητο
            if (block % 2 == 0 && protagonist->getID() == 'w') {
                cout << "PITHANH MALAKIA " << endl;
                delete[] array;
                //delete Target;
                return;
            }

            // Αν η θέση που επιλεχθεί είναι άδεια, τότε το NPC κινείται σε αυτή
            else if (array[block] == '-') {  //Για κάποιον λόγο σε αυτό το σημείο ενώ το ελέγχει δεν ξέρει αν υπάρχει ή όχι κάποιο αντικείμενο
                Grid[protagonist->getY()][protagonist->getX()] = '-';
                protagonist->Move(block);
                Grid[protagonist->getY()][protagonist->getX()] = protagonist->getID();
            }

            //delete Target;
            delete[] array;
        }

        void print(){
            for (int i=0;i<n;i++){
                for (int j=0;j<m;j++){
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
            Player.Move(newMap.Scan(Player.getY(), Player.getX()), k);
        }
};



int main() {
    srand(time(0));
    n=10;
    m=12;

    Map newMap;
    Game newGame;
    Avatar Player('W'); // Το Avatar εισάγεται στο map πριν τα NPC, ώστε να μην εμποδίσει τις κινήσεις του
    newMap.SetCoordinates(&Player);

    newMap.SpawnEntities();
    int num = 0;
    while (1){

        cout << endl;
        for (int i=0; i<newMap.objvecW.size(); i++) {
            newMap.print();
            cout << i << endl;
            // if (newMap.objvecW.at(i)->getID() != 'w'){
            //     cout << "TI SKATA EGINE!" << endl;
            //     cout << newMap.objvecW.at(i)->getID() << endl;
                cout << "CURRENT HP:" << newMap.objvecW.at(i)->getCurrentHP() << endl;
                cout << "Potions: " << newMap.objvecW.at(i)->getPotions() << endl;
            //     cout << newMap.objvecW.size() << endl;
            //     cout << i << endl;
            //     return 0;
            // }
            cout << newMap.objvecW.at(i)->getID() << " "<<newMap.objvecW.at(i)->getY() << " " <<newMap.objvecW.at(i)->getX()  << endl;
            newMap.Action(newMap.objvecW.at(i));
            cout << "Kinish:" << newMap.objvecW.at(i)->getID() << " "<<newMap.objvecW.at(i)->getY() << " " <<newMap.objvecW.at(i)->getX()  << endl;

            for (int i = 0; i<newMap.objvecW.size();i++){
                cout << newMap.objvecW.at(i)->getID() <<endl;
            }
            cout << endl;

        }   
        for (int i=0; i<newMap.objvecV.size(); i++) {
            newMap.print();
            cout << i << endl;
            // if (newMap.objvecV.at(i)->getID() != 'v'){
            //     cout << "TI SKATA EGINE!" << endl;
            //     cout << newMap.objvecV.at(i)->getID() << endl;
                cout << "CURRENT HP:" << newMap.objvecV.at(i)->getCurrentHP() << endl;
                cout << "Potions: " << newMap.objvecV.at(i)->getPotions() << endl;
            //     cout << newMap.objvecV.size() << endl;
            //     cout << i << endl;
            //     return 0;
            // }
            cout << newMap.objvecV.at(i)->getID() << " "<<newMap.objvecV.at(i)->getY() << " " <<newMap.objvecV.at(i)->getX()  << endl;
            newMap.Action(newMap.objvecV.at(i));
            cout << "Kinish:" << newMap.objvecV.at(i)->getID() << " "<<newMap.objvecV.at(i)->getY() << " " <<newMap.objvecV.at(i)->getX()  << endl;

            for (int i = 0; i<newMap.objvecV.size();i++){
                cout << newMap.objvecV.at(i)->getID() <<endl;
            }
            cout << endl;

        }   
        
        //Sleep(2000);
        newMap.print();
        cout << endl;
        if (newMap.objvecV.size() == 0 || newMap.objvecW.size() == 0 ){
            cout << "Paixnidi teleiwse" << endl;
            break;
        }

       
    }
    
    newMap.print();
    
    return 0;
}
// Γύρος: κάθε αντικείμενο εκτελεί μόνο μία ενέργεια. Δυνατές ενέργειες: μένει ακίνητο, αλλάζει θέση, επουλώνει πληγές συμμάχου, επιτίθεται σε αντίπαλο