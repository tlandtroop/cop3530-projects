// Created by Tyler Landtroop on 4/9/2023

#include "graph.h"
#include <iomanip>
#include <iostream>
using namespace std;

void Graph::addEdge(const string &start, const string &end) {
  // Adds the edge from "end" to "start" which represents the indegree of
  // "start"
  pages[end].push_back(start);
  // Adds 1 to the count of outdegrees which is used to calculate the ranks
  outdegrees[start]++;

  // Edge Cases for empty values
  if (outdegrees.find(start) == outdegrees.end()) {
    outdegrees.insert(make_pair(end, 0));
  }
  if (pages.find(start) == pages.end()) {
    pages.insert(make_pair(start, vector<string>{}));
  }
}

void Graph::computePageRank(int powerIterations) {
  // Temporary map that holds the ranks of each page
  map<string, double> newRank;

  // Initialize the ranks to 1 / # of vertices
  map<string, vector<string>>::iterator pageIt = pages.begin();
  while (pageIt != pages.end()) {
    ranks[pageIt->first] = 1.0 / pages.size();
    ++pageIt;
  }
  // Perform power iterations
  for (int i = 1; i < powerIterations; ++i) {
    newRank = ranks;
    // Iterate through the graph
    map<string, vector<string>>::iterator pageIt = pages.begin();
    while (pageIt != pages.end()) {
      // Calculates the total rank of the node
      double total = 0.0;
      // Iterates through the graph
      vector<string>::iterator linkIt = pageIt->second.begin();
      while (linkIt != pageIt->second.end()) {
        // Rank calculation formula
        double rank = ranks[*linkIt] * (1.0 / outdegrees.find(*linkIt)->second);
        total += rank;
        ++linkIt;
      }
      // Updates the page's rank
      newRank[pageIt->first] = total;
      ++pageIt;
    }
    // Update the rank of the page
    ranks = newRank;
  }

  // Sets the decimal to two places
  cout << fixed << setprecision(2);
  // Prints the page ranks
  map<string, double>::const_iterator rankIt = ranks.begin();
  while (rankIt != ranks.end()) {
    cout << rankIt->first << " " << rankIt->second << endl;
    ++rankIt;
  }
}