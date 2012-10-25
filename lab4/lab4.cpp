#include <iostream>
#include <cstdlib>
#include <string>

using namespace std;

template<class T> class node
{
  public:
    node(T d) { next = NULL; data = d; }

    node *next, *prev;
    T data;
};


template<class T> class linked_list
{
  private:
    node<T> *head, *tail, *user;

    string no_list;

  public:

    linked_list()
    {
        head = NULL;
        tail = NULL;
        user = NULL;
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

        size = 1;
        node<T> *counter;
        counter = head;
        while (counter->next != NULL)
        {
            counter = counter->next;
            size++;
        }
        return size;
    };

    void add(int n, T d)
    {
        if (!head && n != 0) {cout << no_list << endl; return;}

        if (head && n == 0)
        {
            node<T> *tmp;
            tmp = head;
            head = new node<T>(d);
            head->next = tmp;
            tmp->prev = head;
            return;
        }

        else if (n == 0) 
        {
            head = new node<T>(d);
            tail = head;
            return;
        }

        else if (n == size())
        {
            node<T> *tmp;
            tmp = tail;
            tail = new node<T>(d);
            tmp->next = tail;
            tail->prev = tmp;
            return;
        }

        else if (n > (size()))
        {
            cout << "There is not a node " << n - 1 << " that would precede this." << endl;
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
                tmp2->prev = tmp3;
                tmp3->next = tmp2;
                tmp3->prev = tmp1;
                return;
            }

            else if (n == (size() - 1))
            {
                node<T> *tmp1, *tmp2;
                tmp2 = tail->prev;
                tmp1 = new node<T>(d);
                tmp1->next = tail;
                tail->prev = tmp1;
                tmp2->next = tmp1;
                tmp1->prev = tmp2;
                return;
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
            cout << "no node " << n << " exists" << endl;
            return -1;
        }

        node<T> *tmp;
        if (n == (size() - 1))  {return tail->data;}
        if (n == 0)   {return head->data;}
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
            cout << "There is no node " << n << "." << endl;
            return;
        }

        if (size() == 1)
        {
            delete(head);
            head = NULL;
            tail = NULL;
            return;
        }

        if (n == 0)
        {
            node<T> *tmp;
            tmp = head->next;
            if (head == user)
            {
                user = user->next;
            }
            delete(head);
            head = tmp;
            head->prev = NULL;
            return;
        }

        else if (n == size() - 1)
        {
            node<T> *tmp1, *tmp2;
            tmp1 = tail;
            if (tmp1 == user)
            {
                user = user->prev;
            }
            tmp2 = tail->prev;
            delete(tmp1);
            tail = tmp2;
            tail->next = NULL;
        }

        else
        {
            node<T> *tmp1, *tmp2, *tmp3;
            tmp2 = get_node(n);
            if (tmp2 == user)
            {
                user = user->next;
            }
            tmp1 = tmp2->prev;
            tmp3 = tmp2->next;
            delete(tmp2);
            tmp1->next = tmp3;
            tmp3->prev = tmp1;
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

    void reset_ptr()
    {
        if (!head)
        {
            cout << no_list << endl;
            return;
        }
        user = head;
    }

    void adv_ptr()
    {
        if (!head)
        {
            cout << no_list << endl;
            return;
        }

        if (tail == user)
        {
            cout << "You are already at the end of the list." << endl;
            return;
        }

        user = user->next;
    }

    void rew_ptr()
    {
        if (!head)
        {
            cout << no_list << endl;
            return;
        }

        if (head == user)
        {
            cout << "You are already at the head of the list." << endl;
            return;
        }

        user = user->prev;
    }

    int getup()
    {
        if (!head)
        {
            cout << no_list << endl;
            return -1;
        }
        return user->data;
    }

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

    bool test_tail(node<T> *tester)
    {
        bool result = false;
        if (&tester == &tail) 
        {
            result = true;
            return result;
        }
    }

    void dump()
    {
        node<T> *headptr, *tailptr;

        cout << "    DUMP: (size = " << size() << ", first = " << get_first() << ", last = " << get_last() << ")\n";

        if (head == NULL) {
            cout << "    DUMP: head = NULL\n\n";
            return;
        }

        headptr = head;
        tailptr = tail;

        cout << "    DUMP:   head = : " << headptr->data << "     tail = : "
             << tailptr->data << endl;
        while (headptr->next != NULL) 
        {
            headptr = headptr->next;
            tailptr = tailptr->prev;
            cout << "    DUMP:   data = : " << headptr->data 
                 << "     data = : " << tailptr->data << endl;
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
        } else if (cmd == "reset") { // set user ptr to head of list
            ll.reset_ptr();
        } else if (cmd == "adv") {  // advance user ptr to next node
            ll.adv_ptr();
        } else if (cmd == "rew") {  // rewind user ptr to pre node
            ll.rew_ptr();
        } else if (cmd == "getup") {  // return value at user ptr node
            int i = ll.getup();
            cout << "getup returns: " << i << endl;
        } else if (cmd == "dump")
            ll.dump();
        else if (cmd == "quit")
            exit(0);
    }
}