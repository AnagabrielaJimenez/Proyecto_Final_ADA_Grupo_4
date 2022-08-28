#include "NodeTree.h"

NodeTree::NodeTree(int MAX) {
    key = new int[MAX];
    ptr = new NodeTree *[MAX + 1];
}
