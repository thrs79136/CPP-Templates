#include <iostream>
using namespace std;

template <class T>
class Node{
	public:
	Node(T *pData);
	T *getData()const{return pData;}
	Node<T> *getNext()const{return pNext;}
	void setNext(Node<T> *pNext){this->pNext=pNext;}
	template <class U>
	friend ostream &operator<<(ostream &OS, Node<U> &node);
	private:
	T *pData;
	Node<T> *pNext;
};

template <class T>
Node<T>::Node(T *pData){
	this->pData = pData;
}

template <class U>
ostream &operator<<(ostream &OS, Node<U> &node){
	OS << *node.pData << "\n";
       	return OS;	
}

template <class T>
class Stack{
	public:
	Stack();
	bool pop();
	bool push(T *pData);
	template <class U>
	friend ostream &operator<<(ostream &OS, const Stack<U> *stack);
	~Stack();
	private:
	Node<T> *pTop;
};

template<class U>
ostream &operator <<(ostream &OS, const Stack<U> *stack){
	for (Node<U> *pS = stack->pTop; pS->getData(); pS = pS->getNext()){
		OS << *pS;
	}
	return OS;
};

template <class T>
Stack<T>::Stack(){
	pTop = new Node<T>(NULL);
}

template <class T>
Stack<T>::~Stack(){
	while (pTop->getData()){
		Node<T> *pN = pTop;
		pTop = pTop->getNext();
		delete pN;
	}
}

template<class T>
bool Stack<T>::pop(){
	if (!pTop->getData()) return false;
	Node<T> *pN = pTop;
	pTop = pTop->getNext();
	delete pN;
	return true;
}

template <class T>
bool Stack<T>::push(T *pData){
	Node<T> *pN = new Node<T>(pData);
	if (!pN) return false;
	pN->setNext(pTop);
	pTop = pN;
	return true;
}

int main(){
	int a = 1, b=2,c=3;
	Stack<int> *stack= new Stack<int>;
	stack->push(&a);
	stack->push(&b);
	stack->push(&c);
	cout << stack;
	delete stack;
	return 0;
}
