#include "graphseparator.h"
#include <unordered_set>

using namespace std;
typedef unordered_set<int> GraphVertices;

void merge_graph_vertices(const GraphVertices &source1, GraphVertices &target2) {
    target2.insert(source1.begin(), source1.end());
}

void separate_graph_vertices(const vector<Cycle> &cycles, vector<GraphVertices> &graphs_vertices) {
    //Iterate through cycles
    for (int i = 0; i < cycles.size(); ++i) {
        Cycle cycle = cycles[i];
        //Create initial graph only with cycle vertices
        GraphVertices current_cycle_graph(cycle.begin(), cycle.end());

        //Check if we can merge with any of existing graphs
        for (long k = graphs_vertices.size() - 1; k >= 0; --k) {
            GraphVertices graph = graphs_vertices[k];

            //Iterate through vertices
            for (int j = 0; j < cycle.size(); ++j) {
                int vertex = cycle[j];
                bool graphHasThisVertex = graph.find(vertex) != graph.end();

                if (graphHasThisVertex) {
                    //If this vertex is already is some of existing graphs
                    //merge it with graph 'current_cycle_graph'
                    merge_graph_vertices(graph, current_cycle_graph);
                    //Remove the element
                    graphs_vertices.erase(remove(graphs_vertices.begin(), graphs_vertices.end(), graph), graphs_vertices.end());
                    break;
                }
            }
        }

        graphs_vertices.push_back(current_cycle_graph);
    }
}

shared_ptr<vector<CycledGraph> > separate_cycles_into_graphs(const vector<Cycle> &cycles) {
    auto cycledGraphs = shared_ptr<vector<CycledGraph> >(new vector<CycledGraph>());

    //Divide vertices into graphs
    vector<GraphVertices> graphs_vertices;
    separate_graph_vertices(cycles, graphs_vertices);

    for (int l = 0; l < graphs_vertices.size(); ++l) {
        CycledGraph emptyGraph;
        cycledGraphs->push_back(emptyGraph);
    }
    //Assign cycles to graph based on vertices
    for (int i = 0; i < cycles.size(); ++i) {
        int firstElement = cycles[i][0];
        for (int j = 0; j < graphs_vertices.size(); ++j) {
            unordered_set<int> currentVertices = graphs_vertices[j];
            bool graphHasThisVertex = currentVertices.find(firstElement) != currentVertices.end();
            if (graphHasThisVertex){
                (*cycledGraphs)[j].push_back(cycles[i]);
                break;
            }
        }
    }
    return cycledGraphs;
}
