#include <iostream>
#include <string>
#include <vector>
#include "Bridges.h"
#include "DataSource.h"
#include "BSTElement.h"
#include <queue>
#include <unordered_map>
#include <random>
#include "GraphAdjList.h"
#include <SLelement.h>
#include <math.h>
#include <chrono>
#include <algorithm>
using namespace std;
using namespace bridges;

/*
  Step 1: Get the Bridges USER ID and API KEY for your program
          by creating an account and signing up (You can use any
          email): https://bridges-cs.herokuapp.com/login

  Step 2: User ID (Username) and Key (API Sha1 Key) can be
          found under Profile on the top left
*/

void bfs(GraphAdjList<int>& graph, int nodeAmt, int nodeFrom, int nodeTo);

void dfs(GraphAdjList<int>& graph, int nodeAmt, int nodeFrom, int nodeTo);

int main(int argc, char **argv)
{

    cout << "Welcome to Graph Traversal!\n";

    Bridges bridges (1, "ProjectThree", "1680912648782");

    //set a title
    bridges.setTitle("Graph Traversal Types.");

    //set description
    bridges.setDescription("This is a visualization of the different types of graph searches and their effectiveness");

    //create a graph with key values of type int
    GraphAdjList<int> graph;

    //Defines amount of nodes to be generated
    int nodeAmt;
    std::cout << "Enter the number of nodes to be generated from 10 to 100,000" << std::endl;
    //Makes sure that a number is being entered.
    while(true)
    {
        try{
            std::string input0;
            std::cin >> input0;
            nodeAmt = stoi(input0);
            if(10 <= nodeAmt && nodeAmt <= 100000)
            {
                break;
            }
            else
            {
                std::cout << "Enter a value within the range!" << std::endl;
            }
        }catch(...)
        {
            std::cout << "Enter a valid number:" << std::endl;
        }
    }
    //Sets amount of edges to double the vertex count
    int edgeAmt = nodeAmt * 2;

    //adds a vertex to the graph
    for(int i = 0; i < nodeAmt; i++)
    {
        graph.addVertex(i);
    }

    //Keeps track of the amount of edges created
    int edgeCounter = 0;

    // Initialize random number generator
    std::random_device rd;
    std::mt19937 gen(rd());

    // Define the range [0, nodeAmt - 1]
    std::uniform_int_distribution<> makeRand(0, nodeAmt - 1);


    //make check for if it is like 2 vertices then
    //or just make minumum like 10 nodes

    /*
    auto possibilities = tgamma(edgeAmt) / tgamma(edgeAmt - edgeAmt);

    if(possibilities < edgeAmt)
    {
        edgeAmt = possibilities;
    }
     */

    std::cout << "Generating Graph" << std::endl;
    //Redirects the out stream to catch the isEdge function cout while graph is being created
    std::ostringstream oss;
    std::streambuf* p_cout_streambuf = std::cout.rdbuf();
    std::cout.rdbuf(oss.rdbuf());

    while((edgeAmt > edgeCounter))
    {
        int from = makeRand(gen);
        int to = makeRand(gen);
        //makes sure that there are no self loops
        while(to == from)
        {
            to = makeRand(gen);
        }
        //if edge doesn't exist, creates it
        if(!graph.isEdge(from, to))
        {

            graph.addEdge(from, to);
            edgeCounter++;
        }
    }
    //restores the stream
    std::cout.rdbuf(p_cout_streambuf);

    //sets the data structure as graph
    bridges.setDataStructure(&graph);

    //Asks user for the IDs of the from and to nodes

    int nodeFrom;
    std::cout << "Enter a node number " << 0 << " to " << (nodeAmt - 1) << " to search from:" << std::endl;
    while(true)
    {
        try{
            std::string input1;
            std::cin >> input1;
            nodeFrom = stoi(input1);
            break;
        }catch(...)
        {
            std::cout << "Enter a valid number:" << std::endl;
        }
    }

    int nodeTo;
    std::cout << "Enter a node number " << 0 << " to " << (nodeAmt - 1) << " to search to:" << std::endl;
    while(true)
    {
        try{
            std::string input2;
            std::cin >> input2;
            nodeTo = stoi(input2);
            break;
        }catch(...)
        {
            std::cout << "Enter a valid number:" << std::endl;
        }
    }

    //asks user which method they want to use

    std::cout << "Enter a traversal method: \n1. Breadth First Search\n2. Depth First Search\n"
                 "3. Dijkstra's Algorithm" << std::endl;

    int selection;
    while(true)
    {
        try{
            std::string choice;
            std::cin >> choice;
            selection = stoi(choice);
            if(selection == 1 || selection == 2 || selection == 3)
            {
                break;
            }
            else
            {
                std::cout << "Enter a valid choice:" << std::endl;
            }
        }catch(...)
        {
            std::cout << "Enter a valid traversal 1 through 3:" << std::endl;
        }

    }

    if(selection == 1)
    {
        bfs(graph, nodeAmt, nodeFrom, nodeTo);
    }
    else if (selection == 2) {
        dfs(graph, nodeAmt, nodeFrom, nodeTo);
    }
    //bfs(graph, nodeAmt, nodeFrom, nodeTo);


    bridges.visualize();


    return 0;
}

void bfs(GraphAdjList<int>& graph, int nodeAmt, int nodeFrom, int nodeTo)
{
    std::chrono::steady_clock::time_point start = std::chrono::steady_clock::now();

    std::queue<int> nodeChecker;

    std::unordered_map<int, bool> visited;
    //makes all distances from nodeFrom infinity to begin with
    std::vector<int> distance(nodeAmt, 1e9);
    //stores the parent node of each node
    std::vector<int> parentTracker(nodeAmt, -1);


    visited[nodeFrom] = true;
    distance[nodeFrom] = 0;
    nodeChecker.push(nodeFrom);


    //while queue isn't empty
    while(!nodeChecker.empty())
    {

        int currNode = nodeChecker.front();
        nodeChecker.pop();

        if(currNode == nodeTo)
        {
            std::cout << "Found node! Distance: " << distance[currNode] << std::endl;
            break;
        }

        auto adj = graph.getAdjacencyList(currNode);
        //loops through node's adjacency list
        while (adj != nullptr) {
            int num = stoi(adj->getLabel());

            if(!visited[num])
            {
                nodeChecker.push(num);
                visited[num] = true;
                distance[num] = distance[currNode] + 1;
                parentTracker[num] = currNode;
            }
            adj = adj->getNext();
        }

    }

    //checks if there is a path
    //if distance is 1e9, means that it was never visited
    if(distance[nodeTo] == 1e9)
    {
        std::cout << "No path found" << std::endl;
    }else
    {
        //path method
        vector<int> path;
        path.push_back(nodeTo);
        int currentNode = nodeTo;
        while (parentTracker[currentNode] != -1) {
            path.push_back(parentTracker[currentNode]);

            graph.getLinkVisualizer(parentTracker[currentNode], currentNode)->setColor("red");

            currentNode = parentTracker[currentNode];
            graph.getVertex(currentNode)->setColor("yellow");
        }

        std::cout << "Path from " << nodeFrom << " to " << nodeTo << " is: ";
        for (int i = int(path.size() - 1); i > 0; i--) {
            std::cout << path[i] << " -> ";
        }
        std::cout << path[0] << std::endl;
    }

    //Prints out the time it took
    std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
    std::cout << "Time took for Breadth First Search = " << std::chrono::duration_cast<std::chrono::microseconds>
            (end - start).count() << " microseconds" << std::endl;

    graph.getVertex(nodeFrom)->setColor("green");
    graph.getVertex(nodeTo)->setColor("green");

}

void dfs(GraphAdjList<int>& graph, int nodeAmt, int nodeFrom, int nodeTo) {

    std::chrono::steady_clock::time_point start = std::chrono::steady_clock::now();

    // Stack for nodes during first dfs
    std::stack<int> nodeStack;

    // Map for visited nodes
    std::unordered_map<int, bool> visited;

    // Array for each parent for path
    std::vector<int> parentTracker(nodeAmt, -1);

    // Array for distance from start node
    std::vector<int> distance(nodeAmt, INT_MAX);

    nodeStack.push(nodeFrom);
    visited[nodeFrom] = true;
    distance[nodeFrom] = 0;

    // Explore all possible paths
    while (!nodeStack.empty()) {
        int currNode = nodeStack.top();
        nodeStack.pop();

        // Print distance when target is reached
        if (currNode == nodeTo) {
            std::cout << "Found node! Distance: " << distance[currNode] << std::endl;
            break;
        }

        // Get adjacent nodes
        SLelement<Edge<int>>* adj = graph.getAdjacencyList(currNode);
        while (adj != nullptr) {
            int num;
            try {
                num = stoi(adj->getLabel());
            } catch (const std::invalid_argument& e) {
                std::cerr << "Invalid argument for stoi: " << adj->getValue().getLabel() << " at node " << currNode << std::endl;
                adj = adj->getNext();
                continue;
            }

            // Handle adjacent nodes
            if (!visited[num]) {
                nodeStack.push(num);
                visited[num] = true;
                parentTracker[num] = currNode;
                distance[num] = distance[currNode] + 1;
            }
            adj = adj->getNext();
        }
    }

    // Build path
    std::vector<int> path;
    if (parentTracker[nodeTo] != -1 || nodeFrom == nodeTo) {
        int at = nodeTo;
        while (at != -1) {
            path.push_back(at);
            at = parentTracker[at];
        }
        std::reverse(path.begin(), path.end());
        std::cout << "Path from " << nodeFrom << " to " << nodeTo << " is: ";
        for (int i = int(path.size() - 1); i > 0; i--) {
            std::cout << path[i] << " -> ";
        }
        std::cout << path[0] << std::endl;
    } else {
        std::cout << "No path found from " << std::endl;
    }

    // Stop timer and print
    std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
    std::cout << "DFS completed in " << std::chrono::duration_cast<std::chrono::microseconds>(end - start).count() << " microseconds" << std::endl;

    // Update node colors
    for (int node : path) {
        if (node == nodeFrom || node == nodeTo) {
            graph.getVertex(node)->setColor("green");
        } else {
            graph.getVertex(node)->setColor("yellow");
        }
    }
    if (!path.empty()) {
        for (size_t i = 0; i < path.size() - 1; i++) {
            graph.getLinkVisualizer(path[i], path[i+1])->setColor("red");
        }
    }
}

