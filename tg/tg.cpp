#include <iostream>
#include <fstream>
#include <conio.h>

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

void pleaseClick() {
	cout << "\n(нажмите любую клавишу...)";
	_getch();
	cout << "\n";
}

void myChoiceAssert(bool smth) {
	if (!smth) throw exception("Введен некорректный вариант ответа");
}

template<typename type1, typename type2>
void getChoice(const string& message, const vector<type1>& anss, type2&ans) {
	cout << message;
	if (anss.size()) {
		cout << "(";
		for (int i = 0; i < anss.size(); ++i) {
			if (i > 0) cout << "/";
			cout << anss[i];
		}
		cout << "): ";
	}
	cin >> ans;
	bool ok = anss.size() == 0;
	for (auto ai : anss)
		if (ai == ans) ok = true;
	myChoiceAssert(ok);
}


template <typename V, typename EM>
void consoleInputSpecial() {
	std::vector<graph<V, EM>*> copies(1);
	int gId = 0;
	string fileOrConsole = " ";
	bool OK = true;
	while (OK) {
		try {
			myChoiceAssert(fileOrConsole == "f" || fileOrConsole == "c" || fileOrConsole == " ");
			if (fileOrConsole == " ") 
				getChoice<string, string>("Хотите считать целый граф из файла или \nсоздадите его прямо из консоли? ", { "f", "c" }, fileOrConsole);
			
			if (fileOrConsole == "c") {
				fileOrConsole = " ";
				cout << "\nСоставим идеальный граф для вашей задачи ^^\n";

				string isOrdered, isWeighted, isMarked;
				getChoice<string, string>("Подойдет ли ориентированный?  ", { "y", "n" }, isOrdered);
				getChoice<string, string>("Должен ли он быть взвешенным? ", { "y", "n" }, isWeighted);
				getChoice<string, string>("Вам нужны метки на ребрах?    ", { "y", "n" }, isMarked);
				copies[gId] = new graph<V, EM>(isOrdered == "y", isWeighted == "y", isMarked == "y");
				cout << "Теперь введите количество вершин и количество ребер(дуг),\n"
					<< "затем согласно выбранному типу введите указаное количество различных вершин, \n"
					<< "и после этого опишите указанное количество ребер(дуг) в формате\n"
					<< "<вершина-начало> <вершина-конец> <вес|пустота> <метка|пустота>\n";
				(copies[gId])->input();
			} else {
				fileOrConsole = " ";
				string file;
				getChoice<string, string>("Укажите путь к файлу (без пробелов!): ", {}, file);
				ifstream fin(file);
				if (copies[gId]) delete (copies[gId]);
				copies[gId] = new graph<V, EM>(fin);
			}

			bool ok = true;
			while (ok) {
				try {
					cout << "Список действий: \n(! - текущий граф будет переписан)\n";
					cout << "0. Считать из файла (!)\n";
					cout << "1. Ввести с консоли (!)\n";
					cout << "2. Создать копию\n";
					cout << "2.0) посмотреть количество копий\n";
					cout << "2.1) переключиться назад\n"; //  (циклически)\n";
					cout << "2.2) переключиться вперед\n"; // (циклически)\n";
					cout << "3. Добавить вершину (!)\n";
					cout << "4. Добавить ребро(дугу) (!)\n";
					cout << "5. Удалить вершину (!)\n";
					cout << "6. Удалить ребро(дугу) (!)\n";
					cout << "7. Вывести список смежности в файл\n";
					cout << "7.0) Вывести список смежности в консоль\n";
					cout << "8. Считать список смежности из файла (!)\n";
					cout << "9. Очистить граф и начать его создание с начала (!)\n";
					cout << "t2. Вывести подвешенные вершины\n";
					cout << "t3. Вывести изолированные вершины\n";
					cout << "t4. Построить орграф, являющийся пересечением двух заданных (!)\n";
					cout << "t5. Найти цикломатическое число графа\n";
					cout << "t6. Проверить, можно ли из графа удалить какую-либо вершину так, \n    чтобы получилось дерево\n";
					cout << "t7. Добавить MST текущего графа в конец списка копий (алгоритм Прима)\n";
					cout << "t8. Вывести кратчайшие пути из вершины u во все остальные вершины (Дейкстра) (в14)\n";
					cout << "t9. Найти радиус графа — минимальный из эксцентриситетов его вершин.(в10)\n";
					cout << "t10. Найти все такие пары вершин, что между ними существует путь сколько угодно малой длины. (в19)\n";
					cout << "!  Конец работы с введёными типами\n";

					string num;
					cout << "Введите номер команды: ";
					cin >> num;
					switch (num[0]) {
					case '0':
						fileOrConsole = 'f';
						ok = false;
						break;
					case '1':
						fileOrConsole = 'c';
						ok = false;
						break;
					case '2':
						if (num.size() == 3) {
							if (num[2] == '0')
								cout << "Количество сохраненных в буфере копий - " << copies.size() << "\n";
							else if (num[2] == '1') {
								if (gId == 0) cout << "Вы в самом начале списка копий.\n";
								else { --gId; cout << "Копия успешно применена\n"; }
							}
							else if (num[2] == '2') {
								if (gId + 1 == copies.size()) cout << "Вы в самом конце списка копий.\n";
								else { ++gId; cout << "Копия успешно применена\n"; }
							}
							else throw exception("Некорректная команда");
						}
						else {
							graph<V, EM>* ng = new graph<V, EM>(*copies[gId]);
							copies.push_back(ng);
							//g = prev(copies.end());
							cout << "Копия успешно добавлена в коней списка\n";
						}
						break;
					case '3':
						cout << "Введите имя вершины: ";
						if ((copies[gId])->add_vertex(cin)) cout << "Успех!!!\n";
						else cout << "Такая вершина уже есть\n";
						break;
					case '4':
						cout << "Формат: <вершина-начало> <вершина-конец> <вес|пустота> <метка|пустота>\n"
							<< "Введите ребро(дугу) : ";
						if ((copies[gId])->add_edge(cin)) cout << "Успех!!!\n";
						else cout << "Такое ребро уже есть\n";
						break;
					case '5':
						cout << "Введите имя вершины: ";
						if ((copies[gId])->erase_vertex(cin)) cout << "Успех!!!\n";
						else cout << "Такой вершины нет\n";
						break;
					case '6':
						cout << "Формат: <вершина-начало> <вершина-конец> <вес|пустота> <метка|пустота>\n"
							<< "Введите ребро(дугу) : ";
						if ((copies[gId])->erase_edge(cin)) cout << "Успех!!!\n";
						else cout << "Такого ребра нет\n";
						break;
					case '7':
						if (num.size() == 3) {
							if (num[2] == '0')
								(copies[gId])->outputAL();
							else throw exception("Некорректная команда");
						}
						else {
							string filele;
							cout << "Укажите путь к файлу (без пробелов!): ";
							cin >> filele;
							ofstream fout(filele);
							(copies[gId])->outputAL(fout);
							cout << "Проверьте файл\n";
						}
						break;
					case '8': {
						string filele;
						cout << "Укажите путь к файлу (без пробелов!): ";
						cin >> filele;
						ifstream fin(filele);
						(copies[gId])->inputAL(fin);
						cout << "Успешно считано\n";
					}
					break;
					case '9':
						fileOrConsole = ' ';
						ok = false;
						break;
					case 't':
						if (num.size() == 2) {
							if (num[1] == '2') {
								for (auto gi : copies[gId]->getVTotalDegN(1)) cout << gi << ' ';
								cout << '\n';
							} else if (num[1] == '3') {
								for (auto gi : copies[gId]->getVTotalDegN(0)) cout << gi << ' ';
								cout << '\n';
							}
							else if (num[1] == '4') {
								int copyId;
								getChoice<int, int>("Укажите номер копии для получения симметрической разности \nразности в текущий граф: ", {}, copyId);
								myChoiceAssert(0 <= copyId && copyId < copies.size()); //cout << '\n';
								copies[gId]->getSimDif(copies[copyId]);
								cout << "Вы получили симметрическую разность, замечательно!\n";
							}
							else if (num[1] == '5') {
								cout << "цикломатическое число: " << copies[gId]->getСyclomaticСomplexity() << '\n';
							}
							else if (num[1] == '6') {
								bool good = false;
								for (auto& ali : copies[gId]->getAdjacencyList()) {
									graph<V, EM> temp(copies[gId]);
									temp.erase_vertex(ali.first);
									if (temp.getEdgeCnt() + 1 == temp.getVertextCnt() && temp.getСyclomaticСomplexity() == 0) {
										good = true;
										cout << "Можно, такой вершиной является " << ali.first << '\n';
										break;
									}
								}
								if (!good) cout << "В данном графе нет таких вершин\n";
							}
							else if (num[1] == '7') {
								copies.push_back(copies[gId]->MSTPrim());
							}
							else if (num[1] == '8') {
								V vert;
								getChoice<V, V>("Введите вершину u: ", {}, vert);
								myChoiceAssert(copies[gId]->isVertex(vert));

								cout << "Вершина-куда | вес | предок\n";
								auto resD = (copies[gId]->algDijkstra(vert));
								for (auto di: resD) {
									cout << di.first << " | " << di.second.first << " | " << di.second.second << '\n';
								}
							}
							else if (num[1] == '9') {
								auto dists = (copies[gId]->algFloydWarshall());
								weightT ans = INF;
								for (auto v : dists) {
									weightT ansV = -INF;
									for (auto u : v.second)
										ansV = max(ansV, u.second);
									ans = min(ans, ansV);
								}
								cout << "Эксцентриситет графа: " << ans << '\n';
							}
							else throw exception("Некорректная команда");
						}
						else if (num.size() == 3) {
							if (num[1] == '1' && num[2] == '0') {
								std::set<pair<V, V>> res;
								int n = copies[gId]->getVertextCnt();
								bool isOrdered = copies[gId]->getOrdered();
								auto adj = copies[gId]->getAdjacencyList();
								for (auto w : adj) {
									auto lastDists = copies[gId]->algFordBellman(w.first);
									auto dists = lastDists.first;
									auto last = lastDists.second;

									if (last.second) {
										V y = last.first;
										for (int i = 0; i < n; ++i)
											y = dists[y].second;

										queue<V> q;
										for (V cur = y; cur != y || q.size() < 1; cur = dists[cur].second) {
											q.push(cur);
										}
										std::map<V, bool> used;
										while (!q.empty()) {
											V top = q.front();
											q.pop();
											used[top] = true;
											if (top != w.first) {
												if (isOrdered)
													res.insert({ w.first, top });
												else
													res.insert({ std::min(w.first, top), std::max(w.first, top) });
											}
											for (auto u : adj[top])
												if (!used[u.first])
													q.push(u.first);
										}
									}
								}
								cout << "Все пары вершин из условия:\nначало пути | конец пути\n";
								for (auto resi : res)
									cout << resi.first << ' ' << resi.second << '\n';
							}
							else throw exception("Некорректная команда");
						} else throw exception("Некорректная команда");
						break;
					case '!':
						OK = ok = false;
						
						break;
					default:
						throw exception("Некорректная команда");
						break;
					}
					if (OK) 
						pleaseClick();
				}
				catch (exception e) {
					cout << "Что-то странное...\n";
					cout << "Сообщение ошибки: " << e.what() << '\n';
					cout << "попробуйте заново, что ли...\n";
					pleaseClick();
				}
				catch (...) {
					cout << "Что-то странное... попробуйте заново, что ли...\n";
					pleaseClick();
				}
			}
		}
		catch (exception e) {
			cout << "Что-то странное...\n";
			cout << "Сообщение ошибки: " << e.what() << '\n';
			cout << "попробуйте заново, что ли...\n";
			fileOrConsole = ' ';
			pleaseClick();
		}
		catch (...) {
			cout << "Что-то странное... попробуйте заново, что ли...\n";
			fileOrConsole = ' ';
			pleaseClick();
		}
		//cout << "+--------------------------------------------------------------------+\n";
	}
	for (auto& ci : copies)
		delete ci;
}


void consoleInput() {
	cout << "Если бы граф был с метками на ребрах, \n"
		 << "то какими бы они были?         (str/int): ";
	string markT = "int", vertexT;
	cin >> markT;  myChoiceAssert(markT == "str" || markT == "int");

	cout << "Какого типа вам нужны вершины? (str/int): ";
	cin >> vertexT; myChoiceAssert(vertexT == "str" || vertexT == "int");

	if (vertexT == "int" && markT == "int") consoleInputSpecial<int, int>();		//copies[g] = new graph<int, int>(isOrdered - 'n', isWeighted - 'n', isMarked - 'n');
	if (vertexT == "int" && markT == "str") consoleInputSpecial<int, string>();		//copies[g] = new graph<int, string>(isOrdered - 'n', isWeighted - 'n', isMarked - 'n');
	if (vertexT == "str" && markT == "int") consoleInputSpecial<string, int>();		//copies[g] = new graph<string, int>(isOrdered - 'n', isWeighted - 'n', isMarked - 'n');
	if (vertexT == "str" && markT == "str") consoleInputSpecial<string, string>();	//copies[g] = new graph<string, string>(isOrdered - 'n', isWeighted - 'n', isMarked - 'n');
}


int main() {
	setlocale(LC_ALL, "ru-RU");

	while (true) {
		consoleInput();
		string res;
		getChoice<string, string>("\n\n  ===\n  Хотите начать работу сначала с другим типом? ", { "y", "n" }, res);
		if (res == "n") {
			cout << "\n\nЗавершение программы...\nПриходите ещё!\n\n\n";
			break;
		}
	}
	
}
