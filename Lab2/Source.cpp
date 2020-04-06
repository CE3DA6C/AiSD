#include <iostream>
#include <memory>
#include <unordered_set>
#include <vector>
#include <list>
#include <algorithm>
#include "Timer.h"

#define N 1000
std::unordered_set<int> random_num_gen(static int how_many, static  int range_begin, static int range_end) {
	std::unordered_set<int> mset;
	int range = range_end - range_begin;

	while (mset.size() < how_many) {
		mset.insert(rand() % range);
	}

	return mset;
}
class BST {
	struct Node {
		int key;

		Node* left;
		Node* right;
	};

	Node* root;

	Node* empty(Node* node_to_empty) {
		if (node_to_empty != NULL) {
			empty(node_to_empty->left);
			empty(node_to_empty->right);
			delete node_to_empty;
		}
		return NULL;
	}

	Node* insert(int new_key, Node* new_node) {
		if (new_node == NULL) {
			new_node = new Node;
			new_node->key = new_key;
			new_node->left = new_node->right = NULL;
		}
		else if (new_key < new_node->key)
			new_node->left = insert(new_key, new_node->left);
		else if (new_key > new_node->key)
			new_node->right = insert(new_key, new_node->right);
		return new_node;
	}

	Node* search_p(Node* current_node, int searched_value) {
		if (current_node == NULL)
			return NULL;
		else if (searched_value < current_node->key)
			return search_p(current_node->left, searched_value);
		else if (searched_value > current_node->key)
			return search_p(current_node->right, searched_value);
		else
			return current_node;
	}

	void display_in_order(Node* current_node) {
		if (current_node == NULL)
			return;
		display_in_order(current_node->left);
		std::cout << current_node->key << " ";
		display_in_order(current_node->right);
	}
public:
	BST() {
		root = NULL;
	}
	~BST() {
		root = empty(root);
	}
	void insert(int n) {
		root = insert(n, root);
	}
	void search_for(int n) {
		root = search_p(root, n);
	}
	void display() {
		display_in_order(root);
		std::cout << "\n";
	}
};
class Sorted_list {
	std::list<int> base_list;
public:
	void insert(int num) {
		if (base_list.size()==0)
			base_list.push_back(num);
		else for (auto it = base_list.begin(); it != base_list.end(); it++) {
			if (*it >= num) {
				base_list.emplace(it, num);
				return;
			}
			else if (*it < num) {
				base_list.emplace_back(num);
				return;
			}
		}
	}
	void clear_elements() {
		for (int i = base_list.size(); i > 0; i--) {
			base_list.pop_front();
		}
	}
	void search_for(int num) {
		for (auto it = base_list.begin(); it != base_list.end(); it++)
			if (*it == num)
				return;
	}
	
	void display() {
		for (auto it = base_list.begin(); it != base_list.end(); it++) {
			std::cout << *it << " ";
		}
		std::cout << "\n";
	}
};

int main() {
	srand(time(NULL));
	static int q = 3000;
	static int rb = 0;
	static int re = 9999;

	std::unordered_set<int> v1 = random_num_gen(q, rb, re);
	
	float t_t1, t_t2, t_t3, t_l1, t_l2, t_l3;
	t_t1 = t_t2 = t_t3 = t_l1 = t_l2 = t_l3 = 0;

	/*Repeating the measurements N times*/
	for (int j = 0; j < N; j++) {
		/*BST measurements*/
		Timer timer_A;
		BST mytree;
		for (auto it = v1.begin(); it != v1.end(); it++) {
			mytree.insert(*it);
		}
		t_t1 += timer_A.elapsedTime();\

		timer_A.reset();
		for (auto it = v1.begin(); it != v1.end(); it++) {
			mytree.search_for(*it);
		}
		t_t2 += timer_A.elapsedTime();
		
		timer_A.reset();
		mytree.~BST();
		t_t3 += timer_A.elapsedTime();
		timer_A.~Timer();

		/*Sorted list measurements*/
		Timer timer_B;
		Sorted_list mylist;
		for (auto it = v1.begin(); it != v1.end(); it++) {
			mylist.insert(*it);
		}
		t_l1 += timer_B.elapsedTime();

		timer_B.reset();
		for (auto it = v1.begin(); it != v1.end(); it++) {
			mylist.search_for(*it);
		}
		t_l2+=timer_B.elapsedTime();

		timer_B.reset();
		mylist.clear_elements();
		t_l3 += timer_B.elapsedTime();
		timer_B.~Timer();
	}

	t_t1 /= N;
	t_l1 /= N;
	t_t2 /= N;
	t_l2 /= N;
	t_t3 /= N;
	t_l3 /= N;

	std::cout << "Czas utworzenia drzewa: " << t_t1 << "\n";
	std::cout << "Czas przeszukania drzewa: " << t_t2 << "\n";
	std::cout << "Czas usuniecia drzewa: " << t_t3 << "\n";

	std::cout << "Czas utworzenia listy: " << t_l1 << "\n";
	std::cout << "Czas przeszukania listy: " << t_l2 << "\n";
	std::cout << "Czas usuniecia listy: " << t_l3 << "\n";

	return 0;
}