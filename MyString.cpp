#define _CRT_SECURE_NO_WARNINGS
#include "MyString.h"
#include <iostream>
#include <string>
#include <iomanip>



MyString::MyString() : str_(nullptr), size_(0), capacity_(0) {};

MyString::MyString(const char* mass) : MyString(mass, strlen(mass))
{};

MyString::MyString(std::string string) : size_(string.size()), capacity_(size_ + 1)
{
	this->str_ = new char[capacity_];
	for (int i = 0; i < this->size_; i++)
		this->str_[i] = string[i];
	this->str_[capacity_ - 1] = '\0';
};

MyString::MyString(const char* mass, int count) : size_(count), capacity_(count + 1)
{
	if (!size_){
		this->capacity_ = 0;
		this->str_ = nullptr;
	}
	else{
		this->str_ = new char[capacity_];
		strcpy_(this->str_, mass, count);
	}
};

MyString::MyString(int count, char word) : size_(count), capacity_(size_ + 1)
{
	this->str_ = new char[capacity_];
	for (int i = 0; i < this->size_; i++)
		this->str_[i] = word;
	this->str_[capacity_ - 1] = '\0';
};

MyString::~MyString()
{
	this->size_ = this->capacity_ = 0;
	delete[] this->str_;
}

int MyString::capacity() { return this->capacity_; };

int  MyString::size() { return this->size_; };

int  MyString::length() { return this->size_; };

bool MyString::empty() { return (this->size_ == 0 ? true : false); };

char& MyString::operator[](int index)
{
	return this->str_[index];
};

MyString MyString::operator + (MyString& String)
{
	MyString temp;
	temp.size_ = this->size_ + String.size_;
	temp.capacity_ = temp.size_ + 1;
	temp.str_ = new char[temp.capacity_];
	strcpy_(temp.str_, this->str_);
	for (int i = 0; i < temp.size_; i++)
		temp.str_[this->size_ + i] = String.str_[i];
	temp.str_[temp.size_] = '\0';
	return temp;
};

MyString MyString::operator + (std::string string)
{
	MyString temp(string);
	return this->operator + (temp);
};

MyString MyString::operator + (const char* mass)
{
	MyString temp(mass);
	return this->operator + (temp);
};

void MyString::operator += (MyString& String)
{
	char* buffer = new char[this->capacity_];
	strcpy_(buffer, this->str_);
	this->size_ += String.size_;
	this->capacity_ = this->size_ + 1;
	delete[] this->str_;
	this->str_ = new char[this->capacity_];
	strcpy_(this->str_, buffer);
	for (int i = 0; i < String.size_; i++)
		this->str_[strlen(buffer) + i] = String.str_[i];
	this->str_[this->size_] = '\0';
	delete[] buffer;
};

void MyString::operator += (std::string string)
{
	MyString temp(string);
	this->operator += (temp);
};
void MyString::operator += (const char* mass)
{
	MyString temp(mass);
	this->operator += (temp);
};

void MyString::operator = (MyString& String)
{
	if (this->str_)
		delete[] this->str_;
	this->size_ = String.size_;
	this->capacity_ = String.capacity_;
	this->str_ = new char[this->capacity_];
	strcpy_(this->str_, String.str_);
};

void MyString::operator = (std::string string)
{
	MyString temp(string);
	this->operator = (temp);
};

void MyString::operator = (const char* mass)
{
	MyString temp(mass);
	this->operator = (temp);
};

void MyString::operator = (const char word)
{
	if (this->str_)
		delete[] this->str_;
	this->size_ = 1;
	this->capacity_ = 2;
	this->str_ = new char[this->capacity_];
	this->str_[0] = word;
	this->str_[1] = '\0';
};

bool MyString::operator == (MyString& String)
{
	if (this->size_ != String.size_)
		return false;
	for (int i = 0; i < this->size_; i++)
	{
		if (this->str_[i] == String.str_[i])
			continue;
		return false;
	}
	return true;
};

bool MyString::operator > (MyString& String)
{
	int length = (this->size_ > String.size_) ? String.size_ : this->size_;
	for (int i = 0; i < length; i++)
	{
		if (this->str_[i] > String.str_[i])
			return true;
		if (this->str_[i] < String.str_[i])
			return false;
	}
	return false;
};

bool MyString::operator < (MyString& String)
{
	return !(*this >= String);
};

bool MyString::operator >= (MyString& String)
{
	return ((*this > String) || (*this == String));
};

bool MyString::operator <= (MyString& String)
{
	return ((*this < String) || (*this == String));
}

bool MyString::operator != (MyString& String)
{
	return !(*this == String);
}

char* MyString::c_str()
{
	char* buffer = new char[this->capacity_];
	strcpy_(buffer, this->str_);
	return buffer;
}
char* MyString::data()
{
	return this->c_str();
}

void MyString::erase(int index, int count)
{
	for (int i = index; i < index + count; i++)
		this->str_[i] = this->str_[i + count];
	this->size_ -= count;
}

void MyString::clear()
{
	delete[] this->str_;
	this->capacity_ = this->size_ = 0;
	this->str_ = nullptr;
}

void MyString::shrink_to_fit()
{
	char* buffer = new char[this->capacity_];
	strcpy_(buffer, this->str_, this->size_ + 1);
	delete[] this->str_;
	this->capacity_ = this->size_ + 1;
	this->str_ = new char[this->capacity_];
	strcpy_(this->str_, buffer);
	delete[] buffer;
}

int MyString::find(const char* mass, int index)
{
	for (int i = index; i < this->size_; i++)
	{
		if (find_str(mass, (this->str_ + i)))
			return i;
	}
	return -1;
}

int MyString::find(std::string string, int index)
{
	MyString temp(string);
	return this->find(temp.str_,index);
}

void MyString::append(const char* mass, int index, int count)
{
	count = (count == -1) ? strlen(mass) : count;
	if (this->capacity_)
	{
		char* buffer = new char[this->capacity_];
		strcpy_(buffer, this->str_);
		delete[] this->str_;
		this->str_ = new char[capacity_ + count];
		strcpy_(this->str_, buffer);
	}
	else
	{
		this->str_ = new char[count + 1];
	}
	strcpy_(this->str_ + this->size_, mass + index, count);
	this->size_ = strlen(this->str_);
	this->capacity_ = this->size_ + 1;
}

void MyString::append(std::string string, int index, int count)
{
	MyString temp(string);
	this->append(temp.str_, index, count);
}

void MyString::append(int count, char word)
{
	MyString temp(count, word);
	this->append(temp.str_);
}

char* MyString::substr(int index, int count)
{
	char* buffer = new char[this->size_ - index + 1];
	count = (count == -1) ? (this->size_ - index) : count;
	strcpy_(buffer, this->str_ + index, count);
	return buffer;
}

void MyString::insert(int index, const char* mass, int count)
{
	count = (count == -1) ? strlen(mass) : count;
	char* buffer = new char[this->capacity_];
	strcpy_(buffer, this->str_);
	delete[] this->str_;
	this->str_ = new char[this->capacity_ + count];
	this->size_ += count;
	this->capacity_ += count;
	strcpy_(this->str_, buffer, index);
	strcpy_(this->str_ + index, mass, count);
	strcpy_(this->str_ + index + count, buffer + index);
	delete[] buffer;
}

void MyString::insert(int index, int count, char word)
{
	MyString temp(count, word);
	this->insert(index, temp.str_, count);
}

void MyString::insert(int index, std::string string, int count)
{
	MyString temp(string);
	this->insert(index, temp.str_, count);
}

void MyString::replace(int index, int count, const char* mass)
{
	this->erase(index, count);
	this->insert(index, mass);
}

void MyString::replace(int index, int count, std::string string)
{
	this->erase(index, count);
	this->insert(index, string);
}

std::ostream& operator<< (std::ostream& out, const MyString& str)
{
	if (str.str_ != nullptr)
		return (out << str.str_);
	else
		return out << "";
}


int main()
{
	MyString a2 = "hello amazing world";
	std::string s1 = "wonderful";
	a2.replace(6, 7, s1);
	std::cout << a2 << std::endl;


	//std::string a, b;
	//a = "aBc";
	//b = "abce";
	//std::cout << a << "  " << b << "\n"
	//	<< std::setw(4) << "== " << (a == b) << "\n"		// 0 or 1
	//	<< std::setw(4) << "!= " << (a != b) << "\n"
	//	<< std::setw(4) << "> " << (a > b) << "\n"
	//	<< std::setw(4) << ">= " << (a >= b) << "\n"
	//	<< std::setw(4) << "< " << (a < b) << "\n"
	//	<< std::setw(4) << "<= " << (a <= b) << "\n";

	//MyString a1, b1;
	//a1 = "aBc";
	//b1 = "abce";
	//std::cout << a << "  " << b << "\n"
	//	<< std::setw(4) << "== " << (a1 == b1) << "\n"		// 0 or 1
	//	<< std::setw(4) << "!= " << (a1 != b1) << "\n"
	//	<< std::setw(4) << "> " << (a1 > b1) << "\n"
	//	<< std::setw(4) << ">= " << (a1 >= b1) << "\n"
	//	<< std::setw(4) << "< " << (a1 < b1) << "\n"
	//	<< std::setw(4) << "<= " << (a1 <= b1) << "\n";
}