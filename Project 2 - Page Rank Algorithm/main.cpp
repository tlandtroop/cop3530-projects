// Created by Tyler Landtroop on 4/9/2023

#include <iomanip>
#include <iostream>
#include "graph.h"
using namespace std;

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