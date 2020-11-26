#include "Graph.hpp"
#include <algorithm>
#include <set>
#include <unordered_map>
#include <utility>
#include <climits>

#include <iostream> //remove later

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

unsigned long Graph::shortestPath(std::string startLabel, std::string endLabel,std::vector<std::string>& path){
   std::unordered_map<std::string,std::pair<unsigned long,std::string>> pathsTable;
   std::set<std::string> unvisitedVertices;
   for(auto vertex : this->vertices){
       std::pair<unsigned long,std::string> entry(ULONG_MAX,"");
       pathsTable[vertex] = entry;
       unvisitedVertices.insert(vertex);
   }
   pathsTable[startLabel].first = 0;
   pathsTable[startLabel].second = "";
   std::string currentVertex = startLabel;
   unvisitedVertices.erase(startLabel);
   while(!unvisitedVertices.empty()){
       //Working on this part...
      for(auto edge : this->edges){
          if(std::get<0>(edge) == currentVertex && !unvisitedVertices.count(std::get<1>(edge)) 
          && (pathsTable[std::get<1>(edge)].first < (pathsTable[std::get<0>(edge)].first + std::get<2>(edge)))){
            pathsTable[std::get<1>(edge)].first =     
          }
      } 
   }
   
   return 0;
}
