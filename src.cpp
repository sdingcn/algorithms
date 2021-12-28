#include <iostream>
#include <sstream>
#include <iomanip>
#include <string>
#include <vector>
#include <deque>
#include <map>
#include <unordered_map>
#include <set>
#include <unordered_set>
#include <queue>
#include <algorithm>
#include <utility>
#include <cmath>
#include <cassert>
using namespace std;

template <typename T, typename CombFunc, typename ChanFunc> struct segment_tree_point {
	int n;
	vector<T> tree;
	CombFunc& combine;
	void build(const vector<T>& a, int l, int r, int i) {
		if (l == r) {
			tree[i] = a[l];
		}
		else {
			int m = (l + r) / 2;
			build(a, l, m, 2 * i + 1);
			build(a, m + 1, r, 2 * i + 2);
			tree[i] = combine(tree[2 * i + 1], tree[2 * i + 2]);
		}
	}
	// indices starting from 0; intervals represents as [l, r] (both are inclusive)
	segment_tree_point(const vector<T>& a, CombFunc& co) : n(a.size()), tree(static_cast<int>(a.size()) * 4), combine(co) {
		build(a, 0, n - 1, 0);
	}
	void update(int p, ChanFunc& ch, int l, int r, int i) {
		if (l == r) {
			ch(tree[i]);
		}
		else {
			int m = (l + r) / 2;
			if (p <= m) {
				update(p, ch, l, m, 2 * i + 1);
			}
			else {
				update(p, ch, m + 1, r, 2 * i + 2);
			}
			tree[i] = combine(tree[2 * i + 1], tree[2 * i + 2]);
		}
	}
	void update(int p, ChanFunc& ch) {
		update(p, ch, 0, n - 1, 0);
	}
	T query(int rl, int rr, int l, int r, int i) {
		if (rl <= l && r <= rr) {
			return tree[i];
		}
		else {
			int m = (l + r) / 2;
			bool has_l = rl <= m, has_r = rr >= m + 1;
			if (has_l && has_r) {
				return combine(query(rl, rr, l, m, 2 * i + 1), query(rl, rr, m + 1, r, 2 * i + 2));
			}
			else if (has_l) {
				return query(rl, rr, l, m, 2 * i + 1);
			}
			else {
				return query(rl, rr, m + 1, r, 2 * i + 2);
			}
		}
	}
	T query(int rl, int rr) {
		return query(rl, rr, 0, n - 1, 0);
	}
};

struct union_find {
	vector<int> prev;
	// range [0, n - 1] (both are inclusive)
	union_find(int n) {
		prev = vector<int>(n);
		for (int i = 0; i < n; i++) {
			prev[i] = i;
		}
	}
	int find(int x) {
		int r = x;
		while (prev[r] != r) {
			r = prev[r];
		}
		int i = x;
		while (prev[i] != r) {
			int tmp = prev[i];
			prev[i] = r;
			i = tmp;
		}
		return r;
	}
	void join(int x, int y) {
		prev[find(x)] = find(y);
	}
};

template <typename T> T gcd(T a, T b) {
	return b == static_cast<T>(0) ? a : gcd(b, a % b);
}

template <typename T> T lcm(T a, T b) {
	return a / gcd(a, b) * b;
}

template <typename T> void ext_gcd(T a, T b, T& x, T& y, T& d) { // xa + yb = d
	if (!b) {
		x = 1;
		y = 0;
		d = a;
	}
	else {
		ext_gcd(b, a % b, y, x, d);
		y -= x * (a / b);
	}
}

template <typename T> T inverse(T a, T n) { // ax = 1 (mod n)
	T x, y, d;
	ext_gcd(a, n, x, y, d);
	assert(d == 1);
	return (x % n + n) % n;
}

struct sieve {
	vector<int> primes;
	// range [2, n] (both are inclusive)
	sieve(int n) : primes(n + 1, 1) {
		int m = sqrt(n + 0.5);
		for (int i = 2; i <= m; i++) {
			if (primes[i]) {
				for (int j = i * i; j <= n; j += i) {
					primes[j] = 0;
				}
			}
		}
	}
};

struct combinatorics {
	int mod;
	vector<int> fact;
	vector<int> fact_inv;
	combinatorics(int m) : mod(m), fact(1, 1), fact_inv(1, 1) {}
	int C(int n, int k) {
		if (k < 0 || k > n) {
			return 0;
		}
		while (static_cast<int>(fact.size()) < n + 1) {
			fact.push_back(fact.back() * static_cast<long long>(fact.size()) % mod);
			fact_inv.push_back(inverse(fact.back(), mod));
		}
		return (((static_cast<long long>(fact[n]) * fact_inv[k]) % mod) * fact_inv[n - k]) % mod;
	}
};

int main()
{
}
