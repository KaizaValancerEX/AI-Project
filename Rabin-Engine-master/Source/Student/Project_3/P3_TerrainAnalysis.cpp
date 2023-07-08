#include <pch.h>
#include "Terrain/TerrainAnalysis.h"
#include "Terrain/MapMath.h"
#include "Agent/AStarAgent.h"
#include "Terrain/MapLayer.h"
#include "Projects/ProjectThree.h"

#include <iostream>

bool ProjectThree::implemented_fog_of_war() const // extra credit
{
	return false;
}

float distance_to_closest_wall(int row, int col)
{
	/*
		Check the euclidean distance from the given cell to every other wall cell,
		with cells outside the map bounds treated as walls, and return the smallest
		distance.  Make use of the is_valid_grid_position and is_wall member
		functions in the global terrain to determine if a cell is within map bounds
		and a wall, respectively.
	*/

	// WRITE YOUR CODE HERE

	int height = terrain->get_map_height();
	int width = terrain->get_map_width();

	float closestwalldist = 1000.f;
	float currwalldist = 0.f;

	for (int i = -1; i < width + 1; i++) {
		for (int j = -1; j < height + 1; j++) {
			if (i == row && j == col) continue;
			if (!terrain->is_valid_grid_position(i, j)) {

				float xdiff = (float)fabs((float)i - (float)row);
				float ydiff = (float)fabs((float)j - (float)col);
				currwalldist = sqrtf((xdiff * xdiff) + (ydiff * ydiff));

				if (currwalldist < closestwalldist) {
					closestwalldist = currwalldist;
				}
			}

			else if (terrain->is_valid_grid_position(i, j)) {
				if (terrain->is_wall(i, j)) {
					float xdiff = (float)fabs((float)i - (float)row);
					float ydiff = (float)fabs((float)j - (float)col);
					currwalldist = sqrtf((xdiff * xdiff) + (ydiff * ydiff));

					if (currwalldist < closestwalldist) {
						closestwalldist = currwalldist;
					}
				}
			}

		}
	}


	return closestwalldist; // REPLACE THIS
}

bool is_clear_path(int row0, int col0, int row1, int col1)
{
	/*
		Two cells (row0, col0) and (row1, col1) are visible to each other if a line
		between their centerpoints doesn't intersect the four boundary lines of every
		wall cell.  You should puff out the four boundary lines by a very tiny amount
		so that a diagonal line passing by the corner will intersect it.  Make use of the
		line_intersect helper function for the intersection test and the is_wall member
		function in the global terrain to determine if a cell is a wall or not.
	*/

	// WRITE YOUR CODE HERE
	int leftRow{}, rightRow{}, aboveCol{}, belowCol{};
	GridPos P0Gridpos{ row0,col0 };
	GridPos P1Gridpos{ row1,col1 };

	if (P0Gridpos.row < P1Gridpos.row) {
		leftRow = P0Gridpos.row;
		rightRow = P1Gridpos.row;
	}

	else if (P0Gridpos.row >= P1Gridpos.row) {
		leftRow = P1Gridpos.row;
		rightRow = P0Gridpos.row;
	}

	if (P0Gridpos.col < P1Gridpos.col) {
		aboveCol = P1Gridpos.col;
		belowCol = P0Gridpos.col;
	}

	else if (P0Gridpos.col >= P1Gridpos.col) {
		aboveCol = P0Gridpos.col;
		belowCol = P1Gridpos.col;
	}

	for (int x = leftRow; x < rightRow + 1; x++) {
		for (int y = belowCol; y < aboveCol + 1; y++) {
			if (terrain->is_wall(x, y)) {
				if (line_intersect(Vec2{ x - 0.51f,y + 0.51f }, Vec2{ x + 0.51f,y + 0.51f }, Vec2{ (float)row0,(float)col0 }, Vec2{ (float)row1,(float)col1 })) return false;
				if (line_intersect(Vec2{ x + 0.51f,y + 0.51f }, Vec2{ x + 0.51f,y - 0.51f }, Vec2{ (float)row0,(float)col0 }, Vec2{ (float)row1,(float)col1 })) return false;
				if (line_intersect(Vec2{ x + 0.51f,y - 0.51f }, Vec2{ x - 0.51f,y - 0.51f }, Vec2{ (float)row0,(float)col0 }, Vec2{ (float)row1,(float)col1 })) return false;
				if (line_intersect(Vec2{ x - 0.51f,y - 0.51f }, Vec2{ x - 0.51f,y + 0.51f }, Vec2{ (float)row0,(float)col0 }, Vec2{ (float)row1,(float)col1 })) return false;
			}
		}
	}

	return true;
}

void analyze_openness(MapLayer<float>& layer)
{
	/*
		Mark every cell in the given layer with the value 1 / (d * d),
		where d is the distance to the closest wall or edge.  Make use of the
		distance_to_closest_wall helper function.  Walls should not be marked.
	*/

	int mHeight = terrain->get_map_height();
	int mWidth = terrain->get_map_width();

	for (int i = 0; i < mWidth; i++) {
		for (int j = 0; j < mHeight; j++) {

			float d = distance_to_closest_wall(i, j);

			if (terrain->is_wall(i, j)) continue;
			else {
				layer.set_value(GridPos{ i,j }, (1.f / (d * d)));
			}

		}
	}
}

void analyze_visibility(MapLayer<float>& layer)
{
	/*
		Mark every cell in the given layer with the number of cells that
		are visible to it, divided by 160 (a magic number that looks good).  Make sure
		to cap the value at 1.0 as well.

		Two cells are visible to each other if a line between their centerpoints doesn't
		intersect the four boundary lines of every wall cell.  Make use of the is_clear_path
		helper function.
	*/

	// WRITE YOUR CODE HERE

	int mHeight = terrain->get_map_height();
	int mWidth = terrain->get_map_width();
	float cellcount{};

	for (int i = 0; i < mWidth; i++) {
		for (int j = 0; j < mHeight; j++) {
			cellcount = 0;
			if (terrain->is_wall(i, j)) continue;

			for (int x = 0; x < mWidth; x++) {
				for (int y = 0; y < mHeight; y++) {
					if (terrain->is_wall(x, y)) continue;
					if (x == i && y == j) continue;

					if (is_clear_path(i, j, x, y)) cellcount++;

				}
			}

			cellcount = cellcount / 160.f;
			if (cellcount > 1.f) cellcount = 1.f;

			layer.set_value(GridPos{ i,j }, cellcount);

		}

	}



}

void analyze_visible_to_cell(MapLayer<float>& layer, int row, int col)
{
	/*
		For every cell in the given layer mark it with 1.0
		if it is visible to the given cell, 0.5 if it isn't visible but is next to a visible cell,
		or 0.0 otherwise.

		Two cells are visible to each other if a line between their centerpoints doesn't
		intersect the four boundary lines of every wall cell.  Make use of the is_clear_path
		helper function.
	*/

	// WRITE YOUR CODE HERE
	int mHeight = terrain->get_map_height();
	int mWidth = terrain->get_map_width();

	for (int i = 0; i < mWidth; i++) {
		for (int j = 0; j < mHeight; j++) {
			layer.set_value(GridPos{ i,j }, 0.f);
		}
	}

	for (int i = 0; i < mWidth; i++) {
		for (int j = 0; j < mHeight; j++) {
			if (terrain->is_wall(i, j)) continue;

			if (is_clear_path(i, j, row, col)) {
				layer.set_value(GridPos{ i,j }, 1.f);

				for (int r = -1; r < 2; r++) {
					for (int c = -1; c < 2; c++) {
						if (r == 0 && c == 0) continue;
						if ((i + r) < 0 || (i + r) >= mWidth) continue;
						if ((j + c) < 0 || (j + c) >= mHeight) continue;
						if (terrain->is_wall(GridPos{ i + r, j + c })) continue;

						if (layer.get_value(GridPos{ i + r,j + c }) != 1) {
							layer.set_value(GridPos{ i + r,j + c }, 0.5f);
						}
					}
				}
			}
		}
	}

}

void analyze_agent_vision(MapLayer<float>& layer, const Agent* agent)
{
	/*
		For every cell in the given layer that is visible to the given agent,
		mark it as 1.0, otherwise don't change the cell's current value.

		You must consider the direction the agent is facing.  All of the agent data is
		in three dimensions, but to simplify you should operate in two dimensions, the XZ plane.

		Take the dot product between the view vector and the vector from the agent to the cell,
		both normalized, and compare the cosines directly instead of taking the arccosine to
		avoid introducing floating-point inaccuracy (larger cosine means smaller angle).

		Give the agent a field of view slighter larger than 180 degrees.

		Two cells are visible to each other if a line between their centerpoints doesn't
		intersect the four boundary lines of every wall cell.  Make use of the is_clear_path
		helper function.
	*/

	// WRITE YOUR CODE HERE
	int mHeight = terrain->get_map_height();
	int mWidth = terrain->get_map_width();

	GridPos agentPos = terrain->get_grid_position(agent->get_position());
	Vec2 agentvwVec = Vec2{ agent->get_forward_vector().x,agent->get_forward_vector().z };


	for (int i = 0; i < mWidth; i++) {
		for (int j = 0; j < mHeight; j++) {
			Vec2 agenttocellVec = Vec2{ (float)i - agentPos.row,(float)j - agentPos.col };

			if (agentvwVec.Dot(agenttocellVec) < -0.1) continue;

			if (is_clear_path(i, j, agentPos.row, agentPos.col)) {
				layer.set_value(GridPos{ i,j }, 1.f);
			}

		}
	}

}

void propagate_solo_occupancy(MapLayer<float>& layer, float decay, float growth)
{
	/*
		For every cell in the given layer:

			1) Get the value of each neighbor and apply decay factor
			2) Keep the highest value from step 1
			3) Linearly interpolate from the cell's current value to the value from step 2
			   with the growing factor as a coefficient.  Make use of the lerp helper function.
			4) Store the value from step 3 in a temporary layer.
			   A float[40][40] will suffice, no need to dynamically allocate or make a new MapLayer.

		After every cell has been processed into the temporary layer, write the temporary layer into
		the given layer;
	*/

	// WRITE YOUR CODE HERE
	int mHeight = terrain->get_map_height();
	int mWidth = terrain->get_map_width();
	float TempMapArr[40][40] = {};
	float N_oldInfluence{};
	float N_newInfluence{};
	float N_highestInfluence{};
	float currCellInfluence{};
	float distance{};

	for (int i = 0; i < mWidth; i++) {
		for (int j = 0; j < mHeight; j++) {

			if (terrain->is_wall(i, j)) continue;


			for (int r = -1; r < 2; r++) {
				for (int c = -1; c < 2; c++) {
					if (r == 0 && c == 0) continue;
					if ((i + r) < 0 || (i + r) >= mWidth) continue;
					if ((j + c) < 0 || (j + c) >= mHeight) continue;
					if (terrain->is_wall(GridPos{ i + r, j + c })) continue;
					if (terrain->is_wall(i+r, j) ||
						terrain->is_wall(i, j+c)) continue;


					float xdiff = fabs(((float)i + (float)r) - (float)i);
					float ydiff = fabs(((float)j + (float)c) - (float)j);

					distance = sqrtf((xdiff * xdiff) + (ydiff * ydiff));
					N_oldInfluence = layer.get_value(i + r, j + c);
					//step 1 - apply decay factor
					N_newInfluence = N_oldInfluence * exp(-1.f * distance * decay);

					//step 2 - Keep highest value among neighbours in step 1
					if (N_newInfluence > N_highestInfluence) N_highestInfluence = N_newInfluence;
				}
			}
			currCellInfluence = layer.get_value(i, j);
			//step 3 - Linearly interpolate cell current value to step 2
			//step 4 -store value in step 3 into temp layer
			TempMapArr[i][j] = lerp(currCellInfluence, N_highestInfluence, growth);


			N_highestInfluence = 0;
		}
	}

	//final step - overwrite maplayer with temp layer
	for (int i = 0; i < mWidth; i++) {
		for (int j = 0; j < mHeight; j++) {
			layer.set_value(i, j, TempMapArr[i][j]);
		}
	}
}

void propagate_dual_occupancy(MapLayer<float>& layer, float decay, float growth)
{
	/*
		Similar to the solo version, but the values range from -1.0 to 1.0, instead of 0.0 to 1.0

		For every cell in the given layer:

		1) Get the value of each neighbor and apply decay factor
		2) Keep the highest ABSOLUTE value from step 1
		3) Linearly interpolate from the cell's current value to the value from step 2
		   with the growing factor as a coefficient.  Make use of the lerp helper function.
		4) Store the value from step 3 in a temporary layer.
		   A float[40][40] will suffice, no need to dynamically allocate or make a new MapLayer.

		After every cell has been processed into the temporary layer, write the temporary layer into
		the given layer;
	*/

	// WRITE YOUR CODE HERE
	int mHeight = terrain->get_map_height();
	int mWidth = terrain->get_map_width();
	float TempMapArr[40][40] = {};
	float N_oldInfluence{};
	float N_newInfluence{};
	float N_highestInfluence{};
	float currCellInfluence{};
	float distance{};

	for (int i = 0; i < mWidth; i++) {
		for (int j = 0; j < mHeight; j++) {

			if (terrain->is_wall(i, j)) continue;


			for (int r = -1; r < 2; r++) {
				for (int c = -1; c < 2; c++) {
					if (r == 0 && c == 0) continue;
					if ((i + r) < 0 || (i + r) >= mWidth) continue;
					if ((j + c) < 0 || (j + c) >= mHeight) continue;
					if (terrain->is_wall(GridPos{ i + r, j + c })) continue;


					float xdiff = fabs(((float)i + (float)r) - (float)i);
					float ydiff = fabs(((float)j + (float)c) - (float)j);

					distance = sqrtf((xdiff * xdiff) + (ydiff * ydiff));
					N_oldInfluence = layer.get_value(i + r, j + c);
					//step 1 - apply decay factor
					N_newInfluence = N_oldInfluence * exp(-1.f * distance * decay);

					//step 2 - Keep highest ABSOLUTE value among neighbours in step 1
					if (fabs(N_newInfluence) > N_highestInfluence) N_highestInfluence = fabs(N_newInfluence);
				}
			}
			currCellInfluence = layer.get_value(i, j);
			//step 3 - Linearly interpolate cell current value to step 2
			//step 4 -store value in step 3 into temp layer
			TempMapArr[i][j] = lerp(currCellInfluence, N_highestInfluence, growth);


			N_highestInfluence = 0;
		}
	}

	//final step - overwrite maplayer with temp layer
	for (int i = 0; i < mWidth; i++) {
		for (int j = 0; j < mHeight; j++) {
			layer.set_value(i, j, TempMapArr[i][j]);
		}
	}
}

void normalize_solo_occupancy(MapLayer<float>& layer)
{
	/*
		Determine the maximum value in the given layer, and then divide the value
		for every cell in the layer by that amount.  This will keep the values in the
		range of [0, 1].  Negative values should be left unmodified.
	*/

	// WRITE YOUR CODE HERE
	int mHeight = terrain->get_map_height();
	int mWidth = terrain->get_map_width();
	float tempMapArr[40][40] = {};
	float max_Value = 0;
	float get_Value{};
	float new_Value = 0;

	for (int i = 0; i < mWidth; i++) {
		for (int j = 0; j < mHeight; j++) {
			get_Value = layer.get_value(i, j);

			if (terrain->is_wall(i, j)) continue;

			if (get_Value > max_Value) max_Value = get_Value;
		}
	}

	for (int i = 0; i < mWidth; i++) {
		for (int j = 0; j < mHeight; j++) {
			get_Value = layer.get_value(i, j);

			if (terrain->is_wall(i, j)) continue;
			if (get_Value < 0) continue;
			else {
				new_Value = get_Value / max_Value;


				tempMapArr[i][j] = new_Value;
				//layer.set_value(i, j, new_Value);
			}
		}
	}

	for (int i = 0; i < mWidth; i++) {
		for (int j = 0; j < mHeight; j++) {
			get_Value = layer.get_value(i, j);

			if (terrain->is_wall(i, j)) continue;
			if (get_Value < 0) continue;

			layer.set_value(i, j, tempMapArr[i][j]);

		}
	}
	

}

void normalize_dual_occupancy(MapLayer<float>& layer)
{
	/*
		Similar to the solo version, but you need to track greatest positive value AND
		the least (furthest from 0) negative value.

		For every cell in the given layer, if the value is currently positive divide it by the
		greatest positive value, or if the value is negative divide it by -1.0 * the least negative value
		(so that it remains a negative number).  This will keep the values in the range of [-1, 1].
	*/

	// WRITE YOUR CODE HERE

	int mHeight = terrain->get_map_height();
	int mWidth = terrain->get_map_width();
	float tempMapArr[40][40] = {};
	float max_Value = 0;
	float min_Value = 1000;
	float get_Value{};
	float new_Value{};

	for (int i = 0; i < mWidth; i++) {
		for (int j = 0; j < mHeight; j++) {
			if (terrain->is_wall(i, j)) continue;
			get_Value = layer.get_value(i, j);

			if (get_Value > max_Value && get_Value > 0) max_Value = get_Value;
			if (get_Value < min_Value && get_Value < 0) min_Value = get_Value;
		}
	}


	for (int i = 0; i < mWidth; i++) {
		for (int j = 0; j < mHeight; j++) {
			if (terrain->is_wall(i, j)) continue;
			get_Value = layer.get_value(i, j);

			if (get_Value < 0) {
				new_Value = get_Value;
				new_Value = new_Value / (-1.f * min_Value);
				tempMapArr[i][j] = new_Value;
			}

			else if (get_Value >= 0) {
				new_Value = get_Value / max_Value;
				tempMapArr[i][j] = new_Value;
			}
		}
	}

	for (int i = 0; i < mWidth; i++) {
		for (int j = 0; j < mHeight; j++) {
			if (terrain->is_wall(i, j)) continue;

			layer.set_value(i, j, tempMapArr[i][j]);

		}
	}
}

void enemy_field_of_view(MapLayer<float>& layer, float fovAngle, float closeDistance, float occupancyValue, AStarAgent* enemy)
{
	/*
		First, clear out the old values in the map layer by setting any negative value to 0.
		Then, for every cell in the layer that is within the field of view cone, from the
		enemy agent, mark it with the occupancy value.  Take the dot product between the view
		vector and the vector from the agent to the cell, both normalized, and compare the
		cosines directly instead of taking the arccosine to avoid introducing floating-point
		inaccuracy (larger cosine means smaller angle).

		If the tile is close enough to the enemy (less than closeDistance),
		you only check if it's visible to enemy.  Make use of the is_clear_path
		helper function.  Otherwise, you must consider the direction the enemy is facing too.
		This creates a radius around the enemy that the player can be detected within, as well
		as a fov cone.
	*/

	// WRITE YOUR CODE HERE

	int mHeight = terrain->get_map_height();
	int mWidth = terrain->get_map_width();
	float currcellvalue{};
	GridPos enemyPos = terrain->get_grid_position(enemy->get_position());
	Vec2 enemyvwVec = Vec2{ enemy->get_forward_vector().x,enemy->get_forward_vector().z };


	//clear out all negative values to 0
	for (int i = 0; i < mWidth; i++) {
		for (int j = 0; j < mHeight; j++) {
			currcellvalue = layer.get_value(i, j);
			if (terrain->is_wall(i, j))continue;

			if (currcellvalue < 0) layer.set_value(i, j, 0.f);

		}
	}

	for (int i = 0; i < mWidth; i++) {
		for (int j = 0; j < mHeight; j++) {
			Vec2 enemytocellVec = Vec2{ (float)i - enemyPos.row,(float)j - enemyPos.col };

			if (enemyvwVec.Dot(enemytocellVec) < -0.1) continue;

			if (is_clear_path(i, j, enemyPos.row, enemyPos.col)) {
				layer.set_value(GridPos{ i,j }, 1.f);
			}

		}
	}


	//for every cell within fov cone

		//Mark with the occupancy value

		//dot product view vector and vector  from agent to cell

		//if tile < closeDistance
			//check if tile is visible to enemy
}

bool enemy_find_player(MapLayer<float>& layer, AStarAgent* enemy, Agent* player)
{
	/*
		Check if the player's current tile has a negative value, ie in the fov cone
		or within a detection radius.
	*/

	const auto& playerWorldPos = player->get_position();

	const auto playerGridPos = terrain->get_grid_position(playerWorldPos);

	// verify a valid position was returned
	if (terrain->is_valid_grid_position(playerGridPos) == true)
	{
		if (layer.get_value(playerGridPos) < 0.0f)
		{
			return true;
		}
	}

	// player isn't in the detection radius or fov cone, OR somehow off the map
	return false;
}

bool enemy_seek_player(MapLayer<float>& layer, AStarAgent* enemy)
{
	/*
		Attempt to find a cell with the highest nonzero value (normalization may
		not produce exactly 1.0 due to floating point error), and then set it as
		the new target, using enemy->path_to.

		If there are multiple cells with the same highest value, then pick the
		cell closest to the enemy.

		Return whether a target cell was found.
	*/

	// WRITE YOUR CODE HERE

	return false; // REPLACE THIS
}
