#include<iostream>
#include<fstream>
#include<vector>
#include<algorithm>
#include <string>
#include<ctime>
using namespace std;

class Pancake{
public:
	Pancake() {}
	void print() const;
	void process();               //��ʾ���Ž�ķ�ת����
	int run(const int cake_arr[], int size, bool show = true);
	void calc_range(int na, int nb);

private:
	Pancake(const Pancake&);
	Pancake& operator=(const Pancake&);
	inline bool init(const int cake_arr[], int& size);
	void search_cake(int size, int step, int least_swap_old);
	void reverse_cake(int index) { //��ת0��index����ӱ�
		++count_reverse;
		std::reverse(&cake[0], &cake[index] + 1);
	}

	bool next_search_cake(int pos, int size, int step, int least_swap)
	{
		if (least_swap + step >= get_min_swap()) return true;
		cake_swap[step] = pos;
		reverse_cake(pos);
		search_cake(size, step, least_swap);
		reverse_cake(pos);
		return false;
	}

	int get_min_swap() const { return result.size(); }

	void output(int i, const std::string& sep, int width) const {
		cout.width(width);
		cout << i << sep;
	}

	void output(const std::string& sep, int width) const {
		cout.width(width);
		cout << sep;
	}

	vector<int> cake_old;        //Ҫ�����ԭ�ӱ�����
	vector<int> cake;            //��ǰ�����ӱ���״̬
	vector<int> result;          //���Ž��У�ÿ�η�ת���ӱ�λ��
	vector<int> cake_swap;       //ÿ�η�ת���ӱ�λ��
	vector<int> cake_order;      //��step+1�η�תʱ����תλ�õ�����˳��
	int min_swap_init;           //���Ž�ķ�ת������ʼֵ
	int count_search;            //search_cake�����ô���
	int count_reverse;           //reverse_cake�����ô���
};


void Pancake::print() const
{
	int min_swap = get_min_swap();
	if (min_swap == 0) return;
	cout << "minimal_swap initial: " << min_swap_init
		<< "  final: " << min_swap
		<< "\nsearch/reverse function was called: " << count_search
		<< "/" << count_reverse << " times\nsolution: ";
	for (int i = 0; i < min_swap; ++i) cout << result[i] << " ";
	cout << "\n\n";
}

void Pancake::process()
{
	int min_swap = get_min_swap();
	if (min_swap == 0) return;
	cake.assign(cake_old.begin(), cake_old.end());
	int cake_size = cake_old.size();
	const int width = 3, width2 = 2 * width + 3;
	output("No.", width2);
	for (int j = 0; j < cake_size; ++j) output(j, " ", width);
	cout << "\n";
	output("old:", width2);

	for (int j = 0; j < cake_size; ++j) output(cake[j], " ", width);
	cout << "\n";

	for (int i = 0; i < min_swap; ++i){
		reverse_cake(result[i]);
		output(i + 1, " ", width);
		output(result[i], ": ", width);
		for (int j = 0; j < cake_size; ++j)  output(cake[j], " ", width);
		cout << "\n";
	}
	cout << "\n\n";
}

bool Pancake::init(const int cake_arr[], int& size)
{
	result.clear();
	if (cake_arr == NULL) return false;
	cake_swap.resize(size * 2);
	cake_order.resize(size * size * 2);
	count_search = 0;
	count_reverse = 0;
	cake_old.assign(cake_arr, cake_arr + size);
	//ȥ��ĩβ�Ѿ�λ���ӱ��������ӱ������С��
	while (size > 1 && size - 1 == cake_arr[size - 1]) --size;
	if (size <= 1) return false;

	cake.assign(cake_arr, cake_arr + size);
	for (int j = size - 1;;) {           //����һ������Ϊmin_swap��ʼֵ��
		while (j > 0 && j == cake[j]) --j;
		if (j <= 0) break;
		int i = j;
		while (i >= 0 && cake[i] != j) --i;
		if (i != 0) {
			reverse_cake(i);
			result.push_back(i);
		}
		reverse_cake(j);
		result.push_back(j);
		--j;
	}
	cake.assign(cake_arr, cake_arr + size); //�ָ�ԭ��������
	cake.push_back(size);                 //���һ���ӱ����������ı߽��ж�
	cake_swap[0] = 0;                     //�����0����ת���ӱ����Ϊ0
	min_swap_init = get_min_swap();
	return true;
}

int Pancake::run(const int cake_arr[], int size, bool show)
{
	if (!init(cake_arr, size)) return 0;
	int least_swap = 0;
	for (int i = 0; i < size; ++i)
		if (cake[i] - cake[i + 1] + 1u > 2) 
			++least_swap;
	if (get_min_swap() != least_swap) search_cake(size, 0, least_swap);
	if (show) print();
	return get_min_swap();
}

void Pancake::search_cake(int size, int step, int least_swap_old)
{
	++count_search;
	while (size > 1 && size - 1 == (int)cake[size - 1]) --size; //ȥ��ĩβ�Ѿ�λ���ӱ�
	int *first = &cake_order[step * cake.size()];
	int *last = first + size;
	int *low = first, *high = first + size;

	for (int pos = size - 1, last_swap = cake_swap[step++]; pos > 0; --pos){
		if (pos == last_swap) continue;
		int least_swap = least_swap_old;
		if (cake[pos] - cake[pos + 1] + 1u <= 2) ++least_swap;
		if (cake[0] - cake[pos + 1] + 1u <= 2) --least_swap;

		if (least_swap + step >= get_min_swap()) continue;
		if (least_swap == 0) {
			cake_swap[step] = pos;
			result.assign(&cake_swap[1], &cake_swap[step + 1]);
			return;
		}

		//����least_swapֵ��С���ֱ𱣴�posֵ�����ȴ���ʹleast_swap_old��С1�ķ�ת
		if (least_swap == least_swap_old) *low++ = pos;
		else if (least_swap > least_swap_old) *--high = pos;
		else next_search_cake(pos, size, step, least_swap);
	}

	//�ٴ���ʹleast_swap_old����ķ�ת
	for (int *p = first; p < low; p++)
	if (next_search_cake(*p, size, step, least_swap_old)) return;

	//�����ʹleast_swap_old����1�ķ�ת
	for (int *p = high; p < last; p++)
	if (next_search_cake(*p, size, step, least_swap_old + 1)) return;
}

void Pancake::calc_range(int na, int nb)
{
	if (na > nb || na <= 0) return;
	clock_t ta = clock();
	static std::vector<int> arr;
	arr.resize(nb);
	unsigned long long total_search = 0;
	unsigned long long total_reverse = 0;
	for (int j = na; j <= nb; ++j) {
		for (int i = 0; i < j; ++i) arr[i] = i;
		int max = 0;
		unsigned long long count_s = 0;
		unsigned long long count_r = 0;
		clock_t tb = clock();
		while (std::next_permutation(&arr[0], &arr[j])) {
			int tmp = run(&arr[0], j, 0);
			if (tmp > max) max = tmp;
			count_s += count_search;
			count_r += count_reverse;
		}
		total_search += count_s;
		total_reverse += count_r;
		output(j, " ", 2);
		output(max, "     time: ", 3);
		output(clock() - tb, "  ms  ", 8);
		cout << " search/reverse: " << count_s << "/" << count_r << "\n";
	}
	cout << "  total  search/reverse: " << total_search
		<< "/" << total_reverse << "\n"
		<< "time :  " << clock() - ta << "  ms\n";
}

int main()
{
	int aa[10] = { 3, 2, 1, 6, 5, 4, 9, 8, 7, 0 };
	//int ab[10]={ 4,8,3,1,5,2,9,6,7,0};
	// int ac[]={1,0, 4, 3, 2};
	Pancake cake;
	cake.run(aa, 10);
	cake.process();
	//cake.run(ab,10);
	//cake.process(); 
	//cake.run(ac,sizeof(ac)/sizeof(ac[0]));
	//cake.process();  
	cake.calc_range(1, 9);
}