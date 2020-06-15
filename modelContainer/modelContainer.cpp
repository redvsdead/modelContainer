#include "pch.h"
#include <iostream>
#include <deque>
#include <vector>
#include <fstream>
#include <algorithm>
#include <iterator>
#include <string>
#include <sstream>
#include <fstream>

using namespace std;

string modelListHistory = "all_models.txt";
string purchasingHistory = "purchase_history.txt";

/*
Модель компьютера характеризуется кодом и названием марки компьютера, типом процессора, частотой работы процессора, 
объемом оперативной памяти, объемом жесткого диска, объемом памяти видеокарты, стоимостью компьютера и количеством экземпляров. 
Поиск по типу процессора, объему ОЗУ, памяти видеокарты и объему жесткого диска.
Реализовать виртуальный магазин ПК. Магазин должен иметь два режима работы
— клиент и сотрудник (выбирается в меню). Сотрудник имеет возможность
управления магазином: добавление, редактирование, удаление моделей ПК.
Предусмотреть вывод списка моделей ПК с сортировкой и/или фильтрацией по
выбранному полю. Пользователь имеет возможность поиска ПК по заданному
критерию (любое поле, для полей типа цены и объема памяти — предусмотреть
ввод диапазона) и покупки выбранного ПК. Предусмотреть хранение истории
покупок и просмотр истории сотрудником.
*/

struct Model
{
public:

	int code;
	string mark;
	string procType;
	int procFreq;
	int ramCap;
	int hddCap;
	int gcardCap;
	int price;
	int amount;

	//просто конструктор
	Model(int _code, string _mark, string _procType, int _procFreq, int _ramCap,
		int _hddCap, int _gcardCap, int _price, int _amount)
	{
		code = _code;
		mark = _mark;
		procType = _procType;
		procFreq = _procFreq;
		ramCap = _ramCap;
		hddCap = _hddCap;
		gcardCap = _gcardCap;
		price = _price;
		amount = _amount;
	}
	Model() {	}

	//перегрузка присваивания для удобства
	Model& operator=(const Model& model)
	{
		code = model.code;
		mark = model.mark;
		procType = model.procType;
		procFreq = model.procFreq;
		ramCap = model.ramCap;
		hddCap = model.hddCap;
		gcardCap = model.gcardCap;
		price = model.price;
		amount = model.amount;

		return *this;
	}
};

//перегрузка >> для быстрого чтения модели с клавиатуры
istream& operator>>(istream &is, Model &model)
{
	//вспомогательные параметры
	int _code;
	string _mark;
	string _procType;
	int _procFreq;
	int _ramCap;
	int _hddCap;
	int _gcardCap;
	int _price;
	int _amount;

	cout << "Enter model information: " << endl;
	cout << endl;
	cout << "Code: "; is >> _code;
	cout << "Mark: "; is >> _mark;
	cout << "Processor type: "; is >> _procType;
	cout << "Processor frequency: "; is >> _procFreq;
	cout << "RAM capacity: "; is >> _ramCap;
	cout << "HDD capacity: "; is >> _hddCap;
	cout << "Graphics card capacity: "; is >> _gcardCap;
	cout << "Price: "; is >> _price;
	cout << "Total amount: "; is >> _amount;
	//просто последовательно читаем информацию с клавиатуры, присваивая ее параметрам, и создаем по ним новую модель
	model = Model(_code, _mark, _procType, _procFreq, _ramCap, _hddCap, _gcardCap, _price, _amount);

	return is;
}

//аналогичная перегрузка <<, тут то же самое, но для вывода, поэтому новую модель не создаем
ostream& operator<<(ostream &os, const Model &model)
{
	if (typeid(os) == typeid(ofstream))
	{
		os << model.code << endl;
		os << model.mark << endl;
		os << model.procType << endl;
		os << model.procFreq << endl;
		os << model.ramCap << endl;
		os << model.hddCap << endl;
		os << model.gcardCap << endl;
		os << model.price << endl;
		os << model.amount << endl;
	}
	else
	{
		os << "Model information: " << endl;
		os << "Code: " << model.code << endl;
		os << "Mark: " << model.mark << endl;
		os << "Processor type: " << model.procType << endl;
		os << "Processor frequency: " << model.procFreq << endl;
		os << "RAM capacity: " << model.ramCap << endl;
		os << "HDD capacity: " << model.hddCap << endl;
		os << "Graphics card capacity: " << model.gcardCap << endl;
		os << "Price: " << model.price << endl;
		os << "Total amount: " << model.amount << endl;
	}
	return os;
}


////////////////////////////////////////////////////////////////////////////////////////

// ниже идут предикаты, передаваемые в find_if и copy_if в главной программе

//поиск модели по всем характеристикам
struct searchModelData
{
	int code;
	string mark;
	string procType;
	int procFreq;
	int ramCap;
	int hddCap;
	int gcardCap;
	int price;
	int amount;

	searchModelData(int _code, string _mark, string _procType, int _procFreq, int _ramCap,
		int _hddCap, int _gcardCap, int _price, int _amount)
	{
		code = _code;
		mark = _mark;
		procType = _procType;
		procFreq = _procFreq;
		ramCap = _ramCap;
		hddCap = _hddCap;
		gcardCap = _gcardCap;
		price = _price;
		amount = _amount;
	}
	bool operator()(const Model &e)
	{
		return (e.code == code) && (e.mark == mark) && (e.procType == procType) && (e.procFreq == procFreq)
			&& (e.ramCap == ramCap) && (e.hddCap == hddCap) && (e.gcardCap == gcardCap)
			&& (e.price == price) && (e.amount == amount);
	}
};

//поиск по процессору
struct isProcType
{
	string  procType;

	isProcType(string _procType)
	{
		procType = _procType;
	}

	bool operator()(const Model &e)
	{
		return e.procType == procType;
	}
};

//поиск по озу
struct isRamCap
{
	int  ramCap;

	isRamCap(int _ramCap)
	{
		ramCap = _ramCap;
	}

	bool operator()(const Model &e)
	{
		return e.ramCap == ramCap;
	}
};

//поиск по видеокарте
struct isGCardCap
{
	int gcardCap;

	isGCardCap(int _gcardCap)
	{
		gcardCap = _gcardCap;
	}

	bool operator()(const Model &e)
	{
		return e.gcardCap == gcardCap;
	}
};

//поиск по жд
struct isHDDCap
{
	int hddCap;

	isHDDCap(int _hddCap)
	{
		hddCap = _hddCap;
	}

	bool operator()(const Model &e)
	{
		return e.hddCap == hddCap;
	}
};

struct isMark
{
	string mark;

	isMark(string _mark)
	{
		mark = _mark;
	}
	bool operator()(const Model &e)
	{
		return e.mark == mark;
	}
};

struct isCode
{
	int code;

	isCode(int _code)
	{
		code = _code;
	}

	bool operator()(const Model &e)
	{
		return e.code == code;
	}
};

struct isPrice
{
	int price;

	isPrice(int _price)
	{
		price = _price;
	}

	bool operator()(const Model &e)
	{
		return e.price == price;
	}
};

struct isAmount
{
	int amount;

	isAmount(int _amount)
	{
		amount = _amount;
	}

	bool operator()(const Model &e)
	{
		return e.amount == amount;
	}
};


///////////////////////////////////////////////////////

//контейнер для хранения информации о моделях
class modelDataList
{
public:
	deque<Model> modelDeque;
	deque<Model> helpDeque;

	modelDataList() :modelDeque(), helpDeque()
	{
	}

	//добавление моделей до тех пор, пока юзер не нажмет 0 (чтобы не приходилось каждый раз вручную вызывать add)
	void addModelData()
	{
		ofstream _file;
		istream_iterator<Model> is;
		bool moreModels = true;
		while (moreModels)
		{
			char answer;
			cout << "Add a new model? 1 - yes, 0 - no" << endl;
			cout << "Your choice is: ";
			cin >> answer;
			cout << endl;
			cout << endl;
			cin.get();
			if (answer == '0')
			{
				moreModels = false;
			}
			else if (answer == '1')
			{
				is = cin;	//считываем информацию о модели
				modelDeque.push_front(*is);
				cout << endl;
				cout << endl;
				cout << "Model was added successfully." << endl;
				cout << endl;
				cout << endl;
				auto x = modelDeque.begin();
				_file.open(modelListHistory, ios::app);
				loadTo(_file, x);
				_file.close();
			}
		}
	}

	void clearList() 
	{
		modelDeque.clear();
		helpDeque.clear();
	}

	//печать текущей модели
	void modelPrint(deque<Model>::iterator x)
	{
		cout << *x;
	}

	//печать всех моделей
	void modelPrintPart()
	{
		copy(helpDeque.begin(), helpDeque.end(), ostream_iterator<Model>(cout, ""));
	}

	//удаление заданной модели
	void modelDataRemove(deque<Model>::iterator x)
	{
		modelDeque.erase(x);
		cout << endl;
		cout << endl;
		cout << "Model information was removed successfully." << endl;
		cout << endl;
		cout << endl;
	}

	//изменение информации о заданной модели
	void modelDataChange(deque<Model>::iterator x)
	{
		istream_iterator<Model> is(cin);
		*x = *is;
		cout << endl;
		cout << endl;
		cout << "Model information was changed successfully." << endl;
		cout << endl;
		cout << endl;
	}

	//загрузка одной выбранной модели в файл
	void loadTo(ofstream& _file, deque<Model>::iterator x)
	{
		ostream_iterator<Model> is(_file);
		*is = *x;
		cout << endl;
		cout << endl;
		cout << "Added to file successfully." << endl;
		cout << endl;
		cout << endl;
	}
	
	//загрузка всех моделей в файл
	void loadPartTo(ofstream& _file)
	{
		copy(modelDeque.begin(), modelDeque.end(), ostream_iterator<Model>(_file));
		cout << endl;
		cout << endl;
		cout << "Added to file successfully." << endl;
		cout << endl;
		cout << endl;
	}

	//загрузка выборки по поиску в отдельный файл 
	void loadResultTo(ofstream& _file)
	{
		copy(helpDeque.begin(), helpDeque.end(), ostream_iterator<Model>(_file));
		cout << endl;
		cout << endl;
		cout << "Added to file successfully." << endl;
		cout << endl;
		cout << endl;
	}

	//загрузка первой модели из файла
	void loadFrom(ifstream& _file)
	{
		istream_iterator<Model> is(_file);
		modelDeque.push_front(*is);
		cout << endl;
		cout << endl;
		cout << "Loaded from file successfully." << endl;
		cout << endl;
		cout << endl;
	}

	//загрузка всех моделей из файла
	void loadPartFrom(ifstream& _file)
	{
		istream_iterator<Model> is(_file);
		while (!_file.eof()) 
		{
			modelDeque.push_front(*is);
			++is;
		}
		cout << endl;
		cout << endl;
		cout << "Loaded from file successfully." << endl;
		cout << endl;
		cout << endl;
	}
};

int InputQuery(string str, int min, int max)
{
	int choise;
	cout << str;
	cin >> choise;
	while (choise < min || choise > max) {
		cout << "Warning: incorrect value, try again" << endl;
		cin >> choise;
	}
	return choise;
}

string InputString(string message)
{
	string str;
	do {
		cout << message << endl;
		cin >> str;
	} while (str == "" && cout << "Warning: incorrect value, try again\n");
	return str;
}

int mainMenu()
{
	cout << "Add model - 1" << endl;					//добавление модели
	cout << "Change model information - 2" << endl;		//изменение модели
	cout << "Remove model - 3" << endl;					//удаление модели
	cout << "Get model excerpt (linear) - 4" << endl;	//выборка моделей по типу проц, озу, видеокарте и жд (основная задача)
	cout << "Get model excerpt (binary) - 5" << endl;
	cout << "Exit - 0" << endl;
	cout << "Your choice is: ";
	int ans = InputQuery("", 0, 5);
	return ans;
}

int selectionMenu()
{
	cout << "Select models by:" << endl;
	cout << "RAM capacity - 1" << endl;				//объем озу
	cout << "Processor type - 2" << endl;			//тип процессора
	cout << "Graphics card capacity - 3" << endl;	//объем видеокарты
	cout << "HDD capacity - 4" << endl;				//объем жд
	cout << "Mark - 5" << endl;						//марка
	cout << "Code - 6" << endl;						//код
	cout << "Price - 7" << endl;					//цена
	cout << "Amount - 8" << endl;					//количество
	cout << "Exit selecting menu - 0" << endl;
	cout << "Your choice is: ";
	int ans = InputQuery("", 0, 5);
	return ans;
}

int sortMenu()
{
	cout << "Sort models by:" << endl;
	cout << "RAM capacity - 1" << endl;				//объем озу
	cout << "Processor type - 2" << endl;			//тип процессора
	cout << "Graphics card capacity - 3" << endl;	//объем видеокарты
	cout << "HDD capacity - 4" << endl;				//объем жд
	cout << "Mark - 5" << endl;						//марка
	cout << "Code - 6" << endl;						//код
	cout << "Price - 7" << endl;					//цена
	cout << "Amount - 8" << endl;					//количество
	cout << "Exit sorting menu - 0" << endl;
	cout << "Your choice is: ";
	int ans = InputQuery("", 0, 5);
	return ans;
}

void selection(modelDataList& models)
{
	int answer = selectionMenu();
	deque<Model> res;
	Model tmp;
	int help1;
	string help2;
	switch (answer)
	{
	case 1:
	{
		cout << endl;
		help1 = InputQuery("Add RAM capacity: ", 1, 100);
		copy_if(models.modelDeque.begin(), models.modelDeque.end(), back_inserter(models.helpDeque), isRamCap(help1));
		cout << endl;
		models.modelPrintPart();
		break;
	}
	case 2:
	{
		cout << endl;
		help2 = InputString("Add Processor type: ");
		copy_if(models.modelDeque.begin(), models.modelDeque.end(), back_inserter(models.helpDeque), isProcType(help2));
		cout << endl;
		models.modelPrintPart();
		break;
	}
	case 3:
	{
		cout << endl;
		help1 = InputQuery("Add Graphics card capacity: ", 1, 1000);
		copy_if(models.modelDeque.begin(), models.modelDeque.end(), back_inserter(models.helpDeque), isGCardCap(help1));
		cout << endl;
		models.modelPrintPart();
		break;
	}
	case 4:
	{
		cout << endl;
		help1 = InputQuery("Add HDD capacity: ", 1, 1000);
		copy_if(models.modelDeque.begin(), models.modelDeque.end(), back_inserter(models.helpDeque), isHDDCap(help1));
		cout << endl;
		models.modelPrintPart();
		break;
	}
	case 5:
	{
		cout << endl;
		help2 = InputString("Add Mark: ");
		copy_if(models.modelDeque.begin(), models.modelDeque.end(), back_inserter(models.helpDeque), isMark(help2));
		cout << endl;
		models.modelPrintPart();
		break;
	}
	case 6:
	{
		cout << endl;
		help1 = InputQuery("Add Code: ", 1, 1000);
		copy_if(models.modelDeque.begin(), models.modelDeque.end(), back_inserter(models.helpDeque), isCode(help1));
		cout << endl;
		models.modelPrintPart();
		break;
	}
	case 7:
	{
		cout << endl;
		help1 = InputQuery("Add Price: ", 10000, 100000);
		copy_if(models.modelDeque.begin(), models.modelDeque.end(), back_inserter(models.helpDeque), isPrice(help1));
		cout << endl;
		models.modelPrintPart();
		break;
	}
	case 8:
	{
		cout << endl;
		help1 = InputQuery("Add Amount: ", 1, 1000);
		copy_if(models.modelDeque.begin(), models.modelDeque.end(), back_inserter(models.helpDeque), isAmount(help1));
		cout << endl;
		models.modelPrintPart();
		break;
	}
	}
}

bool sortDirection()
{
	int res = InputQuery("Select sorting direction:\n1Direct - 1 \n2Indirect - 2 \nYour choice is: ", 1, 2);
	if (res == 1)
		return true;
	else
		return false;
}


void sortSelection(deque<Model>& selection)
{
	int answer = sortMenu();
	bool dir = sortDirection();
	switch (answer)
	{
	case 1:
	{
		if (dir)
		{
			struct sortByRAMCap
			{
				bool operator() (Model model1, Model model2)
				{
					return model1.ramCap < model2.ramCap;
				}
			} sortRAM;
			sort(selection.begin(), selection.end(), sortRAM);
		}
		else
		{
			struct sortByRAMCap
			{
				bool operator() (Model model1, Model model2)
				{
					return model1.ramCap > model2.ramCap;
				}
			} sortRAM;
			sort(selection.begin(), selection.end(), sortRAM);
		}
	}
	case 2:
	{
		if (dir)
		{
			struct sortByProcType
			{
				bool operator() (Model model1, Model model2)
				{
					return model1.procType < model2.procType;
				}
			} sortPT;
			sort(selection.begin(), selection.end(), sortPT);
		}
		else
		{
			struct sortByProcType
			{
				bool operator() (Model model1, Model model2)
				{
					return model1.procType > model2.procType;
				}
			} sortPT;
			sort(selection.begin(), selection.end(), sortPT);
		}
	}
	case 3:
	{
		if (dir)
		{
			struct sortByGC
			{
				bool operator() (Model model1, Model model2)
				{
					return model1.gcardCap < model2.gcardCap;
				}
			} sortGC;
			sort(selection.begin(), selection.end(), sortGC);
		}
		else
		{
			struct sortByGC
			{
				bool operator() (Model model1, Model model2)
				{
					return model1.gcardCap > model2.gcardCap;
				}
			} sortGC;
			sort(selection.begin(), selection.end(), sortGC);
		}
	}
	case 4:
	{
		if (dir)
		{
			struct sortByHDD
			{
				bool operator() (Model model1, Model model2)
				{
					return model1.hddCap < model2.hddCap;
				}
			} sortHDD;
			sort(selection.begin(), selection.end(), sortHDD);
		}
		else
		{
			struct sortByHDD
			{
				bool operator() (Model model1, Model model2)
				{
					return model1.hddCap > model2.hddCap;
				}
			} sortHDD;
			sort(selection.begin(), selection.end(), sortHDD);
		}
	}
	case 5:
	{
		if (dir)
		{
			struct sortByMark
			{
				bool operator() (Model model1, Model model2)
				{
					return model1.mark < model2.mark;
				}
			} sortMark;
			sort(selection.begin(), selection.end(), sortMark);
		}
		else
		{
			struct sortByMark
			{
				bool operator() (Model model1, Model model2)
				{
					return model1.mark > model2.mark;
				}
			} sortMark;
			sort(selection.begin(), selection.end(), sortMark);
		}
	}
	case 6:
	{
		if (dir)
		{
			struct sortByCode
			{
				bool operator() (Model model1, Model model2)
				{
					return model1.code < model2.code;
				}
			} sortCode;
			sort(selection.begin(), selection.end(), sortCode);
		}
		else
		{
			struct sortByCode
			{
				bool operator() (Model model1, Model model2)
				{
					return model1.code > model2.code;
				}
			} sortCode;
			sort(selection.begin(), selection.end(), sortCode);
		}
	}
	case 7:
	{
		if (dir)
		{
			struct sortByPrice
			{
				bool operator() (Model model1, Model model2)
				{
					return model1.price < model2.price;
				}
			} sortPrice;
			sort(selection.begin(), selection.end(), sortPrice);
		}
		else
		{
			struct sortByPrice
			{
				bool operator() (Model model1, Model model2)
				{
					return model1.price > model2.price;
				}
			} sortPrice;
			sort(selection.begin(), selection.end(), sortPrice);
		}
	}
	case 8:
	{
		if (dir)
		{
			struct sortByAmount
			{
				bool operator() (Model model1, Model model2)
				{
					return model1.amount < model2.amount;
				}
			} sortAmount;
			sort(selection.begin(), selection.end(), sortAmount);
		}
		else
		{
			struct sortByAmount
			{
				bool operator() (Model model1, Model model2)
				{
					return model1.amount > model2.amount;
				}
			} sortAmount;
			sort(selection.begin(), selection.end(), sortAmount);
		}
	}
	default:
	{
		break;
	}
	}
}

void purchaseModel(modelDataList& modelList) 
{
	int code;
	string mark;
	string procType;
	int procFreq;
	int ramCap;
	int hddCap;
	int gcardCap;
	int price;
	int amount;

	if (!modelList.modelDeque.empty()) {
		cout << "Enter code: ";  cin >> code; cout << endl;
		cout << "Enter mark: ";  cin >> mark; cout << endl;
		cout << "Enter processor type: ";  cin >> procType; cout << endl;
		cout << "Enter processor frequence: ";  cin >> procFreq; cout << endl;
		cout << "Enter RAM capacity: ";  cin >> ramCap; cout << endl;
		cout << "Enter HDD capacity: ";  cin >> hddCap; cout << endl;
		cout << "Enter graphics card capacity: ";  cin >> gcardCap; cout << endl;
		cout << "Enter price: ";  cin >> price; cout << endl;
		cout << "Enter amount: ";  cin >> amount; cout << endl;
		auto x = find_if(modelList.modelDeque.begin(), modelList.modelDeque.end(), searchModelData(code, mark, procType, procFreq,
			ramCap, hddCap, gcardCap, price, amount));
		int am = InputQuery("Add amount of models you want to purchase", 1, 1000);
		if (x != modelList.modelDeque.end() && (*x).amount >= am){
			int help = (*x).amount;
			(*x).amount = am;
			ofstream _file;
			_file.open(purchasingHistory, ios::out);
			modelList.loadTo(_file, x);
			_file.close();
			(*x).amount = help - am;
		}
		else {
			cout << "Warning: could not purchase model";
		}
	}
}

void userMenu(modelDataList& models)
{
	deque<Model> result;
	while (true)
	{
		int answer = InputQuery("View all models - 1 \nSearch models by filter - 2 \nSort models - 3 \nPurchase a PC - 4 \nYour choice is: ", 0, 4);
		switch (answer)
		{
		case 1:
		{
			ostream_iterator<Model> os(cout, "\n");
			copy(models.modelDeque.begin(), models.modelDeque.end(), os);
			break;
		}
		case 2:
		{
			selection(models);
			break;
		}

		case 3: 
		{
			result = models.modelDeque;
			sortSelection(result);
		}

		case 4:
		{
			purchaseModel(models);
			break;
		}

		case 0:
			return;
		}
	}
}

void workerMenu(modelDataList& modelList)
{
	ofstream _file;
	ifstream f;
	int code;
	string mark;
	string procType;
	int procFreq;
	int ramCap;
	int hddCap;
	int gcardCap;
	int price;
	int amount;
	modelDataList history;
	while (true)
	{
		int answer = InputQuery("Add model - 1 \n Change model information - 2 \n Remove model - 3 \n View user history - 4 \n Exit - 0 \n Your choice is: ", 0, 4);
		switch (answer)
		{
		case 1:
			modelList.addModelData();
			break;
		case 2:
		{
			if (!modelList.modelDeque.empty()) {
				cout << "Enter code: ";  cin >> code; cout << endl;
				cout << "Enter mark: ";  cin >> mark; cout << endl;
				cout << "Enter processor type: ";  cin >> procType; cout << endl;
				cout << "Enter processor frequence: ";  cin >> procFreq; cout << endl;
				cout << "Enter RAM capacity: ";  cin >> ramCap; cout << endl;
				cout << "Enter HDD capacity: ";  cin >> hddCap; cout << endl;
				cout << "Enter graphics card capacity: ";  cin >> gcardCap; cout << endl;
				cout << "Enter price: ";  cin >> price; cout << endl;
				cout << "Enter amount: ";  cin >> amount; cout << endl;
				auto x = find_if(modelList.modelDeque.begin(), modelList.modelDeque.end(), searchModelData(code, mark, procType, procFreq,
					ramCap, hddCap, gcardCap, price, amount));
				cout << endl;
				cout << endl;
				modelList.modelPrint(x);		//выводим юзеру то, что получилось в итоге
				modelList.modelDataChange(x);	//меняем информацию
				_file.open(modelListHistory, ios::app);
				modelList.loadPartTo(_file);
				_file.close();
			}
			else
				cout << "Warning: list is empty" << endl;
			break;
		}

		case 3: 
		{
			if (!modelList.modelDeque.empty()) {
				cout << "Enter code: ";  cin >> code; cout << endl;
				cout << "Enter mark: ";  cin >> mark; cout << endl;
				cout << "Enter processor type: ";  cin >> procType; cout << endl;
				cout << "Enter processor frequence: ";  cin >> procFreq; cout << endl;
				cout << "Enter RAM capacity: ";  cin >> ramCap; cout << endl;
				cout << "Enter HDD capacity: ";  cin >> hddCap; cout << endl;
				cout << "Enter graphics card capacity: ";  cin >> gcardCap; cout << endl;
				cout << "Enter price: ";  cin >> price; cout << endl;
				cout << "Enter amount: ";  cin >> amount; cout << endl;
				auto x = find_if(modelList.modelDeque.begin(), modelList.modelDeque.end(), searchModelData(code, mark, procType, procFreq,
					ramCap, hddCap, gcardCap, price, amount));
				cout << endl;
				cout << endl;
				modelList.modelDataRemove(x);	//удаляем из списка
				_file.open(modelListHistory, ios::app);
				modelList.loadPartTo(_file);
				_file.close();
			}
			else
				cout << "Warning: list is empty" << endl;
			break;
		}

		case 4:
		{
			f.open(purchasingHistory);
			history.loadPartFrom(f);
			_file.close();
			ostream_iterator<Model> os(cout, "\n");
			copy(history.modelDeque.begin(), history.modelDeque.end(), os);
			history.clearList();
		}

		case 0: 
			return;
		}
	}
}


int main()
{	bool menuControl = true;	//для основного меню
	bool excerptControl = true;	//для подменю с выборками
	modelDataList modelList;
	ifstream _file;
	char answer;			    //ответ юзера
	_file.open(modelListHistory);
	while (menuControl)
	{
		modelList.clearList();
		int choise = InputQuery("Enter as:\nManager - 1\nUser - 2\nExit - 0\nYour choice is: ", 0, 2);
		switch (choise)
		{
		case 1:
		{
			modelList.loadPartFrom(_file);
			workerMenu(modelList);
			break;
		}
		case 2:
		{
			modelList.loadPartFrom(_file);
			userMenu(modelList);
			break;
		}
		case 0: 
		{
			menuControl = false;
		}
		}
	}
	_file.close();
}


