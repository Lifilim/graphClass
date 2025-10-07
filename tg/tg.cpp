#include <iostream>
#include <variant>

#include "graphEasier.h"

//#include<>

using namespace std;


void myChoiceAssert(bool smth) {
	if (!smth) throw exception("Введен некорректный вариант ответа");
}

struct typesOfGraphs {
	graph<int, int>			gii = graph<int, int>		(false, false, false);
	graph<int, string>		gis = graph<int, string>	(false, false, false);
	graph<string, int>		gsi = graph<string, int>	(false, false, false);
	graph<string, string>	gss = graph<string, string>	(false, false, false);


};

int main() {
	setlocale(LC_ALL, "ru-RU");

	while (true) {
		try {
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

			//graph<, >g(isOrdered - 'n', isWeighted - 'n', isMarked - 'n');
			variant<graph<int, int>, graph<int, string>, graph<string, int>, graph<string, string>> g;






		} catch (exception e) {
			cout << "Что-то странное...\n";
			cout << "Сообщение ошибки: " << e.what() << '\n';
			cout << "попробуйте заново, что ли...\n";
		} catch (...) {
			cout << "Что-то странное... попробуйте заново, что ли...\n";
		}
		cout << "+--------------------------------------------------------------------+\n";
	}
}
