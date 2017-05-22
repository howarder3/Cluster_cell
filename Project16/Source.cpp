#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#endif
#include <iostream>
#include <time.h>
#include <math.h>
#include<fstream>     //uisng File I/O

using namespace std;

//random generator function
int  Poisson(double mean);
double Exponential(double mean);
double current_arrival_time = 0;
double inter_arrival_time = 0;

class cell{
public:
	void process();
	void print_result();
	cell(int i);
	int ch1 = 0;
	int ch2 = 0;
	int ch3 = 0;
	int ch4 = 0;
	int ch5 = 0;
	double ch1_expired_time = 0;
	double ch2_expired_time = 0;
	double ch3_expired_time = 0;
	double ch4_expired_time = 0;
	double ch5_expired_time = 0;
	double arrival_time[150];
	double service_time[150];
	int call_count=0;
	int blockcall_count=0;
	double mean_poisson;
	double mean_exponential;
	int cell_name;
	double blocking_probability;
};

int main()
{
	//ofstream out_file;
	//out_file.open("outfile.txt");


	//random time
	int seed = time(NULL);
	srand(seed);

	//printf("Mean Value = ");
	//cin >> mean;

	//cout<< "inter-arrival time" << "\t"<< "arrival time" <<"\t" << "service time" << endl;
	//out_file << "inter-arrival time"<< "\t" << "service time"<< endl;

	cell cell1(1);
	cell1.process();
	cell cell2(2);
	cell2.process();
	cell cell3(3);
	cell3.process();
	cell cell4(4);
	cell4.process();
	cell cell5(5);
	cell5.process();
	cell cell6(6);
	cell6.process();
	cell cell7(7);
	cell7.process();
	cell cell8(8);
	cell8.process();
	cell cell9(9);
	cell9.process();
	cell cell10(10);
	cell10.process();
	cell cell11(11);
	cell11.process();
	cell cell12(12);
	cell12.process();



	cout << "Total result : " << endl;
	cell1.print_result();
	cell2.print_result();
	cell3.print_result();
	cell4.print_result();
	cell5.print_result();
	cell6.print_result();
	cell7.print_result();
	cell8.print_result();
	cell9.print_result();
	cell10.print_result();
	cell11.print_result();
	cell12.print_result();
	cout << "\nAverage Blocking probability = " << (cell1.blocking_probability + cell2.blocking_probability + cell3.blocking_probability + cell4.blocking_probability + cell5.blocking_probability + cell6.blocking_probability
		+ cell7.blocking_probability + cell8.blocking_probability + cell9.blocking_probability + cell10.blocking_probability + cell11.blocking_probability + cell12.blocking_probability) / 12 <<endl;

	//out_file.close();   //ÃöÀÉ
	system("pause");
	return 0;
}



cell:: cell(int i)
{
	cell_name = i;
	arrival_time[0] = 0;
	mean_poisson = ((i%4) + 1) * 1;
	mean_exponential = ((i%4) + 1)*0.2; //per time the event happened
}

void cell::process()
{
	for (int i = 1; i < 150; i++)
	{
		inter_arrival_time = Poisson(mean_poisson) + 0.5;
		arrival_time[i] =arrival_time[i - 1] + inter_arrival_time;
		if (arrival_time[i] > 100)
			break;
		call_count++;
		service_time[i] = 1 / (Exponential(mean_exponential)); //per time the event happened -> the event happen time
		 //cout << inter_arrival_time << "\t\t\t" << c1.arrival_time[i]<<"\t\t"  << Exponential(mean_exponential) << endl;
		cout << "Call " << call_count << " arrival: arrival time = " << arrival_time[i] << "\tservice time = " << service_time[i] << endl;
		if (arrival_time[i] > ch1_expired_time)
			ch1 = 0;
		if (arrival_time[i] > ch2_expired_time)
			ch2 = 0;
		if (arrival_time[i] > ch3_expired_time)
			ch3 = 0;
		if (arrival_time[i] > ch4_expired_time)
			ch4 = 0;
		if (arrival_time[i] > ch5_expired_time)
			ch5 = 0;



		if (ch1 == 0)
		{
			ch1_expired_time = arrival_time[i] + service_time[i];
			cout << "Call success, used ch1, the call will end at :" << ch1_expired_time << endl;
			ch1 = 1;
		}
		else if (ch2 == 0)
		{
			ch2_expired_time = arrival_time[i] + service_time[i];
			cout << "Call success, used ch2, the call will end at :" << ch2_expired_time << endl;
			ch2 = 1;
		}
		else if (ch3 == 0)
		{
			ch3_expired_time = arrival_time[i] + service_time[i];
			cout << "Call success, used ch3, the call will end at :" << ch3_expired_time << endl;
			ch3 = 1;
		}
		else if (ch4 == 0)
		{
			ch4_expired_time = arrival_time[i] + service_time[i];
			cout << "Call success, used ch4, the call will end at :" << ch4_expired_time << endl;
			ch4 = 1;
		}
		else if (ch5 == 0)
		{
			ch5_expired_time = arrival_time[i] + service_time[i];
			cout << "Call success, used ch5, the call will end at :" << ch5_expired_time << endl;
			ch5 = 1;
		}
		else
		{
			blockcall_count++;
			cout << "All channel are using, call failed." << endl;
			cout << "ch1 will end call at:" << ch1_expired_time << endl;
			cout << "ch2 will end call at:" << ch2_expired_time << endl;
			cout << "ch3 will end call at:" << ch3_expired_time << endl;
			cout << "ch4 will end call at:" << ch4_expired_time << endl;
			cout << "ch5 will end call at:" << ch5_expired_time << endl;
			cout << "current blocked call = " << blockcall_count << endl;
		}
		//out_file << Poisson(mean)+0.5 <<"\t\t\t"<< Exponential(mean) << endl;
		cout << "\n-----------------------------------------------" << endl;
	}
}

void cell::print_result()
{
	cout << "* Cell "<<cell_name<<" * " << endl;
	cout << "Total call : " << call_count << " Blocked call : " << blockcall_count << endl;
	blocking_probability = blockcall_count*1.0 / call_count;
	cout << "Blocking probability = " << blocking_probability << endl;
}

int Poisson(double mean) //Special technique required: Box-Muller method...
{
	double R;
	double sum = 0;
	int i;
	i = -1;
	double z;

	while (sum <= mean)
	{

		R = (float)rand() / (float)(RAND_MAX + 1);
		z = -log(R);
		sum += z;
		i++;
	}
	return i;
}

double Exponential(double mean)
{
	//Generate a random number between 0 and 1.
	//REMEMBER: Always cast the oparands of a division to float, or truncation will be performed.
	double R;
	R = (float)rand() / (float)(RAND_MAX + 1);

	//Put it as a parameter to the inverse distribution function.
	return  -mean*log(R);
}
