#pragma once
#include "Misc/PathfindingDetails.hpp"

#define SQRT2 1.41421356237f
#define MAX_MAP_HEIGHT (size_t)40
#define MAX_MAP_WIDTH (size_t)40

class AStarPather
{
public:
    /* 
        The class should be default constructible, so you may need to define a constructor.
        If needed, you can modify the framework where the class is constructed in the
        initialize functions of ProjectTwo and ProjectThree.
    */

    AStarPather()  = default;


    /* ************************************************** */
    // DO NOT MODIFY THESE SIGNATURES
    bool initialize();
    void shutdown();
    PathResult compute_path(PathRequest &request);
    /* ************************************************** */

    /*
        You should create whatever functions, variables, or classes you need.
        It doesn't all need to be in this header and cpp, structure it whatever way
        makes sense to you.
    */

    enum class eList : USHORT {
        NA=0,
        OPEN,
        CLOSED
    };

    struct Node {

        float finalcost;
        float givencost;
        eList onlist;
        GridPos gPosition;
        Node* Parent;
        
    };

    float lowest;

    GridPos startgpos, goalgpos;

    std::array<Node, MAX_MAP_HEIGHT* MAX_MAP_WIDTH> GridArr;

    float heuristicCalculation(Heuristic method,const GridPos step1, const GridPos step2);

    void Path_Smoothing(WaypointList& pathList);

    void Path_Rubberbanding(PathRequest& request);

    bool ClearNodes();

    std::vector<Node> OpenList;

    void PopNode(GridPos Node_Pos);
};