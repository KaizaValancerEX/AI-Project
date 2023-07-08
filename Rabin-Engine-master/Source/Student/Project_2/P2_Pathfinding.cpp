#include <pch.h>
#include "Projects/ProjectTwo.h"
#include "P2_Pathfinding.h"


#pragma region Extra Credit
bool ProjectTwo::implemented_floyd_warshall()
{
	return false;
}

bool ProjectTwo::implemented_goal_bounding()
{
	return false;
}

bool ProjectTwo::implemented_jps_plus()
{
	return false;
}
#pragma endregion

bool AStarPather::initialize()
{
	// handle any one-time setup requirements you have

	//VecVecNode = std::vector(40, std::vector<Node*>(40, nullptr));

	//GridArr = new Node[MAX_MAP_HEIGHT * MAX_MAP_WIDTH];

	for (int i = 0; i < MAX_MAP_WIDTH; i++) {
		for (int j = 0; j < MAX_MAP_HEIGHT; j++) {

			//Node* tNode = &GridArr[i + MAX_MAP_WIDTH * j];

			//tNode->Parent = NULL;
			//tNode->gPosition = GridPos{ i,j };
			//tNode->finalcost = 0.f;
			//tNode->givencost = 0.f;
			//tNode->onlist = AStarPather::eList::NA;

			GridArr[(size_t)(i + MAX_MAP_WIDTH * j)].Parent = NULL;
			GridArr[(size_t)i + MAX_MAP_WIDTH * j].gPosition = GridPos{ i,j };
			GridArr[(size_t)i + MAX_MAP_WIDTH * j].finalcost = 0.f;
			GridArr[(size_t)i + MAX_MAP_WIDTH * j].givencost = 0.f;
			GridArr[(size_t)i + MAX_MAP_WIDTH * j].onlist = AStarPather::eList::NA;

		}
	}

	/*
		If you want to do any map-preprocessing, you'll need to listen
		for the map change message.  It'll look something like this:

		Callback cb = std::bind(&AStarPather::your_function_name, this);
		Messenger::listen_for_message(Messages::MAP_CHANGE, cb);

		There are other alternatives to using std::bind, so feel free to mix it up.
		Callback is just a typedef for std::function<void(void)>, so any std::invoke'able
		object that std::function can wrap will suffice.
	*/

	return true; // return false if any errors actually occur, to stop engine initialization
}

void AStarPather::shutdown()
{
	/*
		Free any dynamically allocated memory or any other general house-
		keeping you need to do during shutdown.
	*/
}

PathResult AStarPather::compute_path(PathRequest& request)
{

	startgpos = terrain->get_grid_position(request.start);
	goalgpos = terrain->get_grid_position(request.goal);
	int start_idx = startgpos.row + MAX_MAP_WIDTH * startgpos.col;

	if (request.settings.debugColoring)
	{
		terrain->set_color(startgpos, Colors::Green);
		terrain->set_color(goalgpos, Colors::Red);
	}

	//This is where you handle pathing requests, each request has several fields:

	//start/goal - start and goal world positions
	//path - where you will build the path upon completion, path should be
	//	start to goal, not goal to start
	//heuristic - which heuristic calculation to use
	//heuristicCalculation(request.settings.heuristic, Vec2{});
	//weight - the heuristic weight to be applied
	//hcost = hcost * request.settings.weight;


	//newRequest - whether this is the first request for this path, should generally
	//be true, unless single step is on
	//If(request.newRequest)
	if (request.newRequest /*|| request.settings.singleStep*/) {
		//    Initialize everything.Clear Open / Closed Lists.
		ClearNodes();
		OpenList.clear();
		//    Push Start Node onto the Open List with cost of f(x) = g(x) + h(x).
		GridArr[start_idx].givencost = 0.f;
		GridArr[start_idx].finalcost = heuristicCalculation(request.settings.heuristic, startgpos, goalgpos) * request.settings.weight;
		GridArr[start_idx].gPosition = terrain->get_grid_position(request.start);
		GridArr[start_idx].onlist = eList::OPEN;
		GridArr[start_idx].Parent = NULL;
		//tNode->gPostion = request.start;
		OpenList.push_back(GridArr[start_idx]);

	}


	//While(Open List is not empty) {
	while (!OpenList.empty()) {
		//parentNode = Pop cheapest node off Open List.
		Node pNode;
		int pNode_idx = 0;

		int index = 0;
		int cheapo = 0;
		lowest = OpenList[0].finalcost;
		for (const Node& node : OpenList)
		{
			if (node.finalcost < lowest) {
				lowest = node.finalcost;

				cheapo = index;
			}


			index++;
		}
		pNode = OpenList[cheapo];
		pNode_idx = pNode.gPosition.row + MAX_MAP_WIDTH * pNode.gPosition.col;




		OpenList.erase(OpenList.begin() + cheapo);


		//Place parentNode on the Closed List.
		pNode.onlist = eList::CLOSED;
		GridArr[pNode_idx] = pNode;
		if (request.settings.debugColoring) terrain->set_color(pNode.gPosition, Colors::Yellow);

		//If parentNode is the Goal Node, then path found(return PathResult::COMPLETE).
		if (pNode.gPosition == goalgpos) {
			while (pNode.Parent != NULL) {
				request.path.emplace_front(terrain->get_world_position(pNode.gPosition));

				pNode = *pNode.Parent;

				if (pNode.Parent == NULL)
					request.path.emplace_front(terrain->get_world_position(pNode.gPosition));
			}


			////rubberBanding - whether to apply rubber banding
			if (request.settings.rubberBanding == true) Path_Rubberbanding(request);

			////smoothing - whether to apply smoothing to the path
			if (request.settings.smoothing == true) Path_Smoothing(request.path);


			return PathResult::COMPLETE;
		}



		//For(all valid neighboring child nodes of parentNode) {
		for (int i = -1; i < 2; i++) {
			int crow = pNode.gPosition.row + i;

			for (int j = -1; j < 2; j++) {
				int ccol = pNode.gPosition.col + j;
				if (!terrain->is_valid_grid_position(crow, ccol) ||
					terrain->is_wall(crow, ccol) ||
					(i == 0 && j == 0)) continue;
				//if (GridArr[crow + MAX_MAP_WIDTH * ccol].onlist == eList::CLOSED) continue;


				int cNode_idx = crow + MAX_MAP_WIDTH * ccol;
				Node cNode = GridArr[cNode_idx];
				if (i != 0 && j != 0) {
					if (terrain->is_wall(crow, pNode.gPosition.col) ||
						terrain->is_wall(pNode.gPosition.row, ccol)) continue;
					cNode.givencost = pNode.givencost + SQRT2;
				}
				else
				{
					cNode.givencost = pNode.givencost + 1;
				}

				//Compute its cost, f(x) = g(x) + h(x)

				cNode.gPosition = GridPos{ crow, ccol };
				cNode.finalcost = cNode.givencost + (heuristicCalculation(request.settings.heuristic, cNode.gPosition, goalgpos) * request.settings.weight);

				//If child node isn’t on Open or Closed list, put it on Open List.
				if (cNode.onlist == eList::NA) {
					cNode.Parent = &GridArr[pNode.gPosition.row + MAX_MAP_WIDTH * pNode.gPosition.col];
					cNode.onlist = eList::OPEN;
					OpenList.push_back(cNode);
					if (request.settings.debugColoring) terrain->set_color(cNode.gPosition, Colors::Blue);
					GridArr[cNode_idx] = cNode;
				}

				//Else if child node is on Open or Closed List, AND this new one is cheaper,
				//then take the old expensive one off both listsand put this new
				//cheaper one on the Open List.
				else if (GridArr[cNode_idx].finalcost > cNode.finalcost) {

					if (cNode.onlist == eList::CLOSED) {
						cNode.Parent = &GridArr[pNode.gPosition.row + MAX_MAP_WIDTH * pNode.gPosition.col];
						cNode.onlist = eList::OPEN;
						OpenList.push_back(cNode);
						if (request.settings.debugColoring) terrain->set_color(cNode.gPosition, Colors::Blue);
						GridArr[cNode_idx] = cNode;
					}


					else if (cNode.onlist == eList::OPEN) {
						cNode.Parent = &GridArr[pNode.gPosition.row + MAX_MAP_WIDTH * pNode.gPosition.col];
						for (auto& ol : OpenList) {
							if (ol.gPosition == cNode.gPosition) {
								ol = cNode;
								GridArr[cNode_idx] = cNode;
							}
						}
					}
				}
			}
		}


		//    If taken too much time this frame(or if request.settings.singleStep == true),
		//        abort search for nowand resume next frame(return PathResult::PROCESSING).
		if (request.settings.singleStep == true/*or if time > dt*/) {
			return PathResult::PROCESSING;
		}


	}
	//Open List empty, thus no path possible(return PathResult::IMPOSSIBLE).
	return PathResult::IMPOSSIBLE;





	//method - which algorithm to use: A*, Floyd-Warshall, JPS+, or goal bounding,
	//	will be A* generally, unless you implement extra credit features

	//The return values are:
	//	PROCESSING - a path hasn't been found yet, should only be returned in
	//		single step mode until a path is found
	//	COMPLETE - a path to the goal was found and has been built in request.path
	//	IMPOSSIBLE - a path from start to goal does not exist, do not add start position to path



	//// Just sample code, safe to delete
	//GridPos start = terrain->get_grid_position(request.start);
	//GridPos goal = terrain->get_grid_position(request.goal);
	//terrain->set_color(start, Colors::Green);
	//terrain->set_color(goal, Colors::Red);
	//request.path.push_back(request.start);
	//request.path.push_back(request.goal);
	//return PathResult::COMPLETE;
}

float AStarPather::heuristicCalculation(Heuristic method, GridPos Origin, GridPos Dest)
{
	float xdiff = fabs((float)Dest.row - (float)Origin.row),
		ydiff = fabs((float)Dest.col - (float)Origin.col);



	switch (method)
	{
	case Heuristic::OCTILE:
		//min(xDiff, yDiff)* sqrt(2) + max(xDiff, yDiff) – min(xDiff, yDiff)

		return std::min(xdiff, ydiff) * (SQRT2)+(std::max(xdiff, ydiff) - std::min(xdiff, ydiff));

		break;
	case Heuristic::CHEBYSHEV:
		//max(xDiff, yDiff)

		return std::max(xdiff, ydiff);

		break;

	case Heuristic::MANHATTAN:
		//xDiff + yDiff

		return xdiff + ydiff;

		break;
	case Heuristic::INCONSISTENT:
		if ((Origin.row + Origin.col) % 2 == 0)
		{
			return sqrtf((xdiff * xdiff) + (ydiff * ydiff));
		}
		else {
			return 0.f;
		}

		break;
	case Heuristic::EUCLIDEAN:
		//sqrt(xDiff2 + yDiff2)

		return sqrtf((xdiff * xdiff) + (ydiff * ydiff));

		break;
	default:
		break;
	}

	return 0.f;
}

void AStarPather::Path_Smoothing(WaypointList& pathList)
{
	if (pathList.size() >= 3) {
		int start_idx = -1;
		int end_idx = 2;

		std::vector<Vec3> smoothingPoints;
		std::vector<Vec3> workPoints = { Vec3{},Vec3{},Vec3{},Vec3{} };
		Vec3 tPoint{};

		WaypointList::iterator p1st{}, p2nd{}, p3rd{}, p4th{};

		while (end_idx != pathList.size() + 1) {
			p1st = p2nd = p3rd = p4th = pathList.begin();
			for (int i = 0; i < start_idx; i++) {
				std::advance(p1st, 1);
			}

			for (int i = 0; i < start_idx+1; i++) {
				std::advance(p2nd, 1);
			}
			for (int i = 0; i < start_idx+2; i++) {
				std::advance(p3rd, 1);
			}
			for (int i = 0; i < start_idx+3; i++) {
				std::advance(p4th, 1);
			}


			if (p4th == pathList.end()) {
				p4th = p3rd;
			}

			workPoints[0] = *p1st;
			workPoints[1] = *p2nd;
			workPoints[2] = *p3rd;
			workPoints[3] = *p4th;

			tPoint = tPoint.CatmullRom(workPoints[0], workPoints[1], workPoints[2], workPoints[3], 0.25f);
			smoothingPoints.push_back(tPoint);
			tPoint = tPoint.CatmullRom(workPoints[0], workPoints[1], workPoints[2], workPoints[3], 0.5f);
			smoothingPoints.push_back(tPoint);
			tPoint = tPoint.CatmullRom(workPoints[0], workPoints[1], workPoints[2], workPoints[3], 0.75f);
			smoothingPoints.push_back(tPoint);


			start_idx++;
			end_idx++;
		}

		int idx = 0;
		WaypointList::iterator tempIt = pathList.begin();
		while (idx < smoothingPoints.size()) {
			tempIt++;
			pathList.insert(tempIt, smoothingPoints[idx++]);
			pathList.insert(tempIt, smoothingPoints[idx++]);
			pathList.insert(tempIt, smoothingPoints[idx++]);
		}
	}

	return;
}

void AStarPather::Path_Rubberbanding(PathRequest& request)
{
	if (request.path.size() >= 3) {
		size_t start_idx = 0,
			end_idx = 2;


		while (end_idx != request.path.size()) {

			int i{}, leftRow{}, rightRow{}, aboveCol{}, belowCol{};
			bool wallfound = false;
			WaypointList::iterator p1{}, p2{}, p3{};

			p1 = request.path.begin();
			for (; i < start_idx; i++) {
				p1++;
			}
			p3 = p1;
			std::advance(p3, 2);

			GridPos GridPathStart = terrain->get_grid_position(*p1);
			GridPos GridPathEnd = terrain->get_grid_position(*p3);

			if (GridPathStart.row < GridPathEnd.row) {
				leftRow = GridPathStart.row;
				rightRow = GridPathEnd.row;
			}

			else if (GridPathStart.row >= GridPathEnd.row) {
				leftRow = GridPathEnd.row;
				rightRow = GridPathStart.row;
			}

			if (GridPathStart.col < GridPathEnd.col) {
				aboveCol = GridPathEnd.col;
				belowCol = GridPathStart.col;
			}

			else if (GridPathStart.col >= GridPathEnd.col) {
				aboveCol = GridPathStart.col;
				belowCol = GridPathEnd.col;
			}

			for (int x = leftRow; x < rightRow + 1; x++) {
				for (int y = belowCol; y < aboveCol + 1; y++) {
					if (terrain->is_wall(x, y)) wallfound = true;
					if (wallfound) break;
				}
				if (wallfound) break;
			}

			if (wallfound) {
				start_idx++;
				end_idx++;
			}

			else {
				p2 = p1;
				std::advance(p2, 1);
				request.path.erase(p2);
			}
		}

		if (request.settings.smoothing == true) {
			start_idx = 0;
			end_idx = 1;

			while (end_idx != request.path.size()) {
				WaypointList::iterator sP{}, eP{};

				sP = request.path.begin();
				for (int i = 0; i < start_idx; i++) {
					sP++;
				}
				eP = sP;
				std::advance(eP, 1);

				GridPos GridPathStart = terrain->get_grid_position(*sP);
				GridPos GridPathEnd = terrain->get_grid_position(*eP);
				

				float xdiff = (float)GridPathStart.col - (float)GridPathEnd.col;
				float ydiff = (float)GridPathStart.row - (float)GridPathEnd.row;
				float distance = sqrtf((xdiff * xdiff) + (ydiff * ydiff));

				if (distance > 1.5f) {
					GridPos tpoint = GridPos{ (GridPathStart.row + GridPathEnd.row) / 2,(GridPathStart.col + GridPathEnd.col) / 2 };
					request.path.insert(eP, terrain->get_world_position(tpoint));
				}

				else {
					start_idx++;
					end_idx++;
				}

			}	
		}
	}

	return;

}

bool AStarPather::ClearNodes()
{

	for (auto& elem : GridArr) {
		elem.Parent = nullptr;
		elem.gPosition = {};
		elem.finalcost = INFINITE;
		elem.givencost = INFINITE;
		elem.onlist = eList::NA;
	}

	return true;
}
