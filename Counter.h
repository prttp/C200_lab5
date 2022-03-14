#pragma once
#include <iostream>
class Counter {
	friend class MyString;
	Counter* pNext;
	char* m_pStr;
	size_t m_nOwners;
	static Counter Head;
	static size_t m_curCounters;
	Counter(const char* str);
	Counter();
	~Counter();
	
	static Counter* FindAndAdd(const char* str);
	void FindAndDestroy();

};
class MyString {
	Counter* m_pMyCounter;
public:
	MyString(const char* str);
	~MyString();
	MyString(const MyString& str);
	MyString(MyString&& source);
	MyString& operator=(MyString&& other);
	MyString& operator=(const MyString& other);
	MyString& operator=(const char* text);
	static void PrintAll();
	static void ChngReg();
	static void PrintAllByAlph();
};