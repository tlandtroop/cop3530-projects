#include <iomanip>
#include <iostream>
#include <map>
#include <vector>
using namespace std;

class AdjacencyList {
private:
  // Stores our pages in a map
  map<string, vector<pair<string, double>>> pages;

public:
  void addEdge(string &from, string &to);
  void PageRank(int powerIterations);
};

void AdjacencyList::addEdge(string &from, string &to) {
  // Adds an edge from the "from" page to the "to" page with a given weight
  pages[from].push_back(make_pair(to, 1.0));
}

void AdjacencyList::PageRank(int powerIterations) {
  int n = pages.size();

  map<string, double> ranks;
  for (auto page : pages) {
    ranks[page.first] = 1.0 / n;
  }

  for (int i = 0; i < powerIterations; i++) {
    map<string, double> newRanks;

    for (auto page : pages) {
      double newRank = 0.0;
      for (auto link : page.second) {
        newRank += ranks[link.first] / link.second;
      }
      newRanks[page.first] = newRank;
    }

    ranks = newRanks;
  }

  for (auto page : ranks) {
    cout << page.first << " " << fixed << setprecision(2) << page.second
         << endl;
  }
}

int main() {
  int numLines, powerIterations;
  string from, to;

  cin >> numLines;
  cin >> powerIterations;

  AdjacencyList graph;

  for (int i = 0; i < numLines; i++) {
    cin >> from;
    cin >> to;
    graph.addEdge(from, to);
  }

  graph.PageRank(powerIterations);

  return 0;
}