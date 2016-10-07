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
	cout<<"請輸入執行檔位置: ";
	exe=readPath();
	cout<<"請輸入測資資料夾位置: ";
	folder=readPath();
	folder+="\\";
	cout<<"請輸入第一筆測資編號: ";
	cin>>s;
	cout<<"請輸入最後一筆測資編號: ";
	cin>>e; cin.ignore(); 
//	cout<<"請輸入輸出暫存檔位置: ";
//	temp=readPath();
	temp="temp.out";
	
	while(true)
	{
		for(int i=s;i<=e;i++)
		{
			cout<<"測資"<<i<<"  ";
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
		cout<<"請輸入命令: Enter:rejudge, exe:換執行檔, testdata:換測資, exit:離開"<<endl;
		string command;
		getline(cin,command);
		if(command=="exe")
		{
			cout<<"請輸入新執行檔位置: ";
			exe=readPath();
		}
		else if(command=="testdata")
		{ 
			cout<<"請輸入新測資資料夾位置: ";
			folder=readPath();
			folder+="\\";
			cout<<"請輸入第一筆測資編號: ";
			cin>>s;
			cout<<"請輸入最後一筆測資編號: ";
			cin>>e; cin.ignore(); 
		}
		else if(command=="exit")
		{
			break;
		}
	}
}
