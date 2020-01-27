#include <iostream>
#include <cmath>
#include <string>
#include <fstream>

using namespace std;
//Global Variables
const string GNUPLOT = "D:\\gnuplot\\bin\\gnuplot.exe";
const double PI = 3.14159265359;

//SHAPE INFO
int getCurve() {
	int curveType;
	do {
		cout << "\nWhich curve would you like to draw?" << endl;
		cout << "	1) Circle"
			<< "\n	2) Epicycloid"
			<< "\n	3) Hypotrochoid"
			<< "\n	4) Hypocycloid"
			<< "\n	5) Butterfly" << endl;

		cin >> curveType;
		if (curveType > 5 || curveType <= 0) {
			cout << "Error: Invalid Choice" << endl;
			cout << "Please try again." << endl;
		}
	} while (curveType > 5 || curveType <= 0);
	cout << endl;

	return curveType;
}

string getPngFileName() {
	string Name;
	cout << "\nImage File Name:"
		<< "\nNOTE: Just type your image name, '.png' will be appended automatically." << endl;
	cin >> Name;
	string fileName = Name + ".png";	//appends ".png" to "Name"
	cout << endl;

	return fileName;
}

int getNumPoints() {
	int numPoints = 0;
	do {
		cout << "\nNumber of points generated:" << endl;
		cin >> numPoints;
		if (numPoints < 2) {
			cout << "Error: Number of points must be greater than 2." << endl;
			cout << "Please try again." << endl;
		}
	} while (numPoints < 2);

	return numPoints;
}

string getCurveColor() {
	string curveColor;

	do {
		cout << "\nCurve Color (red, blue, green, black):" << endl;
		cin >> curveColor;

		if (curveColor == "red" || curveColor == "Red") {
			curveColor = "red";
			cout << "You chose color " << curveColor << "." << endl;
		}
		else if (curveColor == "blue" || curveColor == "Blue") {
			curveColor = "blue";
			cout << "You chose color " << curveColor << "." << endl;
		}
		else if (curveColor == "green" || curveColor == "Green") {
			curveColor = "green";
			cout << "You chose color " << curveColor << "." << endl;
		}
		else if (curveColor == "black" || curveColor == "Black") {
			curveColor = "black";
			cout << "You chose color " << curveColor << "." << endl;
		}
		else {
			cout << "Error: Invalid Color." << endl;
			cout << "Please try again." << endl;
		}
	} while (curveColor != "red" && curveColor != "Red" && curveColor != "blue" && curveColor != "Blue" && curveColor != "green" && curveColor != "Green" && curveColor != "black" && curveColor != "Black");

	return curveColor;
}

//SHAPES

void circle(int numPoints, double arrayX[], double radius, double arrayY[]) {
	for (int i = 0; i < numPoints; i++) {
		double theta = (PI / 90) * i;
		arrayX[i] = radius * cos(theta);
		arrayY[i] = radius * sin(theta);
	}
}

void epicycloid(double arrayX[], double arrayY[], int numPoints, double majRadius, double radius) {
	for (int i = 0; i < numPoints; i++) {
		double theta = (PI / 90) * i;
		arrayX[i] = ((majRadius + radius) * cos(theta)) - radius * cos(((majRadius + radius) / radius) * theta);
		arrayY[i] = ((majRadius + radius) * sin(theta)) - radius * sin(((majRadius + radius) / radius) * theta);
	}
}

void hypotrochoid(double arrayX[], double arrayY[], int numPoints, double majRadius, double radius, double diameter) {
	for (int i = 0; i < numPoints; i++) {
		double theta = (PI / 90) * i;
		arrayX[i] = ((majRadius - radius) * cos(theta)) + diameter * cos(((majRadius - radius) / radius) * theta);
		arrayY[i] = ((majRadius - radius) * sin(theta)) - diameter * sin(((majRadius - radius) / radius) * theta);
	}
}

void hypocycloid(double arrayX[], double arrayY[], int numPoints, double majRadius, double radius) {
	for (int i = 0; i < numPoints; i++) {
		double theta = (PI / 90) * i;
		arrayX[i] = ((majRadius - radius) * cos(theta)) + radius * cos(((majRadius - radius) / radius) * theta);
		arrayY[i] = ((majRadius - radius) * sin(theta)) - radius * sin(((majRadius - radius) / radius) * theta);
	}
}

void butterfly(double arrayX[], double arrayY[], int numPoints) {
	for (int i = 0; i < numPoints; i++) {
		double theta = (PI / 90) * i;
		arrayX[i] = sin(theta) * (exp(cos(theta)) - 2 * cos(4 * theta) - pow(sin(theta / 12), 5));
		arrayY[i] = cos(theta) * (exp(cos(theta)) - 2 * cos(4 * theta) - pow(sin(theta / 12), 5));
	}
}

void writeAndDisplayData(int numPoints, double arrayX[], double arrayY[], string FileName, string curveColor) {

	ofstream output;

	output.open("data.dat");

	for (int i = 0; i < numPoints; i++) {
		output << arrayX[i] << " " << arrayY[i] << endl;
	}

	output.close();

	output.open("plot.gnuplot");

	output << "set terminal png medium size 640,640 background '#FFFFFF'" << endl;
	output << "set key off" << endl;
	output << "set output '" << FileName << "'" << endl;
	output << "set style line 1 linetype rgb '" << curveColor << "'" << endl;
	output << "plot 'data.dat' with lines linestyle 1" << endl;

	output.close();


	string plotCmd = GNUPLOT + " plot.gnuplot";
	system(plotCmd.c_str());
	string displayCmd = "start " + FileName;
	system(displayCmd.c_str());
}

int main() {
	cout << "__________________________________" << endl;
	cout << "|        Ethan McCrary's       v.|" << endl;
	cout << "|     Circle Graph Generator   1 |" << endl;
	cout << "|________________________________|" << endl << endl;
	cout << "----------------------------------" << endl << endl;

	string Name;
	double radius;
	double majRadius;
	double diameter;

	int curveType = getCurve();
	string FileName = getPngFileName();
	string curveColor = getCurveColor();
	int numPoints = getNumPoints();

	double* arrayX = new double[numPoints];
	double* arrayY = new double[numPoints];

	if (curveType == 1) { //Circle generation

		cout << "\nEnter radius: " << endl;
		cin >> radius;

		circle(numPoints, arrayX, radius, arrayY);

	}
	else if (curveType == 2) { //epicycloid generation

		cout << "\nEnter minor radius: " << endl;
		cin >> radius;

		cout << "\nEnter major radius: " << endl;
		cin >> majRadius;

		epicycloid(arrayX, arrayY, numPoints, radius, majRadius);

	}
	else if (curveType == 3) { //hypotrochoid generation

		cout << "\nEnter minor radius: " << endl;
		cin >> radius;

		cout << "\nEnter major radius: " << endl;
		cin >> majRadius;

		cout << "\nEnter diameter: " << endl;
		cin >> diameter;

		hypotrochoid(arrayX, arrayY, numPoints, majRadius, radius, diameter);

	}
	else if (curveType == 4) { //hypocycloid generation

		cout << "\nEnter minor radius: " << endl;
		cin >> radius;

		cout << "\nEnter major radius: " << endl;
		cin >> majRadius;

		hypocycloid(arrayX, arrayY, numPoints, majRadius, radius);

	}
	else if (curveType == 5) { //Butterfly generation
		butterfly(arrayX, arrayY, numPoints);
	}

	writeAndDisplayData(numPoints, arrayX, arrayY, FileName, curveColor);

	delete[] arrayX;
	delete[] arrayY;

	system("pause");
}