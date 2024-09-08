#include <bits/stdc++.h>

#include "my_headers/debugging.h"
#define debug(x) \
  cout << "Line(" << __LINE__ << ") -> " << #x << " = " << (x) << '\n'

using namespace std;

int n, m, alive;
const char* filled = "██";
const char* hollow = "  ";
vector<vector<bool>> grid;
ifstream inFile("input.txt");

void takeInputFromFile() {
  if (!inFile.is_open()) {
    cerr << "Error opening file(s)" << endl;
    exit(1);
  }

  inFile >> n >> m;
  grid.resize(n, vector<bool>(m, false));
  char ch;
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < m; ++j) {
      inFile.get(ch);  // Get the empty char
      inFile.get(ch);
      if (ch == 'o') {
        grid[i][j] = true;
        ++alive;
      }
    }
  }
}

void printGrid() {
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < m; ++j) {
      cout << (grid[i][j] ? filled : hollow);
    }
    cout << endl;
  }
}

void updateGrid() {
  vector<vector<bool>> copy(n, vector<bool>(m, false));
  alive = 0;
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < m; ++j) {
      int neighbours = 0;
      // Check the 4 orthogonal neighbors
      if (i > 0 && grid[i - 1][j]) ++neighbours;      // T
      if (j < m - 1 && grid[i][j + 1]) ++neighbours;  // R
      if (i < n - 1 && grid[i + 1][j]) ++neighbours;  // D
      if (j > 0 && grid[i][j - 1]) ++neighbours;      // L

      // Check the 4 diagonal neighbors
      if (i > 0 && j < m - 1 && grid[i - 1][j + 1]) ++neighbours;      // TR
      if (i < n - 1 && j < m - 1 && grid[i + 1][j + 1]) ++neighbours;  // DR
      if (i < n - 1 && j > 0 && grid[i + 1][j - 1]) ++neighbours;      // DL
      if (i > 0 && j > 0 && grid[i - 1][j - 1]) ++neighbours;          // TL
      switch (neighbours) {
        case 2:
          copy[i][j] = grid[i][j];
          break;
        case 3:
          copy[i][j] = true;
          break;
        case 4:
          copy[i][j] = false;
          break;
        default:
          break;
      }
      if (copy[i][j]) ++alive;
    }
  }
  grid = copy;
}

void generateRandomInput() {
  int p;
  cout << "Enter row, column, %: ";
  cin >> n >> m >> p;
  grid.resize(n, vector<bool>(m, false));
  // Seed the random number generator
  srand(time(0));
  // Fill the grid with random values based on the probability
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < m; ++j) {
      // Generate a random number and compare it with the probability
      if (rand() % 100 < p) {
        grid[i][j] = true;  // Cell is alive
        ++alive;
      } else {
        grid[i][j] = false;  // Cell is dead
      }
    }
  }
}

int main() {
  ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);

  char userChoice;
  cout << "Would you like to generate random input? (y/n): ";
  cin >> userChoice;
  if (userChoice == 'y') {
    generateRandomInput();
  } else if (userChoice == 'n') {
    takeInputFromFile();
  } else {
    while (true) cout << "Maa chuda bkl\n";
  }
  cout << "\033[s";
  // Print the initial grid to the output file
  printGrid();

  char choice;
  int count = 0;
  do {
    cout << "Gen: " << count++ << ", " << "Alive: " << alive << '\n';
    cout << "Next:  " << flush;
    cout << "\033[1D";
    choice = cin.get();
    cout << "\033[u";
    if (choice == '\n') {
      updateGrid();
      printGrid();
    }

  } while (choice == '\n');

  inFile.close();

  return 0;
}
