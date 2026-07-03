#include <bits/stdc++.h>
#include <gtest/gtest.h>
using namespace std;
using ll = long long;

namespace {
	struct Node;
	using Tree = shared_ptr<Node>;
	struct Node {
		ll value;
		Tree left, right;
	};

	void pre_order(Tree tree, auto f) {
		if (tree) {
			f(tree->value);
			pre_order(tree->left, f);
			pre_order(tree->right, f);
		}
	}

	void in_order(Tree tree, auto f) {
		if (tree) {
			in_order(tree->left, f);
			f(tree->value);
			in_order(tree->right, f);
		}
	}

	void post_order(Tree tree, auto f) {
		if (tree) {
			post_order(tree->left, f);
			post_order(tree->right, f);
			f(tree->value);
		}
	}

	Tree from_pre_in(span<const ll> pre, span<const ll> in) {
		if (pre.empty() || in.empty())
			return nullptr;
		ll i = ranges::find(in, pre.front()) - in.begin();
		return make_shared<Node>(pre.front(),
			from_pre_in(pre.subspan(1, i), in.subspan(0, i)),
			from_pre_in(pre.subspan(i + 1), in.subspan(i + 1)));
	}

	Tree from_in_post(span<const ll> in, span<const ll> post) {
		if (in.empty() || post.empty())
			return nullptr;
		ll i = ranges::find(in, post.back()) - in.begin();
		return make_shared<Node>(post.back(),
			from_in_post(in.subspan(0, i), post.subspan(0, i)),
			from_in_post(in.subspan(i + 1), post.subspan(i, post.size() - i - 1)));
	}

	bool equal_tree(Tree a, Tree b) {
		if (!a && !b)
			return true;
		else if (a && !b || !a && b)
			return false;
		else
			return a->value == b->value && equal_tree(a->left, b->left) && equal_tree(a->right, b->right);
	}

	const Tree tree = make_shared<Node>(1, make_shared<Node>(2, make_shared<Node>(4), make_shared<Node>(5, make_shared<Node>(6))), make_shared<Node>(3, nullptr, make_shared<Node>(7)));
}

TEST(C144BinaryTrees, preOrder) {
	vector<ll> ret;
	pre_order(nullptr, [&](ll s) { ret.push_back(s); });
	EXPECT_EQ(ret, vector<ll>{});
	ret.clear();
	pre_order(tree, [&](ll s) { ret.push_back(s); });
	EXPECT_EQ(ret, (vector<ll>{1, 2, 4, 5, 6, 3, 7}));
}

TEST(C144BinaryTrees, inOrder) {
	vector<ll> ret;
	in_order(nullptr, [&](ll s) { ret.push_back(s); });
	EXPECT_EQ(ret, vector<ll>{});
	ret.clear();
	in_order(tree, [&](ll s) { ret.push_back(s); });
	EXPECT_EQ(ret, (vector<ll>{4, 2, 6, 5, 1, 3, 7}));
}

TEST(C144BinaryTrees, postOrder) {
	vector<ll> ret;
	post_order(nullptr, [&](ll s) { ret.push_back(s); });
	EXPECT_EQ(ret, vector<ll>{});
	ret.clear();
	post_order(tree, [&](ll s) { ret.push_back(s); });
	EXPECT_EQ(ret, (vector<ll>{4, 6, 5, 2, 7, 3, 1}));
}

TEST(C144BinaryTrees, fromPreIn) {
	EXPECT_TRUE(equal_tree(from_pre_in(vector<ll>{1, 2, 4, 5, 6, 3, 7}, vector<ll>{4, 2, 6, 5, 1, 3, 7}), tree));
}

TEST(C144BinaryTrees, fromInPost) {
	EXPECT_TRUE(equal_tree(from_in_post(vector<ll>{4, 2, 6, 5, 1, 3, 7}, vector<ll>{4, 6, 5, 2, 7, 3, 1}), tree));
}
