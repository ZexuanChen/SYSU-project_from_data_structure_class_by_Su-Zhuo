#include "polyCalculator.h"

polyCalculator::polyCalculator() //构造函数 
{
	clear();
}

polyCalculator::~polyCalculator() {} //析构函数

void polyCalculator::clear() //清空成员变量
{
	poly[0].clear(), poly[1].clear(), res.clear();
}

void polyCalculator::input(int t) //输入多项式
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

void polyCalculator::output() //输出多项式 
{
	//多项式为0的情况
	if (res.size() == 0) {
		cout << "0\n";
		return;
	}
	
	//为了保证输出格式，先输出第一项
	if (res[0].first == 0) cout << res[0].second;
	else {
	    cout << res[0].second << "x^";
		cout << res[0].first;
	}
	
	//输出后面的项 
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

void polyCalculator::plus() //多项式相加
{ 	
	int pa = 0, pb = 0;
	//同时遍历两个多项式，指数小的加入到结果多项式中，指数相同则系数相加并加到结果多项式中 
	while (pa < poly[0].size() && pb < poly[1].size()) {
		if (poly[0][pa].first < poly[1][pb].first) {
			res.push_back(poly[0][pa++]);
		}
		else if (poly[0][pa].first > poly[1][pb].first) {
			res.push_back(poly[1][pb++]);
		}
		else {
			double exp = poly[0][pa].first, num = poly[0][pa++].second + poly[1][pb++].second;
			if (num != 0) res.push_back({exp, num}); //系数相加为0则消掉了 
		}
	}
	
	//第一个多项式剩余部分 
	while (pa < poly[0].size()) {
		res.push_back(poly[0][pa++]);
	}
	//第二个多项式剩余部分 
	while (pb < poly[1].size()) {
		res.push_back(poly[1][pb++]);
	}
}

void polyCalculator::minus() //多项式相减
{
	//把第二个多项式系数均乘以-1，变成多项式相加的情况 
	for (auto & pair : poly[1]) {
		pair.second *= -1;
	}
	
	plus();
}

double polyCalculator::calValue(double x) //计算多项式在x处的值
{
    double ans = 0;
    
	for (auto & pair : poly[0]) {
		ans += pair.second*pow(x, pair.first);
	}
	return ans;
}

void polyCalculator::derivative() //计算多项式的导函数
{
	//根据指数函数求导规则即可 
	for (auto & pair : poly[0]) {
		if (pair.first == 0) continue; //常数项 
		double coefficient = pair.first*pair.second, exp = pair.first-1;
		res.push_back({exp, coefficient});
	}
}

void polyCalculator::mutiply() //多项式相乘
{
	map<double, double> m; //用map做辅助
	//展开多项式，在map的辅助下，相乘后指数相同的项的系数可以加到一起，还可以自动排序，处理完后用vector存储结果 
	for (auto & pair_a : poly[0]) {
		for (auto & pair_b : poly[1]) {
			m[pair_a.first+pair_b.first] += pair_a.second*pair_b.second;
		}
	}
	
	for (auto & pair : m) {
		if (pair.second != 0) res.push_back(pair);
	}
}
