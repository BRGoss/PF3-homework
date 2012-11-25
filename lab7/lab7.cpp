#include <iostream>
#include <cstdlib>
#include <string>

using namespace std;

class node 
{
public:
	int key;
	string value;

	node *left;
	node *right;

	node(int k, string v)
	{
		key = k;
		value = v;

		left = NULL;
		right = NULL;
	}
};

class bst
{
private:
	node *root;

	void place(int k, string v, node *tmp)
	{
		if (k == tmp->key)
		{
			tmp->value = v;
			return;
		}

		if (k < tmp->key)
		{
			cout << "inside place " << k << "<" << tmp->key << endl;
			if (tmp->left == NULL)
			{
				cout << "new node and k is less than " << tmp->key << endl;
				tmp->left = new node(k, v);
				return;
			}

			if (tmp->left != NULL)
			{
				cout << "moving to the left" << endl;
				tmp = tmp->left;
				place(k, v, tmp);
				return;
			}
		}

		if (k > tmp->key)
		{
			cout << "Inside place " << k << ">" << tmp->key << endl;
			if (tmp->right == NULL)
			{
				cout << "new node and k is greater than " << tmp->key << endl;
				tmp->right = new node(k, v);
				return;
			}

			if (tmp->right != NULL)
			{
				cout << "moving to the right" << endl;
				tmp = tmp->right;
				place(k, v, tmp);
				return;
			}
		}
	}

	void recursive_dump(int l, node *tmp, bool d)
	{
		int level = l;
		bool direction = d;

		if (direction)
		{
			if (tmp->left != NULL)
			{
				recursive_dump(l + 1, tmp->left, d);
			}

			cout << "DUMP: index = " << tmp->key << ", data = " << tmp->value
			     << ", level = " << level;

			if (tmp->left != NULL)
			{
				cout << ", lchld = " << tmp->left->key;
			}

			if (tmp->right != NULL)
			{
				cout << ", rcld = " << tmp->right->key;
			}

			cout << endl;

			if (tmp->right != NULL)
			{
				recursive_dump(l + 1, tmp->right, d);
			}
		}

		if (!direction)
		{
			if (tmp->right != NULL)
			{
				recursive_dump(l + 1, tmp->right, d);
			}

			cout << "DUMP: index = " << tmp->key << ", data = " << tmp->value
			     << ", level = " << level;

			if (tmp->left != NULL)
			{
				cout << ", lchld = " << tmp->left->key;
			}

			if (tmp->right != NULL)
			{
				cout << ", rcld = " << tmp->right->key;
			}

			cout << endl;

			if (tmp->left != NULL)
			{
				recursive_dump(l + 1, tmp->left, d);
			}
		}
	}

	node* rec_get(int k, node *tmp)
	{
		if (k == tmp->key)
		{
			return tmp;
		}

		if (k < tmp->key)
		{
			cout << k << " is < " << tmp->key << endl;
			if (tmp->left != NULL)
			{
				tmp = tmp->left;
				rec_get(k, tmp);
			}

			else if (tmp->left == NULL)
			{
				return NULL;
			}
		}

		else if (k > tmp->key)
		{
			cout << k << " is > " << tmp->key << endl;
			if (tmp->right != NULL)
			{
				tmp = tmp->right;
				rec_get(k, tmp);
			}

			else if (tmp->right == NULL)
			{
				return NULL;
			}
		}
	}

	node* recursive_remove(node *tmp)
	{
		node *prev;

		
	}

	node* find_largest(node *tmp)
	{
		node *ret, *prev;
		ret = tmp;
		if (tmp->right != NULL)
			{
				prev = tmp;
				find_largest(tmp->right);
			}

		return prev;
	}

public:
	bst()
	{
		root = NULL;
	}

	void put(int k, string v)
	{
		node *tmp;
		tmp = root;

		if (root == NULL)
		{
			root = new node(k, v);
			cout << "root has been modified" << endl;
			return;
		}
		if (root != NULL)
		{
			cout << "comparing k to root" << endl;
			place(k, v, tmp);
		}
	}

	

	string non_recursive_get(int k)
	{
		int search = k;
		node *tmp;
		tmp = root;
		string novalue = "No value";

		while (search != tmp->key)
		{
			if (search < tmp->key)
			{
				if (tmp->left != NULL)
				{
					tmp = tmp->left;
				}

				else if (tmp->left == NULL)
				{
					cout << "Sorry, no value at that key" << endl;
					return novalue;
				}
			}

			if (search > tmp->key)
			{
				if (tmp->right != NULL)
				{
					tmp = tmp->right;
				}

				else if (tmp->right == NULL)
				{
					cout << "Sorry, no value at that key" << endl;
					return novalue;
				}
			}
		}

		return tmp->value;
	}

	string recursive_get(int k)
	{
		int search = k;
		node *tmp, *ret;
		tmp = root;
		string novalue = "No value";

		ret = rec_get(k, tmp);

		if (ret != NULL)
			return ret->value;

		if (ret == NULL)
		{
			cout << "Sorry, no value at that key" << endl;
			return novalue;
		}
	}

	void remove(int k)
	{
		node *rem, *tmp, *prev;
		tmp = root;
		tmp = rec_get(k, tmp);
//		cout << "recvd value" << endl;

		if (tmp == NULL)
		{
			cout << "Sorry, no value at that key" << endl;
			return;
		}
		
		prev = find_largest(tmp);
		cout << "value to remove " << prev->key << endl;
		rem = prev->right;
		tmp->key = rem->key;
		tmp->value = rem->value;
		prev->right = NULL;
		delete(rem);
	}

	void dump()
	{
		node *tmp;
		tmp = root;
		int level = 1;
		bool d = true;
		cout << "DUMP: (root node = " << tmp->key << ")" << endl;
		recursive_dump(level, tmp, d);
	}

	void dump_rev()
	{
		node *tmp;
		tmp = root;
		int level = 1;
		bool d = false;
		cout << "DUMP: (root node = " << tmp->key << ")" << endl;
		recursive_dump(level, tmp, d);
	}
};

int main(void)
{
	bst mybst;

	string cmd;
	int k;
	string v;

	while (cin >> cmd >> k >> v)
	{
		cout << "MAIN:  cmd= " << cmd << ", key= " << k << ", v= " << v << endl;

		if (cmd == "put")
		{
			mybst.put(k, v);
		}
		else if (cmd == "dump") // traverse tree in ascending order
		{
			mybst.dump();
		}
		else if (cmd == "dump_rev") // traverse tree in descending order
		{
			mybst.dump_rev();
		}
		else if (cmd == "get")
		{
			cout << "MAIN: get returns: " << mybst.non_recursive_get(k) << endl;
		}
		else if (cmd == "rget")
		{
			cout << "MAIN: rget returns: " << mybst.recursive_get(k) << endl;
		}
		else if (cmd == "rem")
		{
			mybst.remove(k);
		}
		else if (cmd == "quit")
		{
			exit(0);
		}
	}
}