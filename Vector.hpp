#include <iostream>
#include <stdexcept>
#include <iterator>
#include <cstdlib>
#include <exception>

using namespace std;
using namespace cop4530;

template <typename T>
Vector<T>::Vector() //default constructor
{
    theSize = 0;
    theCapacity = 0;
    array = nullptr;
}

template <typename T>
Vector<T>::Vector(const Vector &rhs) //copy constructor
{
    T* array = new T[theCapacity];
    for( int i = 0; i < theSize; ++i )
        array[i] = rhs.array[i];
}

template <typename T>
Vector<T>::Vector(Vector &&rhs) //move constructor
{
    T* newArr = new T[rhs.theCapacity];
    for(int i=0; i<rhs.theSize;++i)
        newArr[i] = rhs.array[i];
    theSize = rhs.theSize;
    theCapacity = rhs.theCapacity;
    array = newArr;
    delete [] rhs.array;
    rhs.array = nullptr;
    rhs.theSize = 0;
    rhs.theCapacity = 0;
}

template <typename T>
Vector<T>::Vector(int num, const T& val)//vector with num elements initialized with val
{
    theSize = num;
    theCapacity = num+5;
    T* newArr = new T[theCapacity];
    for(int i=0; i < num; i++)
        newArr[i] = val;
    array = newArr;
}

template <typename T>
Vector<T>::Vector(const_iterator start, const_iterator end) //constructor with elements from another vector between [start,end)
{
    int i=0;
    theSize = 0;
    theCapacity = 5;
    T theArr[10000];
    for(;start!=end; start++)
    {
        theArr[i] = *start;
        ++i;
        ++theSize;
    }
    cout << theSize;
    theCapacity = theSize + 5;
    cout << "you got here...";
    T* newArr = new T[theSize];
    for (int j =0; j< i; j++)
        newArr[j] = theArr[j];
    array = newArr;

}

template <typename T>
Vector<T>::~Vector()//destructor
{
    delete [] array;
}

template <typename T>
T& Vector<T>::operator[](int index)//index operator that returns reference to element at index
{
    try
    {
        return array[index];
    }
    catch(exception& ooR)
    {
        cout << ooR.what() << '\n';
    }
}
template <typename T>
const T& Vector<T>::operator[](int index) const//index operator that returns reference to element at index
{
    try
    {
        return array[index];
    }
    catch(exception& ooR)
    {
        cout << ooR.what() << '\n';
    }
}

template <typename T>
const T& Vector<T>::at(int loc ) const//const index operator
{
    try
    {
        return array[loc];
    }
    catch(exception& ooR)
    {
        cout << ooR.what() << '\n';
    }
}

template <typename T>
T& Vector<T>::front()//return reference to first element in vector
{
    return begin();
}

template <typename T>
const T& Vector<T>::front() const//const reference to first element
{
    return &begin();
}

template <typename T>
T &Vector<T>::back()//return reference to last element in vector
{
    return &end();
}

template <typename T>
const T& Vector<T>:: back() const//const reference to last element
{
    return &end();
}

template <typename T>
int Vector<T>::size() const//return number of elements in vector
{
    return theSize;
}

template <typename T>
int Vector<T>::capacity() const//return capacity of vector
{
    return theCapacity;
}

template <typename T>
bool Vector<T>::empty() const//return true if no elements present in vector
{
    if (theSize == 0)
        return true;
    else
        return false;
}

template <typename T>
void Vector<T>::clear()//deletes all elements in vector
{
    theSize = 0;
    theCapacity = 0;
    array = nullptr;
}

template <typename T>
void Vector<T>::push_back(const T & val)//inserts new object into last element in vector
{
    if(theSize == theCapacity)
        resize(theCapacity+5);
    array[theSize] = val;
    theSize++;
}

template <typename T>
void Vector<T>::pop_back()//delete last element in vector
{
    if(theSize == theCapacity)
        resize(theCapacity+5);
    resize(theSize-1);
    theSize--;
}

template <typename T>
void Vector<T>::resize(int num, T val)//change size of vector to newSize; if greater than theSize resize theCapacity, and new positions hold newValue
{
    if (num < theCapacity)
    {
        T* newArr = new T[num+5];
        for(int i=0; i<num; i++)
            newArr[i] = array[i];
        array = newArr;
        theCapacity = num + 5;
    }
    if (num >= theCapacity)
    {
        T* newArr = new T[num+5];
        for(int i=0; i<num; i++)
        {
            if (i<theSize)
                newArr[i] = array[i];
            if (i>theSize)
                newArr[i] = val;
        }
        array = newArr;
        theCapacity = num + 5;
    }
}
template <typename T>
void Vector<T>::reserve(int newCapacity)//change theCapacity to newCapacity only if newCapacity>theCapacity
{
    if (theCapacity < theCapacity)
    {
        T* newArr = new T[newCapacity];
        for(int i=0; i<theSize; i++)
            newArr[i] = array[i];
        array = newArr;
        theCapacity = newCapacity;
    }
    else
    {
        T* newArr = new T[newCapacity];
        for(int i=0; i<theSize; i++)
            newArr[i] = array[i];
        array = newArr;
        theCapacity = newCapacity;
    }
}
template <typename T>
void Vector<T>::print(std::ostream& os, char ofc) const//print all elements in vector, using ofc as delimiter
{
    for(int i=0; i < theSize; i++)
    {
        os << array[i];
        os << ofc;
    }
}

template <typename T>
bool operator==(const Vector<T> & lhs, const Vector<T> &rhs)//check if vectors are equal in both size, and in elements
{
    if (lhs.size() != rhs.size())
        return false;
    if (lhs.size() == rhs.size())
    {
        for (int i=0; i<lhs.size();i++)
        {
            if (lhs[i]!= rhs[i])
                return false;
        }
        return true;
    }
}

template <typename T>
bool operator!=(const Vector<T> & lhs, const Vector<T> &rhs)//check if vectors are not equal in both size, and elements
{
    if (lhs.theSize != rhs.theSize)
        return true;
    if (lhs.theSize == rhs.theSize)
    {
        for (int i=0; i<lhs.theSize;i++)
        {
            if (lhs.array[i]!=rhs.array[i])
                return true;
        }
        return false;
    }

}

template <typename T>
std::ostream & operator<<(std::ostream &os, const Vector<T> &v)//print all elements in vector by calling print function
{
    v.print(os, ' ');
    return os;
}
template <typename T>
T* Vector<T>::begin()
{
    return &array[0];
}
template <typename T>
const T* Vector<T>::begin() const
{
    return &array[0];
}
template <typename T>
T* Vector<T>::end()
{
    return &array[theSize];
}
template <typename T>
const T* Vector<T>::end() const
{
    return &array[theSize];
}
template <typename T>
T* Vector<T>::insert(iterator itr, const T& val)
{
    if(theSize == theCapacity)
        resize(theSize+5);
    for(iterator iter = itr + 1; iter != end();iter++)
    {
        iter.array = iter.array + 1;
    }
    itr.array = val;
    return itr.array;
}
template <typename T>
T* Vector<T>::erase(iterator itr)
{
    int k=0;
    for (int i=0; i < theSize; i++)
    {
        if (array[i] == itr)
            --i;
        array[i] = array [k];
        k++;
    }
    theSize--;
    resize(theSize);
    ++itr;
    return itr;
}
template <typename T>
T* Vector<T>::erase(iterator start, iterator end)
{
    int k = 0;
    for (int i = 0;i < theSize; i++)
    {
        for(start; start!=end ;start++)
        {
            --i;
            --theSize;
        }
        if(i>=0)
            array[i] = array[k];
        k++;
    }
    resize(theSize);
    ++end;
    return end;
}
