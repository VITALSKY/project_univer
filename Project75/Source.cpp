#include<iostream>
#include<fstream>
#include<string>
#include<vector>
#include<ctime>
using namespace std;
vector<int> Wes;
vector<int> C;
vector<int> W;
vector<double>average_fit;
vector<string>ostanova;
vector<string>kodir;
vector<string>newpop;
vector<int>fitness;
vector<int>start_fitness;
int best_osob;
int best_osob_index;
int z = 0;
int random;
int l = 0;
int randplace = 0;
double sumQ;
const int max_pop = 24;
const int len = 15;
int Wmax;
int score = 0;
int sumW = 0, Q = 0;
int CR, MT, SL;
double AverageFitness = 0;
void reading_data()
{
		setlocale(0, "");
		string path = "text.txt";
		ifstream fin;
		fin.open(path);
		int start = 0;
		while (C.size() != 0)
		{
			C.pop_back();
			W.pop_back();
		}
		if (fin.is_open())
		{
			string str;
			while (!fin.eof())
			{
				str = "";
				if (start == 0)
				{
					getline(fin, str);
					Wmax = atoi(str.c_str());
					start++;
				}
				else
				{
					if (start % 3 == 1)
					{
						fin >> str;
					}
					else if (start % 3 == 2) {
						fin >> str;
						C.push_back(atoi(str.c_str()));
					}
					else if (start % 3 == 0)
					{
						fin >> str;
						W.push_back(atoi(str.c_str()));
					}
					start++;
				}
			}
		}
		fin.close();
}
void create_kodirovka1(vector<int>&C,vector<int>&W)
{
	Q = 0;
	int cmax = 0, index;
	string S;
	for (int j = 0; j < max_pop; j++)
	{
		if (C.size() != 0 && W.size() != 0)
		{
			for (int i = 0; i < C.size(); i++)
			{
				C.pop_back();
				W.pop_back();
			}
		}
		string S = "";
		reading_data();
		for (int i = 0; i < len; i++)
		{
			S += '0';
		}
		for (int i = 0; i < len; i++)
		{
			for (int j = 0; j < len; j++)
			{
				if (cmax < C[j])
				{
					cmax = C[j];
					index = j;
				}
			}
			if (sumW + W[index] <= Wmax)
			{
				sumW = sumW + W[index];
				Q = Q + cmax;
				S[index] = '1';
				C[index] = -1;
				W[index] = -1;
				cmax = 0;
			}
		}
		for (int i = 0; i < len; i++)
		{
			random = rand() % 3;
			if (random == 1)
			{
				S[i] = '1';
			}
		}
		kodir.push_back(S);
		cout << kodir[j] << endl;
	}
}
void create_kodirovka2(vector<int>&C, vector<int>&W)
{
	reading_data();
	string kodirovka;
	for (int i = 0; i < max_pop; i++)
	{
		kodirovka = "";
		for (int j = 0; j < len; j++)
		{
			random = rand() % 2;
			if (random == 1)
			{
				kodirovka += "1";
			}
			else
			{
				kodirovka += "0";
			}
		}
		kodir.push_back(kodirovka);
		cout << kodir[i] << endl;
	}
}
void crossover1()
{
	if (newpop.size() != 0)
	{
		for (int i = 0; i < newpop.size(); i++)
		{
			newpop.pop_back();
		}
	}
	for (int j = 0; j < max_pop; j++)
	{
		string newkodir = "";
		z = rand() % max_pop;
		l = rand() % max_pop;
		randplace = rand() % (len - 2);
		for (int i = 0; i < randplace; i++)
		{
			newkodir += kodir[z][i];
		}
		for (int i = randplace; i < len; i++)
		{
			newkodir += kodir[l][i];
		}
		newpop.push_back(newkodir);
	}
}
void crossover2()
{
	if (newpop.size() != 0)
	{
		for (int i = 0; i < newpop.size(); i++)
		{
			newpop.pop_back();
		}
	}
	for (int j = 0; j < max_pop; j++)
	{
		int z = rand() % max_pop;
		int l = rand() % max_pop;
		string newkodir = "";
		for (int i = 0; i < len; i++)
		{
			random = rand() % 2;
			if (random == 0)
			{
				newkodir += kodir[z][i];
			}
			else if (random == 1)
			{
				newkodir += kodir[l][i];
			}
		}
		newpop.push_back(newkodir);
	}
}
void gennaya_mut()
{
	int veroyatnost;
	for (int i = 0; i < newpop.size(); i++)
	{
		veroyatnost = 1 + rand() % 9;
		if (veroyatnost == 7) {
			int random = rand() % len;
			if (newpop[i][random] == '0')
			{
				newpop[i][random] = '1';
			}
			else
				newpop[i][random] = '0';
		}
	}
}
void hromosomnaya_mut()
{
	int veroyatnost;
	for (int i = 0; i < newpop.size(); i++)
	{
		veroyatnost = 1 + rand() % 9;
		if (veroyatnost == 7) {
			for (int j = 0; j < len; j++)
			{
				if (newpop[i][j] == '0')
				{
					newpop[i][j] = '1';
				}
				else
					newpop[i][j] = '0';
			}
		}
	}
}
void counting_start_fitness()
{
	if (start_fitness.size() != 0)
	{
		for (int i = 0; i < start_fitness.size(); i++)
		{
			start_fitness.pop_back();
		}
	}
	int fit;
	string str = "";
	int locus;
	for (int i = 0; i < max_pop; i++)
	{
		fit = 0;
		for (int j = 0; j < len; j++)
		{
			str = kodir[i][j];
			locus = atoi(str.c_str());
			fit += locus * C[j];
		}
		start_fitness.push_back(fit);
	}
}
void counting_fitness()
{
	if (fitness.size() != 0)
	{
		for (int i = 0; i < fitness.size(); i++)
		{
			fitness.pop_back();
		}
	}
	int fit;
	string str = "";
	int locus;
	for (int i = 0; i < max_pop; i++)
	{
		fit = 0;
		for (int j = 0; j < len; j++)
		{
			str = newpop[i][j];
			locus = atoi(str.c_str());
			fit += locus * C[j];
		}
		fitness.push_back(fit);
	}
}
void counting_wes()
{
	if (Wes.size() != 0)
	{
		for (int i = 0; i < Wes.size(); i++)
		{
			Wes.pop_back();
		}
	}
	int fit;
	string str = "";
	int locus;
	for (int i = 0; i < max_pop; i++)
	{
		fit = 0;
		for (int j = 0; j < len; j++)
		{
			str = kodir[i][j];
			locus = atoi(str.c_str());
			fit += locus * W[j];
		}
		Wes.push_back(fit);
	}
}
void b_turnir(vector<int>&fitness, vector<string>&kodir,vector<int>&start_fitness)
{
	counting_wes();
	int index;
	int max = 0;
	int min = 1000;
	int index_loser;
	int ran;
	for (int i = 0; i < max_pop; i++)
	{
		random = 1 + rand() % max_pop - 1;
		if (random == 13)
		{
			ran = 1 + rand() % max_pop;
			max = 0;
			for (int j = 0; j < ran; j++)
			{
				if (fitness[j] > max)
				{
					max = fitness[j];
					index = j;
				}
			}
			fitness[index] = -1;
			min = 1000;
			for (int k = 0; k < max_pop; k++)
			{
				if (start_fitness[k] < min && start_fitness[k] != -1)
				{
					min = start_fitness[k];
					index_loser = k;
				}
				if (max > min && Wes[index] < Wmax)
				{
					kodir[index_loser] = newpop[index];
					start_fitness[index_loser] = max;
				}
			}
		}
	}
}
void ruletka_sellection(vector<string>&kodir, vector<int>&fitness,vector<int>&start_fitness)
{
	counting_wes();
	sumQ = 0;
	for (int i = 0; i < max_pop; i++)
	{
		sumQ += fitness[i];
	}
	double mas[max_pop];
	mas[0] = fitness[0] / sumQ;
	for (int i = 1; i < max_pop - 1; i++)
	{
		mas[i] = mas[i - 1] + (fitness[i] / sumQ);
	}
	mas[max_pop - 1] = mas[max_pop - 2] + (fitness[max_pop - 1] / sumQ);
	double ran;
	for (int i = 0; i < max_pop; i++)
	{
		ran = 0.001*(rand() % 1001);
		for (int i = 0; i < max_pop - 1; i++)
		{
			if (mas[i] < ran < mas[i + 1] && Wes[i+1] < Wmax)
			{
				kodir[i] = newpop[i + 1];
				start_fitness[i] = fitness[i + 1];
				break;
			}
		}
	}
}

int main()
{
	int count = 0;
	setlocale(0, "");
	srand(time(NULL));
	int step;
	cout << "Введите кол-во шагов." << endl;
	cin >> step;
	cout << "Выберите метод формирования начальной популяции. " << endl;
	cout << "Случайный - press 0 or Жадный алгоритм для ЗоР - press 1. " << endl;
	int choice;
	cin >> choice;
	switch (choice)
	{
	case 1:
	{
		create_kodirovka1(C,W);
		counting_start_fitness();
		counting_wes();
		break;
	}
	case 0:
	{
		create_kodirovka2(C,W);
		counting_start_fitness();
		counting_wes();
		break;
	}
	}
	cout << "Выберите оператор кроссовера. " << endl;
	cout << "Одноточечный - press 0 or Однородный press 1. " << endl;
	cin >> choice;
	switch (choice)
	{
	case 1:
	{
		CR = 1;
		crossover1();
		break;
	}
	case 0:
	{
		CR = 0;
		crossover2();
		break;
	}
	}
	cout << "Выберите оператор мутации. " << endl;
	cout << "Генная - press 0 or Хромосомная press 1. " << endl;
	cin >> choice;
	switch (choice)
	{
	case 1:
	{
		MT = 1;
		hromosomnaya_mut();
		counting_fitness();
		break;
	}
	case 0:
	{
		MT = 0;
		gennaya_mut();
		counting_fitness();
		break;
	}
	}
	cout << "Выберите оператор селекции. " << endl;
	cout << "В-Турнир - press 0 or Рулетка press 1. " << endl;
	cin >> choice;
	switch (choice)
	{
	case 1:
	{
		AverageFitness = 0;
		best_osob = 0;
		SL = 1;
		ruletka_sellection(kodir, fitness, start_fitness);
		for (int i = 0; i < max_pop; i++)
		{
			if (best_osob < start_fitness[i])
			{
				best_osob = start_fitness[i];
				best_osob_index = i;
			}
			AverageFitness += start_fitness[i];
			cout << kodir[i] << endl;
		}
		average_fit.push_back(AverageFitness / max_pop);
		cout << "1-ое поколение." << "Лучшая особь : " << kodir[best_osob_index] <<" , " << start_fitness[best_osob_index] << endl;
		break;
	}
	case 0:
	{
		AverageFitness = 0;
		best_osob = 0;
		SL = 0;
		b_turnir(fitness, kodir, start_fitness);
		for (int i = 0; i < max_pop; i++)
		{
			if (best_osob < start_fitness[i])
			{
				best_osob = start_fitness[i];
				best_osob_index = i;
			}
			AverageFitness += start_fitness[i];
			cout << kodir[i] << endl;
		}
		average_fit.push_back(AverageFitness / max_pop);
		cout << "1-ое поколение." << "Лучшая особь : " << kodir[best_osob_index] <<" , "<< start_fitness[best_osob_index]<< endl;
		break;
	}
	}
	for (int i = 1; i < step; i++)
	{
		if (CR == 1)
		{
			counting_start_fitness();
			crossover1();
		}
		else if (CR == 0)
		{
			counting_start_fitness();
			crossover2();
		}
		if (MT == 1)
		{
			hromosomnaya_mut();
			counting_fitness();
		}
		else if (MT == 0)
		{
			gennaya_mut();
			counting_fitness();
		}
		if (SL == 1)
		{
			AverageFitness = 0;
			best_osob = 0;
			ruletka_sellection(kodir, fitness, start_fitness);
			for (int i = 0; i < max_pop; i++)
			{
				if (best_osob < start_fitness[i])
				{
					best_osob = start_fitness[i];
					best_osob_index = i;
				}
				AverageFitness += start_fitness[i];
				cout << kodir[i] << endl;
			}
			average_fit.push_back(AverageFitness / max_pop);
			cout << i + 1 << "-ое поколение." << "Лучшая особь : " << kodir[best_osob_index] << " , " << start_fitness[best_osob_index] << endl;
			ostanova.push_back(kodir[best_osob_index]);
		}
		else if (SL == 0)
		{
			AverageFitness = 0;
			best_osob = 0;
			b_turnir(fitness, kodir, start_fitness);
			for (int i = 0; i < max_pop; i++)
			{
				if (best_osob < start_fitness[i])
				{
					best_osob = start_fitness[i];
					best_osob_index = i;
				}
				AverageFitness += start_fitness[i];
				cout << kodir[i] << endl;
			}
			average_fit.push_back(AverageFitness / max_pop);
			cout << i + 1 << "-ое поколение." << "Лучшая особь : " << kodir[best_osob_index] << " , " << start_fitness[best_osob_index] << endl;
			ostanova.push_back(kodir[best_osob_index]);
		}
		bool log = false;
		bool stop = false;
		for (int i = 0; i < ostanova.size() - 1; i++)
		{

			if (ostanova[i] == ostanova[i + 1])
			{
				log = true;
				count++;
			}
			if (log == false)
			{
				count = 0;
			}
			log = false;
			if (count == 5)
			{
				stop = true;
				cout << "5 шагов не менялось лушчее решение." << endl;
				break;
			}
		}
		if (stop == true)
			break;
		int proverka = false;
		if (average_fit.size() > 1)
		{
			for (int i = 0; i < average_fit.size() - 1; i++)
			{
				if (average_fit[i] > average_fit[i + 1])
				{
					proverka = true;
					score++;
				}
				if (proverka == false)
				{
					score = 0;
				}
				proverka = false;
				if (score == 5)
				{
					stop = true;
					cout << "5 шагов не увеличивалась средняя приспособленность." << endl;
					break;
				}
			}
		}
		if (stop == true)
			break;
	}

	system("pause");
	return 0;
}