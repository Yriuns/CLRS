#include <cstdio>
#include <stack>

struct Tree {
  int* key;
  int* left;
  int* right;
};

void iterative_traversal(Tree& tree, int root) {
  std::stack<int> s;
  s.push(root);
  while (!s.empty()) {
    int curr = s.top() - 1;
    s.pop();
    printf("%d ", tree.key[curr]);
    if (tree.right[curr] != -1) {
      s.push(tree.right[curr]);
    }
    if (tree.left[curr] != -1) {
      s.push(tree.left[curr]);
    }
  }
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
  iterative_traversal(tree, 6);
  printf("\n");
  return 0;
}