#include <iostream>
#include <vector>
#include <random>
#include <algorithm>
#include <ctime>
enum Suit
{
    DIAMOND,
    CLUBS,
    HEARTS,
    SPADE
};

enum Value
{
    TWO = 2,
    THREE,
    FOUR,
    FIVE,
    SIX,
    SEVEN,
    EIGHT,
    NINE,
    TEN,
    JACK,
    QUEEN,
    KING,
    ACE
};
class Card
{
private:
    Value V;
    Suit S;

public:
    Card() : V(TWO), S(CLUBS) {}
    Card(Value value, Suit suit) : V(value), S(suit) {}

    Value getValue() const { return V; }
    Suit getSuit() const { return S; }
    std::string valueToString() const
    {
        switch (V)
        {
        case TWO:
            return "2";
        case THREE:
            return "3";
        case FOUR:
            return "4";
        case FIVE:
            return "5";
        case SIX:
            return "6";
        case SEVEN:
            return "7";
        case EIGHT:
            return "8";
        case NINE:
            return "9";
        case TEN:
            return "10";
        case JACK:
            return "Jack";
        case QUEEN:
            return "Queen";
        case KING:
            return "King";
        case ACE:
            return "Ace";
        default:
            return "Unknown";
        }
    }

    std::string suitToString() const
    {
        switch (S)
        {
        case DIAMOND:
            return "Diamonds";
        case CLUBS:
            return "Clubs";
        case HEARTS:
            return "Hearts";
        case SPADE:
            return "Spades";
        default:
            return "Unknown";
        }
    }

    void printCard() const
    {
        std::cout << valueToString() << " of " << suitToString() << '\t';
    }
};
class Deck
{
private:
    std::vector<Card> deck;

public:
    Deck()
    {
        for (int i = 0; i < 4; i++)
        {
            for (int j = 2; j < 15; j++)
            {
                deck.push_back(Card(static_cast<Value>(j), static_cast<Suit>(i)));
            }
        }
        Shuffle();
    }
    void Shuffle()
    {
        std::mt19937 rng(time(NULL));

        std::shuffle(deck.begin(), deck.end(), rng);
    }
    Card drawCard()
    {
        Card topCard = deck.back();
        deck.pop_back();
        return topCard;
    }
};
class Hand
{
private:
    Card cards[2];
    int count;

public:
    Hand()
    {
        count = 0;
    }
    void addCard(Card card)
    {
        if (count < 2)
        {
            cards[count] = card;
            count++;
        }
    }

    Card getCard(int index) const
    {
        return cards[index];
    }

    int getCount() const
    {
        return count;
    }
    void showHand()
    {
        for (int i = 0; i < count; i++)
        {
            cards[i].printCard();
        }
        std::cout << "\n";
    }
    void clear()
    {
        count = 0;
    }
};

class CommunityCards
{
private:
    std::vector<Card> community;

public:
    CommunityCards(Deck &deck)
    {
        flop(deck);
    }

    void flop(Deck &deck)
    {
        if (community.empty())
        {
            for (int i = 0; i < 3; i++)
            {
                community.push_back(deck.drawCard());
                community.back().printCard();
                // std::cout<< "\n";
            }
        }
    }

    void turn(Deck &deck)
    {
        if (community.size() == 3)
        {
            community.push_back(deck.drawCard());
            community.back().printCard();
            // std::cout<< "\n";
        }
    }

    void river(Deck &deck)
    {
        if (community.size() == 4)
        {
            community.push_back(deck.drawCard());
            community.back().printCard();
            std::cout << "\n";
        }
    }
};
class Player
{
private:
    std::string name;
    Hand hand;
    int chips;

public:
    Player(std::string playerName, int startingChips)
        : name(playerName), chips(startingChips) {}

    void receiveCard(Card card)
    {
        hand.addCard(card);
    }

    void showPlayerHand()
    {
        std::cout << name << "'s Hand:\n";
        hand.showHand();
    }

    // Simple betting helper
    bool bet(int amount, int &pot)
    {
        if (amount > chips)
        {
            std::cout << name << " doesn't have enough chips!\n";
            return false;
        }
        chips -= amount;
        pot += amount;
        std::cout << name << " bets " << amount << " chips.\n";
        return true;
    }
    void resetForNewHand()
    {
        hand.clear();
    }
    int getChips() const { return chips; }
    std::string getName() const { return name; }
};

class Game
{
private:
    Player p1;
    Player p2;
    int pot;

public:
    Game(std::string name1, std::string name2, int startingChips)
        : p1(name1, startingChips), p2(name2, startingChips), pot(0) {}

    void round()
    {
        pot = 0;
        p1.resetForNewHand();
        p2.resetForNewHand();

        Deck maindeck; 
        p1.receiveCard(maindeck.drawCard());
        p2.receiveCard(maindeck.drawCard());
        p1.receiveCard(maindeck.drawCard());
        p2.receiveCard(maindeck.drawCard());

        p1.showPlayerHand();
        std::cout << "\n";
        p2.showPlayerHand();


        std::cout << "\n--- Pre-Flop Betting ---\n";
        p1.bet(50, pot);
        p2.bet(50, pot);
        std::cout << "Total Pot: " << pot << " chips\n\n";

        // 4. Community cards
        std::cout << "--- Community Board ---\n";
        CommunityCards board(maindeck);
        board.turn(maindeck);
        board.river(maindeck);
    }
};
int main()
{
    Game r1("Jay","Alice",1000);
    r1.round();
    return 0;
}