#include <iostream>
const int     tabu_len= 3;
const int     CityNum = 4;
const int 	  MAX_GEN = 8;
const int NeighborNum = 3;
using namespace std;
// ���ɱ� 
double **tabu_lst;
double D[CityNum][CityNum] = {{0, 1, 0.5, 1}, {1, 0, 1, 1}, {1.5, 5, 0, 1}, {1, 1, 1, 0}};

bool in_TabuList(int* tempGh) {
	// �ж�·���Ƿ��ڽ��ɱ���
	int i, j;
	bool flag;
	for (i=0; i<tabu_len; i++) {
		flag = false;
		for (j=0; j<CityNum && !flag; j++) {
			if(tempGh[j] != tabu_lst[i][j]) {
				flag = true;
			}
		}
		if (!flag) {
			break;
		}
	}
	return !(i == tabu_len);
}

void pushTabuList(int* arr) {
	int i, k;
	// ɾ�����е�һ������
	for(i = 0; i < tabu_len - 1; i++) {
		for(int j = 0; j < CityNum; j++) {
			tabu_lst[i][j] = tabu_lst[i + 1][j];
		}
	}
	// �������β��
	for(k = 0; k < CityNum; k++) {
		tabu_lst[tabu_len - 1][k] = arr[k];
	}
}

double cal(int *lst) {
	// ����·��֮��
	int i;
	double sum = 0;
	for (i=0; i<CityNum+1; i++) {
		sum += D[lst[i]][lst[i+1]];
	}
	return sum;
}

void print_lst(int *lst) {
	int i;
	for (i = 0; i<CityNum-1; i++) {
		cout << lst[i] << "->";
	}
	cout << lst[i] << endl;
}

void swap_gh(int *lst_old, int *lst_new, double x_old, double &x_new) {
	int i;
	for (i = 0; i<CityNum+1; i++) {
		lst_new[i] = lst_old[i];
	}
	x_new = x_old;
}

int main() {

	int i, j, nn, t=0;
	// ��õ�ֵ�����ս������ÿһ�ε�����õĽ����ÿ�ν�����ļ���ֵ
	double x_best=INT_MAX, x_now, x_tmp;
	// ��õ�·�������ս������ÿһ�ε�����õ�·����ÿ�ν�����ļ���ֵ
	int lst_best[CityNum+1] = {0, 1, 2, 3, 0};
	int lst_now[CityNum+1] = {0, 1, 2, 3, 0};
	int lst_tmp[CityNum+1];

	tabu_lst = new double*[tabu_len];
	for(i = 0; i < tabu_len; i++) {
		tabu_lst[i] = new double[CityNum];
	}

	// ���е������޶������������趨ֵ�����ֵ����һ����ϵ���������ε���û�б仯/�仯����
	while (t < MAX_GEN) {
		nn = 0;
		x_now = INT_MAX;
		// ÿ�ζ��⿪��һ��ռ䱣������·�������ڵ���·��
		for (i = 0; i<CityNum+1; i++) {
			lst_tmp[i] = lst_now[i];
		}
		print_lst(lst_tmp);
		// �����޶�����ķ�Χ������nn��������·��
		for (i = 1; i < CityNum && nn < NeighborNum; i++) {
			for (j = i+1; j < CityNum && nn < NeighborNum; j++) {
				swap(lst_tmp[i], lst_tmp[j]);
				// ������ڽ��ɱ��У����м������С�ڵ�ǰ��ֵ���ͽ����滻�����滻·��
				if (!in_TabuList(lst_tmp)) {
					x_tmp = cal(lst_tmp);
					if (x_tmp < x_now) {
						swap_gh(lst_tmp, lst_now, x_tmp, x_now);
					}
				}
				swap(lst_tmp[j], lst_tmp[i]);
				print_lst(lst_tmp);
				nn++;
			}
		}
		if (x_now < x_best) {
			swap_gh(lst_now, lst_best, x_now, x_best);
		}
		pushTabuList(lst_now);
		t++;
	}

	cout << "���·�����: "<< x_best <<endl;
	cout << "���·����";
	print_lst(lst_best);
}
