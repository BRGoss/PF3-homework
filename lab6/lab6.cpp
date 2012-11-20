#include <iostream>
#include <cstdlib>
#include <string>

using namespace std;

class heap
{
private:
	int count;
	int capacity;
	int *array;

public:
	myheap(int n)
	{
		count = 0;
		capacity = n;

		cout << "HEAP:  Making a heap of size " << n << " elements\n";
		array = new int[n+1];
	}

	void grow(int n)
	{
		int tempcap = capacity;
		int *temparray[tempcap];
		array++;
		for (int i = 1; i <=tempcap; i++)
		{
			temparray[i] = *array;
			array++;
		}

		delete(array);

		heap myheap(n);

		array++;
		for (int i = 1; i <= tempcap; i++)
		{
			*array = temparray[i];
			array++;
		}

		delete(temparray);

	}

	void put(int d)
	{
		if (count > capacity)
		{
			myheap.grow(count * 2);
		}

		array[count] = d;
		count++;

	}

	int pop(int d)
	{
		return array[d];
	}

	void dump()
	{
		for (int i = 1; i <= count; i++)
		{
			cout << "  DUMP: node at index [" << i << "] = " << array[i] << endl;
		}

		cout << endl;
	}
};

int main(void)
{
	heap myheap(4);

	string cmd;
	int d;

	while (cin >> cmd >> d)
	{
		cout << "MAIN: cmd = " << cmd << ", d = " << d << endl;

		if (cmd == "put")
		{
			myheap.put(d);
		}
		else if (cmd == "pop")
		{
			int i = myheap.pop();
			cout << "pop returns: " << i << endl;
		}
		else if (cmd == "dump")
		{
			myheap.dump();
		}
		else if (cmd == "quit")
		{
			exit(0);
		}
	}
}