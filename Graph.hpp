#ifndef GRAPH_H
#define GRAPH_H
#include "GraphBase.hpp"
#include <vector>
#include <tuple>
#include <string>

class Graph: public GraphBase{
    private:
        std::vector<std::string> vertices;
        std::vector<std::tuple<std::string,std::string,unsigned long>> edges;
    public:
        Graph();
        void addVertex(std::string label);
        void removeVertex(std::string label);
        void addEdge(std::string label1, std::string label2, unsigned long weight);
        void removeEdge(std::string label1, std::string label2);
        unsigned long shortestPath(std::string startLabel, std::string endLabel, std::vector<std::string> &path);
   

};
#endif