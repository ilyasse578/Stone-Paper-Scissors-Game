#include<iostream>
#include<string>
#include<cmath>
using namespace std;	
enum enGameChoice { Stone = 1, Paper = 2, Scissors = 3 };
enum enWinner { Player1 = 1, Computer = 2, Draw = 3 };

struct stRoundInfo
{
	short RoundNumber = 0;
	enGameChoice Player1Choice;
	enGameChoice ComputerChoice ;
	enWinner Winner;
	string RoundWinnerName ;
};

struct stGameResults
{
	short GameRounds = 0;
	short Player1WinTimes = 0;
	short ComputerWinTimes = 0;
	short DrawTimes = 0;
	enWinner GameWinner;
	string GameWinnerName = "";
};

int RandomNumber(int From, int To)
{
	//Function to generate a random number
	int randNum = rand() % (To - From + 1) + From;
	return randNum;
}

short ReadHowManyRounds()
{
	short GameRounds = 1;

	do
	{
		cout << "How many rounds 1 to 10 ? ";
		cin >> GameRounds;

	} while (GameRounds < 1 || GameRounds > 10);

	return GameRounds;
}

enGameChoice ReadPlayer1Choice()
{
	short Choice = 1;

	do
	{
		cout << "\nYour choice : [1]:Stone, [2]:Paper, [3]:Scissors ? ";
		cin >> Choice;
	} while (Choice < 1 || Choice > 3);

	return enGameChoice(Choice);
}

enGameChoice GetComputerChoice()
{
	return (enGameChoice)RandomNumber(1, 3);
}

enWinner WhoWonTheRound(stRoundInfo RoundInfo)
{
	if (RoundInfo.Player1Choice == RoundInfo.ComputerChoice)
		return enWinner::Draw;

	switch (RoundInfo.Player1Choice) // This switch case check if only the computer win just computer;
	{
	case enGameChoice::Stone:
		if (RoundInfo.ComputerChoice == enGameChoice::Paper)
			return enWinner::Computer;

	case enGameChoice::Paper:
		if (RoundInfo.ComputerChoice == enGameChoice::Scissors)
			return enWinner::Computer;

	case enGameChoice::Scissors:
		if (RoundInfo.ComputerChoice == enGameChoice::Stone)
			return enWinner::Computer;

	}
	// If you reach here that means the winner is the player1;
	return enWinner::Player1;

}

string WinnerName(enWinner Winner)
{
	string ArrWinnerName[3] = { "Player1", "Computer", "No Winner" };
	return ArrWinnerName[Winner - 1];
}

string ChoiceName(enGameChoice Choice)
{
	string ArrGameChoices[3] = { "Stone", "Paper", "Scissors" };
	return ArrGameChoices[Choice - 1];
}

void SetColorScreen(enWinner Winner)
{
	switch (Winner)
	{
	case enWinner::Player1:
		system("color 1F");
		break;
	case enWinner::Computer:
		system("color 4F");
		cout << "\a";
		break;
	default:
		system("color 6F");

	}
}

void PrintRoundResults(stRoundInfo RoundInfo)
{
	cout << "\n_______________Round[" << RoundInfo.RoundNumber << "]_______________\n\n";
	cout << "Player1 choice   : " << ChoiceName(RoundInfo.Player1Choice) << endl;
	cout << "Computer choice  : " << ChoiceName(RoundInfo.ComputerChoice) << endl;
	cout << "Round Winner     :[" << RoundInfo.RoundWinnerName << "]\n";
	cout << "______________________________________\n";

	SetColorScreen(RoundInfo.Winner);

}

enWinner WhoWonTheGame(short Player1WinTimes, short ComputerWinTimes)
{
	if (Player1WinTimes > ComputerWinTimes)
		return enWinner::Player1;
	else if (Player1WinTimes < ComputerWinTimes)
		return enWinner::Computer;
	else
		return enWinner::Draw;
}

stGameResults FillGameResults(short HowManyRounds, short Player1WinTimes, short ComputerWinTimes, short DrawTimes)
{
	stGameResults GameResults;

	GameResults.GameRounds = HowManyRounds;
	GameResults.Player1WinTimes = Player1WinTimes;
	GameResults.ComputerWinTimes = ComputerWinTimes;
	GameResults.DrawTimes = DrawTimes;
	GameResults.GameWinner = WhoWonTheGame(Player1WinTimes, ComputerWinTimes);
	GameResults.GameWinnerName = WinnerName(GameResults.GameWinner);

	return GameResults;
}

stGameResults PlayGame(short HowManyRounds)
{
	stRoundInfo RoundInfo;
	short Player1WinTimes = 0, ComputerWinTimes = 0, DrawTimes = 0;

	for (short GameRound = 1; GameRound <= HowManyRounds; GameRound++)
	{
		cout << "\nRound [" << GameRound << "] begins : \n";
		RoundInfo.RoundNumber = GameRound;
		RoundInfo.Player1Choice = ReadPlayer1Choice();
		RoundInfo.ComputerChoice = GetComputerChoice();
		RoundInfo.Winner = WhoWonTheRound(RoundInfo);
		RoundInfo.RoundWinnerName = WinnerName(RoundInfo.Winner);

		// Increase Win/Draw counter;
		if (RoundInfo.Winner == enWinner::Player1)
			Player1WinTimes++;
		else if (RoundInfo.Winner == enWinner::Computer)
			ComputerWinTimes++;
		else
			DrawTimes++;

		PrintRoundResults(RoundInfo);

	}

	return FillGameResults(HowManyRounds, Player1WinTimes, ComputerWinTimes, DrawTimes);

}

string Tabs(short NumberOfTabs)
{
	string T = ""; // We gave it initial value to avoid any garbage data
	for (int i = 1; i <= NumberOfTabs; i++)
	{
		T = T + "\t";
	}
	return T;
}

void ShowGameOverScreen()
{
	cout << Tabs(3) << "__________________________________________________________\n\n";
	cout << Tabs(5) << " +++ G a m e O v e r +++ \n";
	cout << Tabs(3) << "__________________________________________________________\n\n";
}

void ShowFinalGameResults(stGameResults GameResults)
{
	cout << Tabs(3) << "______________________[Game Results]______________________\n\n";
	cout << Tabs(3) << "Game Rounds         : " << GameResults.GameRounds << endl;
	cout << Tabs(3) << "Player1 Win Times   : " << GameResults.Player1WinTimes << endl;
	cout << Tabs(3) << "Computer Win Times  : " << GameResults.ComputerWinTimes << endl;
	cout << Tabs(3) << "Draw Times          : " << GameResults.DrawTimes << endl;
	cout << Tabs(3) << "Final Winner        : " << GameResults.GameWinnerName << endl;
	cout << Tabs(3) << "__________________________________________________________\n\n";

	SetColorScreen(GameResults.GameWinner);
}

void ResetScreen()
{
	system("cls");
	system("color 0F");
}

void StartGame()
{
	char PlayAgain = 'Y';

	do
	{
		ResetScreen();

		stGameResults GameResults = PlayGame(ReadHowManyRounds());
		ShowGameOverScreen();
		ShowFinalGameResults(GameResults);

		cout << endl << Tabs(3) << "Do you want to play again Y/N ";
		cin >> PlayAgain;

	} while (PlayAgain == 'Y' || PlayAgain == 'y');

}


int main()
{
	srand((unsigned)time(NULL));

	StartGame();


	return 0;
}