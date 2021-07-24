#include <vector>

template <typename T, typename CombFunc>
class static_segment_tree {
	int n;
	std::vector<T> arr;
	std::vector<T> tree;
	CombFunc combine;
	void build(int left, int right, int pos) {
		if (left == right) {
			tree[pos] = arr[left];
		} else {
			int mid = (left + right) / 2;
			build(left, mid, 2 * pos + 1);
			build(mid + 1, right, 2 * pos + 2);
			tree[pos] = combine(tree[2 * pos + 1], tree[2 * pos + 2]);
		}
	}
public:
	static_segment_tree(const vector<T> &a, CombFunc c)
		: n(a.size()), arr(a), tree(static_cast<int>(a.size()) * 4), combine(c) {
		build(0, n - 1, 0);
	}
	T query(int range_left, int range_right, int cur_left, int cur_right, int pos) {
		if (range_left <= cur_left && cur_right <= range_right) {
			return tree[pos];
		} else {
			int mid = (cur_left + cur_right) / 2;
			bool has_left = range_left <= mid;
			bool has_right = range_right > mid;
			if (has_left && has_right) {
				return combine(
						query(range_left, range_right, cur_left, mid, 2 * pos + 1),
						query(range_left, range_right, mid + 1, cur_right, 2 * pos + 2)
					   );
			} else if (has_left) {
				return query(range_left, range_right, cur_left, mid, 2 * pos + 1);
			} else { // has_right
				return query(range_left, range_right, mid + 1, cur_right, 2 * pos + 2);
			}
		}
	}
	T query(int range_left, int range_right) {
		return query(range_left, range_right, 0, n - 1, 0);
	}
};
