#include <iostream>
#include <unordered_set>
#include <tuple>

using namespace std;

// Define the state structure
struct State {
    int father;
    int son1;
    int son2;
    int boat;

    // Overloading the equality operator for set comparisons
    bool operator==(const State& other) const {
        return tie(father, son1, son2, boat) == tie(other.father, other.son1, other.son2, other.boat);
    }
};

// Hash function for the State structure to use it in unordered_set
namespace std {
    template <>
    struct hash<State> {
        size_t operator()(const State& s) const {
            return hash<int>()(s.father) ^ hash<int>()(s.son1) ^ hash<int>()(s.son2) ^ hash<int>()(s.boat);
        }
    };
}

// Function to check if a state is valid
bool isValidState(const State& s) {
    return (s.father >= 0 && s.son1 >= 0 && s.son2 >= 0 &&
            s.father <= 100 && s.son1 <= 50 && s.son2 <= 50 &&
            (s.boat == 1 || s.boat == 2));
}

// Function to check if a state is a goal state
bool isGoalState(const State& s) {
    return s.boat == 2 && s.father == 0 && s.son1 == 0 && s.son2 == 0;
}

// Function to perform DFS
bool dfs(const State& current, unordered_set<State>& visited) {
    // Check if the current state is the goal state
    if (isGoalState(current)) {
        return true;
    }

    // Mark the current state as visited
    visited.insert(current);

    // Generate possible next states
    vector<State> nextStates = {
        {current.father - 1, current.son1, current.son2, 3 - current.boat},
        {current.father - 2, current.son1, current.son2, 3 - current.boat},
        {current.father, current.son1 - 1, current.son2, 3 - current.boat},
        {current.father, current.son1 - 2, current.son2, 3 - current.boat},
        {current.father, current.son1, current.son2 - 1, 3 - current.boat},
        {current.father, current.son1, current.son2 - 2, 3 - current.boat},
        {current.father - 1, current.son1 - 1, current.son2, 3 - current.boat},
        {current.father - 1, current.son1, current.son2 - 1, 3 - current.boat},
        {current.father, current.son1 - 1, current.son2 - 1, 3 - current.boat},
        {current.father - 2, current.son1, current.son2, 3 - current.boat}
    };

    // Iterate over next states
    for (const auto& nextState : nextStates) {
        if (isValidState(nextState) && visited.find(nextState) == visited.end()) {
            // Recursively call DFS for the next state
            if (dfs(nextState, visited)) {
                // If a solution is found, print the move and return true
                cout << "Move: (" << current.father - nextState.father << ", "
                     << current.son1 - nextState.son1 << ", "
                     << current.son2 - nextState.son2 << ") from "
                     << (current.boat == 1 ? "left" : "right")
                     << " to " << (nextState.boat == 1 ? "left" : "right") << "\n";
                return true;
            }
        }
    }

    return false;
}

int main() {
    // Define the initial state
    State initialState = {100, 50, 50, 1};

    // Create an unordered set to keep track of visited states
    unordered_set<State> visitedDFS;

    // Perform DFS starting from the initial state
    if (!dfs(initialState, visitedDFS)) {
        cout << "No solution found using DFS.\n";
    }

    return 0;
}