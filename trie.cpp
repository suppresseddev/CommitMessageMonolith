#ifndef TRIE_H
#define TRIE_H

#include <iostream>
#include <algorithm>
#include <string>
#include <vector>
#include <sstream>
#include <tuple>
#include <cctype>
#include <cmath>
#include <unordered_map>
#include <memory>
#include "trie.h"
using namespace std;

monolith_trie::monolith_trie() : root(make_unique<trie_node>()) {
	count = 0;
}

void monolith_trie::insert(string word) {
	trie_node* curr = root.get();
	for (char c : word) {
		if (curr->children.find(c) == curr->children.end()) {
			curr->children[c] = make_unique<trie_node>();
		}
		curr = curr->children[c].get();
	}
	curr->end_word = true;
	curr->frequency++;
	count++;
}

void monolith_trie::insert_sentence(string sentence) {
	if (sentence.find(' ') == string::npos) {
		insert(sentence);
	} else {
		stringstream ss(sentence);
		string word;
		while (getline(ss, word, ' ')) {
			insert(word);
		}
	}
}

void monolith_trie::remove(string word) {
	trie_node* curr = root.get();
	for (char c : word) {
		if (curr->children.find(c) == curr->children.end()) {
			return;
		}
		curr = curr->children[c].get();
	}
	if (curr->end_word == true) {
		curr->end_word = false;
	}
}

bool monolith_trie::search(string word) {
	trie_node* curr = root.get();
	for (char c : word) {
		if (curr->children.find(c) == curr->children.end()) {
			return false;
		}
		curr = curr->children[c].get();
	}
	return curr != nullptr && curr->end_word;
}

bool monolith_trie::starts_with(string prefix) {
	trie_node* curr = root.get();
	for (char c : prefix) {
		if (curr->children.find(c) == curr->children.end()) {
			return false;
		}
		curr = curr->children[c].get();
	}
	return true;
}

void monolith_trie::collect_words(trie_node* node, string current, vector<pair<string, float>>& words) {
	if (node->end_word) {
		float freq_prop = (float)node->frequency / (float)count;
		words.push_back({current, freq_prop});
	}
	for (auto const& [key, val] : node->children) {
		trie_node* curr = val.get();
		collect_words(curr, current + key, words);
	}
}

tuple<vector<string>, vector<float>> monolith_trie::top_k(int k) {
	vector<pair<string, float>> all_words;
	collect_words(root.get(), "", all_words);

	sort(all_words.begin(), all_words.end(), [](const auto& a, const auto& b) {
		return a.second > b.second;
	});

	vector<string> words;
	vector<float> freqs;
	for (int i = 0; i < min((int)all_words.size(), k); i++) {
		string lower_word = "";
		for (char c : all_words[i].first) {
			if (isalpha(c)) {
				lower_word += tolower(c);
			} else {
				lower_word += c;
			}
		}
		words.push_back(lower_word);
		freqs.push_back(all_words[i].second);
	}

	return make_tuple(words, freqs);
}

tuple<vector<string>, vector<float>> monolith_trie::bottom_k(int k) {
	vector<pair<string, float>> all_words;
	collect_words(root.get(), "", all_words);

	sort(all_words.begin(), all_words.end(), [](const auto& a, const auto& b) {
		return a.second < b.second;
	});

	vector<string> words;
	vector<float> freqs;
	for (int i = 0; i < min((int)all_words.size(), k); i++) {
		string lower_word = "";
		for (char c : all_words[i].first) {
			if (isalpha(c)) {
				lower_word += tolower(c);
			} else {
				lower_word += c;
			}
		}
		words.push_back(lower_word);
		freqs.push_back(all_words[i].second);
	}

	return make_tuple(words, freqs);
}

float monolith_trie::identify(string word) {
	trie_node* curr = root.get();
	for (char c : word) {
		if (curr->children.find(c) == curr->children.end()) {
			return 0;
		}
		curr = curr->children[c].get();
	}
	if (curr != nullptr && curr->end_word) {
		float freq_prop = (float)curr->frequency / (float)count;
		return freq_prop;
	}
	return 0;
}

#endif
