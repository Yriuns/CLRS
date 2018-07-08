#include <cstdio>
#include <stack>

struct Tree {
  int* key;
  int* left;
  int* right;
  int* parent;
};

void traversal(Tree& tree, int root) {
  int prev = -1;
  int curr = root;
  while (curr != -1) {
    curr = curr - 1;
    if (prev == tree.parent[curr]) {
      printf("%d ", tree.key[curr]);
      prev = curr + 1;
      if (tree.left[curr] != -1) {
        curr = tree.left[curr];
      } else if (tree.right[curr] != -1) {
        curr = tree.right[curr];
      } else {
        curr = tree.parent[curr];
      }
    } else if (prev == tree.left[curr] && tree.right[curr] != -1) {
      prev = curr + 1;
      curr = tree.right[curr];
    } else {
      prev = curr + 1;
      curr = tree.parent[curr];
    }
  }
}

Tree build_tree() {
  Tree tree;
  int n = 10;
  tree.key = new int[n]{12, 15, 4, 10, 2, 18, 7, 14, 21, 5};
  tree.left = new int[n]{7, 8, 10, 5, -1, 1, -1, 6, -1, -1};
  tree.right = new int[n]{3, -1, -1, 9, -1, 4, -1, 2, -1, -1};
  tree.parent = new int[n]{6, -1, 1, 6, 4, -1, 1, -1, 4, 3};
  return tree;
}

int main() {
  Tree tree = build_tree();
  traversal(tree, 6);
  printf("\n");
  return 0;
}