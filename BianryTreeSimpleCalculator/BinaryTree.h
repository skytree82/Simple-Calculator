#ifndef __BINARY_TREE_H__
#define __BINARY_TREE_H__

#include <iostream>

template <class T>
class BTree {
private:
	T data;
	BTree<T>* left;
	BTree<T>* right;
	int size; // 해당 노드를 루트로 하는 Sub Tree의 사이즈
public:
	BTree(T data1) : data(data1), size(1) {
		left = NULL;
		right = NULL;
	}

	BTree<T>* GetLeftTree() {
		return left;
	}

	BTree<T>* GetRightTree() {
		return right;
	}

	void MakeLeftSubTree(BTree<T>* bt) {
		if (left != NULL) {
			size -= left->size;
			DeleteSubTree(left);
		}

		left = bt;
		size += bt->size;
	}

	void MakeRightSubTree(BTree<T>* bt) {
		if (right != NULL) {
			size -= right->size;
			DeleteSubTree(right);
		}

		right = bt;
		size += bt->size;
	}

	T GetData() {
		return data;
	}

	int BTSize() {
		return size;
	}
};

template <class T>
void DeleteSubTree(BTree<T>* bt) {
	if (bt == NULL) return;

	DeleteSubTree(bt->GetLeftTree());
	DeleteSubTree(bt->GetRightTree());
	delete bt;
}

template <class T>
void PreTrav(BTree<T>* nd) {
	if (nd == NULL) return;

	cout << nd->GetData();
	PreTrav(nd->GetLeftTree());
	PreTrav(nd->GetRightTree());
}

template <class T>
void InOrTrav(BTree<T>* nd) {
	if (nd == NULL) return;

	InOrTrav(nd->GetLeftTree());
	cout << nd->GetData();
	InOrTrav(nd->GetRightTree());
}

template <class T>
void PostTrav(BTree<T>* nd) {
	if (nd == NULL) return;

	PostTrav(nd->GetLeftTree());
	PostTrav(nd->GetRightTree());
	cout << nd->GetData();
}

#endif
