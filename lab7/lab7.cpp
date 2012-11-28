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
	node *pleft;
	node *pright;

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
			if (tmp->left == NULL)
			{
				tmp->left = new node(k, v);
				return;
			}

			if (tmp->left != NULL)
			{
				tmp = tmp->left;
				place(k, v, tmp);
				return;
			}
		}

		if (k > tmp->key)
		{
			if (tmp->right == NULL)
			{
				tmp->right = new node(k, v);
				return;
			}

			if (tmp->right != NULL)
			{
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

	node* rec_get(int k, node *tmp, node *prev, bool retprev)
	{
		if (k == tmp->key)
		{
			if (retprev)
			{	
				return prev;
			}
			return tmp;
		}

		if (k < tmp->key)
		{
			if (tmp->left != NULL)
			{
				prev = tmp;
				tmp = tmp->left;
				rec_get(k, tmp, prev, retprev);
			}

			else if (tmp->left == NULL)
			{
				return NULL;
			}
		}

		else if (k > tmp->key)
		{
			if (tmp->right != NULL)
			{
				prev = tmp;
				tmp = tmp->right;
				rec_get(k, tmp, prev, retprev);
			}

			else if (tmp->right == NULL)
			{
				return NULL;
			}
		}
	}

	void recursive_remove(node *tmp)
	{
		node *prev, *rem, *passer;
		passer = root;
		prev = tmp;
		int search, keypass;
		string valuepass;

		if ((tmp->left == NULL) && (tmp->right == NULL))
		{
			search = tmp->key;
			rem = tmp;
			prev = rec_get(search, passer, rem, true);

			if ((prev->left != NULL) && (prev->left->key == rem->key))
			{
				prev->left = NULL;
			}

			else if ((prev->right != NULL) && (prev->right->key == rem->key))
			{
				prev->right = NULL;
			}

			delete(rem);
			return;
		}

		else if ((tmp->left != NULL) && (tmp->right == NULL))
		{
			tmp->key = tmp->left->key;
			tmp->value = tmp->left->value;
			tmp->right = tmp->left->right;
			tmp->left = tmp->left->left;
			delete(tmp->left);
			return;
		}

		else if ((tmp->left == NULL) && (tmp->right != NULL))
		{
			tmp->key = tmp->right->key;
			tmp->value = tmp->right->value;
			tmp->left = tmp->right->left;
			tmp->right = tmp->right->right;
			delete(tmp->right);
			return;
		}
		
		else if ((tmp->left != NULL) && (tmp->right != NULL))
		{
			prev = find_largest(tmp->left);
			keypass = prev->key;
			valuepass = prev->value;
			recursive_remove(prev);
			tmp->key = keypass;
			tmp->value = valuepass;
		}
	}

	node* find_largest(node *tmp)
	{
		if (tmp->right != NULL)
			{
				tmp = find_largest(tmp->right);
			}

		return tmp;
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

		if (!root)
		{
			root = new node(k, v);
			return;
		}
		if (root)
		{
			place(k, v, tmp);
		}
	}

	

	string non_recursive_get(int k)
	{
		int search = k;
		node *tmp;
		tmp = root;
		string novalue = "No value";

		if (!root)
		{
			cout << "Sorry, no value at that key" << endl;
			return novalue;
		}

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
		ret = root;
		string novalue = "No value";

		if (!root)
		{
			cout << "Sorry, no value at that key" << endl;
			return novalue;
		}

		ret = rec_get(k, tmp, ret, false);

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
		if (!root)
		{
			cout << "Sorry, no value at that key" << endl;
			return;
		}

		node *rem, *tmp, *prev;
		rem = root;
		prev = root;
		tmp = rec_get(k, rem, prev, false);

		if (tmp == NULL)
		{
			cout << "Sorry, no value at that key" << endl;
			return;
		}

		recursive_remove(tmp);

		
	}

	void dump()
	{
		if (!root)
		{
			cout << "Sorry, no data exists" << endl;
			return;
		}
		node *tmp;
		tmp = root;
		int level = 1;
		bool d = true;
		cout << "DUMP: (root node = " << tmp->key << ")" << endl;
		recursive_dump(level, tmp, d);
	}

	void dump_rev()
	{
		if (!root)
		{
			cout << "Sorry, no data exists" << endl;
			return;
		}
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