#include "Graph.hpp"
#include <algorithm>
#include <set>
#include <unordered_map>
#include <utility>
#include <climits>

// Adds vertex to the graph
void Graph::addVertex(std::string label){
    this->vertices.push_back(label);
}

// Removes a vertex from the graph
void Graph::removeVertex(std::string label){
    for(unsigned int i=0;i<this->vertices.size();i++){
        if(this->vertices.at(i)== label){
            this->vertices.erase(this->vertices.begin() + i);
            break;
        }
    }
}

// Adds Edge to the graph
void Graph::addEdge(std::string label1, std::string label2, unsigned long weight){
    std::tuple<std::string,std::string,unsigned long> newEdge(label1,label2,weight);
    this->edges.push_back(newEdge);
}

// Removes an edge from the graph
void Graph::removeEdge(std::string label1,std::string label2){
    for(unsigned int i=0;i<this->edges.size();i++){
        if((std::get<0>(this->edges.at(i)) == label1) && (std::get<1>(this->edges.at(i)) == label2)){
            this->edges.erase(this->edges.begin()+i);
            break;
        }
    }
}

// Implementation of Dijkstra's Algorithm, finds the shortest path from one vertex to another using a greedy aprouch
unsigned long Graph::shortestPath(std::string startLabel, std::string endLabel,std::vector<std::string>& path){
   std::unordered_map<std::string,std::pair<unsigned long,std::string>> pathsTable;
   std::set<std::string> unvisitedVertices;
//    Setting all vertices to the cost of infinity
   for(auto vertex : this->vertices){
       std::pair<unsigned long,std::string> entry(ULONG_MAX,"");
       pathsTable[vertex] = entry;
       unvisitedVertices.insert(vertex);
   }
   pathsTable[startLabel].first = 0;
   pathsTable[startLabel].second = "";
   std::string currentVertex = startLabel;
//    Algorithm continues until all vertices are visited
   while(!unvisitedVertices.empty()){
    //    Look for neighbor vertices, verify if they were visited and update shortest path if apropiate
        for(auto edge : this->edges){
            if((std::get<0>(edge) == currentVertex && unvisitedVertices.count(std::get<1>(edge)) &&
            (pathsTable[std::get<1>(edge)].first > (pathsTable[std::get<0>(edge)].first + std::get<2>(edge))))){
                pathsTable[std::get<1>(edge)].first = (pathsTable[std::get<0>(edge)].first + std::get<2>(edge)); 
                pathsTable[std::get<1>(edge)].second = currentVertex;
            }
            else if((std::get<1>(edge) == currentVertex && unvisitedVertices.count(std::get<0>(edge)) &&
            (pathsTable[std::get<0>(edge)].first > (pathsTable[std::get<1>(edge)].first + std::get<2>(edge))))){
                pathsTable[std::get<0>(edge)].first = (pathsTable[std::get<1>(edge)].first + std::get<2>(edge));
                pathsTable[std::get<0>(edge)].second = currentVertex;
            }
        }
        // Mark current vertex as visited
        unvisitedVertices.erase(currentVertex);
        // Find the next lowest cost vertex to compute next
        unsigned long nextMinCost = ULONG_MAX;
        for(auto vertex : pathsTable){
            if(unvisitedVertices.count(vertex.first) && nextMinCost > vertex.second.first){
                currentVertex = vertex.first;
                nextMinCost = vertex.second.first;
            }
        }
   }
//    Trace the shortest path and returns its cost
   currentVertex = endLabel;
   while(currentVertex != ""){
       path.insert(path.begin(),currentVertex);
       currentVertex = pathsTable[currentVertex].second;
   }
   return pathsTable[endLabel].first;
}
