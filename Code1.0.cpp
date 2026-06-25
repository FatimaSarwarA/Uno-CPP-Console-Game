#include <iostream>
#include <cstdlib>
#include <ctime>
#include <stdexcept>
#include <string>
#include <windows.h>

HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE); // for colored cout statement

using namespace std;

class UnoCard
{
public:
	enum Color
	{
		Red,
		Blue,
		Green,
		Yellow,
		Wild
	};

	enum Value
	{
		Zero,
		One,
		Two,
		Three,
		Four,
		Five,
		Six,
		Seven,
		Eight,
		Nine,
		DrawTwo,
		Skip,
		Reverse,
		Wild_Card,
		Wild_Four
	};

	Color color;
	Value value;

	UnoCard(Color c, Value v) : color(c), value(v) {}

	Color getColor() const { return color; }

	Value getValue() const { return value; }

	static UnoCard stringToUnoCard(const string& cardString)
	{
		// Parse the card string (e.g., "Red_Skip")
		size_t underscorePos = cardString.find('_');
		if (underscorePos == string::npos) {
			throw runtime_error("Invalid card string format");
		}

		string colorStr = cardString.substr(0, underscorePos);
		string valueStr = cardString.substr(underscorePos + 1);

		// Convert color string to Color enum
		UnoCard::Color color;
		if (colorStr == "Red") {
			color = UnoCard::Red;
		}
		else if (colorStr == "Blue") {
			color = UnoCard::Blue;
		}
		else if (colorStr == "Green") {
			color = UnoCard::Green;
		}
		else if (colorStr == "Yellow") {
			color = UnoCard::Yellow;
		}
		else if (colorStr == "Wild") {
			color = UnoCard::Wild;
		}
		else {
			throw runtime_error("Invalid color string");
		}

		// Convert value string to Value enum
		UnoCard::Value value;
		if (valueStr == "Zero") {
			value = UnoCard::Zero;
		}
		else if (valueStr == "One") {
			value = UnoCard::One;
		}
		else if (valueStr == "Two") {
			value = UnoCard::Two;
		}
		else if (valueStr == "Three") {
			value = UnoCard::Three;
		}
		else if (valueStr == "Four") {
			value = UnoCard::Four;
		}
		else if (valueStr == "Five") {
			value = UnoCard::Five;
		}
		else if (valueStr == "Six") {
			value = UnoCard::Six;
		}
		else if (valueStr == "Seven") {
			value = UnoCard::Seven;
		}
		else if (valueStr == "Eight") {
			value = UnoCard::Eight;
		}
		else if (valueStr == "Nine") {
			value = UnoCard::Nine;
		}
		else if (valueStr == "DrawTwo") {
			value = UnoCard::DrawTwo;
		}
		else if (valueStr == "Skip") {
			value = UnoCard::Skip;
		}
		else if (valueStr == "Reverse") {
			value = UnoCard::Reverse;
		}
		else if (valueStr == "Wild_Card") {
			value = UnoCard::Wild_Card;
		}
		else if (valueStr == "Wild_Four") {
			value = UnoCard::Wild_Four;
		}
		else {
			throw runtime_error("Invalid value string");
		}

		return UnoCard(color, value);
	}

	string toString() const
	{
		return colorToString(color) + "_" + valueToString(value);
	}

	static std::string colorToString(Color c)
	{
		switch (c)
		{
		case Red:
			return "Red";
		case Blue:
			return "Blue";
		case Green:
			return "Green";
		case Yellow:
			return "Yellow";
		case Wild:
			return "Wild";
		default:
			return "";
		}
	}

	static string valueToString(Value v)
	{
		switch (v)
		{
		case Zero:
			return "Zero";
		case One:
			return "One";
		case Two:
			return "Two";
		case Three:
			return "Three";
		case Four:
			return "Four";
		case Five:
			return "Five";
		case Six:
			return "Six";
		case Seven:
			return "Seven";
		case Eight:
			return "Eight";
		case Nine:
			return "Nine";
		case DrawTwo:
			return "DrawTwo";
		case Skip:
			return "Skip";
		case Reverse:
			return "Reverse";
		case Wild_Card:
			return "Wild";
		case Wild_Four:
			return "Wild_Four";
		default:
			return "";
		}
	}
};

class UnoDeck
{
public:
	class Node
	{
	public:
		UnoCard card;
		Node* next;

		Node(UnoCard c) : card(c), next(nullptr) {}
	};

	Node* cards;
	int cardsInDeck;

	UnoDeck() : cards(nullptr), cardsInDeck(0) {}

	~UnoDeck() { clearDeck(); }

	void reset()
	{
		clearDeck();
		initializeDeck();
	}

	bool isEmpty() const
	{
		if (cardsInDeck == 0)
			return true;
		else
			return false;
	}

	void shuffle()
	{
		srand(static_cast<unsigned int>(time(nullptr)));

		for (int i = cardsInDeck - 1; i > 0; --i)
		{
			int j = rand() % (i + 1);

			swapNodes(i, j);
		}
	}

	UnoCard drawCard()
	{
		if (isEmpty())
		{
			throw runtime_error("Cannot draw a card since there are no cards in the deck");
		}

		UnoCard drawnCard = cards->card;
		removeCard(cards->card);

		return drawnCard;
	}
	void removeCard(UnoCard card)
	{
		if (isEmpty())
		{
			throw runtime_error("Cannot remove a card since there are no cards in the deck");
		}

		if (cards->card.color == card.color && cards->card.value == card.value)
		{
			Node* temp = cards;
			cards = cards->next;
			delete temp;
			--cardsInDeck;
		}
		else
		{
			Node* current = cards;
			Node* previous = nullptr;

			while (current != nullptr && !(current->card.color == card.color && current->card.value == card.value))
			{
				previous = current;
				current = current->next;
			}

			if (current == nullptr)
			{
				throw runtime_error("Card not found in the deck");
			}

			previous->next = current->next;
			delete current;
			--cardsInDeck;
		}
	}
public:
	void initializeDeck()
	{
		UnoCard::Color colors[] = { UnoCard::Red, UnoCard::Blue, UnoCard::Green, UnoCard::Yellow };

		for (int i = 0; i < 4; ++i)
		{
			UnoCard::Color color = colors[i];

			addCardToDeck(UnoCard(color, UnoCard::Zero));

			for (int j = 1; j < 10; j++)
			{
				addCardToDeck(UnoCard(color, static_cast<UnoCard::Value>(j)));
				addCardToDeck(UnoCard(color, static_cast<UnoCard::Value>(j)));
			}

			UnoCard::Value values[] = { UnoCard::DrawTwo, UnoCard::Skip, UnoCard::Reverse };

			for (UnoCard::Value value : values)
			{
				addCardToDeck(UnoCard(color, value));
				addCardToDeck(UnoCard(color, value));
			}
		}

		UnoCard::Value wildValues[] = { UnoCard::Wild_Card, UnoCard::Wild_Four };
		for (UnoCard::Value value : wildValues)
		{
			for (int i = 0; i < 4; i++)
			{
				addCardToDeck(UnoCard(UnoCard::Wild, value));
			}
		}

		shuffle();
	}

	void addCardToDeck(UnoCard card)
	{
		Node* newNode = new Node(card);
		newNode->next = cards;
		cards = newNode;
		++cardsInDeck;
	}

	void swapNodes(int i, int j)
	{
		if (i != j)
		{
			Node* nodeI = getNodeAtPosition(i);
			Node* nodeJ = getNodeAtPosition(j);

			UnoCard tempCard = nodeI->card;
			nodeI->card = nodeJ->card;
			nodeJ->card = tempCard;
		}
	}

	Node* getNodeAtPosition(int position)
	{
		Node* current = cards;
		for (int k = 0; k < position; ++k)
		{
			current = current->next;
		}
		return current;
	}

	void clearDeck()
	{
		while (cards != nullptr)
		{
			Node* temp = cards;
			cards = cards->next;
			delete temp;
		}

		cardsInDeck = 0;
	}
	std::string toString() const
	{
		std::string result;
		Node* current = cards;

		while (current != nullptr)
		{
			result += current->card.toString() + " , ";
			current = current->next;
		}

		return result;
	}
};

class UnoGame
{
public:
	int currentPlayer;
	string* playerIds;

	UnoDeck* playerHand;
	int numPlayers;

	UnoDeck deck;
	UnoDeck stockpile;
	UnoDeck discardPile;

	UnoCard::Color validColor;
	UnoCard::Value validValue;

	bool gameDirection;

	UnoGame(string* pids, int numPlayers) : currentPlayer(0), playerIds(pids), numPlayers(numPlayers), gameDirection(false)
	{
		deck.initializeDeck();
		deck.shuffle();

		playerHand = new UnoDeck[numPlayers];
		for (int i = 0; i < numPlayers; ++i)
		{
			playerHand[i] = UnoDeck();
			drawInitialCards(playerHand[i]);
		}
	}

	~UnoGame()
	{
		delete[] playerHand;
	}

	void display()
	{
		SetConsoleTextAttribute(h, 0x94); //9 for background color and $ for word color
		char a = 178;
		for (int i = 0; i < 76; i++)
		{
			cout << a;
		}
		cout << "UNO Game Started!";
		for (int i = 0; i < 75; i++)
		{
			cout << a;
		}
		cout << "\n\n";
	}

	void customColor(UnoGame unoGame)
	{
		if (unoGame.colorToString(unoGame.getTopCard().getColor()) == "Red")
		{
			SetConsoleTextAttribute(h, 0x94);
			cout << "Top Card: " << unoGame.getTopCard().toString() << endl << endl;
		}

		else if (unoGame.colorToString(unoGame.getTopCard().getColor()) == "Green")
		{
			SetConsoleTextAttribute(h, 0x910);
			cout << "Top Card: " << unoGame.getTopCard().toString() << endl << endl;
		}

		else if (unoGame.colorToString(unoGame.getTopCard().getColor()) == "Blue")
		{
			SetConsoleTextAttribute(h, 0x911);
			cout << "Top Card: " << unoGame.getTopCard().toString() << endl << endl;
		}

		else if (unoGame.colorToString(unoGame.getTopCard().getColor()) == "Yellow")
		{
			SetConsoleTextAttribute(h, 0x914);
			cout << "Top Card: " << unoGame.getTopCard().toString() << endl << endl;
		}

		else
		{
			SetConsoleTextAttribute(h, 0x915);
			cout << "Top Card: " << unoGame.getTopCard().toString() << endl << endl;
		}
	}

	void start()
	{
		//display();
		if (deck.isEmpty())
		{
			// Reset and shuffle the deck if it is empty
			deck.reset();
			deck.shuffle();
		}

		UnoCard card = deck.drawCard();
		validColor = card.getColor();
		validValue = card.getValue();

		if (card.getValue() == UnoCard::Wild_Card || card.getValue() == UnoCard::Wild_Four || card.getValue() == UnoCard::DrawTwo)
		{
			start();
		}
		else if (card.getValue() == UnoCard::Skip)
		{
			SetConsoleTextAttribute(h, 0x94);
			cout << playerIds[currentPlayer] << " was skipped\n" << endl;
			handleSkip();
		}
		else if (card.getValue() == UnoCard::Reverse)
		{
			SetConsoleTextAttribute(h, 0x94);
			cout << playerIds[currentPlayer] << " changed the game direction\n" << endl;
			gameDirection ^= true;
			currentPlayer = numPlayers - 1;
		}

		stockpile.addCardToDeck(card);
	}

	UnoCard getTopCard()
	{
		return stockpile.drawCard();
	}

	void drawInitialCards(UnoDeck& hand)
	{
		for (int i = 0; i < 7; ++i)
		{
			hand.addCardToDeck(deck.drawCard());
		}
	}

	void drawCard(string pid)
	{
		checkPlayerTurn(pid);

		if (deck.isEmpty())
		{
			deck.reset();
			deck.shuffle();
		}

		// Check again if the deck is still empty after reset and shuffle
		if (deck.isEmpty())
		{
			cerr << "Error: Cannot draw a card since there are no cards in the deck even after reset and shuffle." << endl;
			exit(EXIT_FAILURE);
		}

		playerHand[currentPlayer].addCardToDeck(deck.drawCard());

		if (gameDirection == false)
		{
			currentPlayer = (currentPlayer + 1) % numPlayers;
		}
		else
		{
			currentPlayer = (currentPlayer - 1 + numPlayers) % numPlayers;
		}
	}

	void playCard(string pid, UnoCard card, UnoCard::Color declaredColor)
	{
		checkPlayerTurn(pid);

		UnoDeck& hand = playerHand[currentPlayer];

		if (!validCardPlay(card))
		{
			if (card.getColor() == UnoCard::Wild)
			{
				validColor = card.getColor();
				validValue = card.getValue();
			}
			else if (card.getColor() != validColor)
			{

				cout << "Invalid player move, expected color: " << colorToString(validColor)
					<< " but got color " << colorToString(card.getColor()) << endl;
				throw runtime_error("Invalid color submission");
			}
			else if (card.getValue() != validValue)
			{
				cout << "Invalid player move, expected value: " << valueToString(validValue)
					<< " but got value " << valueToString(card.getValue()) << endl;
				throw runtime_error("Invalid value submission");
			}
		}

		hand.removeCard(card);

		if (hand.isEmpty())
		{
			SetConsoleTextAttribute(h, 0x94);
			cout << playerIds[currentPlayer] << "\n won the game!\n" << endl;
			exit(0);
		}

		validColor = card.getColor();
		validValue = card.getValue();
		stockpile.addCardToDeck(card);

		if (gameDirection == false)
		{
			currentPlayer = (currentPlayer + 1) % numPlayers;
		}
		else
		{
			currentPlayer = (currentPlayer - 1 + numPlayers) % numPlayers;
		}

		if (card.getColor() == UnoCard::Color::Wild)
		{
			validColor = declaredColor;
		}

		handleSpecialCards(card);
	}

	bool validCardPlay(UnoCard card) const
	{
		if (card.getColor() == validColor || card.getValue() == validValue)
			return true;
		else
			return false;
	}

	void checkPlayerTurn(string pid) const
	{
		if (playerIds[currentPlayer] != pid)
		{
			throw runtime_error("It is not " + pid + "'s turn");
		}
	}

	void handleSkip()
	{
		if (gameDirection == false)
		{
			currentPlayer = (currentPlayer + 1) % numPlayers;
		}
		else
		{
			currentPlayer = (currentPlayer - 1 + numPlayers) % numPlayers;
		}
	}

	void handleSpecialCards(UnoCard card)
	{
		if (card.getValue() == UnoCard::DrawTwo)
		{
			drawCards(playerIds[currentPlayer], 2);
		}
		else if (card.getValue() == UnoCard::Wild_Four)
		{
			drawCards(playerIds[currentPlayer], 4);
		}
		else if (card.getValue() == UnoCard::Skip)
		{
			SetConsoleTextAttribute(h, 0x94);
			cout << playerIds[currentPlayer] << " was skipped!\n" << endl;
			handleSkip();
		}
		else if (card.getValue() == UnoCard::Reverse)
		{
			SetConsoleTextAttribute(h, 0x94);
			cout << playerIds[currentPlayer] << " changed the game direction!\n" << endl;
			gameDirection ^= true;
			currentPlayer = (currentPlayer - 2 + numPlayers) % numPlayers;
		}
	}

	void drawCards(string pid, int numCards)
	{
		UnoDeck& hand = playerHand[currentPlayer];
		for (int i = 0; i < numCards; ++i)
		{
			hand.addCardToDeck(deck.drawCard());
		}
	}

	string colorToString(UnoCard::Color c) const
	{
		switch (c)
		{
		case UnoCard::Red:
			return "Red";
		case UnoCard::Blue:
			return "Blue";
		case UnoCard::Green:
			return "Green";
		case UnoCard::Yellow:
			return "Yellow";
		case UnoCard::Wild:
			return "Wild";
		default:
			return "";
		}
	}

	string valueToString(UnoCard::Value v) const
	{
		switch (v)
		{
		case UnoCard::Zero:
			return "Zero";
		case UnoCard::One:
			return "One";
		case UnoCard::Two:
			return "Two";
		case UnoCard::Three:
			return "Three";
		case UnoCard::Four:
			return "Four";
		case UnoCard::Five:
			return "Five";
		case UnoCard::Six:
			return "Six";
		case UnoCard::Seven:
			return "Seven";
		case UnoCard::Eight:
			return "Eight";
		case UnoCard::Nine:
			return "Nine";
		case UnoCard::DrawTwo:
			return "DrawTwo";
		case UnoCard::Skip:
			return "Skip";
		case UnoCard::Value::Reverse:
			return "Reverse";
		case UnoCard::Value::Wild_Card:
			return "Wild_Card";
		case UnoCard::Value::Wild_Four:
			return "Wild_Four";
		default:
			return "";
		}

	}
	UnoDeck getPlayerHand(int playerIndex) const
	{
		if (playerIndex < 0 || playerIndex >= numPlayers) {
			throw out_of_range("Invalid player index");
		}

		return playerHand[playerIndex];
	}

	int getCurrentPlayer() const
	{
		return currentPlayer;
	}
};


int main()
{
	SetConsoleTextAttribute(h, 0x97);
	const int numPlayers = 2;
	string playerIds[numPlayers] = {};
	for (int i = 0; i < numPlayers; i++)
	{
		cout << "Enter Player no. " << i + 1 << "'s Name\n";
		cin >> playerIds[i];
	}
	UnoGame unoGame(playerIds, numPlayers); //draw initial cards also done
	unoGame.start();
	unoGame.stockpile.addCardToDeck(unoGame.deck.cards->card);

	while (true)
	{
		string cont;
		cout << "Please 'Enter' to continue\n";
		cin.ignore();
		getline(cin, cont);
		if (cont == "")
		{
			system("cls");// to clear console screen
		}
		unoGame.display();
		int currentPlayer = unoGame.getCurrentPlayer();
		SetConsoleTextAttribute(h, 0x97);
		cout << "Current Player: " << playerIds[currentPlayer] << endl << endl;
		cout << "Top Card: " << unoGame.getTopCard().toString() << endl << endl;
		SetConsoleTextAttribute(h, 0x97);
		cout << "Your Hand: " << unoGame.playerHand[currentPlayer].toString() << endl << endl;
		cout << "=======================================================================================" << endl;

		cout << "Enter your move (play/draw): ";
		string move;
		cin >> move;

		try
		{
			if (move == "play")
			{
				cout << "Enter the card to play: ";
				string cardString;
				cin >> cardString;

				UnoCard card = UnoCard::stringToUnoCard(cardString);

				if (card.getColor() == UnoCard::Wild)
				{
					cout << "Enter the declared color (Red/Blue/Green/Yellow): ";
					string declaredColorStr;
					cin >> declaredColorStr;

					UnoCard::Color declaredColor;

					if (declaredColorStr == "Blue")
						declaredColor = UnoCard::Blue;
					else if (declaredColorStr == "Green")
						declaredColor = UnoCard::Green;
					else if (declaredColorStr == "Red")
						declaredColor = UnoCard::Red;
					else if (declaredColorStr == "Yellow")
						declaredColor = UnoCard::Yellow;
					else if (declaredColorStr == "Wild")
						declaredColor = UnoCard::Wild;
					else
						throw std::runtime_error("Invalid declared color");

					unoGame.playCard(playerIds[currentPlayer], card, declaredColor);
				}
				else
				{
					unoGame.playCard(playerIds[currentPlayer], card, UnoCard::Red);
				}
			}
			else if (move == "draw")
			{
				unoGame.drawCard(playerIds[currentPlayer]);
			}
			else
			{
				cout << "Invalid move. Please enter 'play' or 'draw'." << endl;
			}
		}
		catch (const exception& e)
		{
			cerr << "Error: " << e.what() << endl;
		}
	}

	return 0;
}

