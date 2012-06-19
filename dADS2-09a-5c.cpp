#include "suffix.h"

struct rotations_calc {
	static const char END1 = '$';
	static const char END2 = '#';

	size_t n;

	rotations_calc(size_t n) : n(n) {}

	void operator()(trie<suffix_payload> & t) {
		t.payload.is_orig = false;
		t.payload.is_rev = false;
		if (t.ch == END1) {
			t.payload.is_orig = true;
		} else if (t.ch == END2) {
			t.payload.is_rev = true;
		} else {
			for (auto i = t.children.begin(); i != t.children.end(); ++i) {
				if (i->second.payload.is_orig) {
					t.payload.is_orig = true;
				}
				if (i->second.payload.is_rev) {
					t.payload.is_rev = true;
				}
			}
		}
		if (t.payload.depth == n && t.payload.is_orig && t.payload.is_rev) {
			string p = t.path();
			if (is_palindrome(p))
				cout << t.path() << endl;
		}
	}

private:
	bool is_palindrome(string s) {
		for (size_t i = 0; i < s.size()/2; ++i) {
			if (s[i] != s[s.size()-i-1]) return false;
		}
		return true;
	}
};

struct rotations {
	trie<suffix_payload> t;
	size_t n;

	static const char END1 = rotations_calc::END1;
	static const char END2 = rotations_calc::END2;

	void set_string(string s) {
		t.insert_suffixes(s + s + END1);
		string rev(s.rbegin(), s.rend());
		t.insert_suffixes(rev + rev + END2);
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
