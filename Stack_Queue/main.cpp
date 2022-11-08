#include <iostream>
#include <stack>

using namespace std;

class Stack {
public:
  Stack() : head_(nullptr), size_(0) {}
  Stack(const Stack &other) : Stack() {
    Node *temp = other.head_;
    Node *tempHead = nullptr;
    while (temp != nullptr) {
      if (tempHead == nullptr) {
        tempHead = head_ = new Node(temp->val_);
      } else {
        tempHead->prev_ = new Node(temp->val_);
        tempHead = tempHead->prev_;
      }
      temp = temp->prev_;
    }
  }

  ~Stack() {
    while (isEmpty()) {
      pop();
    }
  }

  Stack &pop() {
    Node *oldHead = head_;
    head_ = head_->prev_;
    delete oldHead;
    --size_;
    return *this;
  }

  bool isEmpty() const { return size_ == 0; }

  Stack &push() {
    head_ = new Node(size_, head_);
    ++size_;
  }

private:
  struct Node {
    int val_;
    Node *prev_;
    Node(int val, Node *prev = nullptr) : val_(val), prev_(prev) {}
  };
  Node *head_;
  int size_;
  void copy(Node *node) {
    if (node == nullptr) {
      return;
    } else {
      copy(node->prev_);
      head_ = new Node(node->val_, head_);
    }
  }
};

class Queue {
public:
  Queue() : head_(nullptr), down_(nullptr), size_(0) {}

  ~Queue() {
    while (isEmpty()) {
      pop();
    }
  }

  Queue(const Queue &obj)
      : /*this->head_ = obj.head_;
        this->down_ = obj.down_;*/
        Queue() {
    *this = obj;
  }

  bool isEmpty() const { return size_ == 0; }

  int size() const { return size_; }

  Queue &pop() {
    if (size_ != 0) {
      Node *oldHead;
      oldHead = head_;
      head_ = head_->prev_;
      delete oldHead;
    }
    if (size_ == 1) {
      head_ = down_ = nullptr;
    }
    size_--;
  }

  Queue &push(int a) {
    if (size_ != 0) {
      down_->prev_ = new Node(a);
      down_ = down_->prev_;
    } else {
      down_ = head_ = new Node(a);
    }
    size_++;
  }

  int front() const { return head_->val_; }

  int back() const { cout << down_->val_; }

  Queue &print() const {
    Node *temp = head_;
    for (int i = 0; i < size_; i++) {
      cout << temp->val_ << " ";
      temp = temp->prev_;
    }
  }

private:
  struct Node {
    int val_;
    Node *prev_;
    Node(int val, Node *prev = nullptr) : val_(val), prev_(prev) {}
  };
  Node *down_;
  Node *head_;
  int size_;
};

int main() {}
