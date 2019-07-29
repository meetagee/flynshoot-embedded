#include "linkedlist.h"

void linkedList_init (linkedList_t* linkedList) {
	linkedList->head = nullptr;
	linkedList->tail = nullptr;
}

void insert_back(linkedList_t* linkedList, activeObj_t data) {
	node_t* tmp;
	tmp->data = data;
	tmp->next = nullptr;

	if(linkedList->head == nullptr) {
		linkedList->head = tmp;
		linkedList->tail = tmp;
	}
	else {
		linkedList->tail->next = tmp;
		linkedList->tail = linkedList->tail->next;
	}
}

node_t* getTail (linkedList_t* linkedList) {
	return linkedList->tail;
}

void delete_front (linkedList_t* linkedList) {
	node_t* tmp;
	tmp = linkedList->head;
	linkedList->head = linkedList->head->next;
	delete tmp;
}
