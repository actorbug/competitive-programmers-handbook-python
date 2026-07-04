#include <bits/stdc++.h>
#include <gtest/gtest.h>
using namespace std;
using ll = long long;
#include "c16_1_topological_sorting.h"

namespace {
	void test(const vector<vector<ll>>& adj) {
		ll n = ssize(adj);
		auto ret = topological(adj);
		vector<ll> pos(n);
		for (auto [i, a] : ret | views::enumerate)
			pos[a] = i;
		for (ll a = 1; a < n; ++a) {
			for (ll b : adj[a]) {
				EXPECT_LT(pos[a], pos[b]);
			}
		}
		ranges::sort(ret);
		EXPECT_EQ(ret, views::iota(1ll, n) | ranges::to<vector>());
	}
}

vector<ll> topological(const vector<vector<ll>>& adj) {
	ll n = ssize(adj);
	vector<ll> visited(n), ret;
	auto dfs = [&](this auto self, ll s) {
		if (visited[s])
			return visited[s] != 1;
		visited[s] = 1;
		if (!ranges::all_of(adj[s], self))
			return false;
		ret.push_back(s);
		visited[s] = 2;
		return true;
		};
	for (ll x = 1; x < n; ++x) {
		if (!visited[x] && !dfs(x)) {
			return {};
		}
	}
	ranges::reverse(ret);
	return ret;
}

TEST(C161TopologicalSorting, topological) {
	test({ {} });
	test({ {},{2},{3},{6},{1,5},{2,3},{} });
	EXPECT_EQ(topological({ {},{2},{3},{5,6},{1,5},{2},{} }), vector<ll>{});
}
