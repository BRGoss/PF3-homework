#include <iostream>
#include <cstdlib>
#include <string>

using namespace std;

template<class T> class node
{
  public:
    node(T d) { next = NULL; data = d; }

    node *next;
    T data;
};


template<class T> class linked_list
{
  private:
    node<T> *head;

  public:

    linked_list()
    {
        head = NULL;
    }

    int size()
    {
        int size;
        if (!head)
            {
                size = 0;
                return size; 
            }
        else
        {
            size = 1;
            node<T> *counter;
            counter = head;
            while (counter->next != NULL)
            {
                counter = counter->next;
                size++;
            }
            return size;
        }
    };

    void add(int n, T d)
    {
        if (!head && n != 0) {cout << "Nothing in list" << endl;}

        else if (head && n == 0)
        {
            node<T> *tmp;
            tmp = head;
            head = new node<T>(d);
            head->next = tmp;
        }

        else if (n == 0) {head = new node<T>(d);}

        else if (n == -2)
        {
            node<T> *tmp;
            tmp = get_last_p();
            tmp->next = new node<T>(d);
        }

        else if (n > (size()))
        {
            cout << "There is not a node " << n - 1 << " that would precede this" << endl;
        }

        else
        {
            if (n < size())
            {
                node<T> *tmp1, *tmp2;
                tmp1 = get_node(n - 1);
                tmp2 = get_node(n);
                tmp1->next = new node<T>(d);
                tmp1->next->next = tmp2;
            }
            else
            {
                node<T> *tmp;
                tmp = get_last_p();
                tmp->next = new node<T>(d);
            }

        }
    };

    void add_last(T d)
    {
        int sz = -2;
        add(sz, d);
    };

    void add_first(T d)
    {
        add(0, d);
    };

    T get(int n)
    {
        if (!head)
        {
            cout << "No stacked list exists" << endl;
        }
        else
        {
            node<T> *tmp;
            tmp = get_node(n);
        }
    };

    T get_first()
    {
        return head->data;
    };

    T get_last()
    {
        node<T> *tmp;
        tmp = get_last_p();
        return tmp->data;
    };

    void remove(int n)
    {
        if (!head) {cout << "No list exists" << endl;}

        else if (n >= size())
        {
            cout << "There is no node " << n << endl;
        }

        else if (n == 0)
        {
            node<T> *tmp;
            tmp = head->next;
            delete(head);
            head = tmp;
        }

        else if (n == -2)
        {
            node<T> *tmp1, *tmp2;
            tmp1 = get_last_p();
            tmp2 = get_node((size() - 2));
            delete(tmp1);
            tmp2->next = NULL;
        }

        else
        {
            node<T> *tmp1, *tmp2;
            tmp1 = get_node(n - 1);
            tmp2 = tmp1->next->next;
            delete(tmp1->next);
            tmp1->next = tmp2;
        }

    };

    void remove_first()
    {
        remove(0);
    };

    void remove_last()
    {
        remove(-2);
    };

    node<T> *get_node(int n)
    {
        int counter = 0;
        node<T> *tmp;
        tmp = head;
        while (counter < n)
        {
            tmp = tmp->next;
            counter++;
        }
        return tmp;
    };

    node<T> *get_last_p()
    {
        node<T> *last;
        last = head;
        while (last->next != NULL)
        {
            last = last->next;
        }
        return last;
    };

    void dump()
    {
        node<T> *tptr;

        cout << "    DUMP: (size = " << size() << ", first = " << get_first() << ", last = " << get_last() << ")\n";

        if (head == NULL) {
            cout << "    DUMP: head = NULL\n\n";
            return;
        }

        tptr = head;

        cout << "    DUMP:   head = : " << tptr->data << endl;
        while (tptr->next != NULL) {
            tptr = tptr->next;
        cout << "    DUMP:   data = : " << tptr->data << endl;
        }
        cout << endl;
    }
};


int main(void)
{
    linked_list<int> ll;
    string cmd;
    int i, d;

    while (cin >> cmd >> i >> d)
    {
        cout << "MAIN: cmd = " << cmd << ", i = " << i
             << ", d = " << d << endl;

        if (cmd == "add")
            ll.add(i, d);
        else if (cmd == "addf")
            ll.add_first(d);
        else if (cmd == "addl")
            ll.add_last(d);
        else if (cmd == "rem")
            ll.remove(i);
        else if (cmd == "remf")
            ll.remove_first();
        else if (cmd == "reml")
            ll.remove_last();
        else if (cmd == "get") {
            d = ll.get(i);
            cout << "get returns: " << d << endl;
        } else if (cmd == "getf") {
            d = ll.get_first();
            cout << "getf returns: " << d << endl;
        } else if (cmd == "getl") {
            d = ll.get_last();
            cout << "getl returns: " << d << endl;
        } else if (cmd == "dump")
            ll.dump();
        else if (cmd == "quit")
            exit(0);
    }
}