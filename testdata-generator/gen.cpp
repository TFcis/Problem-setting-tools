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
	cout<<"請輸入執行檔位置: ";
	exe=readPath();
	cout<<"請輸入測資資料夾位置: ";
	folder=readPath();
	folder+="\\";
	char fileformat[100];
	cout<<"請輸入測資編號格式(TOJ:%d, CMS:%.4d): ";
	gets(fileformat);
	cout<<"請輸入第一筆測資編號: ";
	cin>>s;
	cout<<"請輸入最後一筆測資編號: ";
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
