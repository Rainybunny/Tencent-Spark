#include<bits/stdc++.h>
using namespace std;
int main(){
	string s;int count=0;
	while(getline(cin,s)){
		stringstream ss(s);
		string t;ss>>t;
		if(t!="cx")continue;
		int x[2]={0},p=0;++count;
		for(int j=1;j<s.size();j++){
			if(isdigit(s[j]))x[p]=10*x[p]+(s[j]^48);
			else if(isdigit(s[j-1]))++p; 
		}
		cout<<"cz\n2 "<<x[0]<<" "<<x[1]<<"\n0.0\n";
		if(x[0]>=13||x[1]>=13){
			cerr<<"error!\n";
			exit(0);
		}
	}
	cerr<<count<<"\n";
	return 0;
}
