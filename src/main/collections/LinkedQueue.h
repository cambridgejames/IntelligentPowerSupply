#ifndef _LINKED_QUEUE_H_
#define _LINKED_QUEUE_H_

template <class T>
struct LinkNode {
	T data;
	LinkNode<T> *next;
	LinkNode<T> *last;
	LinkNode() {next = nullptr; last = nullptr;}
	LinkNode(T &item, LinkNode<T> *_next = nullptr, LinkNode<T> *_last = nullptr) {data = item; next = _next; last = _last;}
};

template<class T>
class LinkedQueue {

private:
    LinkNode<T> *head;
    LinkNode<T> *tail;
    unsigned short size;

public:
    LinkedQueue(void);
    ~LinkedQueue();

    unsigned short size();
    void offer(T &data);
    T poll(T &defaultValue = nullptr);
    T peek(T &defaultValue = nullptr);
};

#include "LinkedQueue.cpp"

#endif // End for _LINKED_QUEUE_H_