#include<iostream>
#include<memory>
using namespace std;

//Shared pointers 
/*template <class T>
class Shared {
	T* _addr;
	size_t* _count;
public:
	Shared() :_addr(nullptr), _count(nullptr) {}
	Shared(T* addr) :_addr(addr), _count(new size_t(1)) {}
	Shared(const Shared& other) :_addr(other._addr), _count(other._count) {
		(*_count)++;
	}
	Shared& operator=(const Shared& other) {
		if (_count != nullptr) {
			(*_count)--;
			if (*_count == 0)
			{
				delete _addr;
				delete _count;
			}
		}

		_count = other._count;
		_addr = other._addr;
		(*_count)++;
		return *this;
	}

	Shared& operator=(const T*& addr) {
		if (_count != nullptr) {
			(*_count)--;
			if (*_count == 0) {
				delete _addr;
				delete _count;
			}
		}

		_count = new size_t(1);
		_addr = addr;

		return *this;
	}

	T* get() const {
		return _addr;
	}
	T* operator->() const {
		return _addr;
	}
	T& operator*() const {
		return *_addr;
	}


	~Shared()
	{
		if (_count != nullptr) {
			(*_count)--;
			if (*_count == 0)
			{
				delete _addr;
				delete _count;
			}
		}
	}
};*/

//Unique pointers
/*template <class T>
class Unique {
	T* _addr;
	size_t* _count;
public:
	Unique() :_addr(nullptr), _count(nullptr) {}
	Unique(T* addr) :_addr(addr), _count(new size_t(1)) {}
	Unique(const Unique& other) :_addr(other._addr), _count(other._count) {
		(*_count)++;
	}
	Unique& operator=(const Unique& other) {
		if (_count != nullptr) {
			(*_count)--;
			if (*_count == 0)
			{
				delete _addr;
				delete _count;
			}
		}

		_count = other._count;
		_addr = other._addr;
		(*_count)++;
		return *this;
	}

	Unique& operator=(const T*& addr) {
		if (_count != nullptr) {
			(*_count)--;
			if (*_count == 0) {
				delete _addr;
				delete _count;
			}
		}

		_count = new size_t(1);
		_addr = addr;

		return *this;
	}

	T* get() const {
		return _addr;
	}
	T* operator->() const {
		return _addr;
	}
	T& operator*() const {
		return *_addr;
	}


	~Unique()
	{
		if (_count != nullptr) {
			(*_count)--;
			if (*_count == 0)
			{
				delete _addr;
				delete _count;
			}
		}
	}
};*/


class Rectangle {
	int length, breadth;
public:
	Rectangle(int l, int b) :length(l), breadth(b) {}
	int area() { return length * breadth; }
	~Rectangle() { cout << "Destructor" << endl; }
};

int main() {
	/*Shared<Rectangle> r1(new Rectangle(5, 10));
	Shared<Rectangle> r2(r1);
	cout << "Area r1: " << r1->area() << endl;
	cout << "Area r2: " << r2->area() << endl;*/

	/*Unique<Rectangle> r1(new Rectangle(5, 10));
	Unique<Rectangle> r2(r1);
	cout << "Area r1: " << r1->area() << endl;
	cout << "Area r2: " << r2->area() << endl;*/


	//WEAK Pointer - Bu pointerleri dangling pointer probleminin helli ucun istifade etmek olar.

	// OLD, problem with dangling pointer
	// PROBLEM: ref will point to undefined data!

	//int* ptr = new int(10);
	//int* ref = ptr;
	//delete ptr;

	// NEW
	// SOLUTION: pointerin esasligini yoxlamaq ucun istifade edirik: expired() or lock() 

	// bos shared ptr yaradirig
	shared_ptr<int> sptr;

	// sptr-e(shared ptr obyektine) yeni adres veririk ve deyeri 10 edirik
	sptr.reset(new int);
	*sptr = 10;

	// weak ptr obyekti yaradib, ona sptr-i(shared ptr obyektini) assign edirik
	weak_ptr<int> weak1 = sptr;

	// Sonra yeniden sptr-i(shared ptr obyektini) sifirlayib, yeni adres veririk ve deyeri 5 edirik
	sptr.reset(new int);
	*sptr = 5;

	// Yeni weak ptr obyekti yaradib, ona yuxardaki yeni deyer verilen sptr-i assign edirik
	weak_ptr<int> weak2 = sptr;

	// weak1 is expired!
	if (!weak1.expired()) { //bos olub olmadigni yoxlayir
		cout << "1 --> Data: " << *weak1.lock() << endl;
		cout << "1 --> Count: " << weak1.use_count() << endl;
	}
	else {
		cout << "1 --> weak1 is expired" << endl;
		cout << "1 --> Count: " << weak1.use_count() << endl;
	}
	// weak2 points to new data (5)
	if (!weak2.expired()) {
		cout << "2 --> Data: " << *weak2.lock() << endl;
		cout << "2 --> Count: " << weak2.use_count() << endl;
	}
	else {
		cout << "2 --> weak2 is expired" << endl;
		cout << "2 --> Count: " << weak2.use_count() << endl;
	}
	
}