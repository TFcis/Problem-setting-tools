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
	cout<<"�п�J�Ĥ@������s��: ";
	cin>>s;
	cout<<"�п�J�̫�@������s��: ";
	cin>>e; cin.ignore(); 
	
	while(1)
	{
		for(int i=s;i<=e;i++)
		{
			ostringstream oss;
			oss<<"run.bat \""<<exe<<"\" \""<<folder<<i<<".in\" \""<<folder<<i<<".out\"";
			cout<<oss.str()<<endl<<endl;
			system(oss.str().c_str()); 
		}
		system("pause");
	}
}
