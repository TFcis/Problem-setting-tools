#include<iostream>
#include<sstream>
#include<fstream>
#include<ctime>
using namespace std;
string readPath()
{
	string path;
	getline(cin,path);
	if(path[0]=='\"')
	{
		path.erase(0,1);
		path.erase(path.size()-1,1);
	}
	return path;
}
bool cmpFile(string p1,string p2)
{
//	ifstream f1(p1.c_str(),ios::in|ios::binary|ios::ate);
//	ifstream f2(p2.c_str(),ios::in|ios::binary|ios::ate);
//	if(f1.tellg()!=f2.tellg())
//	{
//		f1.close();
//		f2.close();
//		return false;
//	}
	ifstream f1(p1.c_str());
	ifstream f2(p2.c_str());
	char a,b;
	while( true )
	{
		a=f1.get();
		b=f2.get();
		if(f1.eof()||f2.eof()) break;
		if(a!=b)
		{
			f1.close();
			f2.close();
			return false;
		}
	}
	
	if( (!f1.eof()) || (!f2.eof()) )
	{
		f1.close();
		f2.close();
		return false;
	}
	else
	{
		f1.close();
		f2.close();
		return true;
	}
}
int main()
{
	string exe,folder,temp;
	int s,e;
	cout<<"�п�J�����ɦ�m: ";
	exe=readPath();
	cout<<"�п�J�����Ƨ���m: ";
	folder=readPath();
	folder+="\\";
	cout<<"�п�J�Ĥ@������s��: ";
	cin>>s;
	cout<<"�п�J�̫�@������s��: ";
	cin>>e; cin.ignore(); 
//	cout<<"�п�J��X�Ȧs�ɦ�m: ";
//	temp=readPath();
	temp="temp.out";
	
	while(true)
	{
		for(int i=s;i<=e;i++)
		{
			cout<<"����"<<i<<"  ";
			ostringstream oss;
			clock_t start_time,end_time;
			oss<<"run.bat \""<<exe<<"\" \""<<folder<<i<<".in\" \""<<temp<<"\"";
			start_time=clock();
			system(oss.str().c_str());
			end_time=clock();
			oss.str("");
			oss<<folder<<i<<".out";
			if(cmpFile(temp,oss.str()))
				cout<<"AC";
			else
				cout<<"WA--WA -- Wrong Answer!";
			cout<<"  "<<(end_time-start_time)*1000/CLOCKS_PER_SEC<<"ms ";
			cout<<endl;
		}
		cout<<"�п�J�R�O: Enter:rejudge, exe:��������, testdata:������, exit:���}"<<endl;
		string command;
		getline(cin,command);
		if(command=="exe")
		{
			cout<<"�п�J�s�����ɦ�m: ";
			exe=readPath();
		}
		else if(command=="testdata")
		{ 
			cout<<"�п�J�s�����Ƨ���m: ";
			folder=readPath();
			folder+="\\";
			cout<<"�п�J�Ĥ@������s��: ";
			cin>>s;
			cout<<"�п�J�̫�@������s��: ";
			cin>>e; cin.ignore(); 
		}
		else if(command=="exit")
		{
			break;
		}
	}
}
