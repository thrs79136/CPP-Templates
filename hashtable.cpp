#include <iostream>
#include <vector>
using namespace std;

template<class K>
using hashfunc = long(*)(K);

template<class T, class K>
using getKey = K(*)(T);

template<class T, class K>
class HashTable{
	public:
	HashTable(long size, hashfunc<K> pf, getKey<T,K> gK);
	void addEntry(T data);
	T getEntry(K key);
	template <class U, class L>
	friend ostream& operator<<(ostream &OS, HashTable<U,L> ht);
	private:
	long size;
	vector<T> *table;
	hashfunc<K> pf;
	getKey<T,K> gK;
};

template<class T, class K>
HashTable<T,K>::HashTable(long size, hashfunc<K> pf, getKey<T,K> gK){
	this->size = size;
	table = new vector<T>[size];
	this->pf = pf;
	this->gK = gK;
}

template<class T, class K>
void HashTable<T,K>::addEntry(T data){
	table[(*pf)((*gK)(data))%size].push_back(data);
}

template<class T, class K>
T HashTable<T,K>::getEntry(K key){
	for (T t: table[(*pf)(key)%size]){
		if (key == (*gK)(t)) return t;
	}
	throw new string("Element not found.");
}

template <class U, class L>
ostream& operator<<(ostream &OS, HashTable<U,L> ht){
	for (int i =0; i<ht.size;i++){
		for (auto t: ht.table[i])
			OS << t << '\t';
		OS << '\n';
	}
	return OS;
}
