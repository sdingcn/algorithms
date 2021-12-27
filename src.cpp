// requires #include <vector>
template <typename T, typename CombFunc, typename ChanFunc> struct segment_tree_point {
	int n;
	vector<T> tree;
	CombFunc& combine;
	void build(const vector<T> &a, int l, int r, int i) {
		if (l == r) {
			tree[i] = a[l];
		} else {
			int m = (l + r) / 2;
			build(a, l, m, 2 * i + 1);
			build(a, m + 1, r, 2 * i + 2);
			tree[i] = combine(tree[2 * i + 1], tree[2 * i + 2]);
		}
	}
	// indices starting from 0; intervals represents as [l, r] (both are inclusive)
	segment_tree_point(const vector<T> &a, CombFunc& co) : n(a.size()), tree(static_cast<int>(a.size()) * 4), combine(co) {
		build(a, 0, n - 1, 0);
	}
	void update(int p, ChanFunc& ch, int l, int r, int i) {
		if (l == r) {
			ch(tree[i]);
		} else {
			int m = (l + r) / 2;
			if (p <= m) {
				update(p, ch, l, m, 2 * i + 1);
			} else {
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
		} else {
			int m = (l + r) / 2;
			bool has_l = rl <= m, has_r = rr >= m + 1;
			if (has_l && has_r) {
				return combine(query(rl, rr, l, m, 2 * i + 1), query(rl, rr, m + 1, r, 2 * i + 2));
			} else if (has_l) {
				return query(rl, rr, l, m, 2 * i + 1);
			} else {
				return query(rl, rr, m + 1, r, 2 * i + 2);
			}
		}
	}
	T query(int rl, int rr) {
		return query(rl, rr, 0, n - 1, 0);
	}
};
