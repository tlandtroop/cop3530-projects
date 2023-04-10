// Created by Tyler Landtroop on 4/9/2023

#include <map>
#include <string>
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