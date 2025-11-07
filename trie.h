#include <iostream>
#include <string>
#include <tuple>
#include <unordered_map>
#pragma once

using namespace std;

class monolith_trie {
private:
	struct trie_node {
		unordered_map<char, unique_ptr<trie_node>> children;
		bool end_word;
		int frequency;

		trie_node() {
			frequency = 0;
			end_word = false;
		}
	};
		unique_ptr<trie_node> root;
		int count = 0;
	public:
		monolith_trie();
		void insert(string word);
		void insert_sentence(string sentence);
		void remove(string word);
		bool search(string word);
		bool starts_with(string prefix);
		void print(trie_node* node, string prefix) const;
		void print() const;

		void collect_words(trie_node* node, string current, vector<pair<string, float>>& words);
		tuple<vector<string>, vector<float>> top_k(int k);
		tuple<vector<string>, vector<float>> bottom_k(int k);
		float identify(string word);
};


