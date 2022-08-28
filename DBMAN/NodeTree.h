#ifndef PROYECTO_FINAL_ADA_GRUPO_4_NODETREE_H
#define PROYECTO_FINAL_ADA_GRUPO_4_NODETREE_H

#include <bits/stdc++.h>

class NodeTree {
private:
    bool IS_LEAF;
    int *key, size;
    NodeTree **ptr;
    friend class BPTree;
public:
    NodeTree(int);
};


#endif //PROYECTO_FINAL_ADA_GRUPO_4_NODETREE_H
