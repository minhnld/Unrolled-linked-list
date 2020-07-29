#include"UnrolledLinkedList.h"

void UnrolledLinkedList::add(int val) {
	tail = head;
	if (head == NULL) {
		head= new Node(nodeSize);
		head->add(val);
		numOfNodes++;
		size++;
		tail = head;
		return;
	}
	while (head->next != NULL) 
		head = head->next;

	if (head->numElements>=nodeSize) {
		head->next = new Node(nodeSize);
		head->next->prev = head;
		int count = 0;
		for (int i = head->getHalfNodeSize(); i < head->numElements; i++) {
			head->next->add(head->elements[i]);
			count++;
		}
		head->next->add(val);
		numOfNodes++;
		size++;
		for (int i = 0; i < count; i++)
			head->removeAt(head->numElements-1);
	}
	else {
		head->add(val);
		size++;
	}
	head = tail;
}

int UnrolledLinkedList::getAt(int pos) {
	if (pos < 0 || pos >= size) 
		throw "IndexOutOfBoundsException"; // check whether pos is valid or not
	// TODO
	Node* p = head;
	if (p == NULL) return -1;
	int count = 0;
	if (count == pos) return p->elements[0];
	count--;
	while (p != NULL && count!=pos) {
		for (int i = 0; i < p->numElements; i++) {
			count += 1;
			if (count == pos) return p->elements[i];
		}
		p = p->next;
	}
	return -1;
}

void UnrolledLinkedList::setAt(int pos, int val) {
	if (pos < 0 || pos >= size)
		throw "IndexOutOfBoundsException"; // check whether pos is valid or not
	// TODO
	Node* p = head;
	if (p == NULL) return;
	int count = 0;
	if (count == pos) p->elements[0]=val;
	count--;
	while (p != NULL && count != pos) {
		for (int i = 0; i < p->numElements; i++) {
			count += 1;
			if (count == pos) p->elements[i]=val;
		}
		p = p->next;
	}
}
void UnrolledLinkedList::insertAt(int pos, int val) {
	if (pos < 0 || pos > size)
		throw "IndexOutOfBoundsException"; // check whether pos is valid or not	
	// TODO
	Node* p = head;
	if (p == NULL&&pos==0) {
		add(val);
		return;
	}

	if (pos == size) {
		add(val);
		return;
	}
	if (nodeSize == 1) {
		int count = -1;
		while (count != pos) {
				count += 1;
				if (count == pos) {
					tail = head;
					head = p;
					if (p->numElements==1) {
						Node *newNode = new Node(nodeSize);
						newNode->prev = head;
						if (head->next) {
							newNode->next = head->next;
							Node *temp = head->next;
							head->next = newNode;
							temp->prev = newNode;
						}
						else {
							head->next = newNode;
							newNode->next = NULL;
						}

						newNode->add(head->elements[0]);
						head->removeAt(0);
						head = tail;
						insertAt(pos, val);
						numOfNodes++;
					}
					else {
						p->add(val);
						size++;
					}
					head = tail;
					return;
				}
			p = p->next;
		}
	}

	int count = -1;
	while (p!=NULL && count != pos) {
		for (int i = 0; i < p->numElements; i++) {
			count += 1;
			if (count == pos ) {
				tail = head;
				head = p;
				if (head->numElements >= nodeSize) {
					Node *newNode = new Node(nodeSize);
					newNode->prev = head;
					if (head->next) {
						newNode->next = head->next;
						Node *temp = head->next;
						head->next = newNode;
						temp->prev = newNode;
					}
					else {
						head->next = newNode;
						newNode->next = NULL;
					}
					int count = 0;
					for (int i = head->getHalfNodeSize(); i < head->numElements; i++) {
						newNode->add(head->elements[i]);
						count++;
					}
					for (int i = 0; i < count; i++)
						head->removeAt(head->numElements - 1);
					head = tail;
					insertAt(pos, val);
					numOfNodes++;
				}
				else {
					p->insertAt(i, val);
					size++;
				}
				head = tail;
				return;
			}
		}
		p = p->next;
	}
}
void UnrolledLinkedList::deleteAt(int pos)
{
	if (pos < 0 || pos >= size) 
		throw "IndexOutOfBoundsException"; // check whether pos is valid or not
	// TODO
	Node* p = head;
	if (p == NULL) return;
	int count = -1;
	while (p != NULL && count != pos) {
		for (int i = 0; i < p->numElements; i++) {
			count += 1;
			if (count == pos) {
				tail = head;
				head = p;
				head->removeAt(i);
				size--;
				if (size == 0) {
					head = NULL;
					return;
				}
				if (head->numElements < head->getHalfNodeSize()) {
					if (head->next) {
						if (head->next->numElements == head->getHalfNodeSize()) {
							for (int i = 0; i < head->getHalfNodeSize(); i++)
								head->add(head->next->elements[i]);
							if (head->next->next) {
								Node *temp = head->next->next;
								head->next = head->next->next;
								temp->prev = head;
								numOfNodes--;
							}
							else {
								head->next = NULL;
								numOfNodes--;
							}
						}
						else {
							head->add(head->next->elements[0]);
							head->next->removeAt(0);
						}
					}
					else {
						if (head->prev) {
							if (head->prev->numElements == head->getHalfNodeSize()) {
								for (int i = 0; i < head->numElements; i++)
									head->prev->add(head->elements[i]);
								head->prev->next = NULL;
								numOfNodes--;
							}
							else {
								head->insertAt(0, head->prev->elements[head->prev->numElements - 1]);
								head->prev->removeAt(head->prev->numElements - 1);
							}
						}
					}
				}
				head = tail;
				return;
				}
			}
		p = p->next;
		}
}

int UnrolledLinkedList::firstIndexOf(int val) {
	// TODO
	Node* p = head;
	if (p == NULL) return -1;
	int count = -1;
	while (p != NULL) {
		for (int i = 0; i < p->numElements; i++) {
			count += 1;
			if (p->elements[i] == val) return count;
		}
		p = p->next;
	}
	return -1;
}

int UnrolledLinkedList::lastIndexOf(int val) {
	// TODO
	Node* p = head;
	if (p == NULL) return -1;
	int count = -1;
	int lastIndex=-1;
	while (p != NULL) {
		for (int i = 0; i < p->numElements; i++) {
			count += 1;
			if (p->elements[i] == val) lastIndex = count;
		}
		p = p->next;
	}
	return lastIndex;
}

bool UnrolledLinkedList::contains(int val) {
	// TODO
	Node* p = head;
	if (p == NULL) return 0;
	int count = -1;
	while (p != NULL) {
		for (int i = 0; i < p->numElements; i++) {
			count += 1;
			if (p->elements[i] == val) return true;
		}
		p = p->next;
	}
	return false;
}

void UnrolledLinkedList::reverse() {
	// TODO
	tail = head;
	Node *temp = NULL;
	Node *current=head;
	if (head == NULL) return;
	while (head != NULL) {
		head->reverse();
		head = head->next;
	}
	head = tail;
	while (current){
		temp = current->prev;
		current->prev = current->next;
		current->next = temp;
		current = current->prev;
	}
	if (temp) head = temp->prev;
}

int* UnrolledLinkedList::toArray() {
	// TODO
	Node* p = head;
	if (p == NULL) return 0;
	int count = -1;
	int* array = new int[size];
	while (p != NULL) {
		for (int i = 0; i < p->numElements; i++) {
			count += 1;
			array[count] = p->elements[i];
		}
		p = p->next;
	}
	return array;
}