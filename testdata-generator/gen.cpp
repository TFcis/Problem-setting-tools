#include<iostream>
#include<sstream>
#include<cstdlib>
#include<fstream>
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
int main()
{
	string exe,folder;
	int s,e;
	cout<<"�п�J�����ɦ�m: ";
	exe=readPath();
	cout<<"�п�J�����Ƨ���m: ";
	folder=readPath();
	folder+="\\";
	char fileformat[100];
	cout<<"�п�J����s���榡(TOJ:%d, CMS:%.4d): ";
	gets(fileformat);
	cout<<"�п�J�Ĥ@������s��: ";
	cin>>s;
	cout<<"�п�J�̫�@������s��: ";
	cin>>e; cin.ignore(); 
	
	while(1)
	{
		for(int i=s;i<=e;i++)
		{
			ostringstream oss;
			char buffer [10];
			sprintf (buffer, fileformat, i);
			oss<<"run.bat \""<<exe<<"\" \""<<folder<<buffer<<".in\" \""<<folder<<buffer<<".out\"";
			cout<<oss.str()<<endl<<endl;
			system(oss.str().c_str()); 
		}
		system("pause");
	}
}
