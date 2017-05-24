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
	void check_call_end(double current_time);
	int calling(double arrival_time, double service_time);
	void print_result();
	void schedule_generate();
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
	int call_flag = 0;
	int check_table(double current_time);
	int remain_channel=5;
};

class cluster{
public:
	cluster(int a, int b, int c);
	void show_result();
	double current_time = 0;
	int check_cell;
	int calling_check;
	int borrow_count = 0;
	int block_count = 0;
	int cell_name1;
	int cell_name2;
	int cell_name3;
	int total_call_count;
	double Borrowing_probability;
	double Blocking_probability;
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

	cluster cluster1(1, 2, 3);
	cluster cluster2(4, 5, 6);
	cluster cluster3(7, 8, 9);
	cluster cluster4(10, 11, 12);

	cluster1.show_result();
	cluster2.show_result();
	cluster3.show_result();
	cluster4.show_result();

	cout << endl;
	cout << "Total call : " << cluster1.total_call_count+ cluster2.total_call_count+ cluster3.total_call_count+ cluster4.total_call_count<<endl;
	cout << "Total Borrowed call : " << cluster1.borrow_count+ cluster2.borrow_count+ cluster3.borrow_count+ cluster4.borrow_count << endl;
	cout << "Total Blocked call : " << cluster1.block_count+ cluster2.block_count + cluster3.block_count + cluster4.block_count << endl;
	cout << "Total Average Borrowing probability = " <<(cluster1.Borrowing_probability+ cluster2.Borrowing_probability+ cluster3.Borrowing_probability+ cluster4.Borrowing_probability) /4 << endl;
	cout << "Total Average Blocking probability = " << (cluster1.Blocking_probability+ cluster2.Blocking_probability+ cluster3.Blocking_probability+ cluster4.Blocking_probability) /4<< endl;

	//out_file.close();   //ÃöÀÉ
	system("pause");
	return 0;
}


cell:: cell(int i)
{
	cell_name = i;
	arrival_time[0] = 0;
	mean_poisson = ((i%4) + 1) * 1.0;
	mean_exponential = ((i%4) + 1)*0.2; 
}

void cell::schedule_generate()
{
	for (int i = 1; i < 150; i++)
	{
		inter_arrival_time = Poisson(mean_poisson) + 0.5;
		arrival_time[i] = arrival_time[i - 1] + inter_arrival_time;
		if (arrival_time[i] > 100)
			break;
		call_count++;
		service_time[i] = (Exponential(mean_exponential)); //per time the event happened -> the event happen time
	}
}

int cell::check_table(double current_time)
{
	for (int i = 0; i < call_count; i++)
	{
		if (arrival_time[i] == current_time)
			return i; //flag
	}
	return -1; //not found
}

void cell::check_call_end(double current_time)
{
	//cout << "Call " << call_count << " arrival: arrival time = " << arrival_time[i] << "\tservice time = " << service_time[i] << endl;
	if (current_time > ch1_expired_time && ch1== 1)
	{
		ch1 = 0;
		remain_channel++;
	}
	if (current_time > ch2_expired_time && ch2 == 1)
	{
		ch2 = 0;
		remain_channel++;
	}
	if (current_time > ch3_expired_time && ch3 == 1)
	{
		ch3 = 0;
		remain_channel++;
	}
	if (current_time > ch4_expired_time && ch4 == 1)
	{
		ch4 = 0;
		remain_channel++;
	}
	if (current_time > ch5_expired_time && ch5 == 1)
	{
		ch5 = 0;
		remain_channel++;
	}
}


int cell::calling(double arrival_time,double service_time)
{
		if (ch1 == 0)
		{
			ch1_expired_time = arrival_time + service_time;
			cout << "Call success, use BS "<<cell_name<<" ch" << 1 + ((cell_name - 1) % 3) * 5 << ", the call will end at :" << ch1_expired_time << endl;
			ch1 = 1;
			remain_channel--;
		}
		else if (ch2 == 0)
		{
			ch2_expired_time = arrival_time + service_time;
			cout << "Call success, use BS " << cell_name << " ch" << 2 + ((cell_name - 1) % 3) * 5 << ", the call will end at :" << ch2_expired_time << endl;
			ch2 = 1;
			remain_channel--;
		}
		else if (ch3 == 0)
		{
			ch3_expired_time = arrival_time + service_time;
			cout << "Call success, use BS " << cell_name << " ch" << 3 + ((cell_name - 1) % 3) * 5 << ", the call will end at :" << ch3_expired_time << endl;
			ch3 = 1;
			remain_channel--;
		}
		else if (ch4 == 0)
		{
			ch4_expired_time = arrival_time + service_time;
			cout << "Call success, use BS " << cell_name << " ch" << 4 + ((cell_name - 1) % 3) * 5 << ", the call will end at :" << ch4_expired_time << endl;
			ch4 = 1;
			remain_channel--;
		}
		else if (ch5 == 0)
		{
			ch5_expired_time = arrival_time + service_time;
			cout << "Call success, use ch" << 5 + ((cell_name - 1) % 3) * 5 << ", the call will end at :" << ch5_expired_time << endl;
			ch5 = 1;
			remain_channel--;
		}
		else
		{
			cout << "All channel are using......" << endl;
			cout << "ch"<<1+ ((cell_name - 1) % 3) * 5 <<" will end call at:" << ch1_expired_time << endl;
			cout << "ch"<<2+ ((cell_name - 1) % 3) * 5 <<" will end call at:" << ch2_expired_time << endl;
			cout << "ch" << 3 + ((cell_name - 1) % 3) * 5 << " will end call at:" << ch3_expired_time << endl;
			cout << "ch" << 4 + ((cell_name - 1) % 3) * 5 << " will end call at:" << ch4_expired_time << endl;
			cout << "ch" << 5 + ((cell_name-1) % 3)*5 << " will end call at:" << ch5_expired_time << endl;
			return -1; //call failed,need to borrow channel.
			//blockcall_count++;
			//cout << "current blocked call = " << blockcall_count << endl;
		}
		//out_file << Poisson(mean)+0.5 <<"\t\t\t"<< Exponential(mean) << endl;
		cout << "-----------------------------------------------" << endl;
		return 0;
}

void cell::print_result()
{
	cout << "* BS "<<cell_name<<" * " << endl;
	cout << "Total call : " << call_count << " Blocked call : " << blockcall_count << endl;
	blocking_probability = blockcall_count*1.0 / call_count;
	cout << "Blocking probability = " << blocking_probability << endl;
}

int Poisson(double mean) 
{
	double R;
	double sum = 0;
	int i;
	i = -1;
	double z;

	while (sum <= mean)
	{

		R = (double)rand() / (double)(RAND_MAX + 1);
		z = -log(R);
		sum += z;
		i++;
	}
	return i;
}

double Exponential(double mean)
{
	double p;
	p = (double)rand() / (double)(RAND_MAX + 1);
	double temp = log(1 - p);
	temp = -(temp) / (mean);


	return temp;
}


cluster:: cluster(int a, int b, int c)
{
	cell cell1(a);
	cell cell2(b);
	cell cell3(c);
	cell1.schedule_generate();
	cell2.schedule_generate();
	cell3.schedule_generate();
	cell_name1 = a;
	cell_name2 = b;
	cell_name3 = c;

	while (1)
	{

		if (current_time > 100)
			break;
		//cout << "Current time = " << current_time << endl;

		cell1.check_call_end(current_time);
		cell2.check_call_end(current_time);
		cell3.check_call_end(current_time);

		///////////////////////////////////////////////////////////////////////////////
		check_cell = cell1.check_table(current_time);
		if (check_cell != -1)
		{
			cout << "There is a call for BS " << cell1.cell_name << ", arrival time = " << cell1.arrival_time[check_cell] << " service time = " << cell1.service_time[check_cell] << endl;
			calling_check = cell1.calling(cell1.arrival_time[check_cell], cell1.service_time[check_cell]);
			if (calling_check == -1)
			{
				cout << "Now trying to borrow channel......" << endl;
				borrow_count++;

				if (cell2.remain_channel >= cell3.remain_channel)
					calling_check = cell2.calling(cell1.arrival_time[check_cell], cell1.service_time[check_cell]);
				else
					calling_check = cell3.calling(cell1.arrival_time[check_cell], cell1.service_time[check_cell]);

				if (calling_check == -1)
				{
					borrow_count--;
					block_count++;
					cout << "All channel are using, call failed.";
				}
			}
		}
		///////////////////////////////////////////////////////////////////////////////
		check_cell = cell2.check_table(current_time);
		if (check_cell != -1)
		{
			cout << "There is a call for BS " << cell2.cell_name << ", arrival time = " << cell2.arrival_time[check_cell] << " service time = " << cell2.service_time[check_cell] << endl;
			calling_check = cell2.calling(cell2.arrival_time[check_cell], cell2.service_time[check_cell]);
			if (calling_check == -1)
			{
				cout << "Now trying to borrow channel......" << endl;
				borrow_count++;

				if (cell1.remain_channel >= cell3.remain_channel)
					calling_check = cell1.calling(cell2.arrival_time[check_cell], cell2.service_time[check_cell]);
				else
					calling_check = cell3.calling(cell2.arrival_time[check_cell], cell2.service_time[check_cell]);

				if (calling_check == -1)
				{
					borrow_count--;
					block_count++;
					cout << "All channel are using, call failed.";
				}
			}
		}
		///////////////////////////////////////////////////////////////////////////////
		check_cell = cell3.check_table(current_time);
		if (check_cell != -1)
		{
			cout << "There is a call for BS " << cell3.cell_name << ", arrival time = " << cell3.arrival_time[check_cell] << " service time = " << cell3.service_time[check_cell] << endl;
			calling_check = cell3.calling(cell3.arrival_time[check_cell], cell3.service_time[check_cell]);
			if (calling_check == -1)
			{
				cout << "Now trying to borrow channel......" << endl;
				borrow_count++;

				if (cell1.remain_channel >= cell2.remain_channel)
					calling_check = cell1.calling(cell3.arrival_time[check_cell], cell3.service_time[check_cell]);
				else
					calling_check = cell2.calling(cell3.arrival_time[check_cell], cell3.service_time[check_cell]);

				if (calling_check == -1)
				{
					borrow_count--;
					block_count++;
					cout << "All channel are using, call failed.";
				}
			}
		}
		///////////////////////////////////////////////////////////////////////////////
		current_time += 0.5;

	}
	total_call_count = cell1.call_count + cell2.call_count + cell3.call_count;
}

void cluster::show_result()
{
	cout << "*Result For cluster: BS" << cell_name1 << " , BS" << cell_name2 << " , BS" << cell_name3 << " * " << endl;
	cout << "Total call : " << total_call_count;
	cout << " Borrowed call : " << borrow_count;
	cout << " Blocked call : " << block_count << endl;
	Borrowing_probability = borrow_count*1.0 / total_call_count;
	cout << "Cluster Average Borrowing probability = " << Borrowing_probability << endl;
	Blocking_probability = block_count*1.0 / total_call_count;
	cout << "Cluster Average Blocking probability = " << Blocking_probability << endl<<endl;
}