class mergesort
{
  private:
    void dump(int ar[], int len)
    {
        cout<<"      DUMP:   data = : "<< ar[i] << endl;
    }

  public:
    void sort(int a[], int n)
    {
        if the list0 has fewer than two items:  return

        copy first half of list0 to list1

        copy second half of list0 to list2

        if list1 has more than one element
            call sort with list1
        if list2 has more than one element
            call sort with list2

        (merge list1 and list2 into list0)
        while there are items in both lists:
             compare first items from two lists
             put smaller one in combined list

        copy remaining items of longer list to combined list
    }
};
