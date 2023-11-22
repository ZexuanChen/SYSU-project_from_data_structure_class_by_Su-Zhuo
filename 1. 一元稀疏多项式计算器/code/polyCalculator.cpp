#include "polyCalculator.h"

polyCalculator::polyCalculator() //���캯�� 
{
	clear();
}

polyCalculator::~polyCalculator() {} //��������

void polyCalculator::clear() //��ճ�Ա����
{
	poly[0].clear(), poly[1].clear(), res.clear();
}

void polyCalculator::input(int t) //�������ʽ
{
	int n;
	PII pair;
	cin >> n;
	for (int i = 1; i <= n; i++) {
		cin >> pair.second >> pair.first;
		if (pair.second != 0) poly[t].push_back(pair);
	}
	sort(poly[t].begin(), poly[t].end());
}

void polyCalculator::output() //�������ʽ 
{
	//����ʽΪ0�����
	if (res.size() == 0) {
		cout << "0\n";
		return;
	}
	
	//Ϊ�˱�֤�����ʽ���������һ��
	if (res[0].first == 0) cout << res[0].second;
	else {
	    cout << res[0].second << "x^";
		cout << res[0].first;
	}
	
	//���������� 
	for (int i = 1; i < res.size(); i++) {
		if (res[i].second > 0) cout << " + ";
		else cout << " - ";
		
		if (res[i].first == 0) cout << fabs(res[i].second);
		else {
		    cout << fabs(res[i].second) << "x^";
			cout << res[i].first;
		}
	}
	cout << endl;
}

void polyCalculator::plus() //����ʽ���
{ 	
	int pa = 0, pb = 0;
	//ͬʱ������������ʽ��ָ��С�ļ��뵽�������ʽ�У�ָ����ͬ��ϵ����Ӳ��ӵ��������ʽ�� 
	while (pa < poly[0].size() && pb < poly[1].size()) {
		if (poly[0][pa].first < poly[1][pb].first) {
			res.push_back(poly[0][pa++]);
		}
		else if (poly[0][pa].first > poly[1][pb].first) {
			res.push_back(poly[1][pb++]);
		}
		else {
			double exp = poly[0][pa].first, num = poly[0][pa++].second + poly[1][pb++].second;
			if (num != 0) res.push_back({exp, num}); //ϵ�����Ϊ0�������� 
		}
	}
	
	//��һ������ʽʣ�ಿ�� 
	while (pa < poly[0].size()) {
		res.push_back(poly[0][pa++]);
	}
	//�ڶ�������ʽʣ�ಿ�� 
	while (pb < poly[1].size()) {
		res.push_back(poly[1][pb++]);
	}
}

void polyCalculator::minus() //����ʽ���
{
	//�ѵڶ�������ʽϵ��������-1����ɶ���ʽ��ӵ���� 
	for (auto & pair : poly[1]) {
		pair.second *= -1;
	}
	
	plus();
}

double polyCalculator::calValue(double x) //�������ʽ��x����ֵ
{
    double ans = 0;
    
	for (auto & pair : poly[0]) {
		ans += pair.second*pow(x, pair.first);
	}
	return ans;
}

void polyCalculator::derivative() //�������ʽ�ĵ�����
{
	//����ָ�������󵼹��򼴿� 
	for (auto & pair : poly[0]) {
		if (pair.first == 0) continue; //������ 
		double coefficient = pair.first*pair.second, exp = pair.first-1;
		res.push_back({exp, coefficient});
	}
}

void polyCalculator::mutiply() //����ʽ���
{
	map<double, double> m; //��map������
	//չ������ʽ����map�ĸ����£���˺�ָ����ͬ�����ϵ�����Լӵ�һ�𣬻������Զ����򣬴��������vector�洢��� 
	for (auto & pair_a : poly[0]) {
		for (auto & pair_b : poly[1]) {
			m[pair_a.first+pair_b.first] += pair_a.second*pair_b.second;
		}
	}
	
	for (auto & pair : m) {
		if (pair.second != 0) res.push_back(pair);
	}
}
