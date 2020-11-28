#ifndef EDGE_HPP
#define EDGE_HPP

#include <string>

class Edge {
private:
        std::string cur_edge; //edge that is current 
        std::string adj_edge; //edge that is adjacent
        unsigned long weight; 
protected:
public:
        friend class Graph;//allows access to Graph

        
        Edge(std::string a = "", std::string b = "", unsigned long w = 0) {// constructor
                cur_edge = a;
                adj_edge = b;
                weight = w;
        }
        ~Edge() {}// destructor
};
#endif //EDGE_HPP