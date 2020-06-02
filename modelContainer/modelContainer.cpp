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

/*
Модель компьютера характеризуется кодом и названием марки компьютера, типом процессора, частотой работы процессора, 
объемом оперативной памяти, объемом жесткого диска, объемом памяти видеокарты, стоимостью компьютера и количеством экземпляров. 
Поиск по типу процессора, объему ОЗУ, памяти видеокарты и объему жесткого диска.
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
			}
		}
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
			modelDeque.push_front(*is);
		cout << endl;
		cout << endl;
		cout << "Loaded from file successfully." << endl;
		cout << endl;
		cout << endl;
	}
};

void mainMenu()
{
	cout << "Add model - 1" << endl;				//добавление модели
	cout << "Change model information - 2" << endl;	//изменение модели
	cout << "Remove model - 3" << endl;				//удаление модели
	cout << "Get model excerpt (linear) - 4" << endl;		//выборка моделей по типу проц, озу, видеокарте и жд (основная задача)
	cout << "Get model excerpt (binary) - 5" << endl;
	cout << "Exit - 0" << endl;
	cout << "Your choice is: ";
}

void subMenu()
{
	cout << "Excerpt models by:" << endl;
	cout << "RAM capacity - 1" << endl;				//объем озу
	cout << "Processor type - 2" << endl;			//тип процессора
	cout << "Graphics card capacity - 3" << endl;	//объем видеокарты
	cout << "HDD capacity - 4" << endl;				//объем жд
	cout << "Exit excerpt menu - 0" << endl;
	cout << "Your choice is: ";
}

int main()
{
	bool menuControl = true;	//для основного меню
	bool excerptControl = true;	//для подменю с выборками
	modelDataList modelList;
	//от code до amount нужно для поиска модели 
	int code;
	string mark;
	string procType;
	int procFreq;
	int ramCap;
	int hddCap;
	int gcardCap;
	int price;
	int amount;

	deque<Model>::iterator x;
	char answer;	//ответ юзера
	string fileName;	//для всяких файлов, откуда или куда загружаем модели
	while (menuControl)
	{
		mainMenu();
		cin >> answer;
		cin.get();
		cout << endl;
		cout << endl;
		switch (answer)
		{
		case '1':
		{
			cout << endl;
			cout << endl;
			cout << "Add via keyboard - 1" << endl;
			cout << "Load from file - 2" << endl;
			cout << "Your choice is:";
			cin >> answer;
			cin.get();
			if (answer == '1')
			{
				cout << "Enter file name: ";
				cin >> fileName;
				fileName = fileName + ".txt";
				ofstream _file;
				_file.open(fileName);
				modelList.addModelData();
				modelList.loadPartTo(_file);
			}
			else
				if (answer == '2')
				{
					cout << endl;
					cout << endl;
					cout << "Enter file name: ";
					cin >> fileName;
					fileName = fileName + ".txt";
					ifstream _file;
					_file.open(fileName);
					cout << endl;
					cout << endl;
					modelList.loadFrom(_file);
					cout << endl;
					cout << endl;
					cout << "Models were added successfully." << endl;
					cout << endl;
					cout << endl;
					if (modelList.modelDeque.empty()) {
						cout << "empty" << endl;
					}
				}
		}
		break;
		case '2':
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
				x = find_if(modelList.modelDeque.begin(), modelList.modelDeque.end(), searchModelData(code, mark, procType, procFreq,
					ramCap, hddCap, gcardCap, price, amount));
				cout << endl;
				cout << endl;
				modelList.modelPrint(x);		//выводим юзеру то, что получилось в итоге
				modelList.modelDataChange(x);	//меняем информацию
			}
			else
				cout << "Warning: container is empty" << endl;
			break;
		case '3':
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
				x = find_if(modelList.modelDeque.begin(), modelList.modelDeque.end(), searchModelData(code, mark, procType, procFreq,
					ramCap, hddCap, gcardCap, price, amount));
				cout << endl;
				cout << endl;
				modelList.modelDataRemove(x);	//удаляем из списка
			}
			else
				cout << "Warning: container is empty" << endl;
			break;
		case '4':
			if (!modelList.modelDeque.empty()) {
				while (excerptControl)
				{
					subMenu();
					cin >> answer;
					cin.get();
					switch (answer)
					{
					case '1':
						cout << endl;
						cout << "Add RAM capacity: "; cin >> ramCap;
						copy_if(modelList.modelDeque.begin(), modelList.modelDeque.end(), back_inserter(modelList.helpDeque), isRamCap(ramCap));
						cout << endl;
						modelList.modelPrintPart();
						break;

					case '2':
						cout << endl;
						cout << "Add processor type: "; cin >> procType;
						copy_if(modelList.modelDeque.begin(), modelList.modelDeque.end(), back_inserter(modelList.helpDeque), isProcType(procType));
						cout << endl;
						modelList.modelPrintPart();
						break;
					case '3':
						cout << endl;
						cout << "Add graphics card capacity: "; cin >> gcardCap;
						copy_if(modelList.modelDeque.begin(), modelList.modelDeque.end(), back_inserter(modelList.helpDeque), isGCardCap(gcardCap));
						cout << endl;
						modelList.modelPrintPart();
						break;
					case '4':
						cout << endl;
						cout << "Enter HDD capacity: "; cin >> hddCap;
						copy_if(modelList.modelDeque.begin(), modelList.modelDeque.end(), back_inserter(modelList.helpDeque), isHDDCap(hddCap));
						cout << endl;
						modelList.modelPrintPart();
						break;
					case '0':
						cout << endl;
						cout << endl;
						excerptControl = false;
						break;
					}
					//сохраняем в отдельный файл выборку, потому что в консоли неудобно читать
					cout << "Enter file name: ";
					cin >> fileName;
					fileName = fileName + ".txt";
					ofstream _file;
					_file.open(fileName);
					modelList.loadResultTo(_file);
				}
			}
			else
				cout << "Warning: container is empty" << endl;
			break;
		case '5':
			if (!modelList.modelDeque.empty()) {
				deque<Model> sortDeque = modelList.modelDeque;	//чтобы не менять порядок элементов в исходной очереди
				Model _model;
				while (excerptControl)
				{
					subMenu();
					cin >> answer;
					cin.get();
					switch (answer)
					{
					case '1':
						cout << endl;
						cout << "Add RAM capacity: "; cin >> ramCap;
						sort(sortDeque.begin(), sortDeque.end(), [](const Model& obj1, const Model& obj2) {
							return obj1.ramCap > obj2.ramCap;
						});
						cout << endl;
						_model.ramCap = ramCap;
						x = lower_bound(sortDeque.begin(), sortDeque.end(), _model, [](const Model& m, const Model& ram) {
							return m.ramCap < ram.ramCap;
						});
						while ((x != sortDeque.end()) && (x->ramCap == ramCap)) {
							modelList.helpDeque.push_back(*x);
							++x;
						}
						modelList.modelPrintPart();
						break;
					case '2':
						cout << endl;
						cout << "Add processor type: "; cin >> procType;
						sort(sortDeque.begin(), sortDeque.end(), [](const Model& obj1, const Model& obj2) {
							return obj1.procType > obj2.procType;
						});
						cout << endl;
						_model.procType = procType;
						x = lower_bound(sortDeque.begin(), sortDeque.end(), _model, [](const Model& m, const Model& proc) {
							return m.procType < proc.procType;
						});
						while ((x != sortDeque.end()) && (x->procType == procType)) {
							modelList.helpDeque.push_back(*x);
							++x;
						}
						modelList.modelPrintPart();
						break;
					case '3':
						cout << endl;
						cout << "Add graphics card capacity: "; cin >> gcardCap;
						sort(sortDeque.begin(), sortDeque.end(), [](const Model& obj1, const Model& obj2) {
							return obj1.gcardCap > obj2.gcardCap;
						});
						cout << endl;
						_model.gcardCap = gcardCap;
						x = lower_bound(sortDeque.begin(), sortDeque.end(), _model, [](const Model& m, const Model& gcard) {
							return m.gcardCap < gcard.gcardCap;
						});
						while ((x != sortDeque.end()) && (x->gcardCap == gcardCap)) {
							modelList.helpDeque.push_back(*x);
							++x;
						}
						modelList.modelPrintPart();
						break;
					case '4':
						cout << endl;
						cout << "Enter HDD capacity: "; cin >> hddCap;
						sort(sortDeque.begin(), sortDeque.end(), [](const Model& obj1, const Model& obj2) {
							return obj1.hddCap > obj2.hddCap;
						});
						cout << endl;
						_model.hddCap = hddCap;
						x = lower_bound(sortDeque.begin(), sortDeque.end(), _model, [](const Model& m, const Model& hdd) {
							return m.hddCap < hdd.hddCap;
						});
						while ((x != sortDeque.end()) && (x->hddCap == hddCap)) {
							modelList.helpDeque.push_back(*x);
							++x;
						}
						modelList.modelPrintPart();
						break;
					case '0':
						cout << endl;
						cout << endl;
						excerptControl = false;
						break;
					}
					//сохраняем в отдельный файл выборку, потому что в консоли неудобно читать
					cout << "Enter file name: ";
					cin >> fileName;
					fileName = fileName + ".txt";
					ofstream _file;
					_file.open(fileName);
					modelList.loadResultTo(_file);
				}
			}
			else
				cout << "Warning: container is empty" << endl;
			break;
		case '0':
			menuControl = false;
			break;
		}
	}
}


