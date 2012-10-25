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

    string no_list;

  public:

    linked_list()
    {
        head = NULL;
        no_list = "Sorry, no list currently exists.";
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
        if (!head && n != 0) {cout << no_list << endl; return;}

        else if (head && n == 0)
        {
            node<T> *tmp;
            tmp = head;
            head = new node<T>(d);
            head->next = tmp;
            return;
        }

        else if (n == 0) {head = new node<T>(d); return;}

        else if (n == size())
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
            if (n <= (size() - 2))
            {
                node<T> *tmp1, *tmp2, *tmp3;
                tmp1 = get_node(n - 1);
                tmp2 = tmp1->next;
                tmp3 = new node<T>(d);
                tmp1->next = tmp3;
                tmp3->next = tmp2;
            }

            else if (n == (size() - 1))
            {
                node<T> *tmp1, *tmp2, *tmp3;
                tmp1 = get_last_p();
                tmp2 = get_node(size() - 2);
                tmp3 = new node<T>(d);
                tmp3->next = tmp1;
                tmp2->next = tmp3;
            }

        }
    };

    void add_last(T d)
    {
        add(size(), d);
    };

    void add_first(T d)
    {
        add(0, d);
    };

    T get(int n)
    {
        if (!head)
        {
            cout << no_list << endl;
            return -1;
        }

        if (n >= size())
        {
            cout << "no node " << n << " exists." << endl;
            return -1;
        }

        if (n == 0)
        {
            return head->data;
        }
        
        node<T> *tmp;
        tmp = get_node(n);
        return tmp->data;
        
    };

    T get_first()
    {
        get(0);
    };

    T get_last()
    {
        get(size() - 1);
    };

    void remove(int n)
    {
        if (!head) {cout << no_list << endl; return;}

        if (n >= size())
        {
            cout << "There is no node " << n  << "." << endl;
            return;
        }

        if (size() == 1)
        {
            delete(head);
            head = NULL;
            return;
        }

        if (n == 0)
        {
            node<T> *tmp;
            tmp = head->next;
            delete(head);
            head = tmp;
            return;
        }

        else if (n == (size() - 1))
        {
            node<T> *tmp1, *tmp2;
            tmp1 = get_last_p();
            tmp2 = get_node((size() - 2));
            delete(tmp1);
            tmp2->next = NULL;
        }

        else
        {
            node<T> *tmp1, *tmp2, *tmp3;
            tmp2 = get_node(n);
            tmp1 = get_node(n - 1);
            tmp3 = tmp2->next;
            delete(tmp2);
            tmp1->next = tmp3;
        }

    };

    void remove_first()
    {
        remove(0);
    };

    void remove_last()
    {
        remove(size() - 1);
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