class Solution {
public:
    vector<string> maxNumOfSubstrings(string S) {
        int n = S.size();
        vector<int> mins(26, INT_MAX), maxs(26, -1);
        vector<bool> exists(26, false);
        vector<vector<int>> prefixSum(n + 1, vector<int>(26, 0));

        // Preprocessing
        for (int i = 0; i < n; ++i) {
            int c = S[i] - 'a';
            prefixSum[i + 1] = prefixSum[i];
            prefixSum[i + 1][c]++;
            mins[c] = min(mins[c], i);
            maxs[c] = max(maxs[c], i);
            exists[c] = true;
        }

        // Build graph
        vector<vector<bool>> graph(26, vector<bool>(26, false));
        for (int i = 0; i < 26; ++i) {
            if (exists[i]) {
                for (int j = 0; j < 26; ++j) {
                    if (prefixSum[maxs[i] + 1][j] - prefixSum[mins[i]][j] > 0) {
                        graph[i][j] = true;
                    }
                }
            }
        }

        // First DFS for topological sort
        vector<bool> visited(26, false);
        stack<int> st;
        for (int i = 0; i < 26; ++i) {
            if (exists[i] && !visited[i]) {
                dfs1(i, graph, visited, st);
            }
        }

        // Second DFS for SCC on reverse graph
        vector<int> batches(26, -1), degree(26, 0);
        int batch = 0;
        while (!st.empty()) {
            int v = st.top(); st.pop();
            if (batches[v] < 0) {
                dfs2(v, graph, batches, batch, degree);
                batch++;
            }
        }

        // Extract answer
        vector<string> result;
        for (int i = 0; i < batch; ++i) {
            if (degree[i] == 0) {
                int l = INT_MAX, r = -1;
                for (int j = 0; j < 26; ++j) {
                    if (batches[j] == i) {
                        l = min(l, mins[j]);
                        r = max(r, maxs[j]);
                    }
                }
                result.push_back(S.substr(l, r - l + 1));
            }
        }

        return result;
    }

private:
    void dfs1(int v, vector<vector<bool>>& graph, vector<bool>& visited, stack<int>& st) {
        visited[v] = true;
        for (int i = 0; i < 26; ++i) {
            if (graph[v][i] && !visited[i]) {
                dfs1(i, graph, visited, st);
            }
        }
        st.push(v);
    }

    void dfs2(int v, vector<vector<bool>>& graph, vector<int>& batches, int batch, vector<int>& degree) {
        batches[v] = batch;
        for (int i = 0; i < 26; ++i) {
            if (graph[i][v]) { // reversed graph
                if (batches[i] == -1) {
                    dfs2(i, graph, batches, batch, degree);
                } else if (batches[i] != batch) {
                    degree[batches[i]]++;
                }
            }
        }
    }
};
