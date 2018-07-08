#include <cstdio>

struct Node {
  int key;
  Node* next;
};

struct List {
  Node* nil;
  List()  {
    this->nil = new Node();
    this->nil->key = -1;
    this->nil->next = nullptr;
  }
  Node* search(int key);
  void remove(int key);
  void insert(int key);
};


Node* List::search(int key) {
  this->nil->key = key;
  Node* curr = this->nil->next;
  while (curr && curr->key != key) {
    curr = curr->next;
  }
  if (curr == this->nil) {
    return nullptr;
  }
  return curr;
}

void List::insert(int key) {
  Node* node = new Node();
  node->key = key;
  node->next = this->nil->next;
  this->nil->next = node;
}

void List::remove(int key) {
  Node* curr = this->nil->next;
  Node* prev = this->nil;
  while (curr) {
    if (curr->key == key) {
      prev->next = curr->next;
      delete(curr);
    }
    prev = curr;
    curr = curr->next;
  }
}

void traversal(List* l) {
  Node* curr = l->nil->next;
  while (curr) {
    printf("%d ", curr->key);
    curr = curr->next;
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

  // remove
  l.remove(4);
  l.remove(0);
  traversal(&l);

  return 0;
}