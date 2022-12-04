#include "Graph.h"
#include "GraphExceptions.h"

#include <iostream>
#include <iomanip>
#include <queue>
#include <fstream>
#include <sstream>
#include <cstdlib>

// Literally do nothing here
// default constructors of the std::vector is enough
Graph::Graph()
{}

Graph::Graph(const std::string& filePath)
{
    // ============================= //
    // This function is implemented  //
    // Do not edit this function !   //
    // ============================= //
    // Tokens
    std::string tokens[3];

    std::ifstream mapFile(filePath.c_str());
    // Read line by line
    std::string line;
    while (std::getline(mapFile, line))
    {
        // Empty Line Skip
        if(line.empty()) continue;
        // Comment Skip
        if(line[0] == '#') continue;

        // Tokenize the line
        int i = 0;
        std::istringstream stream(line);
        while(stream >> tokens[i]) i++;

        // Single token (Meaning it is a vertex)
        if(i == 1)
        {
            InsertVertex(tokens[0]);
        }
        // Exactly three tokens (Meaning it is an edge)
        else if(i == 3)
        {
            int weight = std::atoi(tokens[0].c_str());
            if(!ConnectVertices(tokens[1], tokens[2], weight))
            {
                std::cerr << "Duplicate edge on "
                          << tokens[0] << "-"
                          << tokens[1] << std::endl;
            }
        }
        else std::cerr << "Token Size Mismatch" << std::endl;
    }
}

void Graph::InsertVertex(const std::string& vertexName)
{
    for(int i=0; i<TotalVertexCount(); i++){
        if(VertexName(i)==vertexName)
            throw DuplicateVertexNameException();
    }
    struct GraphVertex newVertex = {{}, 0, vertexName};
    vertexList.push_back(newVertex);
}

bool Graph::ConnectVertices(const std::string& fromVertexName,
                            const std::string& toVertexName,
                            int weight)
{
    if(fromVertexName==toVertexName){
        return false;
    }
    int fromVertexId=-1, toVertexId=-1;
    for(int i=0; i<TotalVertexCount(); i++){
        if(VertexName(i)==fromVertexName){
            if(vertexList[i].edgeCount==MAX_EDGE_PER_VERTEX){
                throw TooManyEdgeOnVertexExecption();
            }
            fromVertexId = i;
        }
        if(VertexName(i)==toVertexName){
            if(vertexList[i].edgeCount==MAX_EDGE_PER_VERTEX){
                throw TooManyEdgeOnVertexExecption();
            }
            toVertexId = i;
        }
    }
    if(fromVertexId==-1 || toVertexId==-1){
        throw VertexNotFoundException();
    }
    struct GraphVertex &fromVertex = vertexList[fromVertexId];
    struct GraphVertex &toVertex = vertexList[toVertexId];
    for(int i=0; i<fromVertex.edgeCount; i++){
        if(edgeList[fromVertex.edgeIds[i]].vertexId0==toVertexId || edgeList[fromVertex.edgeIds[i]].vertexId1==toVertexId){
            return false;
        }
    }
    toVertex.edgeIds[toVertex.edgeCount++] = fromVertex.edgeIds[fromVertex.edgeCount++] = TotalEdgeCount();
    struct GraphEdge newEdge = {weight, false, fromVertexId, toVertexId};
    edgeList.push_back(newEdge);
}

bool Graph::ShortestPath(std::vector<int>& orderedVertexIdList,
                         const std::string& from,
                         const std::string& to) const
{
    std::priority_queue<DistanceVertexIdPair> pq;
    std::vector<int> distances(TotalVertexCount(), LARGE_NUMBER), paths(TotalVertexCount(), -1);
    int Id=-1;
    for(int i=0; i<TotalVertexCount(); i++){
        if(VertexName(i) == from){
            pq.push(DistanceVertexIdPair(i, 0));
        }
        else if(VertexName(i) == to){
            Id = i;
        }
    }
    if(Id==-1 || pq.empty()){
        throw VertexNotFoundException();
    }
    while(!pq.empty()) {
        DistanceVertexIdPair pair = pq.top();
        pq.pop();
        const GraphVertex &v = vertexList[pair.vId];
        for(int i=0; i<v.edgeCount; i++){
            const GraphEdge &edge = edgeList[v.edgeIds[i]];
            if(!edge.masked){
                int IDw = edge.vertexId1 + edge.vertexId0 - pair.vId;
                int alt = pair.currentWeight + edge.weight;
                if (alt < distances[IDw]) {
                    distances[IDw] = pair.currentWeight + edge.weight;
                    paths[IDw] = pair.vId;
                    pq.push(DistanceVertexIdPair(IDw, alt));
                }
            }
        }
    }
    while(VertexName(Id)!=from){
        orderedVertexIdList.insert(orderedVertexIdList.begin(), Id);
        if((Id = paths[Id])==-1){
            return false;
        }
    }
    orderedVertexIdList.insert(orderedVertexIdList.begin(), Id);
    return true;
}

int Graph::MultipleShortPaths(std::vector<std::vector<int> >& orderedVertexIdList,
                              const std::string& from,
                              const std::string& to,
                              int numberOfShortestPaths)
{
    UnMaskAllEdges();
    std::vector<int> lastFoundPath;
    ShortestPath(lastFoundPath, from, to);
    orderedVertexIdList.push_back(lastFoundPath);
    
    for(int i=1; i<numberOfShortestPaths; i++){
        GraphVertex &vertex = vertexList[lastFoundPath.front()];
        GraphEdge *max;
        for(int k=0; k<vertex.edgeCount; k++){
            GraphEdge &edge = edgeList[vertex.edgeIds[k]];
            if(edge.vertexId0+edge.vertexId1-lastFoundPath.front() == lastFoundPath[1]){
                max = &edge;
            }
        }
        for(int j=2; j<lastFoundPath.size(); j++){
            GraphVertex &vertex = vertexList[lastFoundPath[j]];
            for(int k=0; k<vertex.edgeCount; k++){
                GraphEdge &edge = edgeList[vertex.edgeIds[k]];
                if(!edge.masked && edge.vertexId0+edge.vertexId1-lastFoundPath[j] == lastFoundPath[j-1] && edge.weight>max->weight){
                    max = &edge;
                }
            }
        }
        max->masked = true;
        lastFoundPath.clear();
        ShortestPath(lastFoundPath, from, to);
        if(lastFoundPath.empty()){
            return i;
        }
        else{
            orderedVertexIdList.push_back(lastFoundPath);
        }
    }
    UnMaskAllEdges();
    return numberOfShortestPaths;
}

void Graph::MaskEdges(const std::vector<StringPair>& vertexNames)
{
    
    for(int i=0; i<vertexNames.size(); i++){
        int j=0;
        for(; j<TotalEdgeCount(); j++){
            if((VertexName(edgeList[j].vertexId0)==vertexNames[i].s0 && VertexName(edgeList[j].vertexId1)==vertexNames[i].s1) || (VertexName(edgeList[j].vertexId0)==vertexNames[i].s1 && VertexName(edgeList[j].vertexId1)==vertexNames[i].s0)){
                edgeList[j].masked = true;
                break;
            }
        }
        if(j==TotalEdgeCount()){
            throw VertexNotFoundException();
        }
    }
}

void Graph::UnMaskEdges(const std::vector<StringPair>& vertexNames)
{
    for(int i=0; i<vertexNames.size(); i++){
        int j=0;
        for(; j<TotalEdgeCount(); j++){
            if(VertexName(edgeList[j].vertexId0)==vertexNames[i].s0 && VertexName(edgeList[j].vertexId1)==vertexNames[i].s1){
                edgeList[j].masked = false;
                break;
            }
        }
        if(j==TotalEdgeCount()){
            throw VertexNotFoundException();
        }
    }
}

void Graph::UnMaskAllEdges()
{
    for(int i=0; i<TotalEdgeCount(); i++){
        edgeList[i].masked = false;
    }
}

void Graph::MaskVertexEdges(const std::string& name)
{
    for(int i=0; i<TotalVertexCount(); i++){
        if(VertexName(i)==name){
            struct GraphVertex &vertex = vertexList[i];
            for(i=0; i<vertex.edgeCount; i++){
                edgeList[vertex.edgeIds[i]].masked = true;
            }
            return;
        }
    }
    throw VertexNotFoundException();
}

void Graph::UnMaskVertexEdges(const std::string& name)
{
    for(int i=0; i<TotalVertexCount(); i++){
        if(VertexName(i)==name){
            struct GraphVertex &vertex = vertexList[i];
            for(i=0; i<vertex.edgeCount; i++){
                edgeList[vertex.edgeIds[i]].masked = false;
            }
            return;
        }
    }
    throw VertexNotFoundException();
}

void Graph::ModifyEdge(const std::string& vName0,
                       const std::string& vName1,
                       float newWeight)
{
    for(int i=0; i<TotalEdgeCount(); i++){
        GraphEdge &edge = edgeList[i];
        std::string vertexName0 = VertexName(edge.vertexId0), vertexName1 = VertexName(edge.vertexId1);
        if((vertexName0==vName0 && vertexName1==vName1) || (vertexName0==vName1 && vertexName1==vName0)){
            edge.weight = newWeight;
            return;
        }
    }
    throw VertexNotFoundException();
}

void Graph::ModifyEdge(int vId0, int vId1,
                       float newWeight)
{
    if(vId0<TotalVertexCount() && vId1<TotalVertexCount()){
        GraphVertex &vertex0=vertexList[vId0], &vertex1=vertexList[vId1];
        for(int i=0; i<vertex0.edgeCount; i++){
            GraphEdge &edge = edgeList[vertex0.edgeIds[i]];
            if(vId1 == edge.vertexId0 + edge.vertexId1 - vId0){
                edge.weight = newWeight;
                return;
            }
        }
    }
}

void Graph::PrintAll() const
{
    // ============================= //
    // This function is implemented  //
    // Do not edit this function !   //
    // ============================= //
    for(size_t i = 0; i < TotalVertexCount(); i++)
    {
        const GraphVertex& v = vertexList[i];
        std::cout << v.name << "\n";
        for(int j = 0; j < v.edgeCount; j++)
        {
            int edgeId = v.edgeIds[j];
            const GraphEdge& edge = edgeList[edgeId];
            // Skip printing this edge if it is masked
            if(edge.masked)
                continue;

            // List the all vertex names and weight
            std::cout << "-" << std::setfill('-')
                             << std::setw(2) << edge.weight
                             << "-> ";
            int neigVertexId = (static_cast<int>(i) == edge.vertexId0)
                                 ? edge.vertexId1
                                 : edge.vertexId0;
            std::cout << vertexList[neigVertexId].name << "\n";
        }
    }
    // Reset fill value because it "sticks" to the std out
    std::cout << std::setfill(' ');
    std::cout.flush();
}

void Graph::PrintPath(const std::vector<int>& orderedVertexIdList,
                      bool sameLine) const
{
    // ============================= //
    // This function is implemented  //
    // Do not edit this file !       //
    // ============================= //
    for(size_t i = 0; i < orderedVertexIdList.size(); i++)
    {
        int vertexId = orderedVertexIdList[i];
        if(vertexId >= static_cast<int>(TotalVertexCount()))
            throw VertexNotFoundException();

        const GraphVertex& vertex = vertexList[vertexId];
        std::cout << vertex.name;
        if(!sameLine) std::cout << "\n";
        // Only find and print the weight if next is available
        if(i == orderedVertexIdList.size() - 1) break;
        int nextVertexId = orderedVertexIdList[i + 1];
        if(nextVertexId >= static_cast<int>(TotalVertexCount()))
            throw VertexNotFoundException();

        // Find the edge between these two vertices
        int edgeId = INVALID_INDEX;
        if(vertexId     < static_cast<int>(TotalVertexCount()) &&
           nextVertexId < static_cast<int>(TotalVertexCount()))
        {
            // Check all of the edges of vertex
            // and try to find
            const GraphVertex& fromVert = vertexList[vertexId];
            for(int i = 0; i < fromVert.edgeCount; i++)
            {
                int eId = fromVert.edgeIds[i];
                // Since the graph is not directional
                // check the both ends
                if((edgeList[eId].vertexId0 == vertexId &&
                    edgeList[eId].vertexId1 == nextVertexId)
                ||
                   (edgeList[eId].vertexId0 == nextVertexId &&
                    edgeList[eId].vertexId1 == vertexId))
                {
                    edgeId = eId;
                    break;
                }
            }
        }
        if(edgeId != INVALID_INDEX)
        {
            const GraphEdge& edge = edgeList[edgeId];
            std::cout << "-" << std::setfill('-')
                      << std::setw(2)
                      << edge.weight << "->";
        }
        else
        {
            std::cout << "-##-> ";
        }
    }
    // Print endline on the last vertex if same line is set
    if(sameLine) std::cout << "\n";
    // Reset fill value because it "sticks" to the std out
    std::cout << std::setfill(' ');
    std::cout.flush();
}

int Graph::TotalVertexCount() const
{
    return vertexList.size();
}

int Graph::TotalEdgeCount() const
{
    return edgeList.size();
}

std::string Graph::VertexName(int vertexId) const
{
    return (vertexId<0 || vertexId>=TotalVertexCount())?"":vertexList[vertexId].name;
}

int Graph::TotalWeightInBetween(std::vector<int>& orderedVertexIdList)
{
    int TotalWeight = 0;
    for(int i=1; i<orderedVertexIdList.size(); i++){
        int vertexId0 = orderedVertexIdList[i-1];
        int vertexId1 = orderedVertexIdList[i];
        GraphVertex &vertex0 = vertexList[vertexId0];
        if(vertexId0 < TotalVertexCount() && vertexId1 < TotalVertexCount() && vertexId0 >= 0 && vertexId1 >= 0){
            for(int j=0; j<vertex0.edgeCount; j++){
                GraphEdge &edge = edgeList[vertex0.edgeIds[j]];
                if(edge.vertexId0 + edge.vertexId1 -  vertexId0 == vertexId1){
                    TotalWeight += edge.weight;
                }
            }
        }
        else{
            throw VertexNotFoundException();
        }
    }
    return TotalWeight;
}
