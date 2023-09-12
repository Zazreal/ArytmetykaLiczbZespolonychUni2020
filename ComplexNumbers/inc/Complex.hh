#pragma once
#include <iostream>

struct Complex
{
	double re = 0; /*! Pole repezentuje czesc rzeczywista. */
	double im = 0; /*! Pole repezentuje czesc urojona. */
	Complex();
	Complex(double x,double y);
	~Complex();
	Complex operator+(Complex& other);
	Complex operator-(Complex& other);
	Complex operator*(Complex& other);
	Complex operator/(Complex& other);
	Complex operator!(); //sprzezenie
	bool operator==(Complex& other);
	Complex operator*=(Complex& other);
	Complex operator-=(Complex& other);
	Complex operator=(std::string& str); //nie dokonczone
};

double Arg(Complex& z);
std::istream& operator>>(std::istream& strea, Complex& com);
std::ostream& operator<<(std::ostream& stream,const Complex& com);
//funkcja pokazujaca pobieranie complex bez string parsingu
void InputComplex(Complex& com);


//atan2 look up == arctg