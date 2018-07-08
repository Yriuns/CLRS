#include <cstdio>

struct Node {
  int key;
  Node* np;
};

struct List {
  Node* head;
  Node* tail;
  List() : head(nullptr), tail(nullptr) {}
  Node* search(int key);
  void remove(int key);
  void insert(int key);
  void reverse();
};

Node* XOR(Node* n1, Node* n2) {
  return (Node*)((unsigned long)n1 ^ (unsigned long)n2);
}

Node* List::search(int key) {
  Node* curr = this->head;
  Node* prev = nullptr;
  Node* next;
  while (curr) {
    if (curr->key == key) {
      return curr;
    }
    next = XOR(prev, curr->np);
    prev = curr;
    curr = next;
  }
  return nullptr;
}

void List::insert(int key) {
  Node* node = new Node();
  node->key = key;
  node->np = XOR(nullptr, this->head);
  if (this->head) {
    this->head->np = XOR(node, XOR(nullptr, this->head->np));
  }
  if (!this->tail) {
    this->tail = node;
  }
  this->head = node;
}

void List::remove(int key) {
  Node* curr = this->head;
  Node* prev = nullptr;
  Node* next;
  while (curr) {
    if (curr->key == key) {
      next = XOR(prev, curr->np);
      if (prev) {
        prev->np = XOR(XOR(prev->np, curr), next);
      } else {
        this->head = next;
      }

      if (next) {
        next->np = XOR(XOR(next->np, curr), prev);
      } else {
        this->tail = prev;
      }

      delete curr;
      curr = next;
      return;
    }
    next = XOR(prev, curr->np);
    prev = curr;
    curr = next;
  }
}

void List::reverse() {
  Node* tmp = this->head;
  this->head = this->tail;
  this->tail = tmp;
}

void traversal(List* l) {
  Node* curr = l->head;
  Node* prev = nullptr;
  Node* next;
  while (curr) {
    printf("%d ", curr->key);
    next = XOR(prev, curr->np);
    prev = curr;
    curr = next;
  }
  printf("\n");
}

int main() {
  List l;
  // insert
  for (int i = 0; i < 5; ++i) {
    l.insert(i);
  }
  traversal(&l);

  // search
  Node* node = l.search(3);
  printf("%d\n", node->key);

  // reverse
  l.reverse();
  traversal(&l);

  // remove
  l.remove(3);
  l.remove(1);
  l.remove(0);
  traversal(&l);

  return 0;
}