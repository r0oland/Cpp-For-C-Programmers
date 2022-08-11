#include <stdlib.h> /* srand, rand */
#include <iostream>
#include <vector>
#include <fstream>
#include <iterator>
#include <chrono>
#include <array>
#include <cassert>
#include <algorithm>

using namespace std;
using namespace std::chrono;

//------------------------------------------------------------------------------
enum class suit : uint8_t { SPADE, HEART, DIAMOND, CLUB };

//------------------------------------------------------------------------------
class pips {
public:
  pips(int val) : v(val) {
    assert(v >= 1 && v <= 13);
  }

  // overload the << operator for printing
  friend ostream& operator<<(ostream& os, const pips& p);

  int get_pips() const {
    return v;
  }

  // overload postfix ++ operator
  pips operator++(int) {
    pips tmp = *this;
    ++v;
    if (v > 13) {
      v = 1;
    }
    return tmp;
  }

  // overload prefix ++ operator
  pips& operator++() {
    ++v;
    if (v > 13) {
      v = 1;
    }
    return *this;
  }

  // overload != operator
  bool operator!=(const pips& rhs) const {
    return v != rhs.v;
  }

private:
  int v;
};

class card {
public:
  card() : s(suit::SPADE), p(1) {}
  card(suit s, pips p) : s(s), p(p) {}

  friend ostream& operator<<(ostream& os, const card& c);

  suit get_suit() const {
    return s;
  }

  pips get_pips() const {
    return p;
  }
private:
  suit s;
  pips p;
};

ostream& operator<<(ostream& os, const suit& s) {
  switch (s) {
  case suit::SPADE:
    os << "Spades";
    break;
  case suit::HEART:
    os << "Hearts";
    break;
  case suit::DIAMOND:
    os << "Diamonds";
    break;
  case suit::CLUB:
    os << "Clubs";
    break;
  }
  return os;
}

//------------------------------------------------------------------------------
// overload << operator for pips
ostream& operator<<(ostream& os, const pips& p) {
  switch (p.v) {
  case 1:
    os << "Ace";
    break;
  case 11:
    os << "Jake";
    break;
  case 12:
    os << "Queen";
    break;
  case 13:
    os << "King";
    break;
  default:
    os << p.v;
  }
  return os;
}

ostream& operator<<(ostream& os, const card& c) {
  os << c.p << " of " << c.s;
  return os;
}

// initializes a deck of cards
void init_deck(vector<card>& deck) {
  for (int iSuit = 0; iSuit < 4; iSuit++) {
    for (int iPips = 1; iPips <= 13; iPips++) {
      deck.push_back(card(static_cast<suit>(iSuit), pips(iPips)));
    }
  }
}

// print out the deck
void print_deck(const vector<card>& deck) {
  for (const auto& c : deck) {
    cout << c << endl;
  }
}

bool is_flush(const vector<card> hand){
  // make sure hand has at least 5 cards
  if (hand.size() < 5) {
    return false;
  }
  // make sure to only check the first 5 cards
  for (int i = 0; i < 5; i++){
    if (hand[i].get_suit() != hand[i+1].get_suit()){
      return false;
    }
  }
  return true;
}

bool is_straight(const vector<card> hand){
  // make sure hand has at least 5 cards
  if (hand.size() < 5) {
    return false;
  }

  // extract and sort the first 5 cards
  vector<pips> pips_hand;
  for (int i = 0; i < 5; i++){
    pips_hand.push_back(hand[i].get_pips());
  }
  sort(pips_hand.begin(), pips_hand.end());
  
  //only check the first 5 cards
  for (int i = 0; i < 5; i++){
    pips thisPips = hand[i].get_pips();
    pips nextPips = hand[i+1].get_pips();
    if (++thisPips != nextPips){
      cout << thisPips << " != " << nextPips << endl;
      return false;
    } else {
      cout << thisPips << " == " << nextPips << endl;
    }
  }
  return true;
}

//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
int main() {
  // create a deck of cards
  vector<card> deck;
  init_deck(deck);

  vector<card> hand;
  hand.push_back(deck[0]);

  cout << "Is the deck a flush? " << is_flush(deck) << endl;
  cout << "Is the deck a flush? " << is_straight(deck) << endl;
}