//////////////////////////////////////////////////////////////////////
//Diego's Graph.cpp                       ///////////////////////////
/////////////////////////////////////////////////////////////////////
#include "Graph.hpp"


Graph::~Graph()//graph destructor
{
        for(auto& x : vertices) { delete x; }
        for(auto& x : edges) { delete x; }
    vertices.clear();
        edges.clear();
}
//throwing if single string is null
void Graph::single_string_check(std::string string_input) {
        if (string_input.empty()) {
                throw string_input;//
        }
}
//throwing if both string inputs are null
void Graph::double_string_check(std::string string_input1, std::string string_input2) {
        if (string_input1.empty()) {
                throw string_input1;
        }
else if (string_input2.empty()) {
                throw string_input2;
        }
        else if (string_input1.empty() && string_input2.empty()) {
                throw ("String arguments are empty.\n");
        }
}
//add a vertex to the graph. All vertices have their own lable
void Graph::addVertex(std::string label)
{
        single_string_check(label);
        Vertex *new_vertex = new Vertex;
        new_vertex->vrtx = label;
        new_vertex->min_distance = std::numeric_limits<unsigned long>::max();// setting initial distances to infinite
        new_vertex->most_short_path = { "" };
        new_vertex->visited = false;

        vertices.push_back(new_vertex); //adds to vertices deque
}
/*Removes the vertex with label from the graph. Also, removes the edges between that vertex and
        the other vertices of the graph. Uses the iterator method to get the value at that label, and
        remove them.*/
void Graph::removeVertex(std::string label)
{
        single_string_check(label);
  /*Remove the vertex*/
        for (std::deque<Vertex*>::iterator ver_itr = vertices.begin(); ver_itr != vertices.end();) {
                if ((*ver_itr)->vrtx == label) {
                        vertices.erase(ver_itr);
                }
                else {}
                ++ver_itr;
        }
        /*Remove edges associated with that node*/
        for (std::deque<Edge*>::iterator edg_itr = edges.begin(); edg_itr != edges.end();) {
                if (((*edg_itr)->cur_edge == label) || ((*edg_itr)->adj_edge == label)) {
                        edges.erase(edg_itr);
                }
                else{}
                ++edg_itr;
        }
}
/*Adds an edge of value weight to the graph between the vertex with label1 and the vertex with
        label2.*/
void Graph::addEdge(std::string label1, std::string label2, unsigned long weight)
{
        double_string_check(label1, label2);
        /*Add an edge in between label1 and label2*/
        Edge *newEdge1 = new Edge(label1, label2, weight);
        Edge* newEdge2 = new Edge(label2, label1, weight);
            edges.push_back(newEdge1);
        edges.push_back(newEdge2);
}
/*Removes the edge from the graph between the vertex with label1 and the vertex with label2.*/
void Graph::removeEdge(std::string label1, std::string label2)
{
        double_string_check(label1, label2);
        /*Only erase if both label match with the two label.*/
        for (std::deque<Edge*>::iterator edg_itr = edges.begin(); edg_itr != edges.end();) {
                if (((*edg_itr)->cur_edge == label1) && ((*edg_itr)->adj_edge == label2)) {
                        edges.erase(edg_itr);
                }
                else{}
                ++edg_itr;
        }
}
/*Calculates the shortest path between the vertex with startLabel and the vertex with endLabel
        using greedy Dijkstra's Algorithm. A vector is passed into the method that stores the shortest path
        between the vertices. The return value is the sum of the edges between the start and end
        vertices on the shortest path.*/
unsigned long Graph::shortestPath(std::string startLabel, std::string endLabel, std::vector<std::string>& path)
{
        double_string_check(startLabel, endLabel);

        beginning_of_path(startLabel); /*Selects the node to start*/
        /*Makes the list in the priority queue in ascending order of nodes by their distances (using 
        edge/weight))*/
        make_path(startLabel);
        place_path(endLabel, path); /*Then traverse on priority queue and find the shortest distance from A to B*/
        path_reset(); /*Clear the vertex container*/

        return most_short_distance;/*Return the shortest distance and we are done*/
}
/*Begin the grap at A, initilize its distance to 0, and push into the string as the shortest path*/
void Graph::beginning_of_path(std::string startLabel){

        for (std::deque<Vertex*>::iterator ver_itr = vertices.begin(); ver_itr != vertices.end();) {
                if ((*ver_itr)->vrtx == startLabel) {
                        (*ver_itr)->min_distance = 0;
                        (*ver_itr)->most_short_path.clear();
                        (*ver_itr)->most_short_path.push_back(startLabel);
                }
                else{}
                 ++ver_itr;
        }
        list_of_paths.push(std::make_pair(0, startLabel));
}/*Traverse through the vector deque and if the minimum element matches the vrtx, get its position*/
void Graph::find_min_vrtx_index(std::string& minimum_element){
        int ver_idx = 0;
        for (std::deque<Vertex*>::iterator ver_itr = vertices.begin(); ver_itr != vertices.end();) {
                if ((*ver_itr)->vrtx == minimum_element) {
                        min_vrtx_index = ver_idx;
                }
                else{ ++ver_idx;}
                 ++ver_itr;
        }
}
/*Using BFS, traverse through edge and vertex containers and push possible paths into the priority queue */
void Graph::get_minimum_distance(std::string startLabel){
        /*Traverse through edge*/
        for (std::deque<Edge*>::iterator edg_itr = edges.begin(); edg_itr != edges.end();) {

                if ((*edg_itr)->cur_edge == minimum_element) { /*If one edge toward B matches the minimum element*/

                        /*Start iterating over vertex adjacent to that vector from above*/
                        for (std::deque<Vertex*>::iterator ver_itr = vertices.begin(); ver_itr != vertices.end();) {
                                /*If going backawrd has a smaller weight and has been not visited*/
                                if (((*edg_itr)->adj_edge == (*ver_itr)->vrtx) &&
                                        ((vertices.at(min_vrtx_index)->min_distance + (*edg_itr)->weight) < (*ver_itr)->min_distance) &&
                                        ((*ver_itr)->visited == false))
                                {/*Store the distace+ weight*/
                                  (*ver_itr)->min_distance = vertices.at(min_vrtx_index)->min_distance + (*edg_itr)->weight;

                                        if (minimum_element == startLabel) {
                                                (*ver_itr)->most_short_path.clear(); /*Clear the path, and push A*/
                                                (*ver_itr)->most_short_path.push_back(startLabel);
                                        }
                                        else if (minimum_element != startLabel) { /*Else push a node/vertex at the minimum index*/
                                                (*ver_itr)->most_short_path.clear();
                                                (*ver_itr)->most_short_path = vertices.at(min_vrtx_index)->most_short_path;
                                                (*ver_itr)->most_short_path.push_back(vertices.at(min_vrtx_index)->vrtx);
                                        }
                                        /*Make a pair and push into the priority queue. Contain the minimum distance, and vertex at this position*/
                                        list_of_paths.push(std::make_pair((*ver_itr)->min_distance, (*ver_itr)->vrtx));
                                }
                                else{}
                                ++ver_itr;
                        }
                }
                else{}
                ++edg_itr;
                 }
}
/*visit from A to B via all possible paths*/
void Graph::make_path(std::string startLabel){
        for (;!list_of_paths.empty();) {

                minimum_element = list_of_paths.top().second; /*After the first node*/

                list_of_paths.pop();

                find_min_vrtx_index(minimum_element); /*Gets the index with minium element*/

                get_minimum_distance(startLabel); /*Get the weight*/

                vertices.at(min_vrtx_index)->visited = true;
        }
}
/*Put the nodes in the vector with minimum weight and get shortest distances from A->B*/
void Graph::place_path(std::string endLabel, std::vector<std::string>& path){

        for (std::deque<Vertex*>::iterator ver_itr = vertices.begin(); ver_itr != vertices.end();) {
                if (endLabel == (*ver_itr)->vrtx) { /*Loop until find the endLabel*/
                        most_short_distance = (*ver_itr)->min_distance; /*Get the minimum distaces and store*/
                        (*ver_itr)->most_short_path.push_back(endLabel); /*Put the least weight in the string*/
                        path = (*ver_itr)->most_short_path; /*store that minimum path into vector of path and continue*/
                          }
                else{}
                ++ver_itr;
        }

}
/*Default all of the vertices of the current graph*/
void Graph::path_reset(){
        /*Set the distance back yo infinite */
        for (std::deque<Vertex*>::iterator ver_itr = vertices.begin(); ver_itr != vertices.end();) {
                (*ver_itr)->min_distance = std::numeric_limits<unsigned long>::max();;
                (*ver_itr)->most_short_path = { "" };
                (*ver_itr)->visited = false;
                ++ver_itr;
        }
}