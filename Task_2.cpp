// Task_2.cpp: определяет точку входа для консольного приложения.
//

//Брусенцев Иван Максимович
//Задача №2
//Результатом должна быть консольная программа с текстовым меню.Программа должна содержать шаблонный 
//класс для управления данными согласно заданию.Для хранения данных необходимо выбрать оптимальный с точки 
//зрения задания контейнер.
//1. Предусмотреть операции добавления, изменения и удаления элемента контейнера.
//2. Реализовать ввод и вывод элементов контейнера с использованием потоковых итераторов на экран и в файл.
//3. Реализовать операции поиска по заданным критериям и выборки подмножества элементов по заданным 
//критериям.Реализовать поиск в двух вариантах : линейный поиск и двоичный поиск на отсортированном контейнере.
//4. Предусмотреть вывод подмножества выборки на экран и в файл.
//
//Информация о сотруднике представлена записью с полями : табельный номер, номер отдела, фамилия, 
//оклад, дата поступления на работу, процент надбавки, подоходный налог, количество отработанных дней 
//в месяце, количество рабочих дней в месяце, начислено, удержано.Поиск по номеру отдела, фамилии, 
//дате поступления и окладу.



#include "stdafx.h"

#include "Header.h"

void PrintMainMenu()
{
	std::cout << "-------------------------------------" << std::endl;
	std::cout << " 1)Ввод" << std::endl;
	std::cout << " 2)Вывод" << std::endl;
	std::cout << " 3)Поиск" << std::endl;
	std::cout << " 4)Добавление" << std::endl;
	std::cout << " 5)Подсписок" << std::endl;
	std::cout << " 0)Выход" << std::endl;
	std::cout << "------------------------------" << std::endl;
	std::cout << "Введите команду: ";
}

void PrintMenuConsoleFile()
{
	std::cout << "-------------------------------------" << std::endl;
	std::cout << " 1)Консоль" << std::endl;
	std::cout << " 2)Файл" << std::endl;
	std::cout << " 0)Выход" << std::endl;
	std::cout << "------------------------------" << std::endl;
	std::cout << "Введите команду: ";
}

void PrintMenuFindParam()
{
	std::cout << "-------------------------------------" << std::endl;
	std::cout << " 1)По номеру отдела" << std::endl;
	std::cout << " 2)По фамилии" << std::endl;
	std::cout << " 3)По дате поступления" << std::endl;
	std::cout << " 4)По окладу" << std::endl;
	std::cout << " 0)Выход" << std::endl;
	std::cout << "------------------------------" << std::endl;
	std::cout << "Введите команду: ";
}

void PrintMenuSearch()
{
	std::cout << "-------------------------------------" << std::endl;
	std::cout << " 1)Простой поиск" << std::endl;
	std::cout << " 2)Бинарный поиск" << std::endl;
	std::cout << " 0)Выход" << std::endl;
	std::cout << "------------------------------" << std::endl;
	std::cout << "Введите команду: ";
}

void PrintAction()
{
	std::cout << "-------------------------------------" << std::endl;
	std::cout << "Действия с элементом:" << std::endl;
	std::cout << " 1)Печать" << std::endl;
	std::cout << " 2)Изменение" << std::endl;
	std::cout << " 3)Удаление" << std::endl;
	std::cout << " 0)Выход" << std::endl;
	std::cout << "------------------------------" << std::endl;
	std::cout << "Введите команду: ";
}

std::string InputFileName()
{
	std::string name;
	std::cout << "Введите имя файла: ";
	std::getline(std::cin, name);
	std::getline(std::cin, name);
	if (name == "") name = "default";
	return name + ".txt";
}

void SubAction(EmpContainer& sub, std::string c, bool& flag)
{
	std::cout << " Размер подсписка: " << sub.Size() << "\n";
	std::cout << "-------------------------------------" << std::endl;
	std::cout << " 1)Вывод в консоль" << std::endl;
	std::cout << " 2)Вывод в файл" << std::endl;
	std::cout << " 0)Выход" << std::endl;
	std::cout << "------------------------------" << std::endl;
	std::cout << "Введите команду: ";
	std::cin >> c;
	try
	{
		std::string FName;

		int n = std::stoi(c);
		switch (n)
		{
		case 1:
			ConsoleOutput(sub);
			break;
		case 2:
			FName = InputFileName();
			sub.FileOutput(std::fstream(FName, std::ios::out));
			break;
		case 0:
			flag = false;
			break;
		default:
			std::cout << "Неверная команда!" << std::endl;
			break;
		}
	}
	catch (...)
	{
		std::cout << "Неверная команда!" << std::endl;
	}
}

void SearchAction(bool found, EmpContainer& cont, std::vector<Employee>::iterator& it, std::string c, bool& flag)
{
	if (found)
	{
		std::cout << "Запись найдена! \n";
		flag = true;
		int n;
		while (flag)
		{
			PrintAction();
			std::cin >> c;
			try
			{
				n = std::stoi(c);
				switch (n)
				{
				case 1:
					std::cout << *it;
					break;
				case 2:
					cont.Change(it);
					break;
				case 3:
					cont.Remove(it);
					flag = false;
					break;
				case 0:
					flag = false;
					break;
				default:
					std::cout << "Неверная команда!" << std::endl;
					break;
				}
			}
			catch (...)
			{
				std::cout << "Неверная команда!" << std::endl;
			}
		}
	}
	else
		std::cout << "Запись не найдена \n";
		flag = false;
}

int main()
{
	setlocale(LC_ALL, "rus");

	EmpContainer cont = EmpContainer();
	EmpContainer sub;
	std::string c;
	std::string str;
	int n;
	bool flag;
	bool binarySearch;
	bool found;
	std::string FName;
	std::vector<Employee>::iterator it;

	while (true)
	{
		PrintMainMenu();
		std::cin >> c;
		try
		{
			n = std::stoi(c);
			switch (n)
			{
			case 1:
				flag = true;
				while (flag)
				{
					PrintMenuConsoleFile();
					std::cin >> c;
					try
					{
						n = std::stoi(c);
						switch (n)
						{
						case 1:
							ConsoleInput(cont);
							flag = false;
							break;
						case 2:
							FName = InputFileName();
							cont.FileInput(std::fstream(FName, std::ios::in));
							flag = false;
							break;
						case 0:
							flag = false;
							break;
						default:
							std::cout << "Неверная команда!" << std::endl;
							break;
						}
					}
					catch (...)
					{
						std::cout << "Неверная команда!" << std::endl;
					}
				}
				break;
			case 2:
				flag = true;
				while (flag)
				{
					PrintMenuConsoleFile();
					std::cin >> c;
					try
					{
						n = std::stoi(c);
						switch (n)
						{
						case 1:
							ConsoleOutput(cont);
							flag = false;
							break;
						case 2:
							FName = InputFileName();
							cont.FileOutput(std::fstream(FName, std::ios::out));
							flag = false;
							break;
						case 0:
							flag = false;
							break;
						default:
							std::cout << "Неверная команда!" << std::endl;
							break;
						}
					}
					catch (...)
					{
						std::cout << "Неверная команда!" << std::endl;
					}
				}
				break;
			case 3:
				try
				{
					flag = true;
					while (flag)
					{
						PrintMenuSearch();
						std::cin >> c;
						try
						{
							n = std::stoi(c);
							switch (n)
							{
							case 1:
								binarySearch = false;
								flag = false;
								break;
							case 2:
								binarySearch = true;
								flag = false;
								break;
							case 0:
								flag = false;
								break;
							default:
								std::cout << "Неверная команда!" << std::endl;
								break;
							}
						}
						catch (...)
						{
							std::cout << "Неверная команда!" << std::endl;
						}
					}
					flag = true;
					while (flag)
					{
						PrintMenuFindParam();
						std::cin >> c;
						try
						{
							n = std::stoi(c);
							switch (n)
							{
							case 1:
								std::cout << "Введите номер отдела: ";
								if (binarySearch)
									try
									{
										found = cont.FindByDepartmentBinary(InputInt(), it);
									}
									catch (...) {
										flag = false;
									}
								else
									try
									{
										found = cont.FindByDepartment(InputInt(), it);
									}
									catch (...) {
										flag = false;
									}
									SearchAction(found, cont, it, c, flag);
								break;
							case 2:
								std::cout << "Введите фамилию: ";
								std::cin >> str;
								if (binarySearch)
									try
								{
									found = cont.FindByNameBinary(str, it);
								}
								catch (...) {
									flag = false;
								}
								else
									try
								{
									found = cont.FindByName(str, it);
								}
								catch (...) {
									flag = false;
								}
								SearchAction(found, cont, it, c, flag);
								break;
							case 3:
								if (binarySearch)
									try
								{
									found = cont.FindByEnrollmentDateBinary(InputDate(), it);
								}
								catch (...) {
									flag = false;
								}
								else
									try
								{
									found = cont.FindByEnrollmentDate(InputDate(), it);
								}
								catch (...) {
									flag = false;
								}
								SearchAction(found, cont, it, c, flag);
								break;
							case 4:
								std::cout << "Введите оклад: ";
								if (binarySearch)
									try
								{
									found = cont.FindBySalaryBinary(InputDecimal(), it);
								}
								catch (...) {
									flag = false;
								}
								else
									try
								{
									found = cont.FindBySalary(InputDecimal(), it);
								}
								catch (...) {
									flag = false;
								}
								SearchAction(found, cont, it, c, flag);
								break;
							case 0:
								flag = false;
								break;
							default:
								std::cout << "Неверная команда!" << std::endl;
								break;
							}
						}
						catch (...)
						{
							std::cout << "Неверная команда!" << std::endl;
						}
					}
				}
				catch (...) 
				{
					flag = false;
				}
				break;
			case 4:
				try
				{
					cont.Add(InputEmployee());
				}
				catch (...) {
					flag = false;
				}
				break;
			case 5:
				flag = true;
				while (flag)
				{
					PrintMenuFindParam();
					std::cin >> c;
					try
					{
						n = std::stoi(c);
						switch (n)
						{
						case 1:
							std::cout << "Введите номер отдела: ";
							sub = cont.FindSubVectByDepartment(InputInt());
							flag = true;
							while (flag)
								SubAction(sub, c, flag);
							break;
						case 2:
							std::cout << "Введите фамилию: ";
							std::cin >> str;
							sub = cont.FindSubVectByName(str);
							flag = true;
							while (flag)
								SubAction(sub, c, flag);
							break;
						case 3:
							std::cout << "Введите дату поступления: ";
							sub = cont.FindSubVectByEnrollmentDate(InputDate());
							flag = true;
							while (flag)
								SubAction(sub, c, flag);
							break;

						case 4:
							std::cout << "Введите оклад: ";
							sub = cont.FindSubVectBySalary(InputDecimal());
							flag = true;
							while (flag)
								SubAction(sub, c, flag);
						case 0: flag = false;
						}
					}
					catch (...)
					{
						std::cout << "Неверная команда!" << std::endl;
					}
				}

				break;
			case 0:
				return 0;
				break;
			default:
				std::cout << "Неверная команда!" << std::endl;
				break;
			}
		}
		catch (...)
		{
			std::cout << "Неверная команда!" << std::endl;
		}
	}
	return 0;
}
