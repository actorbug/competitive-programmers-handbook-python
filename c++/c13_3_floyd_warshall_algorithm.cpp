#include <bits/stdc++.h>
#include <gtest/gtest.h>
using namespace std;
using ll = long long;
constexpr ll INF = numeric_limits<ll>::max() / 2;
#include "c13_3_floyd_warshall_algorithm.h"

vector<vector<ll>> floyd_warshall(const vector<vector<ll>>& adj) {
	ll n = ssize(adj);
	vector<vector<ll>> distance = adj;
	for (int i = 1; i < n; ++i) {
		for (int j = 1; j < n; ++j) {
			if (i != j && !adj[i][j]) {
				distance[i][j] = INF;
			}
		}
	}
	for (int k = 1; k < n; ++k) {
		for (int i = 1; i < n; ++i) {
			for (int j = 1; j < n; ++j) {
				distance[i][j] = min(distance[i][j],
					distance[i][k] + distance[k][j]);
			}
		}
	}
	return distance;
}

TEST(C133FloydWarshallAlgorithm, floydWarshall) {
	EXPECT_EQ(floyd_warshall({ {0} }), vector<vector<ll>>{ {0} });
	EXPECT_EQ(floyd_warshall({ {0,0,0,0,0,0},{0,0,5,0,9,1},{0,5,0,2,0,0},{0,0,2,0,7,0},{0,9,0,7,0,2},{0,1,0,0,2,0} }),
		(vector<vector<ll>>{ {0,0,0,0,0,0},{0,0,5,7,3,1},{0,5,0,2,8,6},{0,7,2,0,7,8},{0,3,8,7,0,2},{0,1,6,8,2,0} }));
}
