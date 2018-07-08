#include <cstdio>

struct List {
  int* key;
  int* prev;
  int* next;
  char* used;
  int head;
  int free;
  int m;
  int n;
  List(int _m) : m(_m) {
    head = -1;
    key = new int[m];
    prev = new int[m];
    next = new int[m];
    used = new char[m];
    this->free = 0;
    for (int i = 0; i < m - 1; i++) {
      next[i] = i + 1;
      used[i] = 0;
      prev[i] = -1;
    }
    next[m - 1] = -1;
    prev[m - 1] = -1;
    n = 0;
  }
  int allocate();
  void release(int x);
  void insert(int k);
  void remove(int k);
  void to_string();
  void compactify();
};

int List::allocate() {
  if (this->free == -1) {
    printf("overflow\n");
    return -1;
  }
  int x = this->free;
  used[x] = 1;
  this->free = this->next[x];
  return x;
}

void List::release(int x) {
  this->next[x] = this->free;
  this->free = x;
  used[x] = 0;
}

void List::insert(int k) {
  int i = this->allocate();
  if (i == -1) {
    return;
  }
  n = n + 1;
  this->key[i] = k;
  next[i] = this->head;
  if (this->head != -1) {
    prev[this->head] = i;
  }
  this->head = i;
}

void List::remove(int k) {
  int curr = this->head;
  while (curr != -1) {
    if (this->key[curr] != k) {
      curr = this->next[curr];
    } else {
      int prev = this->prev[curr];
      this->next[prev] = this->next[curr];
      this->prev[this->next[curr]] = prev;
      this->key[curr] = -1;
      release(curr);
      n = n - 1;
      return;
    }
  }
}

void List::compactify() {
  if (m == n) {
    return;
  }
  int p = 0, q = 0;
  while (p < m) {
    while (used[p] && p < m) {
      p += 1;
    }
    if (p == m) {
      break;
    }
    q = p + 1;
    while (!used[q] && q < m) {
      q += 1;
    }
    if (q == m) {
      break;
    }
    next[prev[q]] = p;
    prev[next[q]] = p;
    key[p] = key[q];
    prev[p] = prev[q];
    next[p] = next[q];
    if (head == q) {
      head = p;
    }
    used[p] = 1;
    used[q] = 0;
  }
  for (int i = p; i < m - 1; ++i) {
    next[i] = i + 1;
  }
  next[m - 1] = -1;
}

void List::to_string() {
  printf("\n");
  printf("size : %d\n", n);
  printf("head : %d\n", head);
  printf("free : %d\n", free);
  printf("index: ");
  for (int i = 0; i < m; ++i) {
    printf(" %3d |", i);
  }
  printf("\n");
  printf(
      "------------------------------------------------------------------------"
      "\n");
  printf("key  : ");
  for (int i = 0; i < m; ++i) {
    if (used[i]) {
      printf(" %3d |", key[i]);
    } else {
      printf("     |");
    }
  }
  printf("\n");
  printf("next : ");
  for (int i = 0; i < m; ++i) {
    printf(" %3d |", next[i]);
  }
  printf("\n");
  printf("prev : ");
  for (int i = 0; i < m; ++i) {
    printf(" %3d |", prev[i]);
  }
  printf("\n\n");
}

void travesal(List& l) {
  int curr = l.head;
  while (curr != -1) {
    printf("%d ", l.key[curr]);
    curr = l.next[curr];
  }
  printf("\n");
}

int main() {
  List l(10);
  for (int i = 1; i <= 10; ++i) {
    l.insert(i % 2 ? i : -i);
  }
  l.remove(3);
  l.remove(9);
  l.remove(5);
  l.remove(7);
  travesal(l);
  l.to_string();
  l.compactify();
  travesal(l);
  l.to_string();
  travesal(l);
  return 0;
}