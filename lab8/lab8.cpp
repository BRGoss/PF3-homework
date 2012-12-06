#include <iostream>
#include <cstdlib>
#include <string>

using namespace std;

class mergesort
{
private:
	void dump(int ar[], int len)
	{
		for (int i = 0; i < len; i++)
		{
			cout << "     DUMP:   data = " << ar[i] << endl;
		}

		cout << endl;
	}

public:
	void sort(int a[], int n)
	{
		int length = n;
		int left_length, right_length;
		string breakdown = "BREAKING DOWN:";
		string merge = "MERGED:  list:";

		if (n < 2)
		{
			return;
		}

		left_length = length / 2;
		right_length = length - left_length;

		int left[left_length];
		int right[right_length];

		for (int i = 0; i < left_length; i++)
		{
			left[i] = a[i];
		}

		for (int i = 0; i < right_length; i++)
		{
			right[i] = a[i + left_length];
		}

		cout << "BREAKING DOWN:" << endl;
		dump(a, length);
		cout << "left =" << endl;
		dump(left, left_length);
		cout << "right =" << endl;
		dump(right, right_length);

		if (left_length > 1)
		{
			sort(left, left_length);
		}

		if (right_length > 1)
		{
			sort(right, right_length);
		}

		int left_remaining, right_remaining, main_index;
		main_index = 0;
		left_remaining = left_length;
		right_remaining = right_length;

		while ((left_remaining > 0) && (right_remaining > 0))
		{
			if (left[left_length - left_remaining] <= 
				right[right_length - right_remaining])
			{
				a[main_index] = left[left_length - left_remaining];
				main_index++;
				left_remaining--;
			}

			else if (right[right_length - right_remaining] <
				     left[left_length - left_remaining])
			{
				a[main_index] = right[right_length - right_remaining];
				main_index++;
				right_remaining--;
			}
		}

		if (left_remaining > 0)
		{
			while (left_remaining > 0)
			{
				a[main_index] = left[left_length - left_remaining];
				main_index++;
				left_remaining--;
			}
		}

		else if (right_remaining > 0)
		{
			while (right_remaining > 0)
			{
				a[main_index] = right[right_length - right_remaining];
				main_index++;
				right_remaining--;
			}
		}

		cout << "MERGED:  list:" << endl;
		dump(a, length);
	}
};

int main(void)
{
	int ar[100];
	mergesort ms;

	int i, v, len;

	for (i = 0; i < 100; i++)
	{
		cout << "enter a number (-1 to quit): ";
		cin >> v;

		if (v < 0) break;

		ar[i] = v;
	}

	len = i;

	cout << "main:  before sort:\n";
	for (i = 0; i < len; i++)
	{
		cout << "main:  ar[" << i << "] = " << ar[i] << endl;
	}

	ms.sort(ar, len);

	cout << "main:  after sort:\n";
	for (i = 0; i < len; i++)
	{
		cout << "main: ar[" << i << "] = " << ar[i] << endl;
	}
}