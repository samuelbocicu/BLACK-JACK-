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
   cout<<"IN LUCRU\n";
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

