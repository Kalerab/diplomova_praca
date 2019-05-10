#include "scanner.h"

using namespace std;

Scanner::Scanner() {

}

std::vector<Graph> Scanner::scanFile(std::string file) {
    fstream input (file);
    vector<Graph> graphs;
    readComment(input);


    int noOfGraphs;
    input >> noOfGraphs;
    readComment(input);
    for (int i = 0; i <noOfGraphs; ++i) {
        graphs.push_back(scanGraph(input));
    }
    return graphs;
}

Graph Scanner::scanGraph(fstream &input) {

    Graph G;

    int graphNo;
    int noOfVerticies;
    G.comment = G.comment + readComment(input);

    input >> graphNo;
    G.graphNumber = graphNo;

    G.comment = G.comment + readComment(input);

    input >> noOfVerticies;
    G.noOfVerticies = noOfVerticies;
    G.comment = G.comment + readComment(input);


    for (int i = 0; i < noOfVerticies; ++i) {
        Vertex vertex;
        vertex.number = i;
        //vertex.neighbors = (int*) malloc(3 * sizeof(int));
        G.vertices.push_back(vertex);

    }

    for (int i = 0; i < noOfVerticies; ++i) {
        for (int j = 0; j < 3; ++j) {
            int x;
            input >> x;
            G.vertices[i].neighbors.push_back(x);
            //G.vertices[i].neighbors[j] = x;
        }
    }
    return G;
}

string Scanner::readComment(fstream &input){
    char bracket;
    input >> bracket;
    string line = " ";
    if(bracket == '{'){
        getline(input, line);
        line = "{" + line + "\n" + readComment(input);
    } else {
        input.putback(bracket);
        return "";
    }
    //line = "{" + line;
    line = line.substr(0,line.length()-1);
    return line;
}
