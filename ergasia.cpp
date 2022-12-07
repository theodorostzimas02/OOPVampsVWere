#include <iostream>
#include <cstdlib>
#include <time.h>
using namespace std;

int n, m;

class Entity{

    protected:
        int x, y;
        short int Potions;

    public:
        Entity(){
            x=rand()%n;
            y=rand()%m;
        }
        virtual void Move(int &x, int &y)=0;
        //virtual void Heal()=0;
        int getX(){
            return x;
        }
        int getY(){
            return y;
        }
};

class Avatar : public Entity {
    
    private:
        bool Team_Sup;
        
    public:
        Avatar(bool Team_Sup) : Team_Sup(Team_Sup) {
            Potions=1;
        }    
        short int getPotion(){
            return Potions;
        }
        void setPotion(short int Potion){
            this->Potions = Potions;
        }    
        void Move();  
};

class NPC : public Entity { //Current HP and Cap HP 

    protected:
        short int HP = 10;
        short int Power_Lvl;
        short int Defence_Lvl;

    public:
        NPC(){
            Potions = rand() % 3;
            Power_Lvl = (rand() % 3) + 1;
            Defence_Lvl = (rand() % 2) + 1;
        } 
};

class Vampire : public NPC {
    public:
        void Move(int &x, int &y){
            int MoveNumV = rand() % 9;

            switch (MoveNumV)
            {
                case 0:     // Μένει ακίνητο
	                break;

                case 1:     // Κινείται αριστερά
                    if (this->y > 0) this->y--;

                    break;

                case 2:    // Κινείται δεξιά
                    if (this->y < m - 1)
                        this->y++;

                    break;

                case 3:    // Κινείται πάνω
                    if (this->x > 0)
                        this->x--;

                    break;

                case 4:    // Κινείται κάτω
                    if (this->x < n - 1)
                        this->x++;

                    break;

                case 5:    // Κινείται διαγώνια αριστερά και πάνω
                    if (this->y > 0 && this->x > 0)
                    {
                        this->y--;
                        this->x--;
                    }

                    break;

                case 6:    // Κινείται διαγώνια αριστερά και κάτω
                    if (this->y > 0 && this->x < n - 1)
                    {
                        this->y--;
                        this->x++;
                    }

                    break;

                case 7:    // Κινείται διαγώνια δεξιά και πάνω
                    if (this->y < m - 1 && this->x > 0)
                    {
                        this->y++;
                        this->x--;
                    }

                    break;

                case 8:    // Κινείται διαγώνια δεξιά και κάτω
                    if (this->y < m - 1 && this->x < n - 1)
                    {
                        this->y++;
                        this->x++;
                    }

                    break;
            }
        }
};
//bool randomBool() { return rand() % 2; }
class Werewolf : public NPC {
    public:
        void Move(int &x, int &y){
            int MoveNumW = rand() % 5;
            switch (MoveNumW)
            {
            case 0:         // Μένει ακίνητο
                break;
            case 1:         // Κινείται αριστερά
                if (this->y > 0) this->y--;
                break;
            case 2:         // Κινείται δεξιά
                if (this->y < m - 1) this->y++;
                break;
            case 3:         // Κινείται πάνω
                if (this->x > 0) this->x--;
                break;
            case 4:          // Κινείται κάτω
                if (this->x < n - 1) this->x++;
                break;    
            }
        }
};

class Map {
    private:
        char **Grid;
    public: // ~ T 
        Map(int n, int m) {
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
                //int TreeN = rand() % n, TreeM, Water,Water M
                int ObsN = rand() % n, ObsM = rand() % n;
                if (this->Grid[ObsN][ObsM] == '-')
                    (rand() % 2) ? this->Grid[ObsN][ObsM] = '~' : this->Grid[ObsN][ObsM] = 'T'; // Τυχαία επιλογή μεταξύ δέντρου ή νερού
            }
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

int main() {
    srand(time(0));
    n=20;
    m=20;
  /*  Werewolf lykaki;
    Vampire drakoulas;
       for (int i=0;i<5;i++){
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
    Map newMap(n,m);
    newMap.print();

    return 0;
}
