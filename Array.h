#ifndef ARRAY_H
#define ARRAY_H
#include <iostream>
using namespace std;

template <class T>
class Array{
		template <class U>
		friend ostream &operator<< (ostream &, const Array<U> &);
		template <class U>
		friend istream &operator>> (istream &, Array<U> &);
		template <class GradeStruct>
		friend ostream &operator<< (ostream &, const Array<GradeStruct> &);
		friend class Student;
	public:
		Array( int = 10, T [] = NULL, string = NULL);
		~Array();
		void addSize();
		void subtractSize();
		int getSize() const;
		Array getObject();
        void printObject();
		void printGradeStruct();

		// subscript operator for non-const objects returns modifiable lvalue
		T &operator[]( int );

		// subscript operator for const objects returns rvalue
		T operator[]( int ) const;
        
        //change Item
        void changeProperty(T,int );
        
		//add a value to array
		void add(T );

		//remove a value from array
		void remove(int);
		
		//savedata in file
		void saveData(string);
	private:
		string ID;
		int size; // pointer-based array size
		T *ptr; // pointer to first element of pointer-based array
};
//	    void acivitiesShow();
//	    void subjectShow(int , string[]);

	
#endif