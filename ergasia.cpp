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
        //virtual void Move();
        //virtual void Heal()=0;
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

class Avatar : public Entity {
    
    public:
        Avatar(char Team_Sup){
            ID = Team_Sup;
            Potions=1;
        }
    
        short int getPotion(){
            return Potions;
        }

        void setPotion(short int Potion){
            this->Potions = Potions;
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
        int getPower_Lvl(){
            return Power_Lvl;
        }
};

class Vampire : public NPC {
    public:
        Vampire() { ID = 'v'; }

        /*void Move(int &x, int &y, short int MoveN){
            //int MoveNumV = rand() % 9;

            switch (MoveN)
            {
                case 0:     // Μένει ακίνητο
	                break;

                case 1:     // Κινείται κάτω
                    if (this->y > 0) this->y--;

                    break;

                case 2:    // Κινείται πάνω
                    if (this->y < m - 1)
                        this->y++;

                    break;

                case 3:    // Κινείται αριστερά
                    if (this->x > 0)
                        this->x--;

                    break;

                case 4:    // Κινείται δεξιά
                    if (this->x < n - 1)
                        this->x++;

                    break;

                case 5:    // Κινείται διαγώνια αριστερά και κάτω
                    if (this->y > 0 && this->x > 0)
                    {
                        this->y--;
                        this->x--;
                    }

                    break;

                case 6:    // Κινείται διαγώνια δεξιά και κάτω
                    if (this->y > 0 && this->x < n - 1)
                    {
                        this->y--;
                        this->x++;
                    }

                    break;

                case 7:    // Κινείται διαγώνια αριστερά και πάνω
                    if (this->y < m - 1 && this->x > 0)
                    {
                        this->y++;
                        this->x--;
                    }

                    break;

                case 8:    // Κινείται διαγώνια δεξιά και πάνω
                    if (this->y < m - 1 && this->x < n - 1)
                    {
                        this->y++;
                        this->x++;
                    }

                    break;
            }
        }*/
};
//bool randomBool() { return rand() % 2; }
class Werewolf : public NPC {
    public:
        Werewolf() { ID = 'w'; }

        /*void Move(int &x, int &y, short int MoveN){
            int MoveNumW = rand() % 5;
            switch (MoveNumW)
            {
            case 0:         // Μένει ακίνητο
                break;
            case 1:         // Κινείται κατω
                if (this->y > 0) this->y--;
                break;
            case 2:         // Κινείται πανω
                if (this->y < m - 1) this->y++;
                break;
            case 3:         // Κινείται αριστερα
                if (this->x > 0) this->x--;
                break;
            case 4:          // δεξια
                if (this->x < n - 1) this->x++;
                break;    
            }
        }*/
};

class Map{
    private:
        char **Grid;
    public: // ~ T 
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

            Grid[rand() % n][rand() % m] = 'P'; //check sto telos
        }

        void SetCoordinates(Entity* Obj)
        {
            int x = rand() % n;
            int y = rand() % m;
            while(1)
            {
                if (this->Grid[x][y] == '-')
                {
                    Obj->SetXY(x, y);
                    Grid[x][y]=Obj->getID();
                    break;
                }

                else
                {
                    x = rand() % n;
                    y = rand() % m;
                }
                
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
    Avatar Player('W');
    newMap.SetCoordinates(&Player);
    

    int NumOfNPC=(n*m)/30;
    vector<Vampire*> objvecV;

    for (int i = 0; i < NumOfNPC; i++)
    {
        Vampire drakoulas;
        objvecV.push_back(&drakoulas);
        newMap.SetCoordinates(objvecV.at(i));
    }

    vector<Werewolf*> objvecW;
    for (int i = 0; i < NumOfNPC; i++)
    {
        Werewolf bruh;
        objvecW.push_back(&bruh);
        newMap.SetCoordinates(objvecW.at(i));
    }

    for (int i = 0; i < NumOfNPC; i++)
    {
        cout << "Power lvl of " << i + 1 << " is: " << objvecV.at(i)->getPower_Lvl() << endl;
    }

    newMap.print();
    return 0;
}