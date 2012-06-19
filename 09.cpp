#include "suffix.h"

struct lsr_payload {
	bool is_orig;
	bool is_rev;
	size_t depth;
};

struct lsr_calc {
	static const char END1 = '$';
	static const char END2 = '#';

	void operator()(trie<lsr_payload> & t) {
		t.payload.is_orig = false;
		t.payload.is_rev = false;
		if (t.ch == END1) {
			t.payload.is_orig = true;
			return;
		}
		if (t.ch == END2) {
			t.payload.is_rev = true;
			return;
		}
		for (auto i = t.children.begin(); i != t.children.end(); ++i) {
			if (i->second.payload.is_orig) {
				t.payload.is_orig = true;
			}
			if (i->second.payload.is_rev) {
				t.payload.is_rev = true;
			}
		}
		if (t.payload.is_orig && t.payload.is_rev) {
			if (t.payload.depth > 1) {
				cout << t.path() << endl;
			}
		}
	}
};

struct longest_substring_reversed {
	trie<lsr_payload> t;

	static const char END1 = lsr_calc::END1;
	static const char END2 = lsr_calc::END2;

	void set_string(string s) {
		t.insert_suffixes(s + END1);
		t.insert_suffixes(string(s.rbegin(), s.rend()) + END2);
	}

	void calc() {
		t.pre_order_traversal(depth_calc<lsr_payload>());
		t.post_order_traversal(lsr_calc());
	}
};

int main(int argc, char ** argv) {
	for (int i = 1; i < argc; ++i) {
		longest_substring_reversed l;
		l.set_string(argv[i]);
		l.t.dump(cout);
		cout << endl;
		l.calc();
	}
	return 0;
}

// vim:set sw=4 sts=4 ts=4:
