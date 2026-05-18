#pragma once

template <typename T>
class LineList {
private:
    struct Node {
        T data;
        Node* next;
        Node(const T& val) : data(val), next(nullptr) {}
    };

    Node* head;
    int size;

public:
    LineList() : head(nullptr), size(0) {}

    ~LineList() {
        if (head == nullptr) return;
        Node* cur = head;
        do {
            Node* tmp = cur;
            cur = cur->next;
            delete tmp;
        } while (cur != head);
    }

    void pushBack(const T& val) {
        Node* newNode = new Node(val);
        if (head == nullptr) {
            head = newNode;
            head->next = head;
        } else {
            Node* tail = head;
            while (tail->next != head)
                tail = tail->next;
            tail->next = newNode;
            newNode->next = head;
        }
        size++;
    }

    int getSize() const {
        return size;
    }

    T removeAfter(Node* prev) {
        Node* toDelete = prev->next;
        T val = toDelete->data;
        prev->next = toDelete->next;
        if (toDelete == head)
            head = toDelete->next;
        delete toDelete;
        size--;
        return val;
    }

    Node* advance(Node* node, int steps) {
        for (int i = 0; i < steps; i++)
            node = node->next;
        return node;
    }

    Node* getHead() const {
        return head;
    }
};
