#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "pixel.h"

using namespace std;

void average_colors(vector<Pixel>& pixel_list) {
	double r_sum = 0.0;
	double g_sum = 0.0;
	double b_sum = 0.0;
	int count = pixel_list.size();

	for (size_t i = 0; i < pixel_list.size(); i++) {
		r_sum += pixel_list[i].r;
		g_sum += pixel_list[i].g;
		b_sum += pixel_list[i].b;
	}

	double avg_r = r_sum / count;
	double avg_g = g_sum / count;
	double avg_b = b_sum / count;

	cout << "Average of r values: " << avg_r << endl;
	cout << "Average of g values: " << avg_g << endl;
	cout << "Average of b values: " << avg_b << endl;
}

void flip_vertically(vector<Pixel>& pixel_list) {
	ofstream out("flipped.dat", ios::out);
	if (!out.is_open()) {
		cout << "file can't be opened" << endl;
	}
	else {


		for (int i = 0; i < pixel_list.size() / 2; i++) {
			swap(pixel_list[i].y, pixel_list[pixel_list.size() - 1 - i].y);
		}
		for (Pixel& p : pixel_list) {
			out << p.x << "," << p.y << "," << p.r << "," << p.g << "," << p.b << endl;
		}
		out.close();
	}
}

int main(int argc, char* argv[]) {

	vector<Pixel> pixel_list;

	if (argc < 2) {
		cout << "Data File Name not Entered.\n";
	}
	else {
		char* pixelsDat = argv[1];
		cout << pixelsDat << endl;

		ifstream in;
		in.open(pixelsDat, ios::in);
		if (!in.is_open()) {
			cout << "file can't be opened" << endl;
		}
		else {

			string iline;
			while (getline(in, iline)) {

				cout << iline << endl;

				//Per Line
				int parStart = 0;
				int parEnd = iline.find(",");
				vector<string> pdata;

				while (parEnd != string::npos) {
					pdata.push_back(iline.substr(parStart, parEnd - parStart));
					parStart = parEnd + 1;
					parEnd = iline.find(",", parStart + 1);
				}
				pdata.push_back(iline.substr(parStart));
				if (pdata.size() == 5) {
					Pixel p;
					p.x = stoi(pdata[0]);
					p.y = stoi(pdata[1]);
					p.r = stof(pdata[2]);
					p.g = stof(pdata[3]);
					p.b = stof(pdata[4]);
					pixel_list.push_back(p);
				}
			}

			in.close();

		}

		average_colors(pixel_list);
		flip_vertically(pixel_list);

		cout << "Check 'flipped.dat' in the project folder to see results" << endl;
	}
	return 0;
}
