/*
 * MyList done by F1403022 5140309523 zhanglei.
 * All right running on dev-c.
 */
#include<iostream>
using namespace std;

template <class T> class MyList;
template <class T1> MyList <T1> operator + (const MyList<T1> &l1, const MyList<T1> &l2);// Merge two MyLists and return this new one.  
template <class T1> MyList <T1> operator + (const MyList<T1> &l1, const T1 &item);// Append an item to a MyList to and return this new MyList.
template <class T1> ostream & operator<< (ostream &os, const MyList <T1> &obj);//  Overload the output function.

template <class T>
class MyList{
    friend MyList operator + <>(const MyList<T> &l1, const MyList <T> &l2);
    friend MyList operator + <>(const MyList <T> &l1, const T &item); 
    friend ostream & operator<< <> (ostream &os, const MyList <T> &obj);

private:
	T *a;
	int size=100;
	int ind=-1;
	// When the space is not enough, double the size.
	void double_space();
	// Divide function, serves for quicksort function.
	int divid(T arr[], int low, int hig);
    // Quicksort the array.
    int quicksort(T arr[],int low,int hig);
public:
	// Default initialization.
	MyList();
	// Initialize MyList with 'num' items.
	MyList(int num,const T &item);
	// Copy a MyList by deep assignment.
	MyList(const MyList &l);
	// Initialize a MyList with the first len number item of the MyList. 
    MyList(T* arr, int len);
    // Append the item to current MyList.
	void push(const T &item);
	// Delete the last item and return its value.
	T pop();
	// Insert an item by calling index.
	void insert(int index, const T &item);
	// Refresh the MyList.
	void clean();
	// Return the size.
	int get_size() const;
	/* Delete the items with indexes from 'start' to 'end';
	   'start' and 'end' are included.
	   Minus index are supported.
	*/
	void erase(int start, int end);
	// Get the item by calling index.
	T get_item(int index);
	/* Return a MyList contains elements from 'start' index to 'end' index.
	   Minus numbers are also supported.
	   'Start' element and 'end' element are included. 
	*/ 
	MyList get_item(int start, int end);
	// Return the number of the elements that has the same value as item.
	int count(const T &item);
	//Remove the first element in MyList that is equal to specified item.
	void remove(const T &item);
	//Assign a MyList to another. 
	MyList &operator = (const MyList &l);
	//Append an item to the specified MyList.
	MyList &operator += (const T &item);
	//Append a MyList to the specified MyList.
	MyList &operator += (const MyList &l);
	// Get an item by index.
	T &operator [](int index);
	//Sort the MyList in the case that operator '<' and '>' are supported in that data type.
	void sort(bool less);
    // Reverse the MyList.
	void reverse();
	
	~MyList(){delete [] a;}
};

template <class T>
void MyList <T> ::double_space()
	{
	    if (ind==size-1){
            T *b;
            size*=2;
            b= new T [size];
            for (int i=0;i<size/2;++i){
                b[i]=a[i];
            }
            ind=size/2-1;
            delete [] a;
            a = b;
	    }
	};
template <class T>
int MyList <T> ::divid(T arr[], int low, int hig)
{
	T tem=arr[low];
     while (low!=hig){
        while (low<hig&&tem<=arr[hig]){
            --hig;
        }
        if (low<hig){
            arr[low]=arr[hig];
            ++low;
        }
        while (low<hig&&tem>=arr[low]){
            ++low;
        }
        if (low<hig){
            arr[hig]=arr[low];
            --hig;
        }
    }
    arr[low]=tem;
    return low;
}
template <class T>
// Quicksort the array.
int MyList <T> ::quicksort(T arr[],int low,int hig)
{
    int mid;
    if (low>=hig) return 0;
    mid=divid(arr,low,hig);
    quicksort(arr,low,mid-1);
    quicksort(arr,mid+1,hig);
}
template <class T>
// Default initialization.
MyList <T> ::MyList()
{
	a = new T [size];
}
template <class T>
MyList <T>::MyList(int num,const T &item)
{
    try
    {
        if (num<=0) throw 0;
        a = new T [size];
        for (int i=0;i<num;++i){
            push(item);
            double_space();
	    }
	}
	catch (int)
	{
	    cout<<"Number of items can not be less than 1!";
	    exit(-1);
	}
}
template <class T>
MyList <T>::MyList(const MyList &l)
{
    int len=l.get_size();
    a= new T [size];
    for (int i=0;i<len;++i){
        a[i]=l.a[i];
        ind++;
        double_space();
	}
};
template <class T>
MyList <T> ::MyList(T* arr, int len)
{
	a= new T [size];
	for (int i=0;i<len;++i){
        a[i]=arr[i];
        ind++;
        double_space();
	}
};
template <class T>
void MyList <T>::push(const T &item)
{
    ind++;
    double_space();
	a[ind]=item;
};
template <class T>
T MyList <T>::pop()
{
	try{
		if (get_size()<=0) throw 0;
		T tem=a[ind];
	    ind--;
	    return tem;
	}
	catch (int)
	{
	    cout<<"Cannot pop a empty MyList!";
	    exit(-1);
	}
};
template <class T>
void MyList <T>::insert(int index, const T &item)
{
	int ten=index;
	try{
	    if (ten>get_size()-1||ten<-get_size()) throw 0;
	    if (ten<0){
			ten+=get_size();
	    }
	    T tmp=a[ten],tep;
	    a[ten]=item;
	    for (int i=ten+1;i<=ind;++i){
            tep=a[i];
            a[i]=tmp;
            tmp=tep;
	    }
	    double_space();
        a[ind+1]=tmp;
        ind++;
		}
	catch (int){
		cout<<"Wrong index!";
		exit(-1);
	}
};
template <class T>
void MyList <T>::clean()
{
	delete [] a;
	a = new T [size];
	ind=-1;
};
template <class T>
int MyList <T>::get_size() const
{
	return ind+1;
};
template <class T>
void MyList <T>::erase(int start, int end)
{
	try
	{
        int sta=start,en=end;
        if (sta>get_size()-1||en>get_size()-1||sta<-get_size()||end<-get_size()){
          	throw 0;
		}
        if (sta<0){
            sta+=get_size();
        }
        if (en<0){
            en+=get_size();
        }
        MyList <T> tmp;
        if (sta>en)  throw 0.5;
        for (int i=0;i<sta;++i){
            tmp.push(a[i]);
        }
        for (int i=en+1;i<get_size();++i){
            tmp.push(a[i]);
        }
        this->clean();
        *this=tmp;
	}
	catch (int)
	{
		cout<<"Index out of range!";
		exit(0);
	}
	catch (double)
	{
		cout<<"Start index greater than end index!";
		exit(-1);
	}
};
template <class T>
T MyList <T>::get_item(int index)
{
	try
	{
		int i=index;
		if (i>get_size()-1||i<-get_size())
		{
			throw 0;
		}
	    if (i<0){
            i+=get_size();
        }
	    return a[i];
	}
	catch (int)
	{
		cout<<"Index out of range!";
		exit(-1);
	}
};
template <class T>
MyList <T> MyList<T>::get_item(int start, int end)
{
	try
	{
        int sta=start,en=end;
        if (sta>get_size()-1||en>get_size()-1||sta<-get_size()||end<-get_size()){
         	throw 0;
		}            
        if (sta<0){
            sta+=get_size();
        }
        if (en<0){
            en+=get_size();
        }
	    MyList <T> tmp;
	    if (sta>en){
            return tmp;
	    }
	    for (int i=0;i<en-sta+1;++i){
            tmp.push(a[sta+i]);
            tmp.double_space();
	    }
	    return tmp;	
	}
	catch (int)
	{
		cout<<"index out of range!";
		exit(0);
	}		 
};
template <class T>
int MyList <T>::count(const T &item)
{
	int cnt=0;
	for (int i=0;i<=ind;++i){
        if (a[i]-item<0.00000001&&item-a[i]>-0.00000001){
            cnt++;
        }
	}
	return cnt;
};
template <class T>
void MyList <T>::remove(const T &item)
{
    for (int i=0;i<=ind;++i){
        if (a[i]==item){
            this->erase(i,i);
            break;
        }
	}
};
template <class T>
MyList<T> & MyList <T>::operator = (const MyList &l)
{
	clean();
	for (int i=0;i<l.get_size();++i){
        // cout<<ind<<" "<<"= "<<l.a[i]<<endl;
        double_space();
        push(l.a[i]);
	}
};
template <class T>
MyList<T> & MyList <T>::operator += (const T &item)
{
    double_space();
    push(item);
};
template <class T>
MyList<T> &MyList <T>::operator += (const MyList &l)
{
	for (int i=0;i<l.get_size();++i){
        double_space();
        push(l.a[i]);
	}
};	
template <class T>
T & MyList<T>::operator [](int index)
{
	try
	{
		int i=index;
		if (i>get_size()-1||i<-get_size())
		{
			throw 0;
		}
	    if (i<0){
            i+=get_size();
	    }
	    return a[i];			
	}
	catch (int)
	{
		cout<<"index out of range!";
		exit(-1);
	}		
};
template <class T>
void MyList<T>::sort(bool less=true)
{
	try
	{
		if (get_size()<1) throw 0;
    	quicksort(a,0,ind);
	    if (!less){
            reverse();
	    }
	}
	catch (int)
	{
		cout<<"Error: Cannot sort an empty MyList!";
		exit(-1);
	}
}
template <class T>
void MyList<T>::reverse()
{
	MyList <T> tmp;
	int len=get_size();
	for (int i=0;i<len;++i){
        tmp.push(a[len-i-1]);
        tmp.double_space();
	}
	for (int i=0;i<len;++i){
        a[i]=tmp[i];
	}
};
template <class T>
ostream & operator<<(ostream &os, const MyList <T> &obj)
{
    if (obj.get_size()==0) os<<"[]"<<endl;
    else {
        os<<"[";
        for (int i=0;i<(obj.get_size()-1);++i){
             os<<obj.a[i]<<", ";
        }
        os<<obj.a[obj.get_size()-1]<<"]"<<endl;
        }
        return os;
}
template <class T>
MyList <T> operator + (const MyList<T> &l1, const MyList <T> &l2)
{
    MyList <T> tmp;
    for (int i=0;i<l1.get_size();++i){
        tmp.double_space();
        tmp.push(l1.a[i]);
    }
    for (int i=0;i<l2.get_size();++i){
        tmp.double_space();
        tmp.push(l2.a[i]);
    }
    return tmp;
}
template <class T>
MyList <T> operator + (const MyList <T> &l1, const T &item)
{
    MyList <T> tmp(l1);
    tmp.double_space();
    tmp.push(item);
    return tmp;
}
int main() 
{
	
}

