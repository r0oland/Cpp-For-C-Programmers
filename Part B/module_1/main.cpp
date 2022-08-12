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

  // overload < operator
  bool operator<(const pips& rhs) const {
    return v < rhs.v;
  }

  // overload == operator
  bool operator==(const pips& rhs) const {
    return v == rhs.v;
  }

private:
  int v;
};

//------------------------------------------------------------------------------
class card {
public:
  card() : s(suit::SPADE), p(1) {
  }
  card(suit s, pips p) : s(s), p(p) {
  }

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

//------------------------------------------------------------------------------
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

ostream& operator<<(ostream& os, const vector<card>& v) {
  for (const auto& c : v) {
    os << c << endl;
  }
  return os;
}

ostream& operator<<(ostream& os, const vector<pips>& v) {
  for (const auto& p : v) {
    os << p << endl;
  }
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

bool is_flush(const vector<card> hand) {
  // make sure hand has at least 5 cards
  if (hand.size() < 5) {
    cout << "Not enough cards to check for a flush" << endl;
    return false;
  } else {
    // cout << "Hand has " << hand.size() << " cards" << endl;
  }

  // cout << "Checking for a flush...";

  // make sure to only check the first 5 cards, but we are looking +1 so
  // we only have to make 4 checks and not 5...
  for (int i = 0; i < 4; i++) {
    if (hand[i].get_suit() != hand[i + 1].get_suit()) {
      // cout << "Not a flush" << endl;
      return false;
    }
  }
  // cout << "Flush!" << endl;
  return true;
}

bool is_straight(const vector<card> hand) {
  // make sure hand has at least 5 cards
  if (hand.size() < 5) {
    return false;
  }

  // cout << "Checking for a straigth...";

  // extract and sort the first 5 cards
  vector<pips> pipsHand;
  for (int i = 0; i < 5; i++) {
    pipsHand.push_back(hand[i].get_pips());
  }

  // sort hand in ascending order
  sort(pipsHand.begin(), pipsHand.end());

  // handle case where high card is an ace
  if (pipsHand.back() == 13 && pipsHand[0] == 1) {
    // move ace from the front to the back
    std::rotate(pipsHand.begin(),pipsHand.begin()+1,pipsHand.end());
  }

  // only check the first 5 cards, i.e. check for 4 matches
  for (int i = 0; i < 4; i++) {
    pips thisPips = pipsHand[i];
    pips nextPips = pipsHand[i + 1];
    if (++thisPips != nextPips) {
      // cout << "Not a Straight!" << endl;
      return false;
    }
  }
  // cout << "Straight!" << endl;
  return true;
}

//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
int main() {
  // init random seed
  srand(time(NULL));
  // create a deck of cards
  vector<card> deck;
  init_deck(deck);

  constexpr int NUM_SHUFFLE = 1000000;
  
  int straightCount = 0;
  int flushCount = 0;
  int straightFlushCount = 0;

  for (int iShuffle = 0; iShuffle <= NUM_SHUFFLE; iShuffle++) {
    // shuffle the deck
    random_shuffle(deck.begin(), deck.end());
    // pick 5 cards at random and build a hand
    vector<card> hand;
    for (int i = 0; i < 5; i++) {
      hand.push_back(deck[i]);
    }
    bool isStraight = is_straight(hand);
    bool isFlush = is_flush(hand);
    if (isStraight) {
      straightCount++;
    }
    if (isFlush) {
      flushCount++;
    }
    if (isStraight && isFlush) {
      straightFlushCount++;
    }
  }
  cout << "Number of times straight: " << straightCount << endl;
  cout << "Number of times flush: " << flushCount << endl;
  cout << "Number of times straight flush: " << straightFlushCount << endl;
}