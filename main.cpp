#include <iostream>
#include <iomanip>
#include <cstdlib>
#include "Array.h"
#include<fstream>
using namespace std;

const int personFileName_Size = 3;

//cac file thong tin ca nhan
const string personInfoFileName[ personFileName_Size ] = {"./infoData/info1.txt", "./infoData/info2.txt", "./infoData/info3.txt"};
const int personalInfoNumber = 7; // so thong tin (property) moi ca nhan + 2(username, password) + 1( ID )

//cac file luu cac mon hoc
const string subjectList[personFileName_Size] = {"./subjectData/subjects1.txt", "./subjectData/subjects2.txt", "./subjectData/subjects3.txt"};

template<class T>
void Array<T>::addSize(){
	this->size+=1;
}

template<class T>
void Array<T>::subtractSize(){
	this->size-=1;
}

template <class T>
Array<T>::Array( int arraySize, T input[], string identifyNumber) {
	this->ID = identifyNumber;
	size = ( arraySize > 0 ? arraySize :10 );
	ptr = new T[size];  //create space  for pointer-based array
	for( int i = 0; i < size; i++) {
		ptr[i] = input[i] ;     //set pointer-based array element
	};
};

template <class T>
Array<T>::~Array() {
	delete [] ptr;
};

template <class T>
int Array<T>::getSize() const {
	return size; // number of elements in Array
};
//in ra kq
template<class T>
void Array<T>::printObject() {
	for(int i =0; i < size; i++){
		cout<<i+1<<"   "<<ptr[i]<<endl;
	}
}


// overloaded input operator for class Array;
// inputs values for entire Array
template <class T>
istream &operator>> ( istream &input, Array<T> &a ) {
	for ( int i = 0; i < a.size; i++ ) {
		input >> a.ptr[ i ];
	};
	return input;
}

// overloaded output operator for class Array
template <class T>
ostream &operator<< ( ostream &output, const Array<T> &a ) {
	int i;

	for ( int i = 0; i < a.size; i++ ) {
		output << a.ptr[ i ]<<endl;
	};
	return output;
}


// subscript operator for non-const objects returns modifiable lvalue
template<class T>
T &Array<T>::operator[]( int subscript ) {
	// check for subscript out-of-range error
	if ( subscript < 0 || subscript >= size ) {
		cerr << "\nError: Subscript " << subscript<< " out of range" << endl;
		exit(1);
	}
	return ptr[ subscript ]; // reference return
};

// subscript operator for const objects returns rvalue
template<class T>
T Array<T>::operator[]( int subscript ) const {
	// check for subscript out-of-range error
	if ( subscript < 0 || subscript >= size ) {
		cerr << "\nError: Subscript " << subscript<< " out of range" << endl;
		exit(1);
	};
	return ptr[ subscript ]; // returns copy of this element
};

//ham thay doi mot phan tu cua mang
template<class T>
void Array<T>:: changeProperty(T input,int index){
	ptr[index] = input;
}

//ham them mot phan tu vao danh sach mang
template<class T>
void Array<T>:: add(T input) {
	T *ptrCopyArray = new T[size]; //cap phat mot mang moi de gan
	for(int i = 0; i < size; i++ ) {
		ptrCopyArray[i] = ptr[i];  //copy gia tri cua mang cu vao mang gan
	};
	delete[] ptr;    //xoa mang cu
	size += 1;       //tang so phan tu
	ptr = new T [size];  //tao mang moi
	for(int i = 0; i < size - 1; i++ ) {
		ptr[i] = ptrCopyArray[i];  // copy lai cac gia tri tu mang gan vao mang moi
	};
	ptr[size-1] = input;   // them phan tu

	delete[] ptrCopyArray;  //giai phong bo nho, xoa mang gan
	ptrCopyArray = NULL;
}

//xoa mot phan tu thu k cua mang
template<class T>
void Array<T>:: remove(int index) {
	if(index < size) {
		int count = 0;
		T *ptrCopyArray = new T[size-1];
		// sap xep lai mang
		for(int i = index; i < size - 1; i++ ) {
			ptr[i] = ptr[i+1];
		}
		//gan gia tri mang cu cho mang gan
		for(int i = 0; i < size - 1; i++ ) {
			ptrCopyArray[i] = ptr[i];
		};
		size = size - 1;
		delete[] ptr;  //xoa mang cu
		ptr = new T[size];  //tao mang moi voi size -1
		//gan lai gia tri tu mang gan vao mang moi
		for(int i = 0; i < size; i++ ) {
			ptr[i] = ptrCopyArray[i];
		};

		delete[] ptrCopyArray;
		ptrCopyArray = NULL;
	}
}

template<class T>
void Array<T>:: saveData(string fileName){
	ofstream output;
	output.open(fileName, ios::out);
	if(output.is_open()) {
		output<<ID<<"\n"<<size<<endl;
		for(int i =0 ; i < size; i++ ){
			output<<ptr[i]<<endl;
		}
	} else {
		cout<<" Luu that bai! ";
	}
	output.close();
}

template <class GradeStruct>
void Array<GradeStruct>::printGradeStruct() {
	for(int i = 0; i < size ; i++) {
		cout<<ptr[i].subject<<"   "<<ptr[i].grade<<endl;
	};

};

// ham luu thong tin nguoi dung vao file du lieu
void savePersonalData( string fileName,string ID,string username, string password, string name, string studentID, string major, string university) {
	ofstream output;
	output.open(fileName, ios::out);
	if(output.is_open()) {
		output<< ID <<"\n"<<username << "\n" <<password << "\n" <<name
		      << "\n" <<studentID << "\n" <<major << "\n" <<university<<endl;
	} else {
		cout<<" Luu that bai! ";
	}
	output.close();
}

//in ra info nguoi dung
void printUserInfo(string name, string studentID, string major, string university) {
	cout<<endl;
	cout<<"---Thong tin sinh vien---"<<endl;
	cout<<" ten: "<<name<<",  MSSV: "<<studentID
	    <<"\n Nganh: "<<major
	    <<"\n Truong: "<<university<<endl;
};

//Ham thay doi thong tin hoc sinh
void userInfoShow(string infoFileName) {

	string ID, username, password, name, studentID, major, university;

	//lay thong tin tu file du lieu
	ifstream fileInput;
	fileInput.open(infoFileName,ios::in);

	string *ptr = new string [personalInfoNumber];
	if(fileInput.is_open()) {
		for(int j = 0; j < personalInfoNumber; j++) {
			string subj;                //bien trung gian
			getline(fileInput, subj);      // gan 3 bien dau tien trong file du lieu
			ptr[j] = subj;
		};
		ID = ptr[0];
		username = ptr[1];
		password = ptr[2];
		name     = ptr[3];
		studentID = ptr[4];
		major     = ptr[5];
		university= ptr[6];

	} else {
		cout<<"Loi truy cap thong tin nguoi dung"<<endl;
	};
	delete[] ptr;
	ptr = NULL;
	fileInput.close();

	printUserInfo(name, studentID,major,university);

	cout<<"\n--- Ban co muon thay doi thong tin ?---"<<endl;
	cout<<"An [1] de thay doi ten\n"
	    <<"An [2] de thay doi MSSV\n"
	    <<"An [3] de thay doi nganh\n"
	    <<"An [4] de thay doi truong\n"
	    <<endl;

	int choice;
	cout<<"Lua chon cua ban la:";
	cin>>choice;
	string *inputValue = new string[1] ;   // cap phat bien nhap vao
	cout<<"Thong tin moi duoc sua thanh:"<<endl;
	fflush(stdin);
	getline(cin,inputValue[0]);
	switch(choice) {
		//thay doi ten
		case 1:

			name = inputValue[0];  // gan gia tri da nhap vao thong tin nguoi dung
			cout<<"Ten da duoc sua thanh: "<<name<<endl;
			break;
		case 2:
//			cout<<"Thong tin moi duoc sua thanh:"<<endl;
//			getline(cin,inputValue[0]);
			studentID = inputValue[0]; // gan gia tri da nhap vao thong tin nguoi dung
			cout<<"MSSV da duoc sua thanh: "<<studentID<<endl;
			break;
		case 3:
//			cout<<"Thong tin moi duoc sua thanh:"<<endl;
//			getline(cin,inputValue[0]);
			major = inputValue[0]; // gan gia tri da nhap vao thong tin nguoi dung
			cout<<"Nganh da duoc sua thanh: "<<major<<endl;
			break;
		case 4:
//			cout<<"Thong tin moi duoc sua thanh:"<<endl;
//			getline(cin,inputValue[0]);
			university = inputValue[0]; // gan gia tri da nhap vao thong tin nguoi dung
			cout<<"Truong da duoc sua thanh: "<<university<<endl;
			break;
		default:
			break;
	}
	delete[]inputValue;   // xoa bien khoi tao, giai phong bo nho
	inputValue = NULL;

	//luu thong tin moi vao file du lieu
	savePersonalData(infoFileName,ID,username, password, name, studentID, major, university);

	system("cls");
	cout<<"thong tin moi la:"<<endl;
	printUserInfo(name, studentID, major, university);



};


//chuc nang hien thi mon hoc, them sua xoa
//trong file du lieu mon hoc, dong dau tien la ID, dong thu 2 la so mon hoc
// tu dong thu 3 la cac mon can hoc
void subjectListShow( string ID) {
    
	string fileName;  // ten file mon can truy cap 
    int subjectsNumber; // so mon hoc cua doi tuong
    
    //lay ra file mon hoc can truy cap tuong ung 
    string *ptr = new string [2];
	for(int i = 0; i < personFileName_Size; i++ ) {
		ifstream fileInput;
		fileInput.open(subjectList[i],ios::in);

		if(fileInput.is_open()) {
			for(int j = 0; j < 2; j++) {
				string subj;                //bien trung gian
				getline(fileInput, subj);      // gan 2 bien dau tien trong file mon hoc
				ptr[j] = subj;                // bien dau ptr[0] - id, bien so 2 ptr[1] - so mon hoc
			};
            if( ptr[0] == ID){
            	fileName = subjectList[i];
            	subjectsNumber = atol(ptr[1].c_str());
            	break;
			}
		} else {
			cout<<"Loi truy cap thong tin nguoi dung"<<endl;
		};
		
		fileInput.close();
	}
    delete[] ptr;
	ptr = NULL;
    
    //lay ra du lieu cua file
    const int filePropertyNumber = subjectsNumber + 2; // so phan tu cua file = so mon + 1(ID) + 1(bien chi so mon)
    //mo file
    ifstream fileSubject;
	fileSubject.open(fileName,ios::in);
	if(fileSubject.is_open()) {
		
		//khoi tao mang ptr[2] de luu tru cac dong cua file, bao gom ca ID va cac mon hoc
		string *ptr2 = new string [filePropertyNumber];
		for(int j = 0; j < filePropertyNumber; j++) {
			string subj;                //bien trung gian
			getline(fileSubject, subj);      // trong ptr2[] bao gom bien so 1 - ID, bien so 2 - so mon hoc,
			ptr2[j] = subj;                // tu ptr2[2] tro di la cac mon
		};
        
        //gan cac mon hoc vao mot mang duoc cap phat
        string *subjectsPtr = new string [subjectsNumber];
        for( int i = 2; i < filePropertyNumber;i++ ){
        	subjectsPtr[i-2] = ptr2[i];
		}
        //xoa mang luu cac dong cua file
        delete[] ptr2;
	    ptr2 = NULL;
	    
	    //hien thi cac mon hoc, them, sua ,xoa
	    int subjectChoice;
	    Array<string> subjectsShow(subjectsNumber, subjectsPtr, ID);
	    
	    //in ra cac mon hoc
	    cout<<"\ndanh sach cac mon hoc:"<<endl;
	    subjectsShow.printObject();
	    
	    cout<<"\nban co muon thay doi mon hoc nao khong ?"<<endl;
	    cout<<" them [1] | sua [2] | xoa [3]"<<endl;
	    cout<<"\nlua chon cua ban la:";
	    cin>>subjectChoice;
	    
	    string *changedSubject = new string[1];
	    switch(subjectChoice){
	    	// them mon hoc
	    	case 1:
	    		cout<<"mon hoc ban muon them la"<<endl;
	    		fflush(stdin);
	    		getline(cin,changedSubject[0]);       // nhap mon hoc
	    		subjectsShow.add(changedSubject[0]);  //them mon hoc
	    		break;
	    	
	    	// sua mon hoc
	    	case 2:
	    		int changeSubjectIndex;
	    		cout<<"mon hoc ban muon sua la (an so thu tu mon ban muon sua) :";
	    		cin>>changeSubjectIndex;           //nhap stt mon muon sua
	    		cout<<"mon hoc moi la:";
	    		fflush(stdin);     
	    		getline(cin,changedSubject[0]);     //nhap noi dung mon can sua
	    		subjectsShow.changeProperty(changedSubject[0],changeSubjectIndex - 1);
	    		break;
	    	
	    	//xoa mon hoc
	    	case 3:

	    		int removeSubjectIndex;
	    		cout<<"mon hoc ban muon xoa la (an so thu tu mon ban muon xoa) :";
	    		cin>>removeSubjectIndex;           //nhap stt mon muon xoa
	    		subjectsShow.remove(removeSubjectIndex-1);
	    		break;
	    	default:
	    		cout<<"khong co lua chon nay"<<endl;
	    		break;
		}
	    delete[]changedSubject;
	    system("cls");
	    cout<< "danh sach mon moi la:"<<endl;
	    subjectsShow.printObject();
	    subjectsShow.saveData(fileName);
	    
	    // xoa mang luu cac mon 
	    delete[] subjectsPtr;
	    subjectsPtr = NULL;
	    
	    fileSubject.close();
	} else {
		cout<<"Loi truy cap thong tin nguoi dung"<<endl;
		
	};
}

void gradeShow(){
}

void menu(string ID, string infoFileName) {
	int choice;
	cout<<endl;
	cout<<"            --- MENU---"<<endl;
	cout<<"Hien thi thong tin nguoi dung             "<<"[1]"<<endl;
	cout<<"Hien thi danh sach mon dang ki            "<<"[2]"<<endl;
	cout<<"Hien thi danh sach bang diem hoc tap      "<<"[3]"<<endl;
	cout<<"Hien thi danh sach bang diem ren luyen    "<<"[4]"<<endl;
	cout<<"Thoat chuong trinh                        "<<"[5]"<<endl;
	cout<<"  (an phuong an de chon)"<<endl;
	cout<<"lua chon cua ban:";
	cin>>choice;
	switch(choice) {

		//chuc nang hien thi thong tin nguoi dung
		case 1:
			userInfoShow(infoFileName);
			menu(ID, infoFileName);

		//chuc nang hien thi mon hoc dang ki, them, xoa, sua
		case 2:
			subjectListShow(ID);
            menu(ID, infoFileName);
		//chuc nang hien thi bang diem
		case 3:
			gradeShow();

		case 5:
			exit(0);
		default:
			cout<<"Loi, khong co phuong an nay!";
			menu(ID, infoFileName);
	}

}


int main() {

	string ID;  // id tung hoc sinh khac nhau
	string infoFileName;  //bien - file chua thong tin ca nhan
	string usernameInput,passwordInput;
	bool isLoggedInSucessfully; //bien kiem tra dang nhap thanh cong

	//chuc nang dang nhap
	cout<<"--- Dang nhap ---"<<endl;
	do {
		isLoggedInSucessfully = false;

		cout<<"username:";
		cin>>usernameInput;
		cout<<"password:";
		cin>>passwordInput;


		string *ptr = new string[3];
		//duyet qua cac mang tim username v pass phu hop
		ifstream input;
		for(int i = 0; i < personFileName_Size; i++ ) {
			input.open(personInfoFileName[i], ios::in);
			if( input.is_open()) {
				for(int j = 0; j < 3; j++) {
					string subj;                  //bien trung gian
					getline(input, subj);      // gan 3 bien dau tien trong file du lieu
					ptr[j] = subj;             // bien dau - ID, bien so 2 - username. bien so 3 - password
				};

				if(usernameInput == ptr[1] && passwordInput == ptr[2] ) {
					isLoggedInSucessfully = true;
					ID = ptr[0];           // gan value co ID
					infoFileName = personInfoFileName[i];
					cout<<isLoggedInSucessfully;
					break;  //ket thuc duyet file
				};
			}
//			else {
//				cout<<"Khong mo duoc file"<<endl;
//			}

			input.close();
		}

		if(!isLoggedInSucessfully) {
			cout<<"Loi ! vui long nhap lai"<<endl;
		}

		delete[] ptr;
		ptr= NULL;
	} while (!isLoggedInSucessfully);

	system("cls");
	cout<<" ---Dang nhap thanh cong--- "<<endl;
	menu(ID, infoFileName);
//    string s1[3] = {"mon hoc so 1","mon hoc so 2","mon hoc so 3"};
//	Array<string> s(3,s1,"10");
//	s.printObject();
//	cout<<"sau do"<<endl;
//	s.changeProperty(1);
//	s.printObject();
	return 0;
}

