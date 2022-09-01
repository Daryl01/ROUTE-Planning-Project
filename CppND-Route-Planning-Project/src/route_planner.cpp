#include "route_planner.h"
#include <algorithm>

RoutePlanner::RoutePlanner(RouteModel &model, float start_x, float start_y, float end_x, float end_y): m_Model(model) {
    // Convert inputs to percentage:
    start_x *= 0.01;
    start_y *= 0.01;
    end_x *= 0.01;
    end_y *= 0.01;

    start_node = &m_Model.FindClosestNode(start_x, start_y);
    end_node = &m_Model.FindClosestNode(end_x, end_y);
}


// Calculate the H Value
float RoutePlanner::CalculateHValue(RouteModel::Node const *node) {
    return (*end_node).distance(*node);
}



// - Use the FindNeighbors() method of the current_node to populate current_node.neighbors vector with all the neighbors.
// - For each node in current_node.neighbors, set the parent, the h_value, the g_value. 
// - Use CalculateHValue below to implement the h-Value calculation.
// - For each node in current_node.neighbors, add the neighbor to open_list and set the node's visited attribute to true.

void RoutePlanner::AddNeighbors(RouteModel::Node *current_node) {
    current_node->FindNeighbors();
    for (auto *node : current_node->neighbors){
        // set the parent of the neighbor to the current node
        node->parent = current_node;
        // g_value of the neighbor is : current g_value + distance from the current node to othe neighbor
        node->g_value = current_node->g_value + (*node).distance(*current_node);
        node->h_value = CalculateHValue(node);
        open_list.emplace_back(node);
        node->visited = true;
    }
}


// NextNode method to sort the open list and return the next node.
bool Compare(RouteModel::Node *node1, RouteModel::Node *node2) {
    float sum1 = node1->g_value + node1->h_value;
    float sum2 = node2->g_value + node2->h_value;
    return sum1 > sum2;
}


RouteModel::Node *RoutePlanner::NextNode() {
    std::sort(open_list.begin(), open_list.end(), Compare);
    RouteModel::Node *lwNode = open_list.back();
    open_list.pop_back();
    return lwNode;
}



// - This method take the current (final) node as an argument and iteratively follow the 
//   chain of parents of nodes until the starting node is found.
// - For each node in the chain, add the distance from the node to its parent to the distance variable.
// - the start node is the first element of the vector, the end node should be the last element.

std::vector<RouteModel::Node> RoutePlanner::ConstructFinalPath(RouteModel::Node *current_node) {
  // Create path_found vector
  distance = 0.0f;
  std::vector<RouteModel::Node> path_found;
  
  RouteModel::Node parent_node;

  // TODO: Implement your solution here.
  while(current_node->parent != nullptr) {
    path_found.insert(path_found.begin(), *current_node);
    parent_node = *(current_node->parent);
    distance += current_node->distance(parent_node);
    current_node = current_node->parent;
  }
  
  path_found.insert(path_found.begin(), *current_node);
  
  // Multiply the distance by the scale of the map to get meters.
  distance *= m_Model.MetricScale(); 
  return path_found;
}


// the A* Search algorithm.
void RoutePlanner::AStarSearch() {
    RouteModel::Node *current_node = nullptr;
    

	// set start_node and add it to the open_list
    start_node->visited = true;
    start_node->g_value = 0.0;
    start_node->h_value = CalculateHValue(start_node);
    open_list.push_back(start_node);


    while (open_list.size() > 0)
    {
        current_node = NextNode();
        if (current_node != end_node) {
            AddNeighbors(current_node);
        } else {
            m_Model.path = ConstructFinalPath(current_node);
            break;
        }
    }
}