#include <cstdio>
#include <stack>

struct Tree {
  int* key;
  int* left;
  int* right;
};

void recursive_traversal(Tree& tree, int curr) {
  if (curr == -1) {
    return;
  }
  curr = curr - 1;
  printf("%d ", tree.key[curr]);
  recursive_traversal(tree, tree.left[curr]);
  recursive_traversal(tree, tree.right[curr]);
}

Tree build_tree() {
  Tree tree;
  int n = 10;
  tree.key = new int[n]{12, 15, 4, 10, 2, 18, 7, 14, 21, 5};
  tree.left = new int[n]{7, 8, 10, 5, -1, 1, -1, 6, -1, -1};
  tree.right = new int[n]{3, -1, -1, 9, -1, 4, -1, 2, -1, -1};
  return tree;
}

int main() {
  Tree tree = build_tree();
  recursive_traversal(tree, 6);
  printf("\n");
  return 0;
}