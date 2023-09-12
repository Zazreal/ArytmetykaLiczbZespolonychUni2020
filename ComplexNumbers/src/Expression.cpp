#include "..\inc\Expression.hh"
#include <string>
#include <sstream>
#include <vector>
/*
 * Tu nalezy zdefiniowac funkcje, ktorych zapowiedzi znajduja sie
 * w pliku naglowkowym.
 */

std::ostream & operator<<(std::ostream & stream,const Operator & op)
{
	switch (op)
	{
	case Operator::kAddition: stream << " + "; break;
	case Operator::kSubtraction: stream << " - "; break;
	case Operator::kMultiplication: stream << " * "; break;
	case Operator::kDivision: stream << "/"; break;
	}
	return stream;
}

std::istream& operator>>(std::istream& stream, Operator& op)
{
	char x = ' ';
	stream >> x;
	switch (x)
	{
	case '+': op = Operator::kAddition; break;
	case '-': op = Operator::kSubtraction; break;
	case '*': op = Operator::kMultiplication; break;
	case '/': op = Operator::kDivision; break;
	}
	return stream;
}

std::ostream& operator<<(std::ostream& stream,const Expression& expr)
{
	stream << expr.arg1 << " " << expr.op << " " << expr.arg2;
	return stream;
}

//sad face
//chcialem tutaj znowu string parsing zrobic, ale zostalem od tego odwiedziony
std::istream& operator>>(std::istream& stream, Expression& expr)
{
	stream >> expr.arg1;
	stream >> expr.op;
	stream >> expr.arg2;
	return stream;
}

void Display(Expression& expr)
{
	std::cout << "Podaj Wynik operacji: ";
	std::cout << expr.arg1;
	std::cout << expr.op;
	std::cout << expr.arg2 << " = " << std::endl;
}

//Tutaj solve tylko bierze input, wiekszosc sie rozwiazuje w main, bo nie chcialem zmieniac return type Solve
//jesli mialo by liczyc ilosc odpowiedzy, to musial bym zwrocic struct
//poza tym, wolalbym zeby zwracalo bool wtedy zwracaloby czy odp byla poprawna czy nie
//bo jak ma zwracac complex to ja nie wiem.
Complex Solve()
{
	Complex input;
	std::cout << "Twoja odpowiedz: ";
	std::cin >> input;
	return input;
}
