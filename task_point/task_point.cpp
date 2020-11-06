// task_point.cpp.
//

#include "stdafx.h"
#include <iostream>
#include <string>
using namespace std;

class Timestamp {
private:
	unsigned int n;
	unsigned int ns;
public:
	Timestamp() {
		n = 0;
		ns = 0;
	}
	Timestamp(int n, int ns) {
		this->n = n;
		this->ns = ns;
	}
	int Getn() {
		return n;
	}
	int Getns() {
		return ns;
	}
	void setTimest(int valn, int valns)
	{
		n = valn;
		ns = valns;
	}
	string PrintTime() {
		string out1 = "n= " + to_string(n) + "\t  ns = " + to_string(ns);
		return out1;
	}
};

class Data_point {
public:
	Data_point() {
		value = 0;
		quality = 0;
	}

	// func save data_point
	int setPointData(double valval, double valqua, double valn, double valns)
	{
		try {
			if (valqua < 0 || ceil(valqua) != valqua || valn < 0 || ceil(valn) != valn || valns < 0 || ceil(valns) != valns)
				throw "error";
			value = valval;
			quality = valqua;
			timestamp.setTimest(valn, valns);

			cout << "Success" << endl;
		}
		catch (const char* err)
		{
			cout << err << ": input data type \n";
			return 1;
		}
		return 0;
	}

	int GetQ() {
		return quality;
	}
	double GetV() {
		return value;
	}

	int gettimen_point() {
		return timestamp.Getn();
	}
	int gettimens_point() {
		return timestamp.Getns();
	}
	string Print() {
		string out = "V = " + to_string(value) + " \t Q = " + to_string(quality) + "\t timestamp: " + timestamp.PrintTime();
		return out;
	}
private:
	double value;
	unsigned int quality;
	Timestamp timestamp;
};


Data_point average_func(Timestamp valt1, Timestamp valt2, Data_point* valpoint, int size, string valstatus);

int main()
{

	// dataset for task1
	Data_point point1, point2, point3, point4;
	point1.setPointData(125, 23, 40.6, 320000);

	point2.setPointData(42, -23, 60, 320000);

	point3.setPointData(42, 23, 60, 1000000000);

	point4.setPointData(42, 23.67, 60, 1000000000);


	// dataset for task2
	Data_point point[9];
	point[0].setPointData(37, 42, 44, 250);
	point[1].setPointData(150, 50, 34, 200);
	point[2].setPointData(13, 78, 60, 750);
	point[3].setPointData(73, 33, 50, 650);
	point[4].setPointData(96, 26, 40, 500);
	point[5].setPointData(8, 16, 51, 8000);
	point[6].setPointData(24, 30, 50, 8500);
	point[7].setPointData(17, 45, 30, 650);
	point[8].setPointData(9, 21, 39, 8560);


	Timestamp t1, t2;
	string status;
	int size = 9;


	t1.setTimest(41, 800);
	t2.setTimest(50, 25000);
	status = "Good";
	average_func(t1, t2, point, size, status);


	t1.setTimest(34, 5000);
	t2.setTimest(51, 3520);
	status = "Good";
	average_func(t1, t2, point, size, status);


	t1.setTimest(34, 650);
	t2.setTimest(70, 955);
	status = "Bad";
	average_func(t1, t2, point, size, status);


	t1.setTimest(45, 8500);
	t2.setTimest(60, 750);
	status = "Undefined";
	average_func(t1, t2, point, size, status);


	t1.setTimest(30, 700);
	t2.setTimest(33, 250);
	status = "Good";
	average_func(t1, t2, point, size, status);


	t1.setTimest(41, 800);
	t2.setTimest(50, 2500);
	status = "Good";
	average_func(t1, t2, point, size, status);

	system("pause");
	return 0;
}


Data_point average_func(Timestamp valt1, Timestamp valt2, Data_point* valpoint, int size, string valstatus)
{
	Data_point result;

	int Q = INT_MAX;
	int count = 0;
	double sum_V = 0;

	try {
		for (int i = 0; i <= size; i++) {
			if (valt1.Getn() < valpoint[i].gettimen_point() || (valt1.Getn() == valpoint[i].gettimen_point() && valt1.Getns() <= valpoint[i].gettimens_point()))
				if (valt2.Getn() > valpoint[i].gettimen_point() || (valt2.Getn() == valpoint[i].gettimen_point() && valt2.Getns() >= valpoint[i].gettimens_point()))
				{
					if (valstatus == "Good") {
						if ((valpoint[i].GetQ() % 2) == 0 && ((valpoint[i].GetQ() % 3) != 0)) {
							sum_V += valpoint[i].GetV();
						}
					}
					else if (valstatus == "Bad") {
						if ((valpoint[i].GetQ() % 3) == 0 && ((valpoint[i].GetQ() % 2) != 0)) {
							sum_V += valpoint[i].GetV();
						}
					}
					else if (valstatus == "Undefined") {
						if ((valpoint[i].GetQ() % 3) == 0 && ((valpoint[i].GetQ() % 2) == 0)) {
							sum_V += valpoint[i].GetV();
						}
					}
					if (Q > valpoint[i].GetQ())
					{
						Q = valpoint[i].GetQ();
					}
					count++;
				}
		}
		if (count == 0) {
			throw "error: not data in []";
		}
		if (sum_V == 0) {
			throw "error: not status";
		}

		result.setPointData((sum_V / count), Q, valt1.Getn(), valt1.Getns());
		cout << " result: " << result.Print() << endl;
	}
	catch (const char* err) {
		cout << err << endl;
	}

	return result;
}



