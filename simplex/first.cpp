#include <iostream>
#include <fstream>
#define line_length 100
using namespace std;

/**
    structure of the edge 
    member is cost + capability
*/
struct edge
{
    edge(int cost, int capability)
    {
        cost = cost;
        capability = capability;
    }
    int cost; 
    int capability; 
};

/**
    @param input input file stream
    @param edge_num number of edges
    @param edge_info (nodes, cost, capability)
    @return bool (is an edge or not)
*/
bool analyzeEdge(ifstream &input, const int edge_num, edge[][] edge_info)
{
    char* line;
    for(int i = 0; i < edge_num, i++)
    {
        int start_node;
        input >> start_node;
        int end_node;
        input >> end_node;
        int capability;
        input >> capability;
        int cost;
        input >> cost;

        edge new_edge;
        new_edge
    }
}

int main()
{
    char* line;
    ifstream input("/usr/info/code/cpp/LogMonitor/LogMonitor/simplex/case00.txt",ios::in | ios::binary);
    ofstream output("/usr/info/code/cpp/LogMonitor/LogMonitor/simplex/output.txt", ios::out | ios::binary);

    if(!input || !output)
    {
        cout << "can not find input or output file" << endl;
        exit(1);
    }

    // analyze first line
    int node_number;
    input >> node_number;
    int edge_number;
    input >> edge_number;
    int consumer_number;
    input >> consumer_number;
    int server_cost;
    input >> server_cost;

    // ignore the first break
    input.getline(line, line_length);

    // analyze the edge info
    while(!input.eof())
    {
        input.getline(line, line_length);
        if(line == " ")
        {
            continue;
        }

        cout << line << endl;
        output << line << endl;
    }
    
    input.close();
    output.close();

    return 0;
}