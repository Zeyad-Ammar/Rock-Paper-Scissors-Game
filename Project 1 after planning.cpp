#include <iostream>
#include<cstdlib>
using namespace std;
enum enGameChoice {
    Paper=1,Stone=2,scessior=3
};
enum enTheWinner
{
    Player=1,Computer=2,NoWinner=3

};
struct stRoundInfo
{
    short RoundNumber=0;
    enGameChoice PlayerChoices=Paper, ComputerChoices=Paper;
    enTheWinner TheWinner=NoWinner;
    string PlayerChoiceName="", ComputerChoiceName="", WinnerName="";

};
struct stGameInfo
{
    short GameRounds = 0, PlayerwonPoints = 0, ComputerWonPoints = 0, DrawPoints = 0;
    enTheWinner Winner=NoWinner;
    string WinnerName="";
};
void PrintChoices() {
    cout << "Your choice : [1]:Paper, [2]:Stone, [3]:Scessors ?";
}
short RandomNum(int From, int To)
{
    return rand() % (To - From) + From;

}
enGameChoice PlayerChoice() {
    short Choice = 0;
    do
    {
        PrintChoices();
        cin >> Choice;

    } while (!(Choice > 0 && Choice < 4));
    return enGameChoice(Choice);
}
enGameChoice ComputerChoice() {

    return enGameChoice(RandomNum(1, 3));
}
short ReadRoundsNumber() {
    int Num = 0;
    do
    {
        cout << "Plz enter the Number of Rounds 1:10 ??"<<endl;
        cin >> Num;

    } while (!(Num <= 10 && Num > 0));
    return Num;
}
string PrintTaps(short NumberOfTabs) {
    string Taps = "";
    for (size_t i = 0; i < NumberOfTabs; i++)
    {
        Taps+= "\t";
    }
    return Taps;
}
void PrintRoundInfo(stRoundInfo MyRound) {
    cout << "________________Round [" << MyRound.RoundNumber << "] ________________" << endl;
    cout << "Player   Choice: " << MyRound.PlayerChoiceName << endl;
    cout << "Computer Choice: " << MyRound.ComputerChoiceName << endl;
    cout << "Round Winner   : " << MyRound.WinnerName << endl;
    cout << "__________________________________________\n";
}
void PrintGameOverScreen() {
    cout<<PrintTaps(3) << "______________________________________________________" << endl;
    cout << PrintTaps(3) << "               +++ G a m e O v e r +++              " << endl;
    cout << PrintTaps(3) << "______________________________________________________" << endl;

}
void RoundResultEffect(enTheWinner Winner)
{
    switch (Winner)
    {
    case Player:
        system("color 2f");
        break;
    case Computer:
        system("color 4f");

        cout << "\a";
        break;
    case enTheWinner::NoWinner:
        system("color 6f");
        break;
    default:
        break;
    }
}
void PrintGameInfo(stGameInfo MyGame)
{
    PrintGameOverScreen();
    cout << PrintTaps(3) << "___________________ [Game Result ] ___________________" << endl;
    cout << PrintTaps(3) << "Game Rounds        : " << MyGame.GameRounds << endl;
    cout << PrintTaps(3) << "Player Won Times   : " << MyGame.PlayerwonPoints << endl;
    cout << PrintTaps(3) << "Computer won Times : " << MyGame.ComputerWonPoints << endl;
    cout << PrintTaps(3) << "Draw Times         : " << MyGame.DrawPoints << endl;
    cout << PrintTaps(3) << "Final Winner       : " << MyGame.WinnerName << endl;
    cout << PrintTaps(3)<< "_______________________________________________________" << endl;
    RoundResultEffect(MyGame.Winner);
}

string GetChoiceName(enGameChoice Choice) {
    string arrChoiceNames[3] = { "Paper","Stone","Scessors" };
    return arrChoiceNames[Choice - 1];
}
string GetWinnerName(enTheWinner Winner) {
    string arrWinnerNames[3] = { "Player","Computer","NoWinner" };
    return arrWinnerNames[Winner - 1];
}
enTheWinner WhoIsWinner(enGameChoice PlayerChoice, enGameChoice ComputerChoice) {
    
    if (PlayerChoice == ComputerChoice)
        return NoWinner;
       
    switch (PlayerChoice)
    {
    case Paper:
        if (ComputerChoice == enGameChoice::scessior)
            return Computer;
        break;
    case Stone:
        if (ComputerChoice == enGameChoice::Paper)
            return Computer;
        break;
    case scessior:
        if (ComputerChoice == enGameChoice::Stone)
            return Computer;
        break;
    default:
        break;
    }
    return Player;
}
stRoundInfo FillRoundInfo(short Round) {
    stRoundInfo MyRound;
    MyRound.RoundNumber = Round;
    cout << "Round [" << MyRound.RoundNumber << "] begins: " << endl;
    MyRound.PlayerChoices=PlayerChoice();
    MyRound.ComputerChoices = ComputerChoice();
    MyRound.PlayerChoiceName = GetChoiceName(MyRound.PlayerChoices);
    MyRound.ComputerChoiceName = GetChoiceName(MyRound.ComputerChoices);
    MyRound.TheWinner = WhoIsWinner(MyRound.PlayerChoices, MyRound.ComputerChoices);
    MyRound.WinnerName = GetWinnerName(WhoIsWinner(MyRound.PlayerChoices, MyRound.ComputerChoices)) ;

    return MyRound;
}
enTheWinner FinalWinner(short PlayerPoints, short ComputerPoints)
{
    if (PlayerPoints == ComputerPoints)
        return NoWinner;
    else if (PlayerPoints > ComputerPoints)
        return Player;
    else
        return Computer;
}
stGameInfo PlayGame(short RoundNumber) {
    stGameInfo MyGame;
    MyGame.GameRounds = RoundNumber;
    for (short i = 1; i <= MyGame.GameRounds; i++) {
        stRoundInfo MyRound=FillRoundInfo(i);
        RoundResultEffect(MyRound.TheWinner);
        PrintRoundInfo(MyRound);
        switch (MyRound.TheWinner)
        {
        case Player:
           MyGame.PlayerwonPoints++;
           break;
        case Computer:
            MyGame.ComputerWonPoints++;
            break;
        default:
           MyGame.DrawPoints++;
            break;
        }

    }
    MyGame.Winner = FinalWinner(MyGame.PlayerwonPoints, MyGame.ComputerWonPoints);
    MyGame.WinnerName = GetWinnerName(MyGame.Winner);
    return MyGame;
}
void StartGame() {
    char Again = 'y';
    do
    {
        system("color 0f");
        system("cls");
       short Rounds= ReadRoundsNumber();
       PrintGameInfo(PlayGame(Rounds));
       cout << "Are you want to play Again? y/n? ";
       cin >> Again;
    } while (Again=='y'||Again=='Y');
}
int main()
{
    //seed random function
    srand((unsigned)time(NULL));
    StartGame();

    return 0;
}