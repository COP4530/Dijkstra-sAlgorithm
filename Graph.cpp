#include "Graph.hpp"
#include <algorithm>


void Graph::addVertex(std::string label){
    this->vertices.push_back(label);
}

void Graph::removeVertex(std::string label){
    std::remove(this->vertices.begin(),this->vertices.end(),label);
}

void Graph::addEdge(std::string label1, std::string label2, unsigned long weight){
    std::tuple<std::string,std::string,unsigned long> newEdge(label1,label2,weight);
    this->edges.push_back(newEdge);
}

void Graph::removeEdge(std::string label1,std::string label2){
    for(unsigned int i=0;i<this->edges.size();i++){
        if((std::get<0>(this->edges.at(i)) == label1) && (std::get<1>(this->edges.at(i)) == label2)){
            this->edges.erase(this->edges.begin()+i);
            break;
        }
    }
}

unsigned long shortestPath(std::string startLabel, std::string endLabel,std::vector<std::string>& path){
    return 0;
}
