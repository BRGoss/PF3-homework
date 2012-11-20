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
	heap(int n)
	{
		count = 0;
		capacity = n;

		cout << "HEAP:  Making a heap of size " << n << " elements\n";
		array = new int[n+1];
	}

	void grow(int n)
	{
		int *parray = new int[n + 1];
		for (int i = 1; i <= n; i++)
		{
			parray[i] = array[i];
		}

		for (int i = 0; i <= n; i++)
		{
			delete(array);
			array++;
		}

  		capacity = n * 2;

		array = new int[capacity + 1];

		for (int i = 1; i <= n; i++ )
		{
			array[i] = parray[i];
		}

		for (int i = 1; i <= n + 1; i++)
		{
			delete(parray);
			parray++;
		}

		capacity = n * 2;
	}

	void put(int d)
	{
		if (count == capacity)
		{
			grow(capacity);
			cout << "PUT:  Increasing heap size to " << capacity << endl;
		}

		count ++;

		if (count == 1)
		{
			array[1] = d;
			return;
		}

		if ((d >= array[1]) && (count > 1))
		{
			for (int i = count; i > 0; i--)
			{
				array[i] = array[i - 1];
			}

			array[1] = d;
			return;
		}

		if ((d < array[1]) && (d > array[2]) && (count >= 1))
		{
			for (int i = count; i > 1; i--)
			{
				array[i] = array[i - 1];
			}

			array[2] = d;
			return;
		}

		if (d <= array[1])
		{
        	array[count] = d;
        }

	}

	int pop()
	{
		if (count == 0)
		{
			cout << "Sorry, but nothing is in the heap." << endl;
			return -1;
		}

		int ret = array[1];

		//moves all index values in the array down one to wipe out the first
		for (int i = 1; i < count; i++)
		{
			array[i] = array[i + 1];
		}
		//sets what was the last value to zero, reduces the count
		array[count] = 0;
		count--;
		//since we know index 1 is the new highest, we need to test for the next highest
		//sets second index as max, and tests rest of array to find highest value
		int max = array[2];
		int index = 2;

		for (int i = 2; i <= count; i++)
		{
			if (array[i] > max)
			{
				max = array[i];
				index = i;
			}
		}

		//moves the array in the index after the max down to wipe out it's place
		for (int i = index; i < count; i++)
		{
			array[i] = array[i + 1];
		}
		//moves array back up one and then placing the max value in index 2
		for (int i = count; i > 1; i--)
		{
			array[i] = array[i - 1];
		}
		array[2] = max;

		return ret;

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