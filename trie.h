#include <iostream>
#include <string>
#include <tuple>
#pragma once

using namespace std;

class monolith_trie {
private:
	struct trie_node {
		trie_node* children[26];
		bool end_word;
		int frequency;

		trie_node() {
			for (int i = 0; i < 26; i++) {
				children[i] = nullptr;
			}
			frequency = 0;
			end_word = false;
		}
	};
		trie_node* root;
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


