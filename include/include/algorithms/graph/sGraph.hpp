#pragma once
#include <iostream>
#include <vector>
#include <map>
#include <string>
#include <map>
#include <unordered_map>
#include <vector>
#include <stack>



namespace shb{

/*
                        TODO:
                            1.Make graph omnidirectional
                            2.Do a BFS
*/

struct sGraphVertex;
struct sEdge{
    double cost;
    sGraphVertex* destination;
};

struct sGraphVertex {
    std::vector<sEdge> edges; //cost of edge, (destination vertex)?
    std::string name;
    sGraphVertex(std::string s) : name(s) {}
};

class sGraph
{
public:
    //map of strings and vertices
    typedef std::map<std::string, sGraphVertex *> vmap;
    vmap vertices;

    void addvertex(const std::string &name);
    void addedge(const std::string& from, const std::string& to, double cost);
    ~sGraph();
    void dfs(const std::string str);
};




}//namespace shb