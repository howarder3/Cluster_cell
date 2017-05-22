#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#endif
#include <iostream>
#include <time.h>
#include <math.h>
#include<fstream>     //uisng File I/O

using namespace std;

const float mean_poisson = 0.5;
const float mean_exponential = 0.5;

//random generator function
int  Poisson(float mean);
float Exponential(float mean);

class cell {
public:
	int ch1 = 0;
	int ch2 = 0;
	int ch3 = 0;
	int ch4 = 0;
	int ch5 = 0;
	float ch1_expired_time = 0;
	float ch2_expired_time = 0;
	float ch3_expired_time = 0;
	float ch4_expired_time = 0;
	float ch5_expired_time = 0;
	float arrival_time[150];
	float service_time[150];


};

int main()
{
	ofstream out_file;
	out_file.open("outfile.txt");


	//random time
	int seed = time(NULL);
	srand(seed);
	float current_arrival_time = 0;
	float inter_arrival_time = 0;

	//printf("Mean Value = ");
	//cin >> mean;

	//cout<< "inter-arrival time" << "\t"<< "arrival time" <<"\t" << "service time" << endl;
	//out_file << "inter-arrival time"<< "\t" << "service time"<< endl;

	cell cell1;
	cell1.arrival_time[0] = 0;

	for (int i = 1; i < 150; i++)
	{
		inter_arrival_time = Poisson(mean_poisson) + 0.5;
		cell1.arrival_time[i] = cell1.arrival_time[i-1]+ inter_arrival_time;
		cell1.service_time[i] =Exponential(mean_exponential);
		//cout << inter_arrival_time << "\t\t\t" << c1.arrival_time[i]<<"\t\t"  << Exponential(mean_exponential) << endl;
		cout << "arrival_time = " << cell1.arrival_time[i] << "\tservice_time = " << cell1.service_time[i] << endl;
		if (cell1.arrival_time[i] > cell1.ch1_expired_time)
			cell1.ch1 = 0;

		if (cell1.ch1 == 0)
		{
			cell1.ch1_expired_time = cell1.arrival_time[i] + cell1.service_time[i];
			cout << "call success, expired time:" << cell1.ch1_expired_time <<endl;
			cell1.ch1 = 1;
		} 
		else
		{
			cout << "call failed" << endl;
		}
		//out_file << Poisson(mean)+0.5 <<"\t\t\t"<< Exponential(mean) << endl;

	}

	cout << "Generate  finished! " << endl;

	out_file.close();   //����
	system("pause");
	return 0;
}




int Poisson(float mean) //Special technique required: Box-Muller method...
{
	float R;
	float sum = 0;
	int i;
	i = -1;
	float z;

	while (sum <= mean)
	{

		R = (float)rand() / (float)(RAND_MAX + 1);
		z = -log(R);
		sum += z;
		i++;
	}
	return i;
}

float Exponential(float mean)
{
	//Generate a random number between 0 and 1.
	//REMEMBER: Always cast the oparands of a division to float, or truncation will be performed.
	float R;
	R = (float)rand() / (float)(RAND_MAX + 1);

	//Put it as a parameter to the inverse distribution function.
	return  -mean*log(R);
}