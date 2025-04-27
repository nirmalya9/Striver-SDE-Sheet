class Solution {
public:
    bool canFinish(int numCourses, vector<vector<int>>& prerequisites) {
    vector<vector<int>> graph(numCourses);
    vector<State> states(numCourses, State::kUnvisited);

        for (const vector<int>& prerequisite : prerequisites) {
            int u = prerequisite[1];
            int v = prerequisite[0];
            graph[u].push_back(v);
        }

        for (int i = 0; i < numCourses; ++i) {
            if (hasCycle(graph, i, states)) {
                return false;
            }
        }

        return true;
    }

private:
    enum class State { kUnvisited, kVisiting, kVisited };

    bool hasCycle(const vector<vector<int>>& graph, int u, vector<State>& states) {
        if (states[u] == State::kVisiting) {
            return true;  // Cycle detected
        }
        if (states[u] == State::kVisited) {
            return false;  // Already processed
        }

        states[u] = State::kVisiting;
        for (int v : graph[u]) {
            if (hasCycle(graph, v, states)) {
                return true;
            }
        }
        states[u] = State::kVisited;
        return false;
    }
};