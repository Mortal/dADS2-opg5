#include "suffix.h"

struct rotations_calc {
	static const char END = '$';

	size_t n;

	rotations_calc(size_t n) : n(n) {}

	void operator()(trie<depth_payload> & t) {
		if (t.payload.depth == n) cout << t.path() << endl;
	}
};

struct rotations {
	trie<depth_payload> t;
	size_t n;

	static const char END = rotations_calc::END;

	void set_string(string s) {
		t.insert_suffixes(s + s);
		n = s.size();
	}

	void calc() {
		t.pre_order_traversal(depth_calc());
		t.post_order_traversal(rotations_calc(n));
	}
};

int main(int argc, char ** argv) {
	for (int i = 1; i < argc; ++i) {
		rotations l;
		l.set_string(argv[i]);
		l.t.dump(cout);
		cout << endl;
		l.calc();
	}
	return 0;
}

// vim:set sw=4 sts=4 ts=4:
