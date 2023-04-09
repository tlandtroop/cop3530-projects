// Created by Tyler Landtroop on 4/9/2023


#include <iomanip>
#include <iostream>
#include <map>
#include <vector>
using namespace std;

class Graph {
private:
  // Stores the nodes in a graph
  map<string, vector<string>> pages;
  // Stores the number of out degrees a certain node has
  map<string, int> outdegrees; 
  // Stores the calculated ranks of the pages
  map<string, double> ranks;

public:
  void addEdge(const string &start, const string &end);
  void computePageRank(int powerIterations);
};

void Graph::addEdge(const string &start, const string &end) {
  // Adds the edge source "to" to "source" which represents the indegree of "source"
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
  // Initialize the ranks to 1 / # of vertices
  for (const auto& page : pages) {
    ranks[page.first] = 1.0 / pages.size();
  }
  // Temporary map that holds the ranks of each page
  map<string, double> newRank;
  // Perform power iterations
  for (int i = 1; i < powerIterations; ++i) {
    newRank = ranks;
    // Iterate through the graph
    for (const auto& page : pages) {
      double sum = 0.0;
      // Calculate the rank for each page in the graph
      for (const auto& link : page.second) {
        // Page Rank formula
        sum += ranks[link] * (1.0 / outdegrees.find(link)->second);
      }
      // Update the rank of the page
      newRank[page.first] = sum;
    }
    // Update the rank of the page
    ranks = newRank;
  }


  // Prints the page ranks to two decimal places
  for (auto page : ranks) {
    cout << page.first << " " << fixed << setprecision(2) << page.second << endl;
  }
  
}

int main() {
  // User input variables
  int numLines, powerIterations;
  string start, end;

  // Get user inputs
  cin >> numLines >> powerIterations;

  // Create a new graph object
  Graph graph;

  // Inserts the user inputted edges into graph
  for (int i = 0; i < numLines; i++) {
    // Get the vertices
    cin >> start >> end;

    // Insert vertices into graph
    graph.addEdge(start, end);
  }

  // Do power iterations
  graph.computePageRank(powerIterations);

  return 0;
}