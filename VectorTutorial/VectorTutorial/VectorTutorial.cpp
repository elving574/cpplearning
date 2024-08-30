#include<iostream>  
#include<vector>  
using namespace std;
int main()
{
	vector<string> v1;
	v1.push_back("javaTpoint ");
	v1.push_back("tutorial");
	v1.push_back("potatoes");
	for (string i : v1) {
		cout << i;
	}
	return 0;
}
