#include <iostream>
#include <cstring>
#include <cassert>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
#include "..\inc\Database.hh"

using namespace std;

//HEAVY WORK IN PROGRESS
//I MEAN IT
//napisalem to hmmm... w przyplywie pasji???? nie wiem, ale jest to pewnie super nie zoptymalizowane
//jesli wogole dziala
//pomijajac to ze chyba 3 razy zmnienialem zdanie jak to mam napisac
//ta funkcja ma czytac z pliku, ale nie jak w C tylko C++
//i ten template jest chyba strasznie glupi i zupelnie niepotrzebny
std::vector<Expression>& FileReading(std::string filename)
{
	std::vector<Expression> vec(5);
	std::vector<std::string> strvec(3);
	std::string tempstr = "";
	std::string tempstr2 = "";
	std::stringstream ss(tempstr);
	Expression exp;
	std::ifstream FFile;
	char separator = ' ';
	try {
		if(FFile.is_open() == false)
		FFile.open("..\\" + filename + ".dat", ios_base::in);
	}catch (std::exception& e) { std::cerr << e.what() << std::endl; }
	while (std::getline(FFile, tempstr))
	{
		FFile >> tempstr;
		while (std::getline(ss, tempstr2, separator))
		{
			strvec.emplace_back(tempstr2);
		}
		//exp = { strvec[0],strvec[1],strvec[2] }; //ta czesc nie dziala bo brak mi operatorow
		//string to complex juz praktycznie mam, ale string to enum operator jest problematyczne
		vec.emplace_back(exp);
		vec.clear();
	}
	return vec;
}

static Expression easy_test[] = //== Expression easy_test[4] == ...
    {
        {{2, 1}, kAddition, {1, 2}},
        {{1, 0}, kSubtraction, {0, 1}},
        {{3, 0}, kMultiplication, {0, 3}},
        {{4, 8}, kDivision, {1, 0}},
};
static Expression Hard_Test[]=
{
	{{43.54 , 97.64}, kMultiplication, {86.12, 34.91}},
	{{934.324, 532.43}, kDivision, {846.67, 94.25}}
};

/*
 * W bazie testu ustawia wybrany test jako biezacy test i indeks pytania
 * ustawia na pierwsze z nich.
 * Parametry:
 *    database_ptr        - wskaznik na zmienna reprezentujaca baze testu,
 *    test_array_ptr      - wskaznik na tablice zawierajaca wyrazenia arytmetyczne
 *                          bedace przedmiotem testu,
 *    number_of_questions - ilosc pytan w tablicy.
 *   
 * Warunki wstepne:
 *      - Parametr database_ptr nie moze byc pustym wskaznikiem. Musi zawierac adres
 *        zmiennej reprezentujacej baze testu, ktora wczesniej zostal poprawnie
 *        zainicjalizowany poprzez wywolanie funkcji Init.
 *      - Parametr test_array_ptr zawiera wskaznik na istniejaca tablice.
 *      - Parametr number_of_questions zawiera wartosc, ktora nie przekracza ilosci elementow
 *        w tablicy dostepnej poprzez test_array_ptr.
 */
void SetTest(Database *database_ptr, Expression *test_array_ptr, unsigned int number_of_questions)
{
    database_ptr->test_array_ptr = test_array_ptr;
    database_ptr->number_of_questions = number_of_questions;
    database_ptr->question_index = 0;
}

/*
 * Inicjalizuje test kojarzac zmienna dostepna poprzez wskaznik database_ptr
 * z dana tablica wyrazen, ktora reprezentuje jeden z dwoch dopuszczalnych 
 * testow.
 * Parametry:
 *    database_ptr - wskaznik na zmienna reprezentujaca baze testu.
 *    test_name  - wskaznik na napis wybranego typu testu.
 *
 * Warunki wstepne:
 *      - Parametr database_ptr nie moze byc pustym wskaznikiem. Musi zawierac adres
 *        zmiennej reprezentujacej baze testu, ktora wczesniej zostal poprawnie
 *        zainicjalizowany poprzez wywolanie funkcji Init.
 *      - Parametr test_name musi wskazywac na jedna z nazw tzn. "latwe" lub "trudne".
 *       
 * Zwraca:
 *       true - gdy operacja sie powiedzie i test zostanie poprawnie
 *              zainicjalizowany,
 *       false - w przypadku przeciwnym.
 */
bool Init(Database *database_ptr, const char *test_name)
{
    if (!strcmp(test_name, "latwy"))
    {
        SetTest(database_ptr, easy_test, sizeof(easy_test) / sizeof(Expression));
        return true;
    }
	if (!strcmp(test_name, "trudny"))
	{
		SetTest(database_ptr, Hard_Test, sizeof(Hard_Test) / sizeof(Expression));
		return true;
	}
	/*if (!strcmp(test_name, "latwy"))
	{
		std::vector<Expression> vec = FileReading("latwy");
		SetTest(database_ptr, vec.data(), vec.size());
		return true;
	}*/
    cerr << "Otwarcie testu '" << test_name << "' nie powiodlo sie." << endl;
    return false;
}

/*!
 * Funkcja udostepnia nastepne pytania o ile jest odpowiednia ich ilosc.
 * Parametry:
 *       database_ptr   - wskaznik na zmienna reprezentujaca baze testu.
 *       expression_ptr - wskaznik na zmienna, do ktorej zostanie wpisane
 *                        kolejne wyrazenie z bazy testu.
 *
 * Warunki wstepne:
 *      - Parametr database_ptr nie moze byc pustym wskaznikiem. Musi zawierac adres
 *        zmiennej reprezentujacej baze testu, ktora wczesniej zostal poprawnie
 *        zainicjalizowany poprzez wywolanie funkcji Init.
 *      - Parametr expression_ptr nie moze byc pustym wskaznikiem. Musi wskazywac na
 *        istniejaca zmienna.
 *
 * Zwraca:
 *       true - gdy operacja sie powiedzie i parametrowi *expression_ptr zostanie
 *              przypisane nowe wyrazenie zespolone z bazy,
 *       false - w przypadku przeciwnym.
 */
bool GetNextQuestion(Database *database_ptr, Expression *expression_ptr)
{
    if (database_ptr->question_index >= database_ptr->number_of_questions)
        return false;

    *expression_ptr = database_ptr->test_array_ptr[database_ptr->question_index];
    ++database_ptr->question_index;
    return true;
}
