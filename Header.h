#pragma once


#include "stdafx.h"

#include <iostream>
#include <fstream>
#include <string>
#include <algorithm> 
#include <vector>
#include <iterator>
#include <stdlib.h>
#include <functional>
#include <ctime>
#include "Date.h"
#include "Decimal.h"


class Employee
{
public:
	//табельный номер
	int PersonnelNumber;
	//номер отдела
	int Department;
	//фамилия
	std::string Name;
	//оклад
	dec::decimal<2> Salary; // int Salary; 100.00 = 10000 12345 = 123.45 
	//дата поступления на работу
	Date EnrollmentDate;
	//процент надбавки
	dec::decimal<2> Overhead;
	//подоходный налог
	dec::decimal<2> IncomeTax;
	//кол-во отработанных дней в месяце
	int DaysWorked;
	//кол-во рабочих дней в месяце
	int AllWorkingDays;
	//начислено
	dec::decimal<2> Accrued;
	//удержано
	dec::decimal<2> Withheld;

	Employee(int APersonnelNumber, int ADepartment, std::string AName, dec::decimal<2> ASalary, Date AEnrollmentDate,
		dec::decimal<2> AOverhead, dec::decimal<2> AIncomeTax, int ADaysWorked, int AAllWorkingDays, dec::decimal<2> AAccrued, dec::decimal<2> AWithheld)
	{
		PersonnelNumber = APersonnelNumber;
		Department = ADepartment;
		Name = AName;
		Salary = ASalary;
		EnrollmentDate = AEnrollmentDate;
		Overhead = AOverhead;
		IncomeTax = AIncomeTax;
		DaysWorked = ADaysWorked;
		AllWorkingDays = AAllWorkingDays;
		Accrued = AAccrued;
		Withheld = AWithheld;
	}

	Employee()
	{
		PersonnelNumber = 0;
		Department = 0;
		Name = "";
		Salary = 0;
		EnrollmentDate = Date();
		Overhead = 0;
		IncomeTax = 0;
		DaysWorked = 0;
		AllWorkingDays = 0;
		Accrued = 0;
		Withheld = 0;
	}

	~Employee()	{}

	bool operator==(const Employee& that) const
	{
		return	this->PersonnelNumber == that.PersonnelNumber;
	}

	bool operator < (const Employee &that)
	{
		return this->PersonnelNumber < that.PersonnelNumber;
	}
};

std::istream& operator>>(std::istream& cin, Employee &emp)
{
	cin >> emp.PersonnelNumber;
	cin >> emp.Department;
	cin >> emp.Name;
	cin >> emp.Salary;
	std::string temp;
	cin >> temp;
	Date::StrToDate(temp, emp.EnrollmentDate);
	cin >> emp.Overhead;
	cin >> emp.IncomeTax;
	cin >> emp.DaysWorked;
	cin >> emp.AllWorkingDays;
	cin >> emp.Accrued;
	cin >> emp.Withheld;

	return cin;
}

std::ostream& operator<<(std::ostream &cout, const Employee &emp)
{
	cout << std::to_string(emp.PersonnelNumber) + "\t" +
		std::to_string(emp.Department) + "\t" +
		emp.Name + "\t" <<
		emp.Salary << "\t";
	cout << emp.EnrollmentDate << "\t";
	cout << emp.Overhead << "\t" <<
		emp.IncomeTax << "\t" +
		std::to_string(emp.DaysWorked) + "\t" +
		std::to_string(emp.AllWorkingDays) + "\t" <<
		emp.Accrued << "\t" <<
		emp.Withheld << std::endl;;
	return cout;
}

Employee InputEmployee();

//Predicates


class DepartmentPredicate
{
protected:
	int dep;

public:
	DepartmentPredicate(int _dep)
	{
		dep = _dep;
	}

	bool virtual operator () (Employee emp)
	{
		return emp.Department == dep;
	}

	bool virtual operator () (Employee emp1, Employee emp2)
	{
		return emp1.Department == emp2.Department;
	}
};

class NamePredicate
{
protected:
	std::string name;

public:
	NamePredicate(std::string _name)
	{
		name = _name;
	}

	bool virtual operator () (Employee emp)
	{
		return emp.Name == name;
	}

	bool virtual operator () (Employee emp1, Employee emp2)
	{
		return emp1.Name == emp2.Name;
	}
};

class EnrollmentDatePredicate
{
protected:
	Date d;

public:
	EnrollmentDatePredicate(Date _d)
	{
		d = _d;
	}

	bool virtual operator () (Employee emp)
	{
		return (emp.EnrollmentDate == d);
	}

	bool virtual operator () (Employee emp1, Employee emp2)
	{
		return (emp1.EnrollmentDate == emp2.EnrollmentDate);
	}
};

class SalaryPredicate
{
protected:
	dec::decimal<2> salary;

public:
	SalaryPredicate(dec::decimal<2> _salary)
	{
		salary = _salary;
	}

	bool virtual operator () (Employee emp)
	{
		return emp.Salary == salary;
	}

	bool virtual operator () (Employee emp1, Employee emp2)
	{
		return emp1.Salary == emp2.Salary;
	}
};

//Comparators

class DepartmentComparator
{
public:
	bool virtual operator () (Employee emp1, Employee emp2)
	{
		return emp1.Department < emp2.Department;
	}
};

class NameComparator
{
public:
	bool virtual operator () (Employee emp1, Employee emp2)
	{
		return emp1.Name < emp2.Name;
	}
};

class EnrollmentDateComparator
{
public:
	bool virtual operator () (Employee emp1, Employee emp2)
	{
		if (emp1.EnrollmentDate < emp2.EnrollmentDate) return true;
		return false;
	}
};

class SalaryComparator
{
public:
	bool virtual operator () (Employee emp1, Employee emp2)
	{
		return emp1.Salary < emp2.Salary;
	}
};

//SubVectorsCreators

class DepartmentSubVector
{
protected:
	int dep;
	std::vector<Employee>* v;

public:
	DepartmentSubVector(int _dep)
	{
		dep = _dep;
		v = new std::vector<Employee>();
	}

	std::vector<Employee> getSet()
	{
		return *v;
	}

	void virtual operator () (Employee emp)
	{
		if (emp.Department == dep)
			(*v).push_back(emp);
	}
};

class NameSubVector
{
protected:
	std::string name;
	std::vector<Employee>* v;

public:
	NameSubVector(std::string _name)
	{
		name = _name;
		v = new std::vector<Employee>();
	}

	std::vector<Employee> getSet()
	{
		return *v;
	}

	void virtual operator () (Employee emp)
	{
		if (emp.Name == name)
			(*v).push_back(emp);
	}
};

class EnrollmentDateSubVector
{
protected:
	Date d;
	std::vector<Employee>* v;
public:
	EnrollmentDateSubVector(Date _d)
	{
		d = _d;
		v = new std::vector<Employee>();
	}

	std::vector<Employee> getSet()
	{
		return *v;
	}

	void virtual operator () (Employee emp)
	{
		if (emp.EnrollmentDate == d)
			(*v).push_back(emp);
	}
};

class SalarySubVector
{
protected:
	dec::decimal<2> salary;
	std::vector<Employee>* v;
public:
	SalarySubVector(dec::decimal<2> _salary)
	{
		salary = _salary;
		v = new std::vector<Employee>();
	}

	std::vector<Employee> getSet()
	{
		return *v;
	}

	void virtual operator () (Employee emp)
	{
		if (emp.Salary == salary)
			(*v).push_back(emp);
	}
};

template <class T>
class Container
{
public:

	Container(int size)
	{
		vect = std::vector<T>(size);
	}

	Container()
	{
		vect = std::vector<T>();
	}

	~Container() {}

	void Add(T el) {
		//if (!Find(el))
		//{
			vect.push_back(el);
		//}
		//else
		//	return false;
	}


	bool Find(T el, std::random_access_iterator_tag &it)
	{
		it = std::Find(vect.begin(), vect.end(), el);
		return it != vect.end()
	}

	bool Find(T el)
	{
		std::vector<T>::iterator it =
			std::find(vect.begin(), vect.end(), el);
		return it != vect.end();
	}

	template<class Predicate>
	bool FindBy(Predicate &pred, std::_Vector_iterator<std::_Vector_val<std::_Simple_types<T>>> &it)
	{
		std::_Vector_iterator<std::_Vector_val<std::_Simple_types<T>>> tmpIt;
		tmpIt = std::find_if(vect.begin(), vect.end(), pred);
		if (tmpIt == vect.end())
			return false;
		it = tmpIt;
		return true;
	}

	template<class Comparator>
	bool FindByBinary(Comparator &comp, T &bibb, std::_Vector_iterator<std::_Vector_val<std::_Simple_types<T>>> &it)
	{
		std::sort(vect.begin(), vect.end(), comp);
		std::_Vector_iterator<std::_Vector_val<std::_Simple_types<T>>> tmpIt;
		tmpIt = std::lower_bound(vect.begin(), vect.end(), bibb, comp);
		if (tmpIt == vect.end() || comp(bibb, *tmpIt))
			return false;
		it = tmpIt;
		return true;
	}

	template<class SubVector>
	std::vector<T> FindSubSetBy(SubVector v)
	{
		std::for_each(vect.begin(), vect.end(), v);
		return v.getSet();
	}

	int Size()
	{
		return vect.size();
	}

	void Clear()
	{
		vect.clear();
	}

protected:
	std::vector<T> vect;
};


void InputEmployeChange(std::vector<Employee>::iterator &it);

class EmpContainer : public Container<Employee>
{
public:

	EmpContainer(std::vector<Employee> v)
	{
		vect = v;
	}

	EmpContainer()
	{
		vect = std::vector<Employee>();
	}

	void Remove(std::vector<Employee>::iterator it)
	{
		vect.erase(it);
	}

	void Change(std::vector<Employee>::iterator &it)
	{
		InputEmployeChange(it);
	}

	bool FindByDepartment(int  dep, std::vector<Employee>::iterator &it)
	{
		DepartmentPredicate p = DepartmentPredicate(dep);
		return FindBy(p, it);
	}

	bool FindByName(std::string name, std::vector<Employee>::iterator &it)
	{
		NamePredicate p = NamePredicate(name);
		return FindBy(p, it);
	}
	
	bool FindByEnrollmentDate(Date date, std::vector<Employee>::iterator &it)
	{
		EnrollmentDatePredicate p = EnrollmentDatePredicate(date);
		return FindBy(p, it);
	}

	bool FindBySalary(dec::decimal<2> salary, std::vector<Employee>::iterator &it)
	{
		SalaryPredicate p = SalaryPredicate(salary);
		return FindBy(p, it);
	}

	bool FindByDepartmentBinary(int dep, std::vector<Employee>::iterator &it)
	{
		DepartmentComparator c = DepartmentComparator();
		Employee employee = Employee();
		employee.Department = dep;

		return FindByBinary(c, employee, it);
	}

	bool FindByNameBinary(std::string name, std::vector<Employee>::iterator &it)
	{
		NameComparator c = NameComparator();
		Employee employee = Employee();
		employee.Name = name;

		return FindByBinary(c, employee, it);
	}

	bool FindByEnrollmentDateBinary(Date date, std::vector<Employee>::iterator &it)
	{
		EnrollmentDateComparator c = EnrollmentDateComparator();
		Employee employee = Employee();
		employee.EnrollmentDate = date;

		return FindByBinary(c, employee, it);
	}

	bool FindBySalaryBinary(dec::decimal<2> salary, std::vector<Employee>::iterator &it)
	{
		DepartmentComparator c = DepartmentComparator();
		Employee employee = Employee();
		employee.Salary = salary;

		return FindByBinary(c, employee, it);
	}

	EmpContainer FindSubVectByDepartment(int dep)
	{
		DepartmentSubVector dsv = DepartmentSubVector(dep);
		
		return EmpContainer(FindSubSetBy(dsv));
	}

	EmpContainer FindSubVectByName(std::string name)
	{
		NameSubVector nsv = NameSubVector(name);
		
		return EmpContainer(FindSubSetBy(nsv));
	}

	EmpContainer FindSubVectByEnrollmentDate(Date date)
	{
		EnrollmentDateSubVector esv = EnrollmentDateSubVector(date);
		
		return EmpContainer(FindSubSetBy(esv));
	}

	EmpContainer FindSubVectBySalary(dec::decimal<2> salary)
	{
		SalarySubVector ssv = SalarySubVector(salary);

		return EmpContainer(FindSubSetBy(ssv));
	}

	void FileInput(std::fstream& fin)
	{
		if (fin.is_open())
		{
			std::istream_iterator<Employee> is(fin);
			vect.clear();
			Employee emp = *is++;
			while (!fin.fail() && !fin.eof())
			{
				Add(emp);
				emp = *is++;
			}
			if (emp.PersonnelNumber != 0)
			Add(emp);
			fin.close();
		}
		else
			std::cout << "Файл не найден!" << std::endl;
	}

	void FileOutput(std::fstream& fout)
	{
		if (fout.is_open())
		{
			copy(vect.begin(), vect.end(), std::ostream_iterator<Employee>(fout, "\n"));
			fout.close();
		}
		else
			std::cout << "Ошибка вывода";
	}

	void Output(std::ostream_iterator<Employee> os)
	{
		copy(vect.begin(), vect.end(), os);
	}

};



static void PrintHead();

void ConsoleInput(EmpContainer& cont)
{
	std::string temp;
	Employee emp;
	while (true)
	{
		try
		{
			emp = InputEmployee();
		}
		catch (...)
		{
			return;
		}
		cont.Add(emp);

		std::cout << "Добавить еще один? (0 - нет)\n";
		std::cin >> temp;

		if (std::stoi(temp) == 0) return;		
	}
}

void ConsoleOutput(EmpContainer& cont)
{
	if (cont.Size() != 0)
	{
		PrintHead();
		cont.Output(std::ostream_iterator<Employee>(std::cout, "\n"));
	}
	else
	{
		std::cout << "Контейнер пуст!\n";
	}
}

dec::decimal<2> InputDecimal(std::string message = "", bool isAdd = false, dec::decimal<2> min = (dec::decimal<2>)0,
	dec::decimal<2> max = (dec::decimal<2>)100000)
{
	std::string str;
	dec::decimal<2> res;

	while (true) {
		std::cout << message;
		try {
			std::cin >> str;
			if (str == "выход") throw "выход";
			if (str == "=" && !isAdd) return dec::decimal_cast<2>(-1);
			float tmpflt = std::stof(str);
			res = dec::decimal_cast<2>(str);
			while ((res < min || res > max)&&(str != "=")) {
				std::cout << "Ошибка (значение < " << min << " или значение > " << max << "). Повторите: " << std::endl;
				std::cin >> str;
				res = dec::decimal_cast<2>(str);
			}
			std::cout << std::endl;
			return res;
		}
		catch (...) {
			std::cout << "Невереное число!" << std::endl;
		}
	}
}

int InputInt(std::string message = "", bool isAdd = false, int min = 0, int max = 1000000)
{
	std::string str;
	int res;

	while (true)
	{
		std::cout << message;
		try
		{
			std::cin >> str;
			if (str == "выход") throw "выход";
			if (str == "=" && !isAdd) return -1;
			res = std::stoi(str);
			while (res < min || res > max)
			{
				std::cout << "Ошибка (значение < " << min << " или значение > " << max << "). Повторите: " << std::endl;
				std::cin >> str;
				res = std::stoi(str);
			}
			std::cout << std::endl;
			return res;
		}
		catch (...)
		{
			std::cout << "Невереное число!" << std::endl;
		}
	}
}

Date InputDate(bool isAdd = false, std::string message = "Введите дату в формате дд.мм.гггг: ") {
	Date date = Date();

	std::string buf;
	bool ok = false;
	while (!ok)
	{
		std::cout << message;
		std::cin >> buf;
		if (buf == "выход") throw "выход";
		if (buf == "=" && !isAdd) return Date();
		ok = Date::StrToDate(buf, date);
		if (!ok)
			std::cout << "Неверное значение!";
	}
	return date;
}

Employee InputEmployee()
{
	int _PersonnelNumber;
	int _Department;
	std::string _Name;
	dec::decimal<2> _Salary;
	Date _EnrollmentDate;
	dec::decimal<2> _Overhead;
	dec::decimal<2> _IncomeTax;
	int _DaysWorked;
	int _AllWorkingDays;
	dec::decimal<2> _Accrued;
	dec::decimal<2> _Withheld;

	std::cout << "Ввод информации о сотруднике" << std::endl;

	_PersonnelNumber = InputInt("Табельный номер: ",true, 1);

	_Department = InputInt("Номер отдела: ", true);

	std::cout << "Фамилия: ";
	std::cin >> _Name;
	std::cout << std::endl;

	_Salary = InputDecimal("Оклад: ", true);

	_EnrollmentDate = InputDate(true);

	_Overhead = InputDecimal("Процент надбавки: ", true);
	_IncomeTax = InputDecimal("Подоходный налог: ", true);
	_DaysWorked = InputInt("Отработано дней: ", true, 0, 31);
	_AllWorkingDays = InputInt("Рабочих дней в месяце: ", true, 0, 31);
	_Accrued = InputDecimal("Начислено: ", true);
	_Withheld = InputDecimal("Удержано: ", true);

	return Employee(_PersonnelNumber, _Department, _Name, _Salary, _EnrollmentDate, _Overhead, _IncomeTax, _DaysWorked,
		_AllWorkingDays, _Accrued, _Withheld);
}

void InputEmployeChange(std::vector<Employee>::iterator &it)
{
	std::cout << "-------------Сотрудник-------------" << std::endl;
	std::cout << "Введите = чтобы пропустить" << std::endl;

	std::string tmpstr = "";

	int tmpint = InputInt("Введите табельный номер(текущее " + std::to_string(it->PersonnelNumber) + "): ");
	if (tmpint != -1) it->PersonnelNumber = tmpint;

	tmpint = InputInt("Введите номер отдела(текущее " + std::to_string(it->Department) + "): ");
	if (tmpint != -1) it->Department = tmpint;
	
	std::cout << "Введите фамилию(текущее: " + it->Name + "): ";
	std::cin >> tmpstr;
	if (tmpstr != "=") it->Name = tmpstr;

	dec::decimal<2> tmpdec = InputDecimal("Введите оклад(текущее: " + dec::toString(it->Salary) + "): ");
	if (tmpdec != dec::decimal_cast<2>(-1)) it->Salary = tmpdec;

	std::string datestr = it->EnrollmentDate.to_string();
	Date dt = InputDate(false, "Введите дату поступления(дд.мм.гггг)(текущее : " + datestr + ")");
	Date defDt = Date();
	if (!(dt == defDt))
		it->EnrollmentDate = dt;

	tmpdec = InputDecimal("Введите процент надбавки(текущее: " + dec::toString(it->Overhead) + "): ");
	if (tmpdec != dec::decimal_cast<2>(-1)) it->Overhead = tmpdec;

	tmpdec = InputDecimal("Введите подоходный налог(текущее: " + dec::toString(it->IncomeTax) + "): ");
	if (tmpdec != dec::decimal_cast<2>(-1)) it->IncomeTax = tmpdec;

	tmpint = InputInt("Введите кол - во отработанных дней в месяце(текущее " + std::to_string(it->DaysWorked) + "): ", false, 0, 31);
	if (tmpint != -1) it->DaysWorked = tmpint;

	tmpint = InputInt("Введите кол-во рабочих дней в месяце(текущее " + std::to_string(it->AllWorkingDays) + "): ", false, 0, 31);
	if (tmpint != -1) it->AllWorkingDays = tmpint;

	tmpdec = InputDecimal("Введите начислено(текущее: " + dec::toString(it->Accrued) + "): ");
	if (tmpdec != dec::decimal_cast<2>(-1)) it->Accrued = tmpdec;

	tmpdec = InputDecimal("Введите удержано(текущее: " + dec::toString(it->Withheld) + "): ");
	if (tmpdec != dec::decimal_cast<2>(-1)) it->Withheld = tmpdec;
}

static void PrintHead()
{
	std::cout << "табельный №\t" << "№ отдела\t" << "фамилия\t" << "оклад\t" << "дата поступления\t" << "надбавка\t" << "отработанно\t" << "рабочих дней\t" << "начислено\t" << "удержано\n";
}