//////////////////////////////////////////////////////////////////////
//Diego's Graph.hpp                       ///////////////////////////
/////////////////////////////////////////////////////////////////////
#ifndef GRAPH_HPP
#define GRAPH_HPP

#include "GraphBase.hpp"
#include "Edge.hpp"
#include "Vertex.hpp"
#include <iterator>
#include <queue>
#include <limits>
#include <vector>
#include <deque>
#include <algorithm>

class Graph : public GraphBase {
private:
        std::deque<Vertex*> vertices;//keeps vertices objects. Keeps vertex and distance
        std::deque<Edge*> edges; // Keeps edges and their weight
        unsigned long most_short_distance = 0; //holds the most short distance after every node visit
        int min_vrtx_index = 0; //node indices with minimum distances
        std::string minimum_element = ""; //Gets the minimum element at node/
        /*Priority queue to store wighted vertxes by distance from starting ndoe in  ascneding manner*/
        std::priority_queue<std::pair<unsigned long, std::string>,
                                        std::vector<std::pair<unsigned long, std::string>>,
                                        std::greater<std::pair<unsigned long, std::string>>> list_of_paths;

protected:
        
        void single_string_check(std::string string_input); //throw if single string input is null
        void double_string_check(std::string string_input1, std::string string_input2); //throw if both string inputs are null
        void beginning_of_path(std::string startLabel); 
        void make_path(std::string startLabel);//
        void find_min_vrtx_index(std::string& minimum_element); //get min vertex index
        void get_minimum_distance(std::string startLabel); //put distances in the string
        void place_path(std::string endLabel, std::vector<std::string>& path); //path from cur to adj
        void path_reset(); 

public:
        Graph() {} 
        ~Graph(); 
        
        void addVertex(std::string label);
        void removeVertex(std::string label);
        void addEdge(std::string label1, std::string label2, unsigned long weight);
        void removeEdge(std::string label1, std::string label2);
        unsigned long shortestPath(std::string startLabel, std::string endLabel, std::vector<std::string> &path);
};
#endif // GRAPH_HPP