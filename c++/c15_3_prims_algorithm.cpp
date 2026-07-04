#include <bits/stdc++.h>
#include <gtest/gtest.h>
using namespace std;
using ll = long long;
#include "util.h"
#include "c12_3_applications.h"

namespace {
	vector<vector<pair<ll, ll>>> prim(const vector<vector<pair<ll, ll>>>& adj) {
		ll n = ssize(adj);
		if (n <= 1) return { {} };
		vector<bool> processed(n);
		vector<vector<pair<ll, ll>>> ret(n);
		processed[1] = true;
		priority_queue<tuple<ll, ll, ll>, vector<tuple<ll, ll, ll>>, greater<>> q;
		for (auto [c, w] : adj[1])
			q.emplace(w, 1, c);
		while (!q.empty()) {
			auto [w, a, b] = q.top(); q.pop();
			if (processed[b])
				continue;
			processed[b] = true;
			ret[a].emplace_back(b, w);
			ret[b].emplace_back(a, w);
			for (auto [c, w] : adj[b])
				q.emplace(w, b, c);
		}
		return ret;
	}
}

TEST(C153PrimsAlgorithm, prim) {
	EXPECT_EQ(prim({ {} }), (vector<vector<pair<ll, ll>>>{ {} }));
	auto ret = prim({ {},{{2,3},{5,5}},{{1,3},{3,5},{5,6}},{{2,5},{4,9},{6,3}},{{3,9},{6,7}},{{1,5},{2,6},{6,2}},{{3,3},{4,7},{5,2}} });
	ll sum = 0;
	for (const auto& v : ret)
		for (auto [_, w] : v)
			sum += w;
	EXPECT_EQ(sum, 20 * 2);
	auto adj = delweight(ret);
	EXPECT_EQ(connected(adj).size(), 1);
	EXPECT_FALSE(finding_cycles(adj));
}
