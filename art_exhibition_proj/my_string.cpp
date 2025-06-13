#include "my_string.h"
int MyString::length(const char* s)const {
	int i = 0;
	while (s[i] != '\0') {
		i++;
	}
	return i;
}
void MyString::strCopy(char*& dest, const char* src) {
	if (src == nullptr) {
		dest = new char[1];
		dest[0] = '\0';
		return;
	}
	int len = 0;
	while (src[len] != '\0') {
		++len;
	}

	dest = new char[len + 1];

	for (int i = 0; i < len; ++i) {
		dest[i] = src[i];
	}

	dest[len] = '\0';
}
void MyString::regrow() {
	cap *= 2;
	char* temp = new char[cap];
	strCopy(temp, str);
	delete[] str;
	str = temp;
}
char* MyString::itos(int integer) {
	MyString temp;
	temp.str = new char[cap];
	int count = 0;
	while (integer != 0) {
		int digit = integer % 10;
		integer /= 10;
		char ch = digit + 48;
		temp.insert_at(count, ch);
		count++;

	}
	temp.str[count] = '\0';
	char* string;
	string = new char[count + 1] {'\0'};
	strCopy(string, temp.str);
	return string;
}
MyString::MyString() :str(nullptr), len(0), cap(1) {
}
MyString& MyString:: operator=(const MyString& s) {
	if (this == &s) {
		return *this;
	}
	delete[] str;
	len = s.len;
	cap = s.cap;
	str = new char[cap];
	strCopy(str, s.str);
	return *this;
}
MyString::MyString(int integer) {
	cap = 1;
	len = 0;
	this->str = itos(integer);
	len = length(str);
	cap = len + 1;
}
MyString::MyString(const char* s) {
	len = length(s);
	cap = len + 1;
	str = new char[cap];
	strCopy(str, s);
}
MyString::MyString(int n, char* ch) {
	len = n;
	cap = len + 1;
	str = new char[cap];
	strCopy(str, ch);
}
MyString::MyString(const MyString& s) {
	len = s.len;
	cap = s.cap;
	str = new char[cap];
	strCopy(str, s.str);
}
int MyString::stoi(const MyString s) {
	for (int i = 0; i < s.len; i++) {
		if (s.str[i] < 48 || s.str[i] > 57) {
			cout << "Invalid input" << endl;
			return -1;
		}
	}
	int integer = 0;
	for (int i = 0; i < s.len; i++) {
		integer = integer * 10 + (s.str[i] - 48);
	}
	return integer;
}
void MyString::insert_at(int i, char ch) {
	if (i < 0 || i > len) {
		cout << "Invalid index" << endl;
		return;
	}
	if (len == cap - 1) {
		cap *= 2;
		char* temp = new char[cap];
		for (int j = 0; j < i; j++) {
			temp[j] = str[j];
		}
		temp[i] = ch;
		for (int j = i; j < len; j++) {
			temp[j + 1] = str[j];
		}
		temp[len + 1] = '\0';
		delete[] str;
		str = temp;
		temp = nullptr;
		len++;
	}
	else {
		for (int j = len; j > i; j--) {
			str[j] = str[j - 1];
		}
		str[i] = ch;
		len++;
	}
}
bool MyString::operator==(const MyString& s) const {
	if (len != s.len) {
		return false;
	}
	for (int i = 0; i < len; i++) {
		if (str[i] != s.str[i]) {
			return false;
		}
	}
	return true;
}
MyString MyString::operator+ (const MyString& s) const {
	MyString newStr;
	newStr.len = len + s.len;
	newStr.cap = newStr.len + 1;
	newStr.str = new char[newStr.cap];
	for (int i = 0; i < len; i++) {
		newStr.str[i] = str[i];
	}
	for (int i = 0; i < s.len; i++) {
		newStr.str[len + i] = s.str[i];
	}
	newStr.str[newStr.len] = '\0';
	return newStr;

}
MyString operator+(const char* lhs, const MyString& rhs) {
	MyString temp(lhs); 
	return temp + rhs; 
}
MyString MyString::replace_first(char c) {
	str[0] = c;
	return *this;
}
void MyString::insert_at(int i, const MyString sub) {
	if (i < 0 || i > len) {
		cout << "Invalid index" << endl;
		return;
	}
	if (len + sub.len >= cap - 1) {
		cap = len + sub.len + 1;
		char* temp = new char[cap];
		for (int j = 0; j < i; j++) {
			temp[j] = str[j];
		}
		for (int j = 0; j < sub.len; j++) {
			temp[i + j] = sub.str[j];
		}
		for (int j = i; j < len; j++) {
			temp[j + sub.len] = str[j];
		}
		temp[len + sub.len] = '\0';
		delete[] str;
		str = temp;
		len += sub.len;
	}
	else {
		for (int j = len; j >= i; j--) {
			str[j + sub.len] = str[j];
		}
		for (int j = 0; j < sub.len; j++) {
			str[i + j] = sub.str[j];
		}
		len += sub.len;
	}

}
MyString& MyString::trim() {
	int j = 0;
	for (int i = 0; i < len; i++) {
		if (int(str[i]) > 32) {
			str[j] = str[i];
			j++;
		}
	}
	str[j] = '\0';
	len = j;
	return *this;
}
char& MyString:: operator[](int i)
{
	return this->str[i];
}
char* MyString::return_array()const {
	return str;
}
const char& MyString:: operator[](int i)const {
	return str[i];
}
MyString MyString::concat(const MyString& s2)const {
	MyString newStr;
	newStr.len = len + s2.len;
	newStr.cap = newStr.len + 1;
	newStr.str = new char[newStr.cap];
	for (int i = 0; i < len; i++) {
		newStr.str[i] = str[i];
	}
	for (int i = 0; i < s2.len; i++) {
		newStr.str[len + i] = s2.str[i];
	}
	newStr.str[newStr.len] = '\0';
	return newStr;

}
MyString& MyString::append(const MyString& s2) {
	int Newlen = len + s2.len;
	if (Newlen >= cap) {
		cap = Newlen + 1;
		char* temp = new char[cap];
		for (int i = 0; i < len; i++) {
			temp[i] = str[i];
		}
		for (int i = 0; i < s2.len; i++) {
			temp[len + i] = s2.str[i];
		}
		temp[Newlen] = '\0';
		delete[] str;
		str = temp;
		len = Newlen;
		return *this;
	}
	else {
		for (int i = 0; i < s2.len; i++) {
			str[len + i] = s2.str[i];
		}
		str[Newlen] = '\0';
		len = Newlen;
	}
}
// MyString operator+(const MyString& s) {
// //call concat
// return concat(s);

//}
MyString MyString::operator+=(const MyString& s) {
	//call append
	return append(s);
}

bool MyString::is_equal(const MyString& M) {
	if (len != M.len) {
		return false;
	}
	for (int i = 0; i < len; i++) {
		if (str[i] != M.str[i]) {
			return false;
		}
	}
	return true;
}
bool MyString::is_less(const MyString& M) {
	int minLen = 0;
	if (len < M.len) {
		minLen = len;
	}
	else {
		minLen = M.len;
	}
	for (int i = 0; i < minLen; i++) {
		if (str[i] < M.str[i])
			return true;
		else if (str[i] > M.str[i])
			return false;
	}
	return len < M.len;
}
bool MyString::is_greater(const MyString& M) {
	int minLen = 0;
	if (len < M.len) {
		minLen = len;
	}
	else {
		minLen = M.len;
	}
	for (int i = 0; i < minLen; i++) {
		if (str[i] > M.str[i])
			return true;
		else if (str[i] < M.str[i])
			return false;
	}
	return len > M.len;
}
MyString* MyString::split(char delim, int& count) const {
	count = 0;
	for (int i = 0; i < len; i++) {
		if (str[i] == delim) {
			count++;
		}
	}
	count++;
	MyString* result = new MyString[count];
	int index = 0;
	int start = 0;
	for (int i = 0; i <= len; i++) {
		if (i == len || str[i] == delim) {
			int length = i - start;
			result[index].str = new char[length + 1];
			for (int j = 0; j < length; j++) {
				result[index].str[j] = str[start + j];
			}
			result[index].str[length] = '\0';
			result[index].len = length;
			result[index].cap = length + 1;
			index++;
			start = i + 1;
		}
	}
	return result;
}
MyString* MyString::tokenize(const char* delim, int& count) const {
	count = 0;
	for (int i = 0; i < len; i++) {
		for (int j = 0; j < length(delim); j++) {
			if (str[i] == delim[j]) {
				count++;
				break;
			}
		}
	}
	count++;
	MyString* result = new MyString[count];
	int index = 0;
	int start = 0;
	for (int i = 0; i <= len; i++) {
		bool isDelim = false;
		for (int j = 0; j < length(delim); j++) {
			if (i == len || str[i] == delim[j]) {
				isDelim = true;
				break;
			}
		}
		if (isDelim) {
			int length = i - start;
			result[index].str = new char[length + 1];
			for (int j = 0; j < length; j++) {
				result[index].str[j] = str[start + j];
			}
			result[index].str[length] = '\0';
			result[index].len = length;
			result[index].cap = length + 1;
			index++;
			start = i + 1;
		}
	}
	return result;
}
int MyString::find_first(char ch) {
	for (int i = 0; i < len; i++) {
		if (str[i] == ch) {
			return i;
		}
	}
	return -1;
}
int MyString::find_first(const MyString& string_found) const {
	for (int i = 0; i < len; i++) {
		if (str[i] == string_found.str[0]) {
			bool isSub = true;
			for (int j = 0; j < string_found.len; j++) {
				if (str[i + j] != string_found.str[j]) {
					isSub = false;
					break;
				}
			}
			if (isSub) {
				return i;
			}
		}
	}
	return -1;
}
int MyString::find_last(char ch) {
	for (int i = len - 1; i >= 0; i--) {
		if (str[i] == ch) {
			return i;
		}
	}
	return -1;
}
int MyString::find_last(const MyString& string_found) const {
	for (int i = len - 1; i >= 0; i--) {
		if (str[i] == string_found.str[0]) {
			bool isSub = true;
			for (int j = 0; j < string_found.len; j++) {
				if (str[i + j] != string_found.str[j]) {
					isSub = false;
					break;
				}
			}
			if (isSub) {
				return i;
			}
		}
	}
	return -1;
}
int* MyString::all_sub_strings(const MyString& substring, int& count)const {
	count = 0;
	for (int i = 0; i < len; i++) {
		if (str[i] == substring.str[0]) {
			bool isSub = true;
			for (int j = 0; j < substring.len; j++) {
				if (str[i + j] != substring.str[j]) {
					isSub = false;
					break;
				}
			}
			if (isSub) {
				count++;
			}
		}
	}
	int* indexes = new int[count];
	int index = 0;
	for (int i = 0; i < len; i++) {
		if (str[i] == substring.str[0]) {
			bool isSub = true;
			for (int j = 0; j < substring.len; j++) {
				if (str[i + j] != substring.str[j]) {
					isSub = false;
					break;
				}
			}
			if (isSub) {
				indexes[index] = i;
				index++;
			}
		}
	}
	return indexes;
}
int* MyString::find_all(char ch, int& C) {
	C = 0;
	for (int i = 0; i < len; i++) {
		if (str[i] == ch) {
			C++;
		}
	}
	int* indexes = new int[C];
	int index = 0;
	for (int i = 0; i < len; i++) {
		if (str[i] == ch) {
			indexes[index] = i;
			index++;
		}
	}
	return indexes;

}
int* MyString::find_all(const MyString& substring, int& C) const {
	int* indexes = substring.all_sub_strings(substring, C);
	return indexes;
}
void MyString::remove_at(int i) {
	if (i < 0 || i >= len) {
		cout << "Invalid index" << endl;
		return;
	}
	for (int j = i; j < len - 1; j++) {
		str[j] = str[j + 1];
	}
	len--;
}
void MyString::remove_first(char ch) {
	// use find first
	int index = find_first(ch);
	if (index != -1) {
		remove_at(index);
	}
}

void MyString::remove_last(char ch) {
	int index = find_last(ch);
	if (index != -1) {
		remove_at(index);
	}
}
void MyString::remove_all(char ch) {
	int* indexes = find_all(ch, len);
	for (int i = 0; i < len; i++) {
		remove_at(indexes[i]);
	}
}
void MyString::clear() {
	delete[] str;
	str = new char[1];
	str[0] = '\0';
	len = 0;
	cap = 1;
}
void MyString::display()const {
	for (int i = 0; i < len; i++) {
		cout << str[i];
	}
	cout << endl;
}

MyString:: ~MyString() {
	delete[] str;
	str = nullptr;
	len = 0;
	cap = 1;
}
void MyString::toUpper() {
	for (int i = 0; i < len; i++) {
		if (str[i] >= 97 && str[i] <= 122) {
			str[i] -= 32;
		}
	}
}
void MyString::toLower() {
	for (int i = 0; i < len; i++) {
		if (str[i] >= 65 && str[i] <= 90) {
			str[i] += 32;
		}
	}
}
ostream& operator<<(ostream& out, const MyString& s) {
	out << s.str;
	return out;
}
//static MyString trim(const MyString& s) {
// MyString temp = s;
// temp.trim();
// return temp;
//
//}
//MyString operator+(MyString s1, MyString s2) {
// return s1.concat(s2);
//}