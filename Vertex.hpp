#ifndef VERTEX_HPP
#define VERTEX_HPP

#include <string>
#include <vector>

class Vertex{
private:
        std::string vrtx; 
        unsigned long min_distance; // stores minimum distance between edges
        std::vector<std::string> most_short_path; // stores edges with shortest paths
        bool visited; //variable to see if the node has been visited
protected:
public:
        friend class Graph;//allows access to Graph
        Vertex() { vrtx = ""; }//constructor
        ~Vertex() {}//destructor
};
#endif // VERTEX
