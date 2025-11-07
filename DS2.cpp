#include "DS2.h"
#include <algorithm>
#include <cctype>
#include <string>
#include <vector>
#include <tuple>

static std::string to_lower(const std::string &s) {
    std::string result;
    result.reserve(s.size());
    for (char c : s) result += std::tolower(c);
    return result;
}

void monolith_heap::insertWord(const std::string& word) {
    std::string lw = to_lower(word);
    freqMap[lw]++;
    totalWords++;
}

// Compute relative frequency (%) and build heap vector
void monolith_heap::finalizeFrequencies() {
    heap.clear();
    heap.reserve(freqMap.size());
    for (auto it = freqMap.begin(); it != freqMap.end(); ++it) {
        const std::string& word = it->first;
        int count = it->second;
        float freq = (count / static_cast<float>(totalWords));
        heap.emplace_back(word, freq);
    }
    buildHeap();
    built = true;
}

// Build a simple min-heap by frequency
void monolith_heap::buildHeap() {
    for (int i = heap.size() / 2 - 1; i >= 0; --i)
        heapifyDown(i);
}

void monolith_heap::heapifyDown(int i) {
    int smallest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    if (left < heap.size() && heap[left].frequency < heap[smallest].frequency)
        smallest = left;
    if (right < heap.size() && heap[right].frequency < heap[smallest].frequency)
        smallest = right;

    if (smallest != i) {
        std::swap(heap[i], heap[smallest]);
        heapifyDown(smallest);
    }
}

void monolith_heap::heapifyUp(int i) {
    if (i == 0) return;
    int parent = (i - 1) / 2;
    if (heap[i].frequency < heap[parent].frequency) {
        std::swap(heap[i], heap[parent]);
        heapifyUp(parent);
    }
}

// Return top-k words by frequency (largest first)
std::tuple<std::vector<std::string>, std::vector<float>> monolith_heap::top_k(int k) {
    if (!built) finalizeFrequencies();
    std::vector<Node> copy = heap;
    std::sort(copy.begin(), copy.end(), [](const Node &a, const Node &b) {
        return a.frequency > b.frequency;
    });
    k = std::min(k, (int)copy.size());

    std::vector<std::string> words;
    std::vector<float> freqs;
    for (int i = 0; i < k; ++i) {
        words.push_back(copy[i].word);
        freqs.push_back(copy[i].frequency);
    }
    return {words, freqs};
}

// Return bottom-k words by frequency (smallest first)
std::tuple<std::vector<std::string>, std::vector<float>> monolith_heap::bottom_k(int k) {
    if (!built) finalizeFrequencies();
    std::vector<Node> copy = heap;
    std::sort(copy.begin(), copy.end(), [](const Node &a, const Node &b) {
        return a.frequency < b.frequency;
    });
    k = std::min(k, (int)copy.size());

    std::vector<std::string> words;
    std::vector<float> freqs;
    for (int i = 0; i < k; ++i) {
        words.push_back(copy[i].word);
        freqs.push_back(copy[i].frequency);
    }
    return {words, freqs};
}

// Return frequency of a specific word (0.0 if not found)
float monolith_heap::identify(const std::string& word) {
    if (!built) finalizeFrequencies();
    std::string lw = to_lower(word);
    auto it = freqMap.find(lw);
    if (it == freqMap.end()) return 0.0f;
    return (it->second / totalWords) * 100.0f;
}
