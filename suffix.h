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

	void insert_suffixes(const string & s) {
		for (size_t i = 0; i < s.size(); ++i) {
			insert(s, i);
		}
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

	void dump(ostream & out) {
		if (children.size() == 0) {
			out << ch;
			return;
		}
		if (children.size() == 1) {
			out << ch;
			return children.begin()->second.dump(out);
		}
		out << ch;
		char c = '[';
		for (auto i = children.begin(); i != children.end(); ++i) {
			out << c;
			i->second.dump(out);
			c = ' ';
		}
		out << ']';
	}
};

struct depth_payload {
	size_t depth;
};

struct suffix_payload : public depth_payload {
	bool is_orig;
	bool is_rev;
};

struct depth_calc {
	template <typename Payload>
	void operator()(trie<Payload> & t) {
		depth_payload & pl = static_cast<depth_payload &>(t.payload);
		if (t.root) pl.depth = 0;
		else pl.depth = t.parent->payload.depth + 1;
	}
};

// vim:set sw=4 sts=4 ts=4:
