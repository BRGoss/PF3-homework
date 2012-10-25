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
        if (!head && n != 0) {cout << no_list << endl;}

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
            if (n < (size() - 2))
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
        T data = get(0);
        return data;
    };

    T get_last()
    {
        get(size());
    };

    void remove(int n)
    {
        if (!head) {cout << no_list << endl; return;}

        else if (n >= size())
        {
            cout << "There is no node " << n << "." << endl;
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

template<class T> class stack
{
    private:
        linked_list<T> ll;

    public:
        void push(T d)
        {
            ll.add_first(d);
        }

        T top()
        {
            T tmp = 0;
            tmp = ll.get_first();
            return tmp;
        }

        T pop()
        {
            T tmp = top();
            ll.remove_first();
            return tmp;
        }

};


int main(void)
{
    stack<double> s;
    int n;
    string cmd;
    double d;

    while (cin >> cmd >> d)
    {
        cout << "MAIN: cmd = " << cmd << ", d = " << d << endl;

        if (cmd == "push")
            s.push(d);
        else if (cmd == "pop")
        {
            d = s.pop();
            cout << "MAIN: pop = " << d << endl;
        }
        else if (cmd == "top")
        {
            d = s.top();
            cout << "MAIN: top = " << d << endl;
        }
        else if (cmd == "quit")
            exit(0);
    }
}