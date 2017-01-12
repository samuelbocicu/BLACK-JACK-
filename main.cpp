#include <iostream>
#include <fstream>
#include <string>
#include <windows.h>
#include <algorithm>
#include <ctime>
#include <vector>

struct Player {
std::string userName="";
unsigned int score= 0;
unsigned int hand =0;
unsigned int bet=0;
};
void userAccount(int x, Player users[]);
void menu(bool CardDealt[], int HouseHand[], int PlayerHand[],int HouseCardCount,int PlayerCardCount, int x, Player users[]);
void scores(int x, Player users[]);
void shuffle(bool cardDelt[]);
void displayCard(int Card);
void displayHand(int Hand[], const int CardCount);
void displayScoresAndHands(int HouseHand[],const int HouseCardCount, int PlayerHand[], const int PlayerCardCount);
int nextCard(bool CardsDealt[]);
int scoreHand(int Hand[], const int CardCount);
void gameComputer(bool CardsDealt[], int HouseHand[], int PlayerHand[], int HouseCardCount, int PlayerCardCount, int x, Player users[]);

using namespace std;
//===========================
//      main()              *
//===========================
int main()
{

    time_t qTime;
    time(&qTime);
    srand(qTime);

    int count=0;
    bool CardsDealt[52];
    int HouseCardCount=0;
    int HouseHand[12];
    int PlayerCardCount=0;
    int PlayerHand[12];
    int x=0;
    const int PLAYERS=3;
    Player users[PLAYERS];

    userAccount(x,users);
    menu(CardsDealt, HouseHand, PlayerHand, HouseCardCount, PlayerCardCount, x,users);
    system("pause");
    return 0;
}
//=============================
//      Account()             |
//=============================
void userAccount(int x, Player users[])
{
    fstream inData;
    fstream inScores;
    string userAndPass;
    string passWord, line;
    string userName;
    char option;
    bool found=false;


    cout<<"#==========================================#"<<endl;
    cout<<"=        Black Jack Cont Utilizator        ="<<endl;
    cout<<"#==========================================#"<<endl;
    cout<<endl<<endl;

    cout<<"Va rugam sa selectati una dintre optiunile pentru jucatorul #"<< x+1<<endl<<"(1) Creati un cont nou."<<endl;
    cout<<"(2) Utilizati un cont existent"<<endl;
    cout<<"Optiunea: ";
    cin>>option;
    system("cls");
    switch(option)
    {
    case '1':
        cout<<"#=====================================#"<<endl;
        cout<<"=        Black Jack Utilizator Nou    ="<<endl;
        cout<<"#=====================================#"<<endl;
        inData.open("Username.dat",ios::app);
        inScores.open("Scores.dat",ios::app);
        cout<<"Intoduceti Utilizatorul(doar litere mici): ";
        std::cin>>userName;

    std::transform(userName.begin(), userName.end(),userName.begin(),::tolower);
    cout<<endl;
    users[x].userName=userName;
    users[x].score=1000;
    cout<<"Introduceti parola: ";
    cin>>passWord;
    cout<<endl;
    inData<<userName<<" "<<passWord<<endl;
    inScores<<userName<<endl<<users[x].score<<endl;
    inData.close();
    inScores.close();
    cout<<"Înregistrarea utilizatorilor !";
    cout<<"\n\n *";
    for(int a=1;a<8;a++)
    {
        cout<<"*";
        Sleep(500);

    }
    cin.sync();cin.ignore();
    system("cls");
    break;
    case '2':

cout<<endl;
cout<<"#=====================================#"<<endl;
cout<<"=   Black Jack Utilizator existent    ="<<endl;
cout<<"#=====================================#"<<endl<<endl<<endl;
inData.open("Username.dat",ios::in);

cout<<"Intoduceti Utilizatorul(doar litere mici): ";
std::cin>>userName;
cout<<"\nIntroduceti parola : ";
cin>>passWord;
users[x].userName=userName;

std::transform(userName.begin(),userName.end(),userName.begin(),::tolower);
userAndPass=userName+" "+passWord;
if(inData.is_open()){
    while(getline(inData,line)&&!found){
        if(line.compare(userAndPass)==0){
        found=true;
    }
}
inData.close();
if(found){
    cout<<"\nBine ai venit "<< userName<<"!\n";
    Sleep(2000);
    system("cls");
}
        else{
            cout<<"Ati introdus un nume de utilizator sau parola gresit. Apasati pe (1) pentru pentru a ajunge in meniu."<<endl;
            cin>>passWord;
            if(passWord=="1")
                system("cls");
            userAccount(x, users);
        }
        found=false;
        inScores.open("Scores.dat",ios::in);
        if(inScores.is_open()){
            while(getline(inScores,line)&&!found){
                if(line.compare(userName)==0){
                   found=true;
                   inScores>>users[x].score;
                   }
            }
            inData.close();
            inScores.close();
            }
        }
        break;
    default:
        cout<<"Ati introdus o comanda gresita.Incercati din nou.\n";
        userAccount(x,users);
        break;
    }
}

//==========================
//     menu()              *
//==========================
void menu(bool CardsDealt[], int HouseHand[],int PlayerHand[], int HouseCardCount, int PlayerCardCount,int x,Player users[])
{
    char option;
    cout<<"#========================================="<<endl;
    cout<<"=        Black Jack Selectare Mod        ="<<endl;
    cout<<"#========================================#\n\n"<<endl;

    cout<<"Doresti sa joci cu...\n";
    cout<<"<1> Computerul\n";
    cout<<"<2> Cu un alt utilizator."<<endl;
    cin>>option;
    switch(option)
    {
    case '1':

        system("cls");
        cout<<"Se pregateste jocul cu calculatorul!";
        cout<<"\n\n *";
        for(int a=1;a<8;a++)
    {
        cout<<"*";
        Sleep(500);
    }
    cin.sync();cin.ignore();
    system("cls");
  gameComputer(CardsDealt,HouseHand,PlayerHand,HouseCardCount,PlayerCardCount,x,users);
    break;
    case '2':

    system("cls");
    cout<<"Se pregateste cu alti utilizatori!";
    cout<<"\n\n *";
            for(int a=1;a<8;a++)
    {
        cout<<"*";
        Sleep(500);
    }
    cin.sync();cin.ignore();
    system("cls");
    cout<<"IN LUCRU!\n";
    break;
    default:
        break;
    }
}


//========================================
//              shuffle()                =
//========================================
void shuffle(bool CardsDealt[]){
for (int Index=0;Index<52;++Index){
        CardsDealt[Index]=false;
     }
}
//=========================================
//      displayCard()                     =
//=========================================
void displayCard(int Card){
//Display the Rank}
const int Rank=(Card%13);
if(Rank==0){
   cout<<"Ace/";}
    else if(Rank<9){
    cout<<(Rank+1)<<"/";}
    else
    if(Rank==9){
        cout<<"10/";
    }
    else if(Rank==10){
            cout<<"Valet/";
            }
            else if(Rank==11){
                cout<<"Dama/";
            }
            else{
                cout<<"Rege/";
            }
            const int Suit=(Card/13);
            if(Suit==0){
                cout<<"Trefla";
            }
            else if(Suit==1){
                cout<<"Romb";
            }
            else if(Suit==2){
                cout<<"Inima";
            }
            else{
                    cout<<"Cruce";
            }
            }
//===========================================
// displayHand()                            =
//===========================================
void displayHand(int Hand[],const int CardCount){

    for (int CardIndex=0;CardIndex<CardCount;++CardIndex){
        const int NextCard=Hand[CardIndex];
        displayCard(NextCard);
        cout<<" ";
    }
    cout<<endl;
}
//============================================
//             nextCard()                    =
//============================================
int nextCard(bool CardsDealt[]){

bool CardDealt=true;
int NewCard=-1;
do{
    NewCard=(rand()%52);
    if(!CardsDealt[NewCard]){
        CardDealt=false;
    }
}while(CardDealt);
return NewCard;
}
//===============================================
//        scoreHand()                           =
//===============================================
int scoreHand(int Hand[],const int CardCount){
int AceCount=0;
int Score=0;
for(int CardIndex=0;CardIndex<CardCount;++CardIndex){
const int NextCard =Hand[CardIndex];
const int Rank=(NextCard%13);
if(Rank==0){
    ++AceCount;
    ++Score;
}
else if(Rank<9){
    Score=Score+(Rank+1);
}
    else {
        Score=Score+10;
    }
}
while(AceCount>0 &&Score<12){
    --AceCount;
    Score=Score+10;
}
return Score;
}
//=======================================
// displayScoreAndHands()               =
//=======================================
void displayScoresAndHands(int HouseHand[],const int HouseCardCount, int PlayerHand[], const int PlayerCardCount){
cout<<"House's Hand: Score = "<<scoreHand(HouseHand,HouseCardCount)<<endl;
displayHand(HouseHand, HouseCardCount);
cout<<"\nPlayer's Hand: Score = "<<scoreHand(PlayerHand,PlayerCardCount)<<endl;
displayHand(PlayerHand, PlayerCardCount);
cout<<endl;
}
//==============================================
//                 score()                     =
//==============================================
void scores(int x,Player users[])
{
    //Declarations
    fstream inScores;
    string line;
    string userName;
    int score;
    bool found=false;

    userName=users[x].userName;
    score=users[x].score;
   inScores.open("Scores.dat",ios::in|ios::out);
    while(getline(inScores,line)&&!found){
        if(line.compare(userName)==0){
            found=true;
            inScores<<score;
        }
    }
    inScores.close();
    }
//================================
//         gameComputer()        *
//================================
void gameComputer(bool CardsDealt[], int HouseHand[], int PlayerHand[], int HouseCardCount,int PlayerCardCount, int x, Player users[])
{
    bool flag=true;
    int choice=1;
    int bets;
    while(flag==true){
        shuffle(CardsDealt);
        PlayerHand[0]=nextCard(CardsDealt);
        HouseHand[0]=nextCard(CardsDealt);
        PlayerHand[1]=nextCard(CardsDealt);
        HouseHand[1]=nextCard(CardsDealt);
        HouseCardCount=2;
        PlayerCardCount=2;
        char PlayerChoice;
        bool PlayerHits=true;
        int PlayerScore=scoreHand(PlayerHand, PlayerCardCount);

        cout<<"============================================"<<endl;
        cout<<"=              Black Jack 21               ="<<endl;
        cout<<"============================================"<<endl;
        cout<<users[x].userName<<" are suma de : $"<<users[x].score<<endl;
        cout<<"Pariaza!"<<endl;
        cout<<"Suma pariu: ";
        cin>>bets;
        system("cls");
        while(bets>users[x].score){
        cout<<"Ai introdus o suma mai mare decat cea pe care o aveti in cont.\n"<<"Va rugam reintrodueti Suma pariu: ";
        cin>>bets;
        }
        system("cls");

        cout<<"============================================"<<endl;
        cout<<"=              Black Jack 21               ="<<endl;
        cout<<"============================================"<<endl;

    users[x].score=users[x].score-bets;
    cout<<"Ai pariat: $"<<bets<<"   Suma ramasa: $"<<users[x].score<<endl<<endl;

    do{

        cout<<"Carti Dealear"<<endl;
        cout<<"** ";
        displayCard(HouseHand[1]);
        cout<<endl;
        cout<<"\nCarti jucator:Scor="<<scoreHand(PlayerHand, PlayerCardCount)<<endl;
        displayHand(PlayerHand, PlayerCardCount);


        if(users[x].score>users[x].bet){
            cout<<"\nHit(h)  stay(s) or double (d): ";
            cin>>PlayerChoice;
        }
        else
        {
            cout<<"\nHit(h)  stay(s): ";
            cin>>PlayerChoice;
        }
        if(PlayerChoice=='h'){
            PlayerHand[PlayerCardCount]=nextCard(CardsDealt);
            ++PlayerCardCount;
        }
        else if (PlayerChoice=='s')
        {
            PlayerHits=false;
        }
        else if((PlayerChoice=='d')&&(users[x].score>users[x].bet)){
            PlayerHand[PlayerCardCount]=nextCard(CardsDealt);
            ++PlayerCardCount;
            users[x].bet=users[x].bet*2;
            PlayerHits=false;
        }
        else {
            cout<<"Eroare: Incearca din nou!"<<endl;

        }
        cout<<endl;

        PlayerScore=scoreHand(PlayerHand, PlayerCardCount);
        }while(PlayerHits&&(PlayerScore<22));

        if(PlayerScore>21){


            system("cls");
            scores(x,users);
            cout<<"Casa a castigat!"<<endl;
            cout<<"Ai pierdut suma: $"<<bets<<endl;
            displayScoresAndHands(HouseHand, HouseCardCount, PlayerHand, PlayerCardCount);
        }
        else{

            int HouseScore=scoreHand(HouseHand, HouseCardCount);
            while(HouseScore<17){
                    HouseHand[HouseCardCount]=nextCard(CardsDealt);
                    ++HouseCardCount;
                    HouseScore=scoreHand(HouseHand, HouseCardCount);
                }
                bool HouseBusts=(HouseScore>21);
                if(HouseBusts){

                    system("cls");
                    scores(x,users);
                    cout<<"Ai castigat!"<<endl;
                    bets=bets*2;
                    cout<<"Ai castigat suma: $"<<bets<<endl;
                    users[x].score=bets+users[x].score;
                    displayScoresAndHands(HouseHand,HouseCardCount, PlayerHand, PlayerCardCount);
                }
                else{

                    if(PlayerScore==HouseScore){


                        system("cls");
                        scores(x,users);
                        cout<<"Egal!"<<endl;
                        cout<<"Ai castigat $0"<<endl;
                        users[x].score=bets+users[x].score;
                        displayScoresAndHands(HouseHand, HouseCardCount, PlayerHand, PlayerCardCount);
                    }
                    else if(PlayerScore>HouseScore){

                        system("cls");
                        scores(x,users);
                        cout<<"Ai castigat!"<<endl;
                        bets=bets*2;
                        cout<<"Ai castigat suma $"<<bets<<endl;
                        users[x].score=bets+users[x].score;
                         displayScoresAndHands(HouseHand, HouseCardCount,PlayerHand, PlayerCardCount);
                    }
                    else{
                    system("cls");
                    scores(x,users);
                    cout<<"Casa a castigat!"<<endl;
                    cout<<"Ai piedut suma $"<<bets<<endl<<endl;
                    displayScoresAndHands(HouseHand, HouseCardCount,PlayerHand, PlayerCardCount);
                    }
                }
            }
        system("pause");
        system("cls");
        cout<<"Ai vrea sa joci inca un meci? Da(1) ori Nu(2)"<<endl;
        cin>>choice;
        while(!((choice==1)||(choice==2))){
            cout<<"Ai intodus o tasta gresita.\nTe rog sa introduci din nou: ";
            cin>>choice;
        }
        if(choice==2){
            flag=false;
        }
        else{flag=true;
        system("cls");
        }
    }
}
