#include <iostream>
#include <cstdlib>
#include <string>

using namespace std;

template<class T>
class node
{
public:
	node(int i, T d)
	{
		nextrow = NULL;
		prevrow = NULL;
		nextcol = NULL;
		prevcol = NULL;

		index = i;
		data = d;
	}

	int index;
	T data;

	node<T> *nextrow;
	node<T> *prevrow;
	node<T> *nextcol;
	node<T> *prevcol;
};

template<class T>
class sparseArray
{
private:
	node<T> *root;

public:
	sparseArray()
	{
		root = new node<T>(-1, -1);
	}

	void put(int r, int c, T d)
	{
		node<T> *mover, *add_row, *add_col, *prevptr;
		mover = root;

		if (root->nextrow == NULL)
		{
			add_row = new node<T>(r, -1);
			mover->nextrow = add_row;
			add_row->prevrow = mover;
			add_col = new node<T>(c, d);
			add_col->prevcol = add_row;
			add_row->nextcol = add_col;
			return;
		}

		while (mover->nextrow != NULL)
		{
			mover = mover->nextrow;
			if (mover->index == r)
			{
				while (mover->nextcol !=NULL)
				{
					mover = mover->nextcol;
					if (mover->index == c)
					{
						mover->data = d;
						return;
					}
					if (mover->index > c)
					{
						prevptr = mover->prevcol;
						add_col = new node<T>(c, d);
						prevptr->nextcol = add_col;
						add_col->prevcol = prevptr;
						add_col->nextcol = mover;
						mover->prevcol = add_col;
						return;
					}
					if ((mover->index < c) && mover->nextcol == NULL)
					{
						add_col = new node<T>(c, d);
						mover->nextcol = add_col;
						add_col->prevcol = mover;
						return;
					}
					if ((mover->index < c) && (mover->nextcol->index > c))
					{
						prevptr = mover;
						mover = mover->nextcol;
						add_col = new node<T>(c, d);
						prevptr->nextcol = add_col;
						add_col->prevcol = prevptr;
						add_col->nextcol = mover;
						mover->prevcol = add_col;
						return;
					}
				}
			}
			if ((mover->index < r) && (mover->nextrow == NULL))
			{
				add_row = new node<T>(r, -1);
				mover->nextrow = add_row;
				add_row->prevrow = mover;
				add_col = new node<T>(c, d);
				add_col->prevcol = add_row;
				add_row->nextcol = add_col;
				return;
			}

			if (mover->index > r)
			{
				prevptr = mover->prevrow;
				add_row = new node<T>(r, -1);
				prevptr->nextrow = add_row;
				add_row->prevrow = prevptr;
				add_row->nextrow = mover;
				mover->prevrow = add_row;
				add_col = new node<T>(c, d);
				add_row->nextcol = add_col;
				add_col->prevcol = add_row;
				return;
			}

			if ((mover->index < r) && (mover->nextrow->index > r))
			{
				prevptr = mover;
				mover = mover->nextrow;
				add_row = new node<T>(r, -1);
				prevptr->nextrow = add_row;
				add_row->prevrow = prevptr;
				add_row->nextrow = mover;
				mover->prevrow = add_row;
				add_col = new node<T>(c, d);
				add_col->prevcol = add_row;
				add_row->nextcol = add_col;
				return;
			}
		}

	}

	T get(int r, int c)
	{
		node<T> *mover, *rowptr;
		mover = root;

		if (mover->nextrow == NULL)
		{
			cout << "Sorry, but row " << r << " does not exist." << endl;
			return 0;
		}

		while (mover->nextrow != NULL)
		{
			mover = mover->nextrow;

			if (mover->index == r)
			{
				rowptr = mover;

				while (mover->nextcol != NULL)
				{
					mover = mover->nextcol;

					if (mover->index == c)
					{
						return mover->data;
					}

					if ((mover->index != c) && (mover->nextcol == NULL))
					{
						cout << "Sorry, but column " << c 
						     << " does not exist." << endl;
						return 0;
					}
				}

			}

			if ((mover->index != r) && (mover->nextrow == NULL))
			{
				cout << "Sorry, but row " << r << " does not exist." << endl;
				return 0;
			}
		}
	}

	void remove(int r, int c)
	{
		node<T> *mover, *rowptr, *colptr, *prevptr, *nextptr;
		mover = root;

		if (mover->nextrow == NULL)
		{
			cout << "Sorry, but row " << r << " does not exist." << endl;
			return;
		}

		while (mover->nextrow != NULL)
		{
			mover = mover->nextrow;
			if (mover->index == r)
			{
				rowptr = mover;

				while (mover->nextcol != NULL)
				{
					mover = mover->nextcol;
					if (mover->index == c)
					{
						if (mover->nextcol != NULL)
						{
							colptr = mover;
							prevptr = mover->prevcol;
							nextptr = mover->nextcol;
							delete(colptr);
							prevptr->nextcol = nextptr;
							nextptr->prevcol = prevptr;
							return;
						}

						if ((mover->prevcol->prevcol != NULL) && (mover->nextcol == NULL))
						{
							colptr = mover;
							prevptr = mover->prevcol;
							delete(colptr);
							prevptr->nextcol = NULL;
							return;
						}

						if ((mover->prevcol->prevcol == NULL) && (mover->nextcol == NULL))
						{
							if (rowptr->nextrow != NULL)
							{
								colptr = mover;
								delete(colptr);
								prevptr = rowptr->prevrow;
								nextptr = rowptr->nextrow;
								delete(rowptr);
								prevptr->nextrow = nextptr;
								nextptr->prevrow = prevptr;
								return;
							}

							if (rowptr->nextrow == NULL)
							{
								prevptr = rowptr->prevrow;
								delete(rowptr);
								prevptr->nextrow = NULL;
								return;
							}
						}
					}

					if ((mover->index != c) && (mover->nextcol == NULL))
					{
						cout << "Sorry, but the column " << c 
						     << " does not exist." << endl;
						return;
					}
				}
			}

			if ((mover->nextrow == NULL) && (mover->index != r))
			{
				cout << "Sorry, but the row " << r << " does not exist." << endl;
				return;
			}
		}
	}

	void dump()
	{
		node<T> *rowptr, *colptr;

		rowptr = root;

		while (rowptr->nextrow != NULL)
		{
			rowptr = rowptr->nextrow;
			cout << "     DUMP:     row = " << rowptr->index << endl;
			colptr = rowptr;
			while (colptr->nextcol != NULL)
			{
				colptr = colptr->nextcol;
				cout << "     DUMP:     col =      " << colptr->index
				     << " data = " << colptr->data << endl;
			}
		}
		cout << endl;
	}

	void rdump()
	{
		node<T> *rowptr, *colptr;

		rowptr = root;

		while (rowptr->nextrow != NULL)
		{
			rowptr = rowptr->nextrow;
		}

		while ((rowptr->prevrow != NULL)  && (rowptr->index != -1))
		{

			cout << "     DUMP:     row = " << rowptr->index << endl;
			colptr = rowptr;

			while (colptr->nextcol != NULL)
			{
				colptr = colptr->nextcol;
			}

			while ((colptr->prevcol != NULL) && (colptr->index != -1))
			{
				cout << "     DUMP:     col =     " << colptr->index
				     <<  " data = " << colptr->data << endl;
				colptr = colptr->prevcol;
			}
			rowptr = rowptr->prevrow;
		}

		cout << endl;
	}
};

int main(void)
{
	sparseArray<int> sa;
	string cmd;
	int d, r, c;

	while (cin >> cmd >> r >> c >> d)
	{
		cout << "MAIN: cmd = " << cmd << ", r = " << r << ", c = "
		     << c << ", d = " << d << endl;

		if (cmd == "put")
		{
			sa.put(r, c, d);
		}
		else if (cmd == "get")
		{
			int i = sa.get(r, c);
			cout << "get returns: " << i << endl;
		}
		else if (cmd == "rem")
		{
			sa.remove(r, c);
		}
		else if (cmd == "dump")
		{
			sa.dump();
		}
		else if (cmd == "rdump")
		{
			sa.rdump();
		}
		else if (cmd == "quit")
		{
			exit(0);
		}
	}
}