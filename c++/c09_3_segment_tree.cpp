#include <bits/stdc++.h>
#include <gtest/gtest.h>
using namespace std;
using ll = long long;
constexpr ll INF = numeric_limits<ll>::max() / 2;

namespace {
	struct SegTree {
		SegTree(size_t n) : tree(1ll << (bit_width(max(n, 1uz) - 1) + 1)) {}
		SegTree(const vector<ll>& ary) : SegTree(ary.size()) {
			ll n = ssize(tree) / 2;
			ranges::copy(ary, tree.begin() + n);
			for (ll i = n - 1; i > 0; --i)
				tree[i] = tree[2 * i] + tree[2 * i + 1];
		}
		ll sum(ll a, ll b) const {
			ll n = ssize(tree) / 2;
			a += n; b += n;
			ll s = 0;
			while (a <= b) {
				if (a % 2 == 1) s += tree[a++];
				if (b % 2 == 0) s += tree[b--];
				a /= 2; b /= 2;
			}
			return s;
		}
		void add(ll k, ll x) {
			k += ssize(tree) / 2;
			tree[k] += x;
			for (k /= 2; k >= 1; k /= 2) {
				tree[k] = tree[2 * k] + tree[2 * k + 1];
			}
		}
	private:
		vector<ll> tree;
	};

	struct SegTreeMin {
		SegTreeMin(const vector<ll>& array) : tree(1ll << (bit_width(max(array.size(), 1uz) - 1) + 1), INF) {
			ll n = ssize(tree) / 2;
			ranges::copy(array, tree.begin() + n);
			for (ll i = n - 1; i > 0; --i)
				tree[i] = std::min(tree[2 * i], tree[2 * i + 1]);
		}
		ll min(ll a, ll b) const {
			ll n = ssize(tree) / 2;
			a += n; b += n;
			ll m = INF;
			while (a <= b) {
				if (a % 2 == 1)
					m = std::min(m, tree[a++]);
				if (b % 2 == 0)
					m = std::min(m, tree[b--]);
				a /= 2; b /= 2;
			}
			return m;
		}
		void add(ll k, ll x) {
			k += ssize(tree) / 2;
			tree[k] += x;
			while ((k /= 2) >= 1)
				tree[k] = std::min(tree[2 * k], tree[2 * k + 1]);
		}
		ll minpos() const {
			ll k = 1, n = ssize(tree) / 2;
			while (k < n)
				k = (tree[k] == tree[2 * k]) ? 2 * k : 2 * k + 1;
			return k - n;
		}
	private:
		vector<ll> tree;
	};
}

TEST(C093SegmentTree, SegTree) {
	SegTree s({});
	EXPECT_EQ(s.sum(0, -1), 0);
	s = SegTree({ 5,8,6,3,2,7,2,6 });
	EXPECT_EQ(s.sum(2, 7), 26);
	s.add(5, 7);
	EXPECT_EQ(s.sum(2, 7), 33);
}

TEST(C093SegmentTree, SegTreeMin) {
	SegTreeMin s({ 5 });
	EXPECT_EQ(s.min(0, 0), 5);
	EXPECT_EQ(s.minpos(), 0);
	s = SegTreeMin({ 5,8,6,3,1,7,2,6 });
	EXPECT_EQ(s.min(2, 7), 1);
	EXPECT_EQ(s.minpos(), 4);
	s.add(4, 3);
	EXPECT_EQ(s.min(2, 7), 2);
	EXPECT_EQ(s.minpos(), 6);
}
