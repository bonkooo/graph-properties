# Graph Social Network properties in C

## Overview

This project is a demonstration of several social network properties of a graph written in C, designed to handle operations such as creating, modifying, and analyzing graphs represented by adjacency matrices. It provides various functionalities like adding and removing nodes or edges, calculating centrality, and finding paths using algorithms like Floyd-Warshall. The program supports both interactive input and file-based loading of graphs.

## Features

- **Graph Creation**: Create a graph using an adjacency matrix. Nodes can be added dynamically, and edges can be set with custom weights.
- **Node and Edge Manipulation**: Add or remove nodes and edges from the graph.
- **Centrality Calculation**: Calculate the degree centrality for each node.
- **Pathfinding (Warshall Algorithm)**: Compute reachability between nodes and display paths between them.
- **Shortest Path (Floyd-Warshall Algorithm)**: Calculate the shortest path between all node pairs and determine the center of the graph based on eccentricity.
- **Graph Fragmentation**: Calculate graph fragmentation based on the connectivity of its nodes.
- **Graph Input/Output**: The graph can be input manually or read from a file.

## How to Use

1. **Start the Program**: Run the program from the terminal. You can interact with the menu to perform various graph operations.
2. **Menu Options**:
   - **a**: Create a graph (initialize adjacency matrix).
   - **b**: Add a new node.
   - **c**: Add an edge between two nodes with a specified weight.
   - **d**: Remove an edge.
   - **f**: Remove a node.
   - **g**: Display the current graph.
   - **h**: Delete the entire graph.
   - **i**: Input the graph adjacency matrix manually.
   - **j**: Calculate degree centrality for each node.
   - **k**: Calculate reachability using the Warshall algorithm.
   - **l**: Calculate the graph's fragmentation coefficient.
   - **m**: Load a graph from a file.
   - **e**: Exit the program.

## Key Functions

- **`kreirajGraf()`**: Creates and initializes an adjacency matrix to represent the graph.
- **`dodajCvor()`**: Dynamically adds a new node to the graph.
- **`dodajGranu()`**: Adds an edge between two nodes with a specific weight.
- **`ukloniCvor()`**: Removes a node from the graph, along with all its edges.
- **`warshall()`**: Uses the Warshall algorithm to calculate reachability and find paths between nodes.
- **`floyd()`**: Applies the Floyd-Warshall algorithm to compute the shortest paths between all pairs of nodes and determines the graph's center based on eccentricity.
- **`centralnost()`**: Calculates the degree centrality of nodes in the graph.
- **`fragmentacijaCvorova()`**: Calculates the fragmentation coefficient of the graph.

## Compilation and Execution

1. Compile the code using GCC:
   ```bash
   gcc graph.c -o graph_manager
   ```
2. Run the program:
   ```bash
   ./graph_manager
   ```
   
   
