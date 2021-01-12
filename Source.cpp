#include<conio.h>
#include <Windows.h>
#include <cmath>
#include "cmath"
#include "memory"
#include <iostream>
#include <conio.h>
#include <locale.h>
#include <typeinfo>
#include <vector>
#include <list>
#include <ctime>
using namespace std;
//ФУНКЦИИ
class Function
{
public:
	virtual double _displai_XtoY(double x) = 0;
	virtual void print_func(ostream&str)const = 0;
	virtual ~Function() {}
};
class Parabola_x_in_2 :public Function {
public:
	virtual void print_func(ostream&str)const override
	{
		str << "Функция:y=x^2" << endl;
	}
	virtual double _displai_XtoY(double argyment) override
	{
		return pow(argyment, 2);
	}
};
class Natur_Logorifm :public Function {
public:
	virtual void print_func(ostream&str)const override
	{
		str << "Функция:y=Ln(sin(x^1/2))" << endl;

	}
	virtual double _displai_XtoY(double argymen)
	{
		return log(sin(sqrt(argymen)));
	}
};
class Drobnay : public Function
{
public:
	virtual void print_func(ostream&str)const override
	{
		str << "(3x^2+4x+10)^3/(6+x)^4" << endl;
	}
	virtual double _displai_XtoY(double argymen)
	{
		return   ((pow((3 * pow(argymen, 2) + 4 * argymen + 10), 3)) / (pow((6 + argymen), 4)));
	}
};
class Sinys : public Function
{
public:
	virtual void print_func(ostream&str)const override
	{
		str << "Функция:y=sin(?x)" << endl;
	}
	virtual double _displai_XtoY(double argymen)
	{
		return sin(pow(argymen, 0.5));
	}
};
//ИНТЕГРАЛЛ
class Integral
{
public:
	const double RAZDIENIE = 0.001;
	virtual double Integral_Value(shared_ptr<Function> func, double a, double b) = 0;
	virtual ~Integral() {}
	virtual void print_integral(ostream &str, shared_ptr<Function> func)const = 0;
};
class By_Lower_Value :public Integral
{
public:
	virtual void print_integral(ostream &str, shared_ptr<Function> func)const override
	{
		str << "Это нижний интеграл дарблу--?";
		func->print_func(str);
	}
	virtual double Integral_Value(shared_ptr<Function> func, double a, double b)override
	{
		double result = 0, tmpA = a, tmpA1 = a + RAZDIENIE;
		while ((tmpA <= b) && (tmpA1 <= b))
		{
			if ((func->_displai_XtoY(tmpA)) < (func->_displai_XtoY(tmpA1)))
			{
				result += (func->_displai_XtoY(tmpA) * RAZDIENIE);
				tmpA += RAZDIENIE;
				tmpA1 += RAZDIENIE;
			}
			else
			{
				result += (func->_displai_XtoY(tmpA1) * RAZDIENIE);
				tmpA += RAZDIENIE;
				tmpA1 += RAZDIENIE;
			}
		}
		return result;
	}
};
class By_Power_Value :public Integral
{
public:
	virtual void print_integral(ostream &str, shared_ptr<Function> func)const override
	{
		str << "Это верхний интеграл дарблу--?";
		func->print_func(str);
		str << endl;
	}
	virtual double Integral_Value(shared_ptr<Function> func, double a, double b) override
	{
		double result = 0, tmpA = a, tmpA1 = a + RAZDIENIE;
		while ((tmpA <= b) || (tmpA1 <= b))
		{
			if ((func->_displai_XtoY(tmpA)) > (func->_displai_XtoY(tmpA1)))
			{
				result += (func->_displai_XtoY(tmpA) * RAZDIENIE);
				tmpA += RAZDIENIE;
				tmpA1 += RAZDIENIE;
			}
			else
			{
				result += (func->_displai_XtoY(tmpA1) * RAZDIENIE);
				tmpA += RAZDIENIE;
				tmpA1 += RAZDIENIE;
			}
		}
		return result;
	}
};
class By_Middle_Value :public Integral
{
private:
public:
	virtual void print_integral(ostream &str, shared_ptr<Function> func) const override
	{
		str << "Это интеграл римана--?";
		func->print_func(str);
		str << endl;
	}
	virtual double Integral_Value(shared_ptr<Function> func, double a, double b) override
	{
		double r = RAZDIENIE;
		double result = 0, tmp = a + r / 2;
		while (tmp <= b)
		{

			result += (func->_displai_XtoY(tmp) *RAZDIENIE);
			tmp = tmp + RAZDIENIE;
		}
		return result;
	}
};
template <typename T>
struct Node
{
	T data;
	Node *next, *prev;
	Node() { next = prev = nullptr; }
	Node(T data1, Node *next1, Node *prev1) : data(data1), next(next1), prev(prev1) {}
};
template <typename T>
class Iterator
{
private:
	template <typename T>
	friend class LincedList;
	Node<T>* _node;
	Iterator(Node<T>*node) :_node(node) {};
public:
	Iterator() :_node(nullptr) {};
	Iterator(const Iterator&rhs)
	{
		this->_node = rhs._node;
	}
	Iterator&operator=(const Iterator&rhs)
	{
		this->_node = rhs._node;
		return *this;
	}
	bool operator=(const Iterator& rhs)const
	{
		return (this->_node == rhs._node);
	}
	bool operator!=(const Iterator& rhs)const
	{
		return (this->_node != rhs._node);
	}
	Iterator& operator++()
	{
		this->_node = this->_node->next;
		return *this;
	}
	Iterator& operator--()
	{
		this->_node = this->_node->prev;
		return *this;
	}
	Iterator& operator++(int)
	{
		Iterator copy(*this)
			this->_node = this->_node->next;
		return copy;
	}
	Iterator& operator--(int)
	{
		Iterator copy(*this)
			this->_node = this->_node->prev;
		return copy;
	}
	T& operator*()const
	{
		return (_node->data);
	}
};
template <typename T>
class LincedList
{
private:
	Node<T>*head, *tail;
public:
	LincedList()
	{
		head = new Node<T>;
		tail = head;
		head->next = nullptr;
		head->prev = nullptr;
	}
	~LincedList()
	{
		Node<T>*tmp = head;
		while (head != nullptr)
		{
			head = head->next;
			delete tmp;
			tmp = head;
		}
	}
	LincedList(const LincedList &rhs)
	{
		head(new Node<T>);
		tail = head;
		Node<T>*tmp = rhs.tail->prev;
		Node<T>*temp;
		while (tmp != nullptr)
		{
			temp = new Node<T>(tmp->data, head, nullptr);
			head->prev = temp;
			head = temp;
			tmp = tmp->prev;
		}
	}
	LincedList &operator=(const LincedList&rhs)
	{
		Node<T>*tmp = rhs.tail->prev;
		Node<T>*temp;
		Node<T>*star_head = head;
		while (tmp != nullptr)
		{
			temp = new Node<T>(tmp->data, head, nullptr);
			head->prev = temp;
			head = temp;
			tmp = tmp->prev;
		}
		Node<T>*star_haed_prev = star_head;
		star_haed_prev = star_haed_prev->prev;
		Node<T>*t = star_head;
		while (star_head != tail)
		{
			star_head = star_head->next;
			delete t;
			t = star_head;
		}
		tail->prev = star_haed_prev;
		star_haed_prev->next = tail;
		return *this;
	}
	Iterator<T> begin()
	{
		Iterator<T>h(head);
		return h;
	}
	Iterator<T>& erase(Iterator<T>& index)
	{
		if (index._node == head)
		{
			Node<T> *tmp = head;
			head == head->next;
			head->prev = nullptr;
		}
		else
		{
			Node<T> *tmp = index._node;
			tmp->prev->next = tmp->next;
			tmp->next->prev = tmp->prev;
		}
		index._node = index._node->next;
		delete tmp;
		return *this;
	}
	void push_front(T data)
	{
		Node<T>*tmp = new Node<T>(data, head, nullptr);
		head->prev = tmp;
		head = tmp;
	}
	void push_back(T data)
	{
		Node<T> *tmp = new Node<T>(data, tail, tail->prev);
		if (empty())
		{
			head = tmp;
			tail->prev = head;
		}
		else
		{
			tail->prev->next = tmp;
			tail->prev = tmp;
		}
	}
	bool empty()
	{
		return (head == tail);
	}

	Iterator<T> end()
	{
		Iterator<T>E(tail);
		return E;
	}
	int size()const
	{
		Node<T>tmp = head;
		int size = 0;
		while (tmp != tail)
		{
			tmp = tmp->next;
			++size;
		}
		return size;
	}
	void clear()
	{
		head = tail;
		Node<T>tmp = tail;
		Node<T>tmp1 = tail;
		while (tmp != nullptr)
		{
			tmp = tmp->prev;
			delete tmp1;
			tmp1 = tmp;
		}
	}
	Iterator<T> find(const T& data)
	{
		Node<T> *tmp = head;
		while (tmp->data != data && tmp != tail)
		{
			tmp = tmp->next;
		}
		Iterator<T> res(tmp);
		return res;
	}
	void insert(const Iterator<T>& index, T data)
	{
		if (index._node == head)
		{
			Node<T> *tmp = new Node<T>(data, head, nullptr);
			head->prev = tmp;
			head = tmp;
		}
		Node<T> *tmp = new Node<T>(data, index._node, index._node->prev);
		index._node->prev->next = tmp;
		index._node->prev = tmp;
	}
};
template<typename T>
void random(T&obj)
{
	size_t amount = rand() % 50;
	for (size_t i = 0; i < amount; ++i)
	{
		size_t k = rand() % 3;
		switch (k)
		{
		case 0:
			shared_ptr<Integral>integ(new By_Lower_Value);
			system("cls");
			cout << "выберите функцию[1]-парабола [2]-натуральный логирифм {3}-дробь {4}-синнус";
			int key = getch()
				if (key == 1)
				{
					shared_ptr<Function>func(new Parabola_x_in_2);
					integ->Integral_Value(func, 1, 5);
					obj.push_front(integ);
				}
				else if (key == 2)
				{
					shared_ptr<Function>func(new Natur_Logorifm);
					integ->Integral_Value(func, 1, 5);
					obj.push_front(integ);
				}
				else if (key == 3)
				{
					shared_ptr<Function>func(new Drobnay);
					integ->Integral_Value(func, 1, 5);
					obj.push_front(integ);
				}
				else if (key == 4)
				{
					shared_ptr<Function>func(new Sinys);
					integ->Integral_Value(func, 1, 5);
					obj.push_front(integ);
				}
			break;
		}
	}
}
template<typename T>
double total_sum(T&list, double a, double b)
{
	double res = 0;
	for (Iterator<T> i = list.begin(); i != list.end(); ++i)
	{
		res += (*i)->Integral_Value(a, b);
	}
	return res;
}
template<typename T>
void printlist(T& list)
{
	size_t j = 0;
	for (auto i : list)
	{
		if (j == 10)
		{
			cout << ". . ." << endl;
			return;
		}
		i->print_integral(cout);
		++j;
	}
}

template<class T >
struct func
{
	bool operator ()(T x)
	{
		if (x > 0)
		{
			return true;
		}
		else
		{
			return false;
		}
	}
};
template<class T >
bool predicat(const T& begin, const T& end, func<T> obj)
{
	for (auto i = begin; i != end; i++)
	{
		if (obj(i) == false)
		{
			return false;
		}
	}
	return true;
}



template<class T>
class shared
{
private:
	T*obj;
	int*sz;
public:
	shared()
	{
		obj = nullptr;
		sz = new int;
		*sz = 0;
	}
	shared(T*ptr)
	{
		sz = new int;
		*sz = 1;
		obj = ptr;

	}
	~shared()
	{
		--*sz;
		if (sz == 0)
		{
			delete obj;
		}
	}
	shared(const shared&ptr)
	{
		obj = ptr->obj;
		++*sz;
	}
};

	int main()
	{
		LincedList<shared_ptr<Integral>> L;
		
		return 0;
	}
		//setlocale(LC_ALL, "RUS");
		////shared_ptr<Integral> p2(new By_Lower_Value(shared_ptr<Function>(new Natur_Logorifm)));
		//	//shared_ptr<Integral> p3(new By_Middle_Value(shared_ptr<Function>(new Drobnay)));
		//	//shared_ptr<Integral> p4(new By_Power_Value(shared_ptr<Function>(new Parabola_x_in_2)));
		//	//shared_ptr<Integral> p5(new By_Middle_Value(shared_ptr<Function>(new Sinys)));
		//	//shared_ptr<Integral> p6(new By_Power_Value(shared_ptr<Function>(new Sinys)));
		//	////cout << p2->Integral_Value(1, 5) << endl;
		//	////cout << p3->Integral_Value(1, 5) << endl;
		//	////cout << p4->Integral_Value(1, 5) << endl;
		//	////cout << p5->Integral_Value(1, 5) << endl;

		//	//LincedList<shared_ptr<Integral>>L;
		//	//L.push_front(p2);
		//	//L.push_front(p3);
		//	//L.push_front(p4);
		//	//L.push_back(p5);
		//	//L.push_back(p6);
		//	//printlist(L);
		//	//cout << total_sum(L, 1, 5);
		//	//auto f=L.begin();
		//	//++f;
		//	//random(L);
		//	//printlist(L);
		//	//cout << total_sum(L, 1, 5);
//LincedList<shared_ptr<Integral>>obj;
		//shared_ptr<Function>func(new Parabola_x_in_2);
		//shared_ptr<Integral>integ(new By_Lower_Value);
		//integ->Integral_Value(func, 1, 5);
		//obj.push_front(integ);
		//getchar();
		//getchar();