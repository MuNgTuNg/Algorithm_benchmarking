#include "sGraph.hpp"

namespace shb{

    

void sGraph::addvertex(const std::string &name)
{   
    //takes in name of vertex and searches the map for the vertex by name
    vmap::iterator itr = vertices.find(name);
    if (itr == vertices.end())//if not found
    {
        sGraphVertex *v;           //create new vertex in memory using name
        v = new sGraphVertex(name);

        vertices[name] = v;  //indexed value is the new pointer
        return;
    }
    std::cout << "\nVertex already exists!";
}

void sGraph::addedge(const std::string& from, const std::string& to, double cost)
{
    //find the vertex it's coming from, and the vertex it's going to and get pointers from them
    sGraphVertex *f = (vertices.find(from)->second);
    sGraphVertex *t = (vertices.find(to)->second);

    //add an edge, using the cost and the destination, then push it to the adjacency matrix from the origin vertex
    sEdge edge{cost, t};
    f->edges.push_back(edge);
}
    
    
    
sGraph::~sGraph() {
    for( vmap::iterator itr = vertices.begin(); itr != vertices.end(); ++itr){
        delete (itr->second);
    }
    vertices.clear();
}
    
    
    
void sGraph::dfs(const std::string str){
    
    std::map<const std::string, bool> visited{}; //create map of visited nodes
    std::stack<sGraphVertex*> stc{}; //create stack
    stc.push(vertices[str]);         //push first vertex

    double totalCost = 0;
    
    
    while(!stc.empty()){
        sGraphVertex* curr = stc.top();
        std::cout<< curr->name << " ";
        stc.pop();

        if(curr == nullptr){
            return;
        }

        //if the currently indexed node hasn't been visited
        if(visited.find(curr->name) == visited.end()){
            //mark it as visited
            visited[curr->name] = true;
            
            //search current edges
            for(int i = 0; i < curr->edges.size(); ++i){
                //if we find a destination we haven't visited
                if(visited.find(curr->edges[i].destination->name) == visited.end()){
                    //add it to the stack 
                    stc.push(curr->edges[i].destination);
                    totalCost += curr->edges[i].cost;
                    continue; //skip to the next iteration
                }
            }
            
        }

    }
    std::cout << "Total traversal cost = " << totalCost << "\n";
}

void graphDriverProgram(){
  sGraph graph;

  graph.addvertex("London");
  graph.addvertex("Manchester");
  graph.addvertex("Liverpool");
  graph.addvertex("China");
  graph.addvertex("Brazil");
  
  graph.addedge("London","Liverpool",20);
  graph.addedge("Manchester","Liverpool",30);
  graph.addedge("Liverpool","Manchester",30);
  graph.addedge("Liverpool","London",50);
  graph.addedge("London","Brazil",50);
  graph.addedge("Brazil","London",50);
  graph.addedge("London","China",770);
  graph.addedge("China","London",770);
   
  graph.dfs("China");

  // std::cout << "Route: " << graph.vertices["London"]->name
  // << " to " <<graph.vertices["London"]->edges[0].destination->name
  // << " to " <<graph.vertices["London"]->edges[1].destination->name << "\n";
  // std::cout <<  "Cost: " << graph.vertices["London"]->edges[0].cost + graph.vertices["London"]->edges[1].cost << "\n" ;

}

}//namespace shb