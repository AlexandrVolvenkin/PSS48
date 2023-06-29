#include <iostream>

using namespace std;

template<class T>
class Node
{
public:
    T value;
    Node<T> *next;

    Node();

    explicit Node(T val);
};

template<class T>
Node<T>::Node()
{
    next = nullptr;
}

template<class T>
Node<T>::Node(T val)
{
    value = val;
    next = nullptr;
}


template<class E>
class LinkedList
{

private:
    Node<E> *head;
    int s;

public:

    const static int SORT_ASC = 0;
    const static int SORT_DESC = 1;

    LinkedList();

    /**
     * Appends the specified element to the end of this list.
     *
     * @param e - the element to add
     */
    void add(E e);

    /**
     * Inserts the specified element at the specified position in this list.
     * Shifts the element currently at that position (if any) and any subsequent
     * elements to the right (adds one to their indices).
     *
     * @param index index at which the specified element is to be inserted
     * @param e  element to be inserted
     */
    void add(int index, E e);

    /**
     * Inserts the specified element at the beginning of this list.
     *
     * @param e  the element to add
     */
    void addFirst(E e);

    /**
     * Appends the specified element to the end of this list.
     *
     * @param e the element to add
     */
    void addLast(E e);

    /**
     * Removes the first occurrence of the specified element from this list, if it is present.
     * If this list does not contain the element, it is unchanged.
     *
     * @param e
     */
    void remove(E e);

    /**
     * Removes and returns the first element from this list.
     */
    void removeFirst();

    /**
     * Removes and returns the last element from this list.
     */
    void removeLast();

    /**
     * Returns the number of elements in this list.
     *
     * @return the number of elements in this list
     */
    int size();

    /**
     * Returns true if this list contains the specified element.
     *
     * @param e element whose presence in this list is to be tested
     * @return <b>true</b> if this list contains the specified element
     */
    bool contains(E e);

    /**
     * Reverse the whole list
     */
    void reverse();

    /**
     * Sort the list by the given order
     *
     * @param order the order to sort the list
     */
    void sort(int order);

    /**
     * Displays the whole list
     */
    void print();

    /**
     * Removes all of the elements from this list and free the allocated memory.
     */
    void clear();
};

template<class E>
LinkedList<E>::LinkedList()
{
    head = nullptr;
    s = 0;
}

template<class E>
void LinkedList<E>::addFirst(E e)
{
    auto *newNode = new Node<E>(e);
    if (head == nullptr)
    {
        head = newNode;
    }
    else
    {
        newNode->next = head;
        head = newNode;
    }

    s++;
}

template<class E>
void LinkedList<E>::add(E e)
{

    auto *newNode = new Node<E>(e);
    if (head == nullptr)
    {
        head = newNode;
        s++;
        return;
    }

    Node<E> *current = head;
    Node<E> *tmp;

    do
    {
        tmp = current;
        current = current->next;
    }
    while (current != nullptr);


    tmp->next = newNode;

    s++;
}

template<class E>
void LinkedList<E>::remove(E e)
{

    Node<E> *current = head;
    Node<E> *prev = nullptr;
    bool found = false;

    if (current == nullptr)
    {
        cerr << "Err: can't perform remove() on an empty list" << endl;
        return;
    }

    do
    {
        if (current->value == e)
        {
            found = true;
            break;
        }

        prev = current;
        current = current->next;
    }
    while (current != nullptr);

    if (!found)
    {
        cerr << "Err: no element found with value " << e << endl;
        return;
    }

    // if the first element
    if (current == head)
    {
        prev = head;
        head = current->next;
        delete prev;
        return;
    }

    // if the last element
    if (current->next == nullptr)
    {
        prev->next = nullptr;
        delete current;
        return;
    }

    prev->next = current->next;
    delete current;

    s--;
}

template<class E>
void LinkedList<E>::removeFirst()
{
    Node<E> *tmp = head;

    if (tmp == nullptr)
    {
        cerr << "Err: can't perform removeFirst() on an empty list" << endl;
        return;
    }

    head = tmp->next;
    delete tmp;

    s--;
}

template<class E>
void LinkedList<E>::removeLast()
{
    Node<E> *current = head;
    Node<E> *prev = nullptr;

    if (current == nullptr)
    {
        cerr << "Err: can't perform removeLast() on an empty list" << endl;
        return;
    }

    do
    {
        prev = current;
        current = current->next;
    }
    while (current->next != nullptr);


    if (current->next == nullptr)
    {
        prev->next = nullptr;
        delete current;
        s--;
        return;
    }

}

template<class E>
void LinkedList<E>::reverse()
{

    Node<E> *current = head;
    Node<E> *newNext = nullptr;
    Node<E> *tmp;

    if (current == nullptr)
    {
        cerr << "Err: can't perform reverse() on an empty list" << endl;
        return;
    }

    do
    {
        tmp = current->next;
        current->next = newNext;
        newNext = current;
        current = tmp;
    }
    while (current != nullptr);

    head = newNext;
}

template<class E>
void LinkedList<E>::sort(int order)
{

    Node<E> *tmpPtr = head;
    Node<E> *tmpNxt = nullptr;

    if (tmpPtr == nullptr)
    {
        cerr << "Err: can't perform sort() on an empty list" << endl;
        return;
    }

    tmpNxt = head->next;

    E tmp;

    while (tmpNxt != nullptr)
    {
        while (tmpNxt != tmpPtr)
        {
            if (order == SORT_ASC)
            {
                if (tmpNxt->value < tmpPtr->value)
                {
                    tmp = tmpPtr->value;
                    tmpPtr->value = tmpNxt->value;
                    tmpNxt->value = tmp;
                }
            }
            else if (order == SORT_DESC)
            {
                if (tmpNxt->value > tmpPtr->value)
                {
                    tmp = tmpPtr->value;
                    tmpPtr->value = tmpNxt->value;
                    tmpNxt->value = tmp;
                }
            }
            else
            {
                cerr << "Err: invalid sort order '" << order << "'" << endl;
                return;
            }
            tmpPtr = tmpPtr->next;
        }
        tmpPtr = head;
        tmpNxt = tmpNxt->next;
    }
}

template<class E>
void LinkedList<E>::print()
{

    Node<E> *current = head;

    cout << "Size:" << s << " -> [ ";
    while (current != nullptr)
    {
        cout << current->value << " ";
        current = current->next;
    }
    cout << "] " << endl;
}

template<class E>
void LinkedList<E>::clear()
{

    Node<E> *current = head;

    do
    {
        Node<E> *tmp = current;
        current = current->next;
        delete tmp;
    }
    while (current != nullptr);

    head = nullptr;

    s = 0;
}

template<class E>
int LinkedList<E>::size()
{
    return s;
}

template<class E>
void LinkedList<E>::addLast(E e)
{
    add(e);
}

template<class E>
void LinkedList<E>::add(int index, E e)
{

    if (index < 0 || index > s)
    {
        char buff[32];
        snprintf(buff, sizeof(buff), "Index: %d, Size: %d", index, s);
        throw std::out_of_range(buff);
    }

    if (index == 0)
    {
        addFirst(e);
        return;
    }

    if (index == s)
    {
        addLast(e);
        return;
    }

    Node<E> *current = head;
    auto *newNode = new Node<E>(e);

    int i = 0;
    do
    {
        if (i++ == index)
        {
            break;
        }
        current = current->next;
    }
    while (current != nullptr);

    newNode->next = current->next;
    current->next = newNode;

    s++;

}

template<class E>
bool LinkedList<E>::contains(E e)
{
    Node<E> *current = head;

    while (current != nullptr)
    {
        if (current->value == e)
        {
            return true;
        }
        current = current->next;
    }
    return false;
}


//int main()
//{
//    LinkedList<int> ll {};
//
//
//    ll.add(20);
//    ll.add(10);
//    ll.add(50);
//    ll.add(40);
//    ll.add(70);
//    ll.add(60);
//    ll.add(80);
//
//    ll.addFirst(15);
//    ll.add(90);
//    ll.add(2, 0);
//    ll.add(5, 30);
//    ll.addLast(100);
//
//    ll.print();
//
//    cout << endl << "LinkedList#remove(60)" << endl;
//    ll.remove(60);
//    ll.print();
//
//    cout << endl << "LinkedList#reverse()" << endl;
//    ll.reverse();
//    ll.print();
//
//    cout << endl << "LinkedList#sort(LinkedList<E>::SORT_DESC)" << endl;
//    ll.sort(LinkedList<int>::SORT_DESC);
//    ll.print();
//
//    cout << endl << "LinkedList#sort(LinkedList<E>::SORT_ASC)" << endl;
//    ll.sort(LinkedList<int>::SORT_ASC);
//    ll.print();
//
//    cout << endl << "LinkedList#removeFirst()" << endl;
//    ll.removeFirst();
//    ll.print();
//
//    cout << endl << "LinkedList#removeLast()" << endl;
//    ll.removeLast();
//    ll.print();
//
//    cout << endl << "LinkedList#removeFirst()\nLinkedList#removeLast()" << endl;
//    ll.removeFirst();
//    ll.removeLast();
//    ll.print();
//
//    ll.clear();
//
//    return 0;
//}
