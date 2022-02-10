#include <iostream>
#include <vector>
#include <ctime>
#include <string>

class Card {
    private:
        int rank, suit;
    public:
        Card(int r , int s);
        std::string name(void);
    
    int getRank(void){
        return rank;
    }
    int getSuit(void){
        return suit;
    }
    bool matchSuit(Card * other){
        if(suit == other->getSuit()){
            return true;
        }
        else{
            return false;
        }
    }
    bool matchRank(Card * other){
        if(rank == other->getRank()){
            return true;
        }
        else{
            return false;
        }
    }
    
};

Card::Card(int r, int s) {
    // rank should be a value from 1 to 13, 1 = Ace, 11 = Jack, 12 = Queen, 13 = King
    if(r > 13 || r < 1){
        rank = 1;
    }
    else{
        rank = r;
    }
    /** suit should be a value from 1 to 4
     * 1 = Clubs
     * 2 = Spades
     * 3 = Hearts
     * 4 = Diamonds
     */
    if(s > 4 || s < 1){
        suit = 1;
    }
    else{
        suit = s;
    }
}
// String representation of the card
std::string Card::name(){
    std::string cardname = "";
    // String representation of rank
    std::string rankStr;
    switch(rank){
        case 13:
            rankStr = "King of ";
            break;
        case 12:
            rankStr = "Queen of ";
            break;
        case 11: 
            rankStr = "Jack of ";
            break;
        case 1:
            rankStr = "Ace of ";
            break;
        default:
            // convert the rank (int) to a string
            std::string numberStr = std::to_string(rank);
            rankStr = numberStr + " of "; 
    }

    // String representation of suit
    std::string suitStr;
    switch(suit){
        case 1:
            suitStr = "Clubs";
            break;
        case 2:
            suitStr = "Spades";
            break;
        case 3:
            suitStr = "Hearts";
            break;
        case 4:
            suitStr = "Diamonds";
            break;
        default:
            suitStr = "ERROR";
            break;
    }
    // Concatenate strings
    cardname = rankStr + suitStr;
    return cardname;
}

// swap function for Card pointers
void swap(Card *a, Card *b)
{
    Card temp = *a;
    *a = *b;
    *b = temp;
}
// Bubble sort
void sortHand(Card * h[], int size){
    int i, j;
    for(i = 0; i < size-1; i++){
        
        for(j = 0; j < size-i-1; j++){
            if( h[j]->getRank() > h[j+1]->getRank() )
                swap(h[j], h[j+1]);
        }
    }
}
// find whether hand contains a straight
bool findStraight(Card * h[], int size){
    // keep track of # of consecutive cards
    int ascending = 1;
    
    // if the "smallest" card is an Ace
    if(h[0]->getRank() == 1){
        // start at the next card, after the Ace
        for(int i = 1; i < size-1; i++){
            // if next card is consecutive to current card
            if(h[i]->getRank() == (h[i+1]->getRank())-1 ){
                ascending++;
            }
        }
        
        // if last card is King and all other cards are consecutive
        if(ascending == (size - 1) && h[size-1]->getRank() == 13){
            // then all cards must be consecutive
            ascending++;
        }
        // if above is true but the last card's rank is equal to hand size
        // instead of King
        if(ascending == (size - 1) && h[size-1]->getRank() == size){
            // then all cards must be consecutive
            ascending++;
        }
    }
    else{
        for(int i = 0; i < size-1; i++){
            // if next card is consecutive to current card
            if(h[i]->getRank() == (h[i+1]->getRank())-1 ){
                ascending++;
            }
        }
    }
    
    if(ascending == size)
        return true;
    else
        return false;
}

// find whether a hand has a flush
bool findFlush(Card * h[], int size){
    // # of matching suits
    int flush = 1;

    for(int i = 0; i < size-1; i++){
        if(h[i]->matchSuit(h[i+1])){
            flush++;
        }
    }
    if(flush == size)
        return true;
    else
        return false;
}

int main(){
    // Set up random number generator
    srand((unsigned)time(0));
    int randInt;

    // Create deck
    int deckSize = 52;
    // deck is a vector of Card pointers
    std::vector<Card*> deck;

    for(int i = 1; i < 5; i++){
        for(int j = 1; j < 14; j++){
            // add each card to the back of deck
            deck.push_back(new Card(j, i));
        }
    }

    // Card array for storing the 5 card pointers in hand
    int handsize = 5;
    Card * hand[handsize];
    
   

    for(int i = 0; i < handsize; i++){
        // generate random index from deck vector
        randInt = ((rand() % deck.size()));
        // get Card from that index and put into hand
        hand[i] = deck.at(randInt);
        // remove card from deck, so no duplicates in hand
        deck.erase(deck.begin() + randInt);
    }
    // After populating hand, put cards back into deck (in case multiple hands)
    int deckPosition;
    for(int i = 0; i < handsize; i++){
        // position = [(suit-1) * 13] + (rank-1)
        deckPosition = ( ((hand[i]->getSuit())-1) * 13 ) + 
            ( (hand[i]->getRank())-1 );
        // emplace back into deck
        deck.emplace(deck.begin() + deckPosition, hand[i]);
    }
    // sort hand by rank for simplicity
    sortHand(hand, handsize);

    // Test cases

    // Test #1 - Check if deck generates a card and
    //      that name() works correctly
    if(deck.at(0)->name() == "Ace of Clubs")
        std::cout << "Test #1 Successful." << std::endl;
    else
        std::cout << "Test #1 Failed." << std::endl;

    // Test #2
    /**for(int i = 0; i < handsize; i++){
    *    std::cout << hand[i]->name() << std::endl;
    * }
    */
    // Test #3
    Card * hand_2[] = { new Card(1, 1), new Card(2, 1), new Card(3, 1), new Card(4, 1), new Card(5, 1) };

    if(findStraight(hand_2, 5) == true)
        std::cout << "Test #3 Successful." << std::endl;
    else
        std::cout << "Test #3 Failed." << std::endl;
        
    // Test #4
    Card * hand_3[] = { new Card(1, 2), new Card(2, 1), new Card(3, 4), new Card(4, 1), new Card(5, 3) };

    if(findStraight(hand_2, 5) == true)
        std::cout << "Test #4 Successful." << std::endl;
    else
        std::cout << "Test #4 Failed." << std::endl;
        
    // Test #5
    if(findFlush(hand_2, 5) == true)
        std::cout << "Test #5 Successful." << std::endl;
    else
        std::cout << "Test #5 Failed." << std::endl;    
    
    // Test #6
    Card * hand_4[] = { new Card(3, 2), new Card(2, 2),
        new Card(7, 2), new Card(12, 2), new Card(5, 2) };
    
    if(findFlush(hand_4, 5) == true)
        std::cout << "Test #6 Successful." << std::endl;
    else
        std::cout << "Test #6 Failed." << std::endl;

    return 0;
}



