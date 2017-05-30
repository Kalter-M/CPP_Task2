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
	//��������� �����
	int PersonnelNumber;
	//����� ������
	int Department;
	//�������
	std::string Name;
	//�����
	dec::decimal<2> Salary; // int Salary; 100.00 = 10000 12345 = 123.45 
	//���� ����������� �� ������
	Date EnrollmentDate;
	//������� ��������
	dec::decimal<2> Overhead;
	//���������� �����
	dec::decimal<2> IncomeTax;
	//���-�� ������������ ���� � ������
	int DaysWorked;
	//���-�� ������� ���� � ������
	int AllWorkingDays;
	//���������
	dec::decimal<2> Accrued;
	//��������
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

	~Employee()
	{	
		EnrollmentDate.~Date();
	}

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

	bool Add(T el) {
		if (!Find(el))
		{
			vect.push_back(el);
			return true;
		}
		else
			return false;
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
		it = std::find_if(vect.begin(), vect.end(), pred);
		return it != vect.end();
	}

	template<class Comparator>
	bool FindByBinary(Comparator &comp, T &bibb, std::_Vector_iterator<std::_Vector_val<std::_Simple_types<T>>> &it)
	{
		std::sort(vect.begin(), vect.end(), comp);
		std::_Vector_iterator<std::_Vector_val<std::_Simple_types<T>>> tmpIt;
		tmpIt = std::lower_bound(vect.begin(), vect.end(), bibb, comp);
		if (tmpIt == vect.end())
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

		return FindByBinary(c, employee, it) && it->Department == dep;
	}

	bool FindByNameBinary(std::string name, std::vector<Employee>::iterator &it)
	{
		NameComparator c = NameComparator();
		Employee employee = Employee();
		employee.Name = name;

		return FindByBinary(c, employee, it) && it->Name == name;
	}

	bool FindByEnrollmentDateBinary(Date date, std::vector<Employee>::iterator &it)
	{
		EnrollmentDateComparator c = EnrollmentDateComparator();
		Employee employee = Employee();
		employee.EnrollmentDate = date;

		return FindByBinary(c, employee, it) && it->EnrollmentDate == date;
	}

	bool FindBySalaryBinary(dec::decimal<2> salary, std::vector<Employee>::iterator &it)
	{
		DepartmentComparator c = DepartmentComparator();
		Employee employee = Employee();
		employee.Salary = salary;

		return FindByBinary(c, employee, it) && it->Salary == salary;
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
			Add(emp);
			fin.close();
		}
		else
			std::cout << "���� �� ������!" << std::endl;
	}

	void FileOutput(std::fstream& fout)
	{
		if (fout.is_open())
		{
			copy(vect.begin(), vect.end(), std::ostream_iterator<Employee>(fout, "\n"));
			fout.close();
		}
		else
			std::cout << "������ ������";
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

		std::cout << "�������� ��� ����? (0 - ���)\n";
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
		std::cout << "��������� ����!\n";
	}
}

float InputFloat(std::string message = "", float min = 0, float max = 10000)
{
	std::string str;
	float res;

	while (true) {
		std::cout << message;
		try {
			std::cin >> str;
			if (str == "�����") throw "�����";
			res = std::stof(str);
			while (res < min || res > max) {
				std::cout << "������ (�������� < " << min << " ��� �������� > " << max << "). ���������: ";
				std::cin >> res;
			}
			return res;
		}
		catch (std::exception &e) {
			std::cout << "��������� �����!" << std::endl;
		}
	}
}

int InputInt(std::string message = "", int min = 0, int max = INT_MAX)
{
	std::string str;
	int res;

	while (true)
	{
		std::cout << message;
		try
		{
			std::cin >> str;
			if (str == "�����") throw "�����";
			res = std::stoi(str);
			while (res < min || res > max)
			{
				std::cout << "������ (�������� < " << min << " ��� �������� > " << max << "). ���������: ";
				std::cin >> res;
			}
			std::cout << std::endl;
			return res;
		}
		catch (std::exception& e)
		{
			std::cout << "��������� �����!" << std::endl;
		}
	}
}

Date InputDate(std::string message = "������� ���� � ������� ��.��.����: ") {
	Date date = Date();

	std::string buf;
	bool ok = false;
	while (!ok)
	{
		std::cout << message;
		std::cin >> buf;
		if (buf == "�����") throw "�����";
		if (buf == "=") return Date();
		ok = Date::StrToDate(buf, date);
		if (!ok)
			std::cout << "�������� ��������!";
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

	std::cout << "���� ���������� � ����������" << std::endl;

	_PersonnelNumber = InputInt("��������� �����: ");

	_Department = InputInt("����� ������: ");

	std::cout << "�������: ";
	std::cin >> _Name;
	std::cout << std::endl;

	_Salary = InputFloat("�����: ");

	_EnrollmentDate = InputDate();

	_Overhead = InputFloat("������� ��������: ");
	_IncomeTax = InputFloat("���������� �����: ");
	_DaysWorked = InputInt("���������� ����: ");
	_AllWorkingDays = InputInt("������� ���� � ������: ");
	_Accrued = InputFloat("���������: ");
	_Withheld = InputFloat("��������: ");

	return Employee(_PersonnelNumber, _Department, _Name, _Salary, _EnrollmentDate, _Overhead, _IncomeTax, _DaysWorked,
		_AllWorkingDays, _Accrued, _Withheld);
}

void InputEmployeChange(std::vector<Employee>::iterator &it)
{
	std::cout << "-------------���������-------------" << std::endl;
	std::cout << "������� = ����� ����������" << std::endl;

	std::string tmpstr = "";

	int tmpint;

	std::cout << "������� ��������� �����(������� " + std::to_string(it->PersonnelNumber) + "): ";
	std::cin >> tmpstr;
	if (tmpstr != "=")
		it->PersonnelNumber = std::stoi(tmpstr);

	std::cout << "������� ����� ������(������� " + std::to_string(it->Department) + "): ";
	std::cin >> tmpstr;
	if (tmpstr != "=")
		it->Department = std::stoi(tmpstr);
	
	std::cout << "������� �������(�������: " + it->Name + "): ";
	std::cin >> tmpstr;
	if (tmpstr != "=") it->Name = tmpstr;

	std::cout << "������� �����(�������: " << it->Salary << "): ";
	std::cin >> tmpstr;
	if (tmpstr != "=") it->Salary = dec::decimal_cast<2>(std::stoi(tmpstr));

	std::string datestr = it->EnrollmentDate.to_string();
	Date dt = InputDate("������� ���� �����������(��.��.����)(������� : " + datestr + ")");
	Date defDt = Date();
	if (!(dt == defDt))
		it->EnrollmentDate = dt;

	std::cout << "������� ������� ��������(�������: " << it->Overhead << "): ";
	std::cin >> tmpstr;
	if (tmpstr != "=") it->Overhead = dec::decimal_cast<2>(std::stoi(tmpstr));

	std::cout << "������� ���������� �����(�������: " << it->IncomeTax << "): ";
	std::cin >> tmpstr;
	if (tmpstr != "=") it->IncomeTax = dec::decimal_cast<2>(std::stoi(tmpstr));

	std::cout << "������� ���-�� ������������ ���� � ������(������� " + std::to_string(it->DaysWorked) + "): ";
	std::cin >> tmpstr;
	if (tmpstr != "=")
		it->DaysWorked = std::stoi(tmpstr);

	std::cout << "������� ���-�� ������� ���� � ������(������� " + std::to_string(it->AllWorkingDays) + "): ";
	std::cin >> tmpstr;
	if (tmpstr != "=")
		it->AllWorkingDays = std::stoi(tmpstr);

	std::cout << "������� ���������(�������: " << it->Accrued << "): ";
	std::cin >> tmpstr;
	if (tmpstr != "=") it->Accrued = dec::decimal_cast<2>(std::stoi(tmpstr));

	std::cout << "������� ��������(�������: " << it->Withheld << "): ";
	std::cin >> tmpstr;
	if (tmpstr != "=") it->Withheld = dec::decimal_cast<2>(std::stoi(tmpstr));
}

static void PrintHead()
{
	std::cout << "��������� �\t" << "� ������\t" << "�������\t" << "�����\t" << "���� �����������\t" << "��������\n" << "�����������\n" << "������� ����\n" << "���������\n" << "��������\n";
}