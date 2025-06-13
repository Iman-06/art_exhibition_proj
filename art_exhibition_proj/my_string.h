#ifndef MY_STRING_H
#define MY_STRING_H
#include <iostream>
using namespace std;
class MyString {
	char* str;
	int len;
	int cap;
	void strCopy(char*& dest, const char* src);
	void regrow();
	char* itos(int integer);
public:
	MyString();
	MyString& operator=(const MyString& s);
	bool operator==(const MyString& s) const;
	MyString(int integer);
	MyString(const char* s);
	int length(const char* s)const;
	MyString(int n, char* ch);
	MyString(const MyString& s);
	int stoi(const MyString s);
	char* return_array()const;
	void insert_at(int i, char ch);
	MyString replace_first(char c);
	void insert_at(int i, const MyString sub);
	MyString& trim();
	char& operator[](int i);
	const char& operator[](int i)const;
	MyString concat(const MyString& s2)const;
	MyString& append(const MyString& s2);
	MyString operator+=(const MyString& s);
	MyString operator+(const MyString& s) const;
	bool is_equal(const MyString& M);
	bool is_less(const MyString& M);
	bool is_greater(const MyString& M);
	MyString* split(char delim, int& count) const;
	MyString* tokenize(const char* delim, int& count) const;
	int find_first(char ch);
	int find_first(const MyString& string_found) const;
	int find_last(char ch);
	int find_last(const MyString& string_found) const;
	int* all_sub_strings(const MyString& substring, int& count)const;
	int* find_all(char ch, int& C);
	int* find_all(const MyString& substring, int& C) const;
	void remove_at(int i);
	void remove_first(char ch);
	void remove_last(char ch);
	void remove_all(char ch);
	void clear();
	void display()const;
	~MyString();
	void toUpper();
	friend MyString operator+(const char* lhs, const MyString& rhs);
	void toLower();
	friend ostream& operator<<(ostream& out, const MyString& s);
	friend istream& operator>>(istream& in, MyString& s) {
		char buffer[1024];
		in >> buffer;
		s = MyString(buffer);
		return in;
	}
};

#endif