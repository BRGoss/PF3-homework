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
		cout << "count is " << count << " capacity is " << capacity << endl;
	}

	void grow(int n)
	{
		cout << "inside grow and declare tempcap" << endl;
		int tempcap = capacity;
		cout << "tempcap = " << tempcap << endl;
		cout << "declare temparray" << endl;
		int *temparray;
		cout << "assign temparray" << endl;
		temparray = new int[(n / 2 + 1)];

		cout << "about to do tempcap" << endl;
		for (int i = 1; i <= tempcap; i++)
		{
			temparray[i] = array[i];
		}

		delete(array);

		array = new int(n + 1);
		capacity = n;
		cout << "PUT:  Increasing heap size to " << capacity << endl;

		for (int i = 1; i <= tempcap; i++)
		{
			array[i] = temparray[i];
//			count++;
			cout << "count is " << count << endl;
		}

		delete(temparray);
	}

	void put(int d)
	{
		if (count == capacity)
		{
			grow(capacity * 2);
		}
		array[count + 1] = d;
        count++;

        cout << "count " << count << " capacity " << capacity << endl;
	}

	int pop(int d)
	{
		
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
//			int i = myheap.pop();
//			cout << "pop returns: " << i << endl;
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