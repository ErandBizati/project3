/**
 * file DblLink.h
 * author Erand Bizati
 * date 21 October 2023
 *
 * brief Doubly-linked list in C++.
 *
 * details this file contains the doubly linked definition and iterator for traversal
 */


#ifndef DBLLINK_H
#define DBLLINK_H

#include "Node.h" 																			// headerfile inclusion


template <class eltType>
class DblLink {
	
	private:
		friend class DblLinkItr<eltType>;													//friend declaration
		Node<eltType>* head; 																// first node pointer
		Node<eltType>* tail; 																// last node pointer
		int count;																			// number of elts
		void clear();																		// clears the list
		void copyFrom(const DblLink<eltType>& other);										//copies elts from list
	
	public:
	DblLink() : head(nullptr), tail(nullptr), count(0) {}									//constructor
	DblLink(const DblLink<eltType>& other);									    			//copy constructor
	~DblLink();																		        //destructor

	DblLinkItr<eltType> begin() {
		return DblLinkItr<eltType>(this, head);												// create iterator at head of list
	}

	DblLinkItr<eltType> end() {
		return DblLinkItr<eltType>(this, tail);												// create iterator at tail of list
	}
	  
																				            //assignment operator
	DblLink& operator=(const DblLink<eltType>& other);
	
																				            //member func	
	void insert(const eltType& item);														//insert and keep order
	
	
	bool remove(const eltType& item);   													// remove
	
	int size() const {															    		//return size of list
		return count;		
	} 	  

	bool isEmpty() const {																	//checks if list is empty
   		 return count == 0;
	}

};

template <class ItrEltType>
class DblLinkItr {
	private:
		Node<ItrEltType>* current; 															// current node pointer
		DblLink<ItrEltType>* list; 															// linked list pointer

		void next() {																		//advance iterator to next node
			if (current != nullptr) {
				current = current->next;
			}
		}
		
		void prev() {																		// move iterator to prev node
			if (current != nullptr) {
				current = current->prev;
			}
		}

	public:
		
		DblLinkItr(DblLink<ItrEltType>* listPtr, Node<ItrEltType>* startNode)				//constructor
    : list(listPtr), current(startNode) {}

		void start() {																		//point to first node of list
			current = list->head;
		}

		bool isEmpty() const {																// check if list is empty
			return current == nullptr;
		}

		bool isLastNode() const {															// check if iterator is at last node
			return (current != nullptr && current->next == nullptr);
		}

		bool isFirstNode() const {															// check if the iterator is at first node
			return (current != nullptr && current->prev == nullptr);
		}

																							// prefix increment
   		 DblLinkItr& operator++() {
        	next();  																		// move to the next node
        	return *this;
   		 }
																							// prefix decrement
		 DblLinkItr& operator--() {															
        	prev();  																		// move to the prev node
       		 return *this;
    	}


																							// postfix increment
		DblLinkItr operator++(int) {
			DblLinkItr temp = *this;
			next();
			return temp;
		}

																							// postfix decrement
		DblLinkItr operator--(int) {
			DblLinkItr temp = *this;
			prev();
			return temp;
		}

		 ItrEltType& operator*() {															// non const version of dereference operator
       		 if (current != nullptr) {
            return current->data;
       		 } else {
            throw std::runtime_error("Iterator is pointing to nullptr.");
        }
    }

   		 const ItrEltType& operator*() const {												// const version of dereference operator
       		 if (current != nullptr) {
         	   return current->data;
      		  } else {
            throw std::runtime_error("Iterator is pointing to nullptr.");
        }
    }

};

	
template <class eltType>														  			//copy constructor operator def
DblLink<eltType>::DblLink(const DblLink<eltType>& other) {
	head = tail = nullptr;															  		//initialize head, tail, and count
	count = 0;

	Node<eltType>* current = other.head;													//copy elts from other and update count
	while (current != nullptr) {
		insert(current->data); 													  			// insert increments count
		current = current->next;
	}
}

template <class eltType>															  		//destructor operator def
DblLink<eltType>::~DblLink() {
	clear();
}


template <class eltType>															  		//assignment operator def
DblLink<eltType>& DblLink<eltType>::operator=(const DblLink<eltType>& other) {
	
	if (this != &other) {															
		clear();																	         //clear list
		copyFrom(other);															   		 //copy elts from other and update count
	}	
	return *this;
}

template<class eltType>
void DblLink<eltType>::clear() {															//clear def
	Node<eltType>* current = head;															//start at head
	Node<eltType>* nextNode;												  				//declare pointer
	while (current) {														
		nextNode = current->next;															//store next node
		delete current;															  			//delete node
		current = nextNode;																	//move node
	}
	head = tail = nullptr;																	//reset
	count = 0;

}

template<class eltType>															      		//copyFrom def
void DblLink<eltType>::copyFrom(const DblLink<eltType>& other) {
	Node<eltType>* current = other.head;													//start at other head
	while (current) {
		insert(current->data);													    		//insert data from other list into current list
		current = current->next;												      		//move node
	}
	
}

template <class eltType>
void DblLink<eltType>::insert(const eltType& item) { 										// insert definition
    Node<eltType>* newNode = new Node<eltType>(item);
    Node<eltType>* current = head;							
    if (!head) { 																			//if list is empty
        head = tail = newNode;																//newNode becomes only node
    } else {																				//if not empty
        if (head->data >= item) {
            newNode->next = head;
            head->prev = newNode;
            head = newNode;																	// insert at beginning
        } else {
            while (current->next != nullptr && current->next->data < item) {				//insert at middle or end
                current = current->next;
            }
            newNode->next = current->next;
            if (current->next != nullptr) {													//if insertion wont occur at end, adjust link of next node
                current->next->prev = newNode;
            }
            current->next = newNode;														//if insertion at end, update tail
            newNode->prev = current;
            if (newNode->next == nullptr) {
                tail = newNode;
            }
        }
    }
    ++count; 
}

template<class eltType>	
bool DblLink<eltType>::remove(const eltType& item){          								//remove definition
  Node<eltType>* current = head;                            								//start from head
  
  while (current != nullptr && current->data != item){      								//find node to remove
    current = current->next;
  }
if (current == nullptr) {                                   								 //if not found
  return;                                                   								 //return
}

if (current ->prev != nullptr){                            									 //update node pointers 
  current->prev->next = current->next;
} else {
  head = current->next;                                   									 //if head gets removed, update
}
if (current->next != nullptr) {
  current->next->prev = current->prev;  
} else {
  tail = current->prev;                                  									//if tail gets removed, update 
}

delete current;                                        										 //delete node
--count;                                              										 //decrement count
}

#endif 