#define	  stop __asm nop
#include "Counter.h"
int main() {
	MyString b = "bbb";
	MyString a = "aaa";
	MyString o ="one";
	MyString t ="two";
	MyString th = "three";
	MyString f = "four";
	MyString ff = "four";
	MyString::PrintAll();
	MyString::ChngReg();
	MyString::PrintAll();
	MyString::PrintAllByAlph();
}