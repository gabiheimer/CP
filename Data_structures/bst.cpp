#include<bits/stdc++.h>

using namespace std;

struct TreeNode {
    int val;
    TreeNode *left, *right;

    TreeNode(int v) {
        val = v;
        left = NULL;
        right = NULL;
    }
};

class bst {
    TreeNode *root;

    bst() {
        root = NULL;
    }

    bool recursiveSearch(TreeNode *cur, int key) {
        if(!cur) return false;

        if(key < cur->val) return recursiveSearch(cur->left, key);
        if(key > cur->val) return recursiveSearch(cur->right, key);

        return true;
    }

    bool search(int key) {
        return recursiveSearch(root, key);
    }

    TreeNode* recursiveInsert(TreeNode *cur, int key) {
        if(!cur) return new TreeNode(key);

        if(key < cur->val) cur->left = recursiveInsert(cur->left, key);
        else if(key > cur->val) cur->right = recursiveInsert(cur->right, key);

        return cur;
    }

    void insert(int key) {
        root = recursiveInsert(root, key);
    }

    TreeNode *recursiveRemove(TreeNode *cur, int key) {
        if(!cur) return NULL;

        if(key < cur->val) cur->left = recursiveRemove(cur->left, key);
        if(key > cur->val) cur->right = recursiveRemove(cur->right, key);

        if(key == cur->val) {
            if(!cur->left) return cur->right;
            if(!cur->right) return cur->left;

            TreeNode *next = cur->right, *nextParent = cur;

            while(next->left) {
                nextParent = next;
                next = next->left;
            }

            cur->val = next->val;
            
            if(nextParent == cur) nextParent->right = next->right;
            else nextParent->left = next->right;
        }

        return cur;
    }

    void remove(int key) {
        root = recursiveRemove(root, key);
    }
};