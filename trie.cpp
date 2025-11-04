#ifndef TRIE_H
#define TRIE_H

#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <tuple>
#include <cctype>
#include "trie.h"
using namespace std;

monolith_trie::monolith_trie() {
	root = new trie_node();
}

void monolith_trie::insert(string word) {
	trie_node* curr = root;
	for (char c : word) {
		if (isalpha(c)) {
			c = tolower(c);
			int index = c - 'a';
			if (!curr->children[index]) {
				curr->children[index] = new trie_node();
			}
			curr = curr->children[index];
		}
	}
	curr->end_word = true;
	curr->frequency++;
}

void monolith_trie::insert_sentence(string sentence) {
	trie_node* curr = root;
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
	trie_node* curr = root;
	for (char c : word) {
		int index = c - 'a';
		if (!curr->children[index]) {
			return;
		}
		curr = curr->children[index];
	}
	if (curr->end_word == true) {
		curr->end_word = false;
	}
}

bool monolith_trie::search(string word) {
	trie_node* curr = root;
	for (char c : word) {
		int index = c - 'a';
		if (!curr->children[index]) {
			return false;
		}
		curr = curr->children[index];
	}
	return curr->end_word;
}

bool monolith_trie::starts_with(string prefix) {
	trie_node* curr = root;
	for (char c : prefix) {
		int index = c - 'a';
		if (!curr->children[index]) {
			return false;
		}
		curr = curr->children[index];
	}
	return true;
}


void monolith_trie::print(trie_node* node, string prefix) const {
	if (node->end_word) {
		cout << prefix << endl;
	}
	for (int i = 0; i < 26; i++) {
		if (node->children[i]) {
			print(node->children[i], prefix + char(i + 'a'));
		}
	}
}

void monolith_trie::print() const {
	print(root, "");
}

void monolith_trie::collect_words(trie_node* node, string current, vector<pair<string, float>>& words) {
	if (node->end_word) {
		words.push_back({current, node->frequency});
	}
	for (int i = 0; i < 26; i++) {
		if (node->children[i]) {
			char c = i + 'a';
			collect_words(node->children[i], current + c, words);
		}
	}
}

tuple<vector<string>, vector<float>> monolith_trie::top_k(int k) {
	vector<pair<string, float>> all_words;
	collect_words(root, "", all_words);

	sort(all_words.begin(), all_words.end(), [](const auto& a, const auto& b) {
		return a.second > b.second;
	});

	vector<string> words;
	vector<float> freqs;
	for (int i = 0; i < min((int)all_words.size(), k); i++) {
		words.push_back(all_words[i].first);
		freqs.push_back(all_words[i].second);
	}

	return make_tuple(words, freqs);
}

tuple<vector<string>, vector<float>> monolith_trie::bottom_k(int k) {
	vector<pair<string, float>> all_words;
	collect_words(root, "", all_words);

	sort(all_words.begin(), all_words.end(), [](const auto& a, const auto& b) {
		return a.second < b.second;
	});

	vector<string> words;
	vector<float> freqs;
	for (int i = 0; i < min((int)all_words.size(), k); i++) {
		words.push_back(all_words[i].first);
		freqs.push_back(all_words[i].second);
	}

	return make_tuple(words, freqs);
}

float monolith_trie::identify(string word) {
	trie_node* curr = root;
	for (char c : word) {
		int index = c - 'a';
		if (!curr->children[index]) {
			return 0;
		}
		curr = curr->children[index];
	}
	if (curr != nullptr && curr->end_word) {
		return curr->frequency;
	}
	return 0;
}

#endif