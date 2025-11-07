#ifndef DS2_H
#define DS2_H

#include <string>
#include <vector>
#include <tuple>
#include <unordered_map>

class monolith_heap {
private:
    // Internal node to hold word and relative frequency
    struct Node {
        std::string word;
        float frequency; // relative frequency in percent
        Node(std::string w = "", float f = 0.0f) : word(std::move(w)), frequency(f) {}
    };

    std::vector<Node> heap;                  // internal heap storage
    std::unordered_map<std::string, int> freqMap; // word -> count
    float totalWords = 0.0f;                 // total words for frequency calculation
    bool built = false;                      // flag to indicate heap built

    // Heap helper functions
    void heapifyDown(int i);
    void heapifyUp(int i);
    void buildHeap();

public:
    monolith_heap() = default;

    // Insert a word (increments count)
    void insertWord(const std::string& word);

    // Compute relative frequencies (%) and build heap
    void finalizeFrequencies();

    // Public API
    std::tuple<std::vector<std::string>, std::vector<float>> top_k(int k);
    std::tuple<std::vector<std::string>, std::vector<float>> bottom_k(int k);
    float identify(const std::string& word);
};

#endif
