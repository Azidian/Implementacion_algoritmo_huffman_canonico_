#ifndef HUFFMAN_NODE_H
#define HUFFMAN_NODE_H

#include <memory>

/**
 * Node structure for the Huffman tree
 */
struct HuffmanNode {
    char symbol;           // Character symbol (only for leaf nodes)
    int frequency;         // Frequency of the symbol or sum of children
    std::shared_ptr<HuffmanNode> left;
    std::shared_ptr<HuffmanNode> right;
    bool is_leaf;          // True if this is a leaf node

    // Constructor for leaf nodes
    HuffmanNode(char sym, int freq) 
        : symbol(sym), frequency(freq), left(nullptr), right(nullptr), is_leaf(true) {}
    
    // Constructor for internal nodes
    HuffmanNode(int freq, std::shared_ptr<HuffmanNode> l, std::shared_ptr<HuffmanNode> r)
        : symbol('\0'), frequency(freq), left(l), right(r), is_leaf(false) {}
};

/**
 * Comparator for priority queue (min-heap)
 * Orders by frequency (ascending), then by symbol (ascending) for deterministic tie-breaking
 */
struct NodeComparator {
    bool operator()(const std::shared_ptr<HuffmanNode>& a, const std::shared_ptr<HuffmanNode>& b) const {
        if (a->frequency != b->frequency) {
            return a->frequency > b->frequency; // Min-heap: smaller frequency has higher priority
        }
        // Tie-breaking: compare by symbol (for leaf nodes)
        // For internal nodes, we use the minimum symbol in their subtree
        return getMinSymbol(a) > getMinSymbol(b);
    }

private:
    // Helper to get the minimum symbol in a subtree (for tie-breaking)
    static char getMinSymbol(const std::shared_ptr<HuffmanNode>& node) {
        if (node->is_leaf) {
            return node->symbol;
        }
        char left_min = node->left ? getMinSymbol(node->left) : 127;
        char right_min = node->right ? getMinSymbol(node->right) : 127;
        return std::min(left_min, right_min);
    }
};

#endif // HUFFMAN_NODE_H
