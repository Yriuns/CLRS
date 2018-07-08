#include <cstdio>
#include <stack>

struct Tree {
  int* key;
  int* parent;
  int* left_child;
  int* right_sibling;
};

void traversal(Tree& tree, int curr) {
  if (curr == -1) {
    return;
  }
  curr = curr - 1;
  printf("%d ", tree.key[curr]);
  int child = tree.left_child[curr];
  while (child != -1) {
    traversal(tree, child);
    child = tree.right_sibling[child - 1];
  }
}

Tree build_tree() {
  Tree tree;
  int n = 14;
  tree.key = new int[n]{3, 1, 2, 5, 9, 12, 7, 4, 6, 11, 10, 8, 13, 14};
  tree.left_child = new int[n] {-1, 1, 4, -1, -1, -1, 2, 5, -1, 9, -1, -1, 14, -1};
  tree.right_sibling = new int[n] {3, 8, -1, -1, 6, 10, -1, 13, 11, 12, -1, -1, -1, -1};
  tree.parent = new int[n] {2, 7, 2, 3, 8, 8, -1, 7, 10, 8, 10, 8, 7, 13};
  return tree;
}

int main() {
  Tree tree = build_tree();
  traversal(tree, 7);
  printf("\n");
  return 0;
}