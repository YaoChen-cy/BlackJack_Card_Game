# include <iostream>
#include <vector>
#include <string>
# include <cstdlib>
# include <time.h>

using namespace std;

//a class represent a card
class Card {
    public:
    //define the ranke of a card
    enum Rank{ACE = 1, TWO, THREE, FOUR, FIVE, SIX, SEVEN, EIGHT, NINE, TEN, JACK, QUEEN, KING};
    //define the type(suit) of a card
    enum Type{CLUBS, DIAMONDS, HEARTS, SPADES};

    //a default constructor of a card
    Card(){}
    //a self-defined constructor of a card
    Card(Rank rank,Type type);

    //declaration of methods
    int getValue() const;
    void displayCard();

    //data mumbers of a card
    Rank rank;
    Type type;
};
//a self-defined constructor of a card
Card::Card(Rank rank,Type type){
    this->rank=rank;
    this->type=type;
}
//a method that return the numerical value of a card
int Card::getValue()const{
    //jake,queen,king consider as rank of 10
    if (this->rank>10){
        return 10;
    }
    return this->rank;
}
//a method that print the card info to the screen
void Card::displayCard(){
    //for the card smaller than 10, print their rank directly
    if(this->getValue()<10){
        cout<<this->rank;
    }
    else{
        //print the first letter of jack
        if(this->rank==Card::JACK){
            cout<<"J";
        }
        //print the first letter of queen
        else if(this->rank==Card::QUEEN){
            cout<<"Q";
        }
        //print the rank value if ten
        else if(this->rank==Card::TEN){
            cout<<"10";
        }
        //print the first letter of king
        else if(this->rank==Card::KING){
            cout<<"K";
        }
    }
    //print the first letter of the type of card
    if(this->type==Card::SPADES){
        cout<<"S";
    }
    else if(this->type==Card::CLUBS){
        cout<<"C";
    }
    else if(this->type==Card::DIAMONDS){
        cout<<"D";
    }
    else if(this->type==Card::HEARTS){
        cout<<"H";
    }
}

//a class represent the set of cards that players or the computer holds
class Hand {
    public:
    //a default construstor
    Hand(){};

    //define a vector contains a list of cards
    std::vector<Card> cardList;

    //declaration of methods
    void add(Card card);
    void clear();
    int getTotal() const;
};
//a method that add a card to the hand
void Hand::add(Card card){
    this->cardList.push_back(card);
}
//a method that clear all cards from a hand
void Hand::clear(){
    this->cardList.clear();
}
//a method that get the total sum of the cards numerical values of a hand
int Hand::getTotal()const{
    int result=0;
    //iterate the cardlist,add up the rank of each card in the hand
    for (int i = 0; i < this->cardList.size(); i++){
        result+=this->cardList[i].getValue();
    }
    return result;
}

//a class represent the decks of cards
class Deck :public Hand {
    public:
    //a default constructor
    Deck(){};

    //a vector that contains a deck
    std::vector<Card> deck;

    //declaration of methods
    void Populate();
    void shuffle();
    void deal(Hand* hand1);
    
    //a data mumber represent a card
    Card card;
};

//a method that create a  standard deck of 52 cards
void Deck::Populate(){
    //for each rank of a card
    for(int k = 0; k < 13; k++){
        if(k==0){
            this->card.rank=Card::ACE;
        }
        else if(k==1){
            this->card.rank=Card::TWO;
        }
        else if(k==2){
            this->card.rank=Card::THREE;
        }
        else if(k==3){
            this->card.rank=Card::FOUR;
        }
        else if(k==4){
            this->card.rank=Card::FIVE;
        }
        else if(k==5){
            this->card.rank=Card::SIX;
        }
        else if(k==6){
            this->card.rank=Card::SEVEN;
        }
        else if(k==7){
            this->card.rank=Card::EIGHT;
        }
        else if(k==8){
            this->card.rank=Card::NINE;
        }
        else if(k==9){
            this->card.rank=Card::TEN;
        }
        else if(k==10){
            this->card.rank=Card::JACK;
        }
        else if(k==11){
            this->card.rank=Card::QUEEN;
        }
        else if(k==12){
            this->card.rank=Card::KING;
        }
        //for each type of a card
        for (int i = 0; i < 4; i++){
            if(i==0){
                this->card.type=Card::CLUBS;
            }
            else if (i==1){
                this->card.type=Card::DIAMONDS;
            }
            else if (i==2){
                this->card.type=Card::HEARTS;
            }
            else if (i==3){
                this->card.type=Card::SPADES;
            }
            //add a card to the deck
            this->deck.push_back(this->card);
        }
    }
}
//a method that shuffle the cards
void Deck::shuffle(){
    // set a different seed
    //get different number everytime when calling this method
    srand((unsigned)time(0));
    //iterate each card from the deck
	for (int i=0;i<52;i++) 
        //swap the position of the current card with a random card in this deck
		swap(this->deck[i], this->deck[rand() % 52]);  
}
//a method that deal one card to a hand
void Deck::deal(Hand* hand1){
    //add the first card from the deck to the input hand
    hand1->add(this->deck.front());
    //remove the first card from the deck
	this->deck.erase(deck.begin());
}

//a class represent a abstract player(human or computer)
class AbstractPlayer : public Hand {
    public:
    //a default constructor and destructor
    AbstractPlayer(){};
    virtual ~AbstractPlayer(){};

    //a pure virtual method that indicates whether a player
    // want to draw another card
    virtual bool isDrawing() const =0;

    //declaration of methods
    bool isBusted();
};
//a method that represnet whether a player has busted
bool AbstractPlayer::isBusted(){
    //if sum of cardss exceeds 21, a player busted
    if(this->getTotal()>21){
        return true;
    }
    //otherwise,a player not busted
    return false;
}

//a class represents the human player. This class inherits AbstractPlayer
class HumanPlayer : public AbstractPlayer{
    public:
    //a default constructor and destrcutor
    HumanPlayer(){};
    virtual ~HumanPlayer(){};

    //declaration of methods
    virtual bool isDrawing()const;
    void announce();
};
//a method implements the inherited method that 
//indicates whether a player wants to draw another card
bool HumanPlayer::isDrawing()const{
    //a string use to store the input from human player
    std::string answer;
    //print a message tp screen that ask for answer
    cout<<"DO you want to draw? (y/n):";
    cin>>answer;
    //if player does not want to draw another card, return false
    if(answer.compare("y")!=0){
        return false;
    }
    //otherwise, return true
    return true;
}
//a method that prints information about 
//whether the player wins, loses or had a push situation
void HumanPlayer::announce(){
    if(this->getTotal()>21){
        cout<<"Player busts."<<endl<<"Casino wins."<<endl;
    }
    else if (this->getTotal()<21){
        cout<<"Computer busts."<<endl<<"Player wins."<<endl;
    }
    else{
        cout<<"Push: No one wins."<<endl;
    }

}

//a class that represents the computer (the casino)
//This class inherits AbstractPlayer 
class ComputerPlayer : public AbstractPlayer {
    public:
    //declaration of methods
    virtual bool isDrawing()const;
    ComputerPlayer(){};

    //a virtual destructor
    virtual ~ComputerPlayer(){};
};
//a method that implements the inherited method that 
//indicates whether the computer should be drawing another card
bool ComputerPlayer::isDrawing()const{
    //if the sum of cards is less or equal to 16,
    //computer should draw another card
    if(this->getTotal()<=16){
        return true;
    }
    return false;
}

//a class represent the overall game
class BlackJackGame {
    public:
    //a data mumber represent a deck of card
    Deck m_deck;
    //a data mumber represent a computer player
    ComputerPlayer m_casino;
    //a default constructor and descructor
    BlackJackGame(){};
    ~BlackJackGame(){};
    //declaration of methods
    void play();
};
//a method playes the game of blackjack
void BlackJackGame::play(){
    //create a variable of human player
    HumanPlayer player;
    //clear all cards of casino for a new round
    m_casino.clear();
    //create a standard deck of 52 cards
    m_deck.Populate();
    //shuffle the cards of the deck
    m_deck.shuffle();
    //deal a card to player
    m_deck.deal(&player);
    //deal a card to casino
    m_deck.deal(&m_casino);
    //print the card info of casino to the screen
    cout<<"Casino: ";
    for (int i=0;i<m_casino.cardList.size();i++){
        m_casino.cardList[i].displayCard();
        cout<<" ";
    }
    cout<<"["<<m_casino.getTotal()<<"]"<<endl;
    //deal another card to player
    m_deck.deal(&player);
    //print the card info of player to the screen
    cout<<"Player: ";
    for (int i=0;i<player.cardList.size();i++){
        player.cardList[i].displayCard();
        cout<<" ";
    }
    cout<<"["<<player.getTotal()<<"]"<<endl;
    //while player wants to draw another card
    while(player.isDrawing()){
        //deal a card to player
        m_deck.deal(&player);
        //print the current cards info of player to screen
        cout<<"Player: ";
        for (int i=0;i<player.cardList.size();i++){
            player.cardList[i].displayCard();
            cout<<" ";
        }
        cout<<"["<<player.getTotal()<<"]"<<endl;
        //if the player busted, make an announce 
        if(player.isBusted()){
            player.announce();
            return;
        }
    }
    //while a computer decide to draw ome more card
    while(m_casino.isDrawing()){
        //deal a card to casino
        m_deck.deal(&m_casino);
        //print the current cards info to screen
        cout<<"Casino: ";
        for (int i=0;i<m_casino.cardList.size();i++){
            m_casino.cardList[i].displayCard();
            cout<<" ";
        }
        cout<<"["<<m_casino.getTotal()<<"]"<<endl;
        //if the casino busted, make an announce 
        if(m_casino.isBusted()){
            player.announce();
            return;
        }
    }
    //if no one busted for this round, 
    //print a result of this round to the creen
    //if the player and casino end up with the same points
    if(player.getTotal()==m_casino.getTotal()){
        cout<<"Push: No one wins."<<endl;
    }
    //if the player end up with more points than casino
    else if(player.getTotal()>m_casino.getTotal()){
        cout<<"Player wins."<<endl;
    }
    //if the player end up with less points than casino
    else{
        cout<<"Computer wins."<<endl;
    }
    //clear the hand for both player and computer for a new round
    player.clear();
    m_casino.clear();
}
int main(){
    cout << "Welcome to the Comp322 Blackjack game!" << endl;
    BlackJackGame game;
    // The main loop of the game
    bool playAgain = true; char answer = 'y'; while (playAgain)
    {
        game.play();
        cout << endl << endl;
        // Check whether the player would like to play another round
        cout << "Would you like another round? (y/n): "; 
        cin >> answer;
        
        playAgain = (answer == 'y' ? true : false);
    }
    cout <<"Gave over!";
    return 0;
}
