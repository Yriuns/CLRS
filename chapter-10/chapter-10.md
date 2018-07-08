# 第10章 基本数据结构

## 10.1 栈和队列

没啥好说的

### 练习

#### 10.1-1

```
初始时
| | | | | | |

PUSH(S, 4)
|4| | | | | |

PUSH(S, 1)
|4|1| | | | |

PUSH(S, 3)
|4|1|3| | | |

POP(S)
|4|1| | | | |

PUSH(S, 8)
|4|1|8| | | |
```

#### 10.1-2

两个`top`指针，一左一右

#### 10.1-3

```
初始时
| | | | | | |

ENQUEUE(Q, 4)
|4| | | | | |

ENQUEUE(Q, 1)
|4|1| | | | |

ENQUEUE(Q, 3)
|4|1|3| | | |

DEQUEUE(Q)
| |1|3| | | |

ENQUEUE(Q, 3)
| |1|3|8| | |

DEQUEUE(Q)
| | |3|8| | |
```

#### 10.1-4

```
ENQUEUE(Q, x)
  if Q.head == Q.tail + 1
    error "overflow"
  Q[Q.tail] = x
  if Q.tail == Q.length
    Q.tail = 1
  else
    Q.tail = Q.tail + 1

DEQUEUE(Q)
  if Q.head == Q.tail
    error "underflow"
  x = Q[Q.head]
  if Q.head == Q.length
    Q.head = 1
  else
    Q.head = Q.head + 1
  return x
```

#### 10.1-5

两个指针`head`和`tail`

- `push_back`: `tail + 1`
- `pop_back`: `tail -1`
- `push_front`: `head - 1`
- `pop_front`: `head + 1`

#### 10.1-6

两个栈`S1`、`S2`
- `ENQUEUE`时`PUSH`至`S1`. $O(1)$
- `DEQUEUE`时
  - 若`S2`为空，则将`S1`内的元素全部`POP`到`S2`，然后再`POP`. $O(n)$
  - 若`S2`非空，则直接`POP`. $O(1)$

均摊$O(1)$

#### 10.1-7

两个队列`Q1`、`Q2`
- `PUSH`时`ENQUEUE`至某个非空队列，若皆空则至`Q1`. $O(1)$
- `POP`时，将非空队列的元素逐个`DEQUEUE`至另一个队列，直至剩下一个元素，`DEQUEUE`即可. $O(n)$

## 10.2 链表

- 双向链表
```cpp
template <typename T>
class Node {
  Node* prev;
  Node* next;
  T val;
}
```

- 单向链表

```cpp
template <typename T>
class Node {
  Node* next;
  T val;
}
```

- 哨兵的使用：在链表头部加入空`Node`，简化边界处理

### 练习

#### 10.2-1

- `INSERT`：可以
- `DELETE`：不行，需定位到`prev`

#### 10.2-2

把`L.head`当`S.top`用

#### 10.2-3

加入指针`L.tail`

#### 10.2-4
```
LIST-SEARCH(L, k)
  L.nil.key = k
  x = L.nil.next
  while x.key != k
    x = x.next
  return x
```

#### 10.2-5

```cpp
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
```

#### 10.2-6

因为是**不相交集合**，所以可以直接合并，于是选择链表，把`S2`的`head`接在`S1`的`tail`之后即可

#### 10.2-7

```cpp
Node* reverse(Node* head) {
  if (head == nullptr || head->next == nullptr) {
    return head;
  }
  Node* prev = head;
  Node* curr = head->next;
  Node* next;
  while (curr != nullptr) {
    next = curr->next;
    curr->next = prev;
    prev = curr;
    curr = next;
  }
  head->next = nullptr;
  return prev;
}
```

#### 10.2-8

问题的核心在于怎么从`x.np`中得到`x.next`与`x.prev`。注意到`a^b^b=a`与`a^0=a`，有如下性质：

- `T.head.np = T.head.next ^ T.head.prev = T.head.next`，也就是说对于表头来说，其`np`指针指向它的下一个元素。
- `T.head.np.np = T.head.next.prev ^ T.head.next.next = T.head ^ T.head.next.next`，从而`T.head.next.next = T.head.np.np ^ T.head`
- 类似地，有`T.head.next.next.next = T.head.np.np.np ^ T.head.next`
- 不难发现第`k`个元素的地址为`T.head`的第`k`个`np`指针与第`k-2`个元素地址的异或

从而代码如下

```cpp
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
```

## 10.3 指针和对象的实现

以链表为例，可以使用三个数组来表示
- `key[n]`
- `next[n]`
- `prev[n]`

### 练习

#### 10.3-1

一个可能的答案
```
L.head --------------------------+
                                 |
                                 V

       1   2   3   4    5   6    7   8   9
     +---+---+---+---+----+---+----+---+----+
next | 4 |   | 5 | 9 |  / |   |  1 |   |  3 |
     +---+---+---+---+----+---+----+---+----+
key  | 4 |   | 5 | 8 | 11 |   | 13 |   | 19 |
     +--------------------------------------+
prev | 7 |   | 9 | 1 |  3 |   |  / |   |  4 |
     +---+---+---+---+----+---+----+---+----+
```

单数组的把3个数组按`|key|next|prev|`三个一组的顺序合并一下就好，大概就是`|4|4|7| | | |5|5|9|...|19|3|4|`

#### 10.3-2

```
ALLOCATE-OBJECT()
  if free == NIL
    error "out of space"
  else
    x = free
    free = A[x + 1]
    return x

FREE-OBJECT(x)
  A[x + 1] = free
  free = x
```

#### 10.3-3

`prev`的变化由调用者自行维护，分配与释放只和自由表有关

#### 10.3-4

`FREE-OBJECT(x)`时，把`x`之后的所有元素左移一位，并且更新指针指向

#### 10.3-5

基本思路是双指针`p`、`q`，`p`指向最左侧的空槽，`q`指向`p`右边最靠左的非空槽，然后将`q`中的元素挪至`p`。

```cpp
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
```

## 10.4 有根树的表示

- 可以利用`k+1`个数组来表示`k`叉树(`parent, child_1, child_2, ..., child_k`)
- 还可以采用左孩子右兄弟表示法
  - `left-child`指向其最左的孩子节点
  - `right-sibling`指向其右侧的兄弟节点

### 练习

#### 10.4-1

```
          
         18
        /   \
       /     \
      /       \
     /         \
    /           \
   12           10
  / \          /  \
 /   \        /    \
7     4      2     21
     /
    /
   5
```

#### 10.4-2

```cpp
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
```

#### 10.4-3

```cpp
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
```

#### 10.4-4

```cpp
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
```

#### 10.4-5

基本思路是记录上一个访问的节点`prev`，然后通过判断`curr`与`prev`的父子关系来移动。`left`、`right`与`parent`里的下标是从1开始的(我后悔了)，所以要注意`+1`或`-1`。

```cpp
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
```

#### 10.4-6

`left-child`、`next`、`is_last`。`left-child`指针与原来保持一致。`next`指针在`is_last`为`false`时与`right-sibling`一致，否则指向`parent`。也就是说，最后一个兄弟节点的`next`指针为`parent`。

## 思考题

### 10-1

|| 未排序的单链表 | 已排序的单链表 | 未排序的双向链表 | 已排序的双向链表 |
|:--|:--:|:--:|:--:|:--:|
|`SEARCH(L, k)`| $O(n)$ | $O(n)$ | $O(n)$ | $O(n)$ |
|`INSERT(L, x)`| $O(1)$ | $O(n)$ | $O(1)$ | $O(n)$ |
|`DELETE(L, x)`| $O(n)$ | $O(n)$ | $O(1)$ | $O(1)$ |
|`SUCCESSOR(L, x)`| $O(n)$ | $O(1)$ | $O(n)$ | $O(1)$ |
|`PREDECESSOR(L, x)`| $O(n)$ | $O(n)$ | $O(n)$ | $O(1)$ |
|`MININUM(L)`| $O(n)$| $O(1)$ | $O(n)$ | $O(1)$ |
|`MAXIMUM(L)`| $O(n)$| $O(1)$ | $O(n)$ | $O(1)$ |

> 没有`tail`指针的话，最后一行应为$O(n)$、$O(n)$、$O(n)$、$O(n)$

### 10-2

注意只要支持以下操作就是可合并堆，不需要按照一般的堆的实现方式来实现。

||a|b|c|
|:--|:--|:--|:--|
|`MAKE-HEAP`|$O(1)$|$O(1)$|$O(1)$|
|`INSERT`|$O(n)$|$O(1)$|$O(1)$|
|`MINIMUM`|$O(1)$|$O(n)$|$O(n)$|
|`EXTRACT-MIN`|$O(1)$|$O(n)$|$O(n)$|
|`UNION`|$O(n)$|$O(n)$|$O(1)$|

### 10-3

**(a)** 对于第4行的`if`判断，由以下四种情况：
  - `COMPACT-LIST-SEARCH`不通过，`COMPACT-LIST-SEARCH'`通过。则必然有`j' == i`，从而两者`i == i'`。
  - `COMPACT-LIST-SEARCH`通过，`COMPACT-LIST-SEARCH'`通过。则有`i == i'`值相等。
  - `COMPACT-LIST-SEARCH`通过，`COMPACT-LIST-SEARCH'`不通过。不可能发生，因为前者在每次循环后还通过`i = next[i]`前进了一步，从而`key[i] >= key[i']`。
  - `COMPACT-LIST-SEARCH`不通过，`COMPACT-LIST-SEARCH'`不通过。`key[i] > key[i']`。

也就是说`i`比`i`离目标总是*更不远*，那么则有：
  - 若前者在第`t`次`random`后的`j`能够找到`k`，后者也一定可以，因为两者的`j`总是相同的
  - 若前者没有找到，则后者也一定找不到，因为`key[i] >= key[i']`总是成立的。且在前者的第9行有三种情况：
    - `i == NIL`：链表中没有`k`，后者也找不到
    - `key[i] > k`：链表中没有`k`，后者也找不到
    - `key[i] == k`：在第`t`次的`i = next[i]`时找到`k`，那么后者一定也能通过`while`循环找到(因为是逐个遍历的)

综上，二者返回值相等，且迭代次数至少为`t`。

**(b)** 距离为$X_t$，期望运行时间自然为$O(E[X_t])$

**(c)** 证明

$$E[X_t]\leq\sum_{r=1}^{n}(1-r/n)^t$$

过程如下：

$$E[X_t]=\sum_{r=0}^{n-1}P(X_t=r)\cdot r\leq \sum_{r=0}^{n-1}P(X_t\geq r)$$

又

$$P(X_t\geq r)=(\frac{n-r-1}{n})^t$$

从而

$$E[X_t]\leq \sum_{r=1}^{n}(1-\frac{r}{n})^t$$

**(d)** 证明

$$\sum_{r=0}^{n-1}\leq n^{t+1}/(t+1)$$

过程如下：

$$\sum_{r=0}^{n-1}r^t\leq\int_{0}^{n}r^t dr=\left.\frac{1}{t+1}\cdot r^{t+1}\right|_{0}^{n}=\frac{n^{t+1}}{t+1}$$

**(e)** 证明

$$E[X_t]\leq n/(t+1)$$

过程如下：

由c知：

$$E[X_t]\leq\sum_{r=1}^{n}(\frac{n-r}{n})^t$$

令$x=n-r-1$，上式化为

$$E[X_t]\leq\sum_{x=0}^{n}(\frac{x}{n})^t\leq\frac{n^{t+1}}{t+1}\cdot \frac{1}{n^t}=\frac{n}{t+1}$$

**(f)**

$$O(t+E[X_t])=O(t+\frac{n}{t+1})=O(t+n/t)$$

**(g)**

$$t+n/t\geq2\sqrt{n}$$

**(h)**

会导致第4行的`if`很难通过。比如考虑一个前`n-1`个元素都是`0`，最后一个元素为`1`的链表，搜索`1`将需要`O(n)`的时间。