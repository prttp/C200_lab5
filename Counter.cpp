#include "Counter.h"
#include<cstring>

Counter Counter::Head;
size_t Counter::m_curCounters = 0;
Counter::Counter() {
	pNext = nullptr;
	m_pStr = nullptr;
	m_nOwners = 0;
	}
Counter::Counter(const char* str){
	pNext = Head.pNext;
	m_pStr = new char[strlen(str)+1];
	strcpy(m_pStr, str);
	m_nOwners = 1;
	Head.pNext = this;
	m_curCounters++;
	}
Counter::~Counter() {
	//Counter* p = &Head;
	//do { p = p->pNext; } while (p->pNext != this);
	//p->pNext = pNext;
	delete[] m_pStr;
	m_curCounters--;
	}

MyString::MyString(const char* str) {
	m_pMyCounter = Counter::FindAndAdd(str);
}
MyString::~MyString() {
	m_pMyCounter->FindAndDestroy();
}
Counter* Counter::FindAndAdd(const char* str) {
	Counter* p = &Head;
	while (p->pNext != 0) {
		if (p->m_pStr != nullptr) {
			if (strcmp(p->m_pStr, str) == 0)
			{
				p->m_nOwners++; return p;
			}
		}
		p = p->pNext;
	}
	
	return new Counter(str);
};
void Counter::FindAndDestroy() {
	m_nOwners--;
	if (m_nOwners == 0) { delete this; }
	};
MyString::MyString(const MyString& source) {
	m_pMyCounter = source.m_pMyCounter;
	m_pMyCounter->m_nOwners++;
	};
MyString::MyString(MyString&& source)
{
	m_pMyCounter = source.m_pMyCounter;
	source.m_pMyCounter = nullptr;
};

MyString& MyString::operator=(MyString&& other) {
	m_pMyCounter = other.m_pMyCounter;
	other.m_pMyCounter = nullptr;
	return *this;
};
MyString& MyString::operator=(const MyString& other) {
	m_pMyCounter = other.m_pMyCounter;
	m_pMyCounter->m_nOwners++;
	return *this;
};
MyString& MyString::operator=(const char* text) {
	m_pMyCounter = Counter::FindAndAdd(text);
	return *this;
};
void MyString::PrintAll() {
	Counter* p = &Counter::Head;
	while (p != 0) {
		if (p->m_pStr != nullptr) { std::cout << p->m_pStr << ", "; };
		p = p->pNext;
	};
	std::cout << std::endl;
}
void MyString::ChngReg()
{
	Counter* p = Counter::Head.pNext;
	while (p != 0) {
		int i = 0;
		while (p->m_pStr[i] != '\0') {
			if ((p->m_pStr[i] > 64) && (p->m_pStr[i] < 91)) { p->m_pStr[i] = p->m_pStr[i] + 32; };
			if ((p->m_pStr[i] > 96) && (p->m_pStr[i] < 123)) { p->m_pStr[i] = p->m_pStr[i] - 32; };
			i++;
		}
		p = p->pNext;
	};
}
void MyString::PrintAllByAlph() {
	if (Counter::m_curCounters != 0) {
		for (int i = 0; i < Counter::m_curCounters; i++) {
			Counter* prev = &Counter::Head;
			Counter* p = Counter::Head.pNext;
				while (p->pNext != 0) {
					if (strcmp(p->m_pStr, p->pNext->m_pStr) > 0) {
						Counter* tmp = p;
						p=p->pNext;
						Counter* tmp1 = p->pNext;
						p->pNext = tmp;
						p->pNext->pNext = tmp1;
						prev->pNext = p;
						continue;
					}
					
					prev = p;
					p = p->pNext;
				}
				}
			PrintAll();
	};

}
