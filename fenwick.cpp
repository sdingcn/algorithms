#include <iostream>
#include <cassert>
#include <vector>
#include <cstdlib>

template <typename Number>
class fenwick {
	int n;
	std::vector<Number> array;
public:
	fenwick(int nn) {
		if (nn < 0 || nn > 2000000000) {
			std::cerr << "fenwick: wrong initial length\n";
			std::exit(EXIT_FAILURE);
		}
		n = nn;
		array = std::vector<Number>(nn);
	}
	void add(int pos, Number val) { // pos : [0 ... n)
		if (pos < 0 || pos >= n) {
			std::cerr << "fenwick: wrong index in function add\n";
			std::exit(EXIT_FAILURE);
		}
		pos++;
		while (pos <= n) {
			array[pos - 1] += val;
			pos += ((pos) & (- pos));
		}
	}
	Number sum(int pos) { // pos : [0 ... n], sum([0 ... pos))
		if (pos < 0 || pos > n) {
			std::cerr << "fenwick: wrong index in function sum\n";
			std::exit(EXIT_FAILURE);
		}
		Number ret = 0;
		while (pos >= 1) {
			ret += array[pos - 1];
			pos -= ((pos) & (- pos));
		}
		return ret;
	}
};

int main() {
	fenwick<int> f(100);
	f.add(0, 1);
	f.add(5, 1);
	f.add(10, 22);
	f.add(20, -1);
	assert(f.sum(0) == 0);
	assert(f.sum(1) == 1);
	assert(f.sum(5) == 1);
	assert(f.sum(6) == 2);
	assert(f.sum(11) == 24);
	assert(f.sum(21) == 23);
	assert(f.sum(100) == 23);
}
