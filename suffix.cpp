#include <map>
#include <string>
#include <iostream>

using namespace std;

template <typename Payload>
struct trie {
	map<char, trie> children;
	Payload payload;
	bool root;
	char ch;
	trie<Payload> * parent;

	trie()
		: root(true)
	{
	}

	trie(trie * p, char ch)
		: root(false)
		, ch(ch)
		, parent(p)
	{
	}

	void insert(const string & str, size_t off = 0) {
		if (str.size() <= off) return;
		char ch = str[off];
		trie & child = children.insert(make_pair(ch, trie(this, ch))).first->second;
		child.insert(str, off+1);
	}

	template <typename F>
	void post_order_traversal(F f) {
		for (auto i = children.begin(); i != children.end(); ++i) {
			i->second.post_order_traversal(f);
		}
		f(*this);
	}

	template <typename F>
	void pre_order_traversal(F f) {
		f(*this);
		for (auto i = children.begin(); i != children.end(); ++i) {
			i->second.pre_order_traversal(f);
		}
	}

	string path() {
		trie<Payload> * n = this;
		size_t depth = 0;
		while (!n->root) {
			++depth;
			n = n->parent;
		}
		string res(depth, '\0');
		auto p = res.end();
		n = this;
		while (!n->root) {
			*--p = n->ch;
			n = n->parent;
		}
		return res;
	}
};

struct lsr_payload {
	bool is_orig;
	bool is_rev;
	size_t depth;
};

struct depth_calc {
	void operator()(trie<lsr_payload> & t) {
		if (t.root) t.payload.depth = 0;
		else t.payload.depth = t.parent->payload.depth + 1;
	}
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
		string insert(s.size()*2+2, '\0');
		for (size_t i = 0; i < s.size(); ++i) {
			char ch = s[i];
			if (ch == END1 || ch == END2)
				cerr << "End-of-string marker \"" << ch << "\" occurs in input, result is incorrect" << endl;
			insert[i] = insert[2*s.size()-i] = ch;
		}
		insert[s.size()] = END1;
		insert[2*s.size()+1] = END2;

		for (size_t i = 0; i < insert.size(); ++i) {
			t.insert(insert, i);
		}
	}

	void calc() {
		t.pre_order_traversal(depth_calc());
		t.post_order_traversal(lsr_calc());
	}
};

int main(int argc, char ** argv) {
	for (int i = 1; i < argc; ++i) {
		longest_substring_reversed l;
		l.set_string(argv[i]);
		l.calc();
	}
	return 0;
}

// vim:set sw=4 sts=4 ts=4:
