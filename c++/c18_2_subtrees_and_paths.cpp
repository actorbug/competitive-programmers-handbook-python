#include <bits/stdc++.h>
#include <gtest/gtest.h>
using namespace std;
using ll = long long;
using ull = unsigned long long;
#include "c09_2_binary_indexed_tree.h"
#include "c09_4_additional_techniques.h"

namespace {
	vector<ll> traversal(const vector<vector<ll>>& adj, ll x) {
		vector<ll> ret;
		auto dfs = [&](this auto self, ll s, ll e) -> void {
			ret.push_back(s);
			for (ll u : adj[s]) {
				if (u != e) {
					self(u, s);
				}
			}
			};
		dfs(x, 0);
		return ret;
	}

	struct SubtreeQueries {
		SubtreeQueries(const vector<vector<ll>>& adj, const vector<ll>& val, ll x)
			: pos(adj.size()), size(adj.size()), value(adj.size()) {
			ll cur = 1;
			auto& pos_ = pos;
			auto& size_ = size;
			auto dfs = [&](this auto self, ll s, ll e) -> ll {
				pos_[s] = cur++;
				ll sz = 1;
				for (ll u : adj[s]) {
					if (u != e) {
						sz += self(u, s);
					}
				}
				return size_[pos_[s]] = sz;
				};
			dfs(x, 0);
			for (ll i = 1; i < ssize(adj); ++i)
				value.add(pos[i], val[i]);
		}
		void set(ll k, ll x) {
			value.set(pos[k], x);
		}
		ll sum(ll k) const {
			ll p = pos[k];
			return value.sum(p + size[p] - 1) - value.sum(p - 1);
		}
	private:
		vector<ll> pos, size;
		BIT value;
	};

	struct PathQueries {
		PathQueries(const vector<vector<ll>>& adj, const vector<ll>& val, ll x)
			: pos(adj.size()), size(adj.size() - 1), value(adj.size() - 1) {
			ll cur = 0;
			auto& pos_ = pos;
			auto& size_ = size;
			auto& value_ = value;
			auto dfs = [&](this auto self, ll s, ll e, ll v) -> ll {
				pos_[s] = cur;
				v += val[s];
				value_.add(cur, cur, v);
				++cur;
				ll sz = 1;
				for (ll u : adj[s]) {
					if (u != e) {
						sz += self(u, s, v);
					}
				}
				return size_[pos_[s]] = sz;
				};
			dfs(x, 0, 0);
		}
		void add(ll k, ll x) {
			ll p = pos[k];
			value.add(p, p + size[p] - 1, x);
		}
		ll sum(ll k) const {
			return value[pos[k]];
		}
	private:
		vector<ll> pos, size;
		RangeUpdates value;
	};
}

TEST(C182SubtreesAndPaths, traversal) {
	EXPECT_EQ(traversal({ {},{} }, 1), vector<ll>{1});
	EXPECT_EQ(traversal({ {},{2,3,4,5},{1,6},{1},{1,7,8,9},{1},{2},{4},{4},{4} }, 1), (vector<ll>{1,2,6,3,4,7,8,9,5}));
}

TEST(C182SubtreesAndPaths, SubtreeQueries) {
	EXPECT_EQ(SubtreeQueries({ {},{} }, { 0,3 }, 1).sum(1), 3);
	SubtreeQueries sq({ {},{2,3,4,5},{1,6},{1},{1,7,8,9},{1},{2},{4},{4},{4} }, { 0,2,3,5,3,1,4,4,3,1 }, 1);
	EXPECT_EQ(sq.sum(4), 11);
	sq.set(7, 2);
	EXPECT_EQ(sq.sum(4), 9);
}

TEST(C182SubtreesAndPaths, PathQueries) {
	EXPECT_EQ(PathQueries({ {},{} }, { 0,3 }, 1).sum(1), 3);
	PathQueries pq({ {},{2,3,4,5},{1,6},{1},{1,7,8,9},{1},{2},{4},{4},{4} }, { 0,4,5,3,5,2,3,5,3,1 }, 1);
	EXPECT_EQ(pq.sum(7), 14);
	pq.add(4, 1);
	EXPECT_EQ(pq.sum(7), 15);
	EXPECT_EQ(pq.sum(5), 6);
}
