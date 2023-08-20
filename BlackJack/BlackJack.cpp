#include <algorithm>  // std::shuffle
#include <array>
#include <cassert>
#include <ctime>  // std::time
#include <iostream>
#include <random>  // std::mt19937

// Maximum score before losing.
constexpr int g_maximumScore{21};

// Minimum score that the dealer has to have.
constexpr int g_minimumDealerScore{17};

// Cash at the start of a new game.
constexpr unsigned int g_cashAtStart{100};

class Card {
 public:
  enum Suit {
    club,
    diamond,
    heart,
    spade,

    max_suits
  };

  enum Rank {
    rank_2,
    rank_3,
    rank_4,
    rank_5,
    rank_6,
    rank_7,
    rank_8,
    rank_9,
    rank_10,
    rank_jack,
    rank_queen,
    rank_king,
    rank_ace,

    max_ranks
  };

 private:
  Rank m_rank{};
  Suit m_suit{};

 public:
  Card() = default;
  Card(Rank rank, Suit suit) : m_rank{rank}, m_suit{suit} {}

  void print() const {
    switch (m_rank) {
      case Rank::rank_2:
        std::cout << '2';
        break;
      case Rank::rank_3:
        std::cout << '3';
        break;
      case Rank::rank_4:
        std::cout << '4';
        break;
      case Rank::rank_5:
        std::cout << '5';
        break;
      case Rank::rank_6:
        std::cout << '6';
        break;
      case Rank::rank_7:
        std::cout << '7';
        break;
      case Rank::rank_8:
        std::cout << '8';
        break;
      case Rank::rank_9:
        std::cout << '9';
        break;
      case Rank::rank_10:
        std::cout << 'T';
        break;
      case Rank::rank_jack:
        std::cout << 'J';
        break;
      case Rank::rank_queen:
        std::cout << 'Q';
        break;
      case Rank::rank_king:
        std::cout << 'K';
        break;
      case Rank::rank_ace:
        std::cout << 'A';
        break;
      default:
        std::cout << '?';
        break;
    }

    switch (m_suit) {
      case Suit::club:
        std::cout << 'C';
        break;
      case Suit::diamond:
        std::cout << 'D';
        break;
      case Suit::heart:
        std::cout << 'H';
        break;
      case Suit::spade:
        std::cout << 'S';
        break;
      default:
        std::cout << '?';
        break;
    }
  }

  int value() const {
    switch (m_rank) {
      case Rank::rank_2:
        return 2;
      case Rank::rank_3:
        return 3;
      case Rank::rank_4:
        return 4;
      case Rank::rank_5:
        return 5;
      case Rank::rank_6:
        return 6;
      case Rank::rank_7:
        return 7;
      case Rank::rank_8:
        return 8;
      case Rank::rank_9:
        return 9;
      case Rank::rank_10:
        return 10;
      case Rank::rank_jack:
        return 10;
      case Rank::rank_queen:
        return 10;
      case Rank::rank_king:
        return 10;
      case Rank::rank_ace:
        return 11;
      default:
        assert(false && "should never happen");
        return 0;
    }
  }

  char suit() const {
    switch (m_suit) {
      case Suit::club:
        return 'C';
        break;
      case Suit::diamond:
        return 'D';
        break;
      case Suit::heart:
        return 'H';
        break;
      case Suit::spade:
        return 'S';
        break;
      default:
        assert(false && "should never happen");
        return '?';
    }
  }
};

class Deck {
 public:
  using DeckType = std::array<Card, 52>;
  using Index = DeckType::size_type;

 private:
  DeckType m_deck{};
  Index m_nextCardIndex{};

 public:
  Deck() : m_nextCardIndex{0} {
    Index index{0};
    for (int suit{0}; suit < static_cast<int>(Card::Suit::max_suits); suit++) {
      for (int rank{0}; rank < static_cast<int>(Card::Rank::max_ranks);
           rank++) {
        m_deck[index] = {static_cast<Card::Rank>(rank),
                         static_cast<Card::Suit>(suit)};
        index++;
      }
    }
  }
  ~Deck() {}

  void print() const {
    for (auto& card : m_deck) {
      card.print();
      std::cout << ' ';
    }
    std::cout << '\n';
  }

  void shuffle() {
    static std::mt19937 mt{
        static_cast<std::mt19937::result_type>(std::time(nullptr))};
    std::shuffle(m_deck.begin(), m_deck.end(), mt);
    m_nextCardIndex = 0;
  }

  const Card& deal() {
    assert(m_nextCardIndex < m_deck.size() && "All cards Have been dealt");
    return m_deck[m_nextCardIndex++];
  }
};

class Player {
 private:
  int m_score{};
  unsigned int m_money{};

 public:
  Player() : m_score{0}, m_money{g_cashAtStart} {}
  int draw(Deck& deck) {
    int value = deck.deal().value();
    m_score += value;
    return value;
  }

  int score() const { return m_score; }

  unsigned int money() const { return m_money; }

  void removeBetMoney(unsigned int betMoney) {
    if (betMoney > m_money) {
      std::cout << "You don't have that much going all in..." << std::endl;
      m_money = 0;
      return;
    }
    m_money -= betMoney;
  }

  void addMoney(unsigned int wonMoney) { m_money += wonMoney; }

  bool isBust() const { return m_score > g_maximumScore; }

  void resetScore() { m_score = 0; }
};

bool playerWantsHit() {
  std::cout << "(h) to hit, or (s) to stand: ";
  while (true) {
    char ch{};
    std::cin >> ch;

    switch (ch) {
      case 'h':
        return true;
      case 's':
        return false;
    }
  }
}

// Returns true if the player went bust. False otherwise.
bool playerTurn(Deck& deck, Player& player) {
  while (true) {
    if (player.score() > g_maximumScore) {
      // This can happen even before the player had a choice if they drew 2
      // aces.
      std::cout << "You busted!\n";
      return true;
    } else {
      if (playerWantsHit()) {
        int cardValue{player.draw(deck)};
        std::cout << "You were dealt a " << cardValue << " and now have "
                  << player.score() << '\n';
      } else {
        // The player didn't go bust.
        return false;
      }
    }
  }
}

// Returns true if the dealer went bust. False otherwise.
bool dealerTurn(Deck& deck, Player& dealer) {
  // Draw cards until we reach the minimum value.
  while (dealer.score() < g_minimumDealerScore) {
    int cardValue{dealer.draw(deck)};
    std::cout << "The dealer turned up a " << cardValue << " and now has "
              << dealer.score() << '\n';
  }

  // If the dealer's score is too high, they went bust.
  if (dealer.score() > g_maximumScore) {
    std::cout << "The dealer busted!\n";
    return true;
  }

  return false;
}

// returns true if player want to play again otherwise false
// also shuffle the cards, reset players score, bets and results if playing
// again
bool playAgain(Deck& deck, std::vector<bool>& results,
               std::vector<Player>& players, std::vector<unsigned int>& bets) {
  std::cout << "(y) to Play again, (n) to stop: ";
  char ch{};
  while (true) {
    std::cin >> ch;
    if (ch == 'y' || ch == 'n') break;
  }
  if (ch == 'n') {
    return false;
  } else {
    std::cout << "shuffling ...." << std::endl;
    deck.shuffle();
    std::for_each(std::next(players.begin()), players.end(),
                  [](Player& player) { player.resetScore(); });
    std::for_each(std::next(results.begin()), results.end(),
                  [](auto&& result) { result = true; });
    std::for_each(std::next(bets.begin()), bets.end(),
                  [](unsigned int& bet) { bet = 0; });
    return true;
  }
}

void updateMoney(std::vector<bool>& results, std::vector<Player>& players,
                 std::vector<unsigned int>& bets) {
  for (std::size_t i{1}; i < results.size(); i++) {
    if (results[i]) {
      players[i].addMoney(2 * bets[i]);
    }
  }
}

void showResults(std::vector<bool>& results, std::vector<Player>& players,
                 std::vector<int>& inGame) {
  std::cout << "###########################################" << std::endl;
  for (std::size_t i{1}; i < results.size(); i++) {
    if (inGame[i]) {
      if (results[i]) {
        std::cout << "Player" << i << " Won!!!" << std::endl;

      } else {
        std::cout << "Player" << i << " Lost :(" << std::endl;
      }
      std::cout << "Player" << i << " Now have ₹" << players[i].money()
                << std::endl;
    }
  }
  std::cout << "###########################################" << std::endl;
}

// Enter deck and results, players and bets vector
void playBlackjack(Deck& deck, std::vector<bool>& results,
                   std::vector<Player>& players,
                   std::vector<unsigned int>& bets, std::vector<int> inGame) {
  std::cout << "###########################################" << std::endl;
  // is true if all players are out of money
  bool AllOutOfMoney = true;
  for (std::size_t i{1}; i < players.size(); i++) {
    std::cout << "Player" << i << " have: ₹" << players[i].money() << std::endl;
    if (players[i].money() == 0) {
      std::cout << "You are out of money." << std::endl;
      inGame[i] = 0;
      continue;
    }
    AllOutOfMoney = false;
    std::cout << "Place your bet: ";
    std::cin >> bets[i];
    players[i].removeBetMoney(bets[i]);
  }

  if (AllOutOfMoney) {
    return;
  }

  Player dealer{};
  dealer.draw(deck);
  std::cout << "###########################################" << std::endl;
  std::cout << "The dealer is showing: " << dealer.score() << '\n';
  for (int j{0}; j < 2; j++) {
    for (std::size_t i{1}; i < players.size(); i++) {
      if (inGame[i]) players[i].draw(deck);
    }
  }

  for (std::size_t i{1}; i < players.size(); i++) {
    if (inGame[i])
      std::cout << "Player" << i << " have: " << players[i].score()
                << std::endl;
    else
      std::cout << "Player" << i << " is out of the game. " << std::endl;
  }

  for (std::size_t i{1}; i < players.size(); i++) {
    if (inGame[i]) {
      std::cout << "###########################################" << std::endl;
      std::cout << "Player" << i << ": " << std::endl;
      if (playerTurn(deck, players[i])) {
        results[i] = false;
      }
    }
  }

  std::cout << "###########################################" << std::endl;
  if (dealerTurn(deck, dealer)) {
    updateMoney(results, players, bets);
    showResults(results, players, inGame);
    if (playAgain(deck, results, players, bets)) {
      playBlackjack(deck, results, players, bets, inGame);
    } else {
      return;
    }
  } else {
    for (std::size_t i{1}; i < players.size(); i++) {
      if (results[i] && players[i].score() > dealer.score()) {
        results[i] = true;
      } else {
        results[i] = false;
      }
    }
    updateMoney(results, players, bets);
    showResults(results, players, inGame);
    if (playAgain(deck, results, players, bets)) {
      playBlackjack(deck, results, players, bets, inGame);
    } else {
      return;
    }
  }
}

int main() {
  Deck deck{};
  deck.shuffle();
  int noOfPlayers;
  std::cout << "Enter No. of Players: ";
  std::cin >> noOfPlayers;
  assert(noOfPlayers > 0 and noOfPlayers < 9 &&
         "# of players can only be 1 to 8");

  // Note that players.size is 1 greater than no. of players
  std::cout << "At start all players have ₹ 100 and dealer have unlimited."
            << std::endl;
  std::vector<Player> players(static_cast<std::size_t>(noOfPlayers + 1));
  std::vector<bool> results(static_cast<std::size_t>(noOfPlayers + 1), true);
  std::vector<unsigned int> bets(static_cast<std::size_t>(noOfPlayers + 1));
  // ith entry is 1 if player is In game otherwise 0
  std::vector<int> inGame(static_cast<std::size_t>(noOfPlayers + 1), 1);
  playBlackjack(deck, results, players, bets, inGame);
  std::cout << "Game Over Good bye!!!" << std::endl;
  return 0;
}
