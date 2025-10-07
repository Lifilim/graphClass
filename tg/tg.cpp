#include <iostream>
#include <fstream>

#include "graphEasier.h"
#include <vector>

//#include<>

using namespace std;

/*
struct typesOfGraphs {
	graph<int, int>			gii = graph<int, int>		(false, false, false);
	graph<int, string>		gis = graph<int, string>	(false, false, false);
	graph<string, int>		gsi = graph<string, int>	(false, false, false);
	graph<string, string>	gss = graph<string, string>	(false, false, false);
};
*/

void myChoiceAssert(bool smth) {
	if (!smth) throw exception("Введен некорректный вариант ответа");
}

int main() {
	setlocale(LC_ALL, "ru-RU");

	std::vector<graphBase*> copies(1);
	auto g = copies.begin();
	char fileOrConsole = ' ';
	//graphBase* g;
	while (true) {
		try {
			if (fileOrConsole == ' ') {
				cout << "Хотите считать целый граф из файла или \nсоздадите его прямо из консоли? (f/c): ";
				cin >> fileOrConsole;
			}
			myChoiceAssert(fileOrConsole == 'f' || fileOrConsole == 'c');
			if (fileOrConsole == 'c') {
				fileOrConsole = ' ';

				cout << "Составим идеальный граф для вашей задачи ^^\n";
				cout << "Должен ли он быть взвешенным? (y/n): ";
				char isWeighted;
				cin >> isWeighted; myChoiceAssert(isWeighted == 'y' || isWeighted == 'n');
				cout << "Подойдет ли ориентированный?  (y/n): ";
				char isOrdered;
				cin >> isOrdered; myChoiceAssert(isOrdered == 'y' || isOrdered == 'n');
				cout << "Вам нужны метки на ребрах?    (y/n): ";
				char isMarked;
				cin >> isMarked; myChoiceAssert(isMarked == 'y' || isMarked == 'n');
				string markT = "int", vertexT;
				if (isMarked == 'y') {
					cout << "Какого типа будут метки?  (str/int): ";
					cin >> markT;  myChoiceAssert(markT == "str" || markT == "int");
				}
				cout << "А какие нужны вершины?    (str/int): ";
				cin >> vertexT; myChoiceAssert(vertexT == "str" || vertexT == "int");

				if (markT == "int" && vertexT == "int") *g = new graph<int, int>(isOrdered - 'n', isWeighted - 'n', isMarked - 'n');
				if (markT == "int" && vertexT == "str") *g = new graph<int, string>(isOrdered - 'n', isWeighted - 'n', isMarked - 'n');
				if (markT == "str" && vertexT == "int") *g = new graph<string, int>(isOrdered - 'n', isWeighted - 'n', isMarked - 'n');
				if (markT == "str" && vertexT == "str") *g = new graph<string, string>(isOrdered - 'n', isWeighted - 'n', isMarked - 'n');
				
				cout << "Теперь введите количество вершин и количество ребер(дуг),\n"
					 << "затем согласно выбранному типу введите указаное количество различных вершин, \n"
					 << "и после этого опишите указанное количество ребер(дуг) в формате\n"
					 << "<вершина-начало> <вершина-конец> <вес|пустота> <метка|пустота>:\n";
				(*g)->input();
			} else {
				fileOrConsole = ' ';
				string file;
				cout << "Укажите путь к файлу (без пробелов!): ";
				cin >> file;
				ifstream fin(file);
				(*g)->input(fin);
			}

			while (true) {
				cout << "Список действий: \n(! - текущий граф будет переписан)\n";
				cout << "0. Считать из файла (!)\n";
				cout << "1. Ввести с консоли (!)\n";
				cout << "2. Создать копию\n";
				cout << "2.0) посмотреть количество копий\n";
				cout << "2.1) переключиться назад  (циклически)\n";
				cout << "2.2) переключиться вперед (циклически)\n";
				cout << "3. Добавить вершину (!)\n";
				cout << "4. Добавить ребро(дугу) (!)\n";
				cout << "5. Удалить вершину (!)\n";
				cout << "6. Удалить ребро(дугу) (!)\n";
				cout << "7. Вывести список смежности в файл\n";
				cout << "8. Считать список смежности из файла (!)\n";
				cout << "9. Очистить граф и начать его создание с начала (!)\n";
				cout << "!  Конец работы\n";

				string num;
				cout << "Введите номер команды: ";
				cin >> num;
				int command = num[0] - '0';
				switch (command) {
				case 0: 
					fileOrConsole = 'f';
					continue;
				case 1:
					fileOrConsole = 'c';
					continue;
				default:
					break;
				}

			}
			//cout << "Готово!\n";
		} catch (exception e) {
			cout << "Что-то странное...\n";
			cout << "Сообщение ошибки: " << e.what() << '\n';
			cout << "попробуйте заново, что ли...\n";
		} catch (...) {
			cout << "Что-то странное... попробуйте заново, что ли...\n";
		}
		//cout << "+--------------------------------------------------------------------+\n";
	}
}
