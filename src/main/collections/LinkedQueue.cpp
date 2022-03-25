#ifndef _LINKED_QUEUE_CPP_
#define _LINKED_QUEUE_CPP_

#include "LinkedQueue.h"

template<class T>
LinkedQueue<T>::LinkedQueue(): size(0) {
    LinkNode<T> *current = new LinkNode<T>();
    this->head = current;
    this->tail = current;
}

template<class T>
LinkedQueue<T>::~LinkedQueue() {
    while (this->size > 0) {
        this->poll();
    }
    this->tail = nullptr;
    delete this->head;
}

// Implementation of methods

/**
 * @brief 获取队列的长度
 * 
 * @tparam T 模板类型
 * @return unsigned short 队列的长度
 */
template<class T>
unsigned short LinkedQueue<T>::size() {
    return this->size;
}

/**
 * @brief 向队列中添加一个元素
 *
 * @tparam T 模板类型
 * @param data 元素的值
 */
template<class T>
void LinkedQueue<T>::offer(T &data) {
    LinkNode<T> *current = new LinkNode<T>(data, nullptr, this->tail);
    this->tail = current;
    this->size++;
}

/**
 * @brief 移除并返回队列头部元素的值
 *
 * @tparam T 模板类型
 * @param defaultValue 默认返回值
 * @return T 队列头部元素的值
 */
template<class T>
T LinkedQueue<T>::poll(T &defaultValue) {
    if (this->size <= 0) {
        return defaultValue;
    }
    LinkNode<T> *current = this->head->next;
    this->head->next = current->next;
    if (current->next != nullptr) {
        current->next->last = head;
    }
    current->last = nullptr;
    current->next = nullptr;
    T data = current->data;
    delete current;
    this->size--;
    return data;
}

/**
 * @brief 返回队列头部元素的值，但不删除该元素
 *
 * @tparam T 模板类型
 * @param defaultValue 默认返回值
 * @return T 队列头部元素的值
 */
template<class T>
T LinkedQueue<T>::peek(T &defaultValue) {
    if (this->size <= 0) {
        return defaultValue;
    }
    return this->head->next->data;
}

#endif // End for _LINKED_QUEUE_CPP_
