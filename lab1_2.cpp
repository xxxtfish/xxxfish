#include<iostream>
#include<fstream>
#include<cstdlib>
#include<iomanip>
#include<vector>
#include<algorithm>
using namespace std;
int main()
{    
	string test;
	vector <string> nums; 
	string filename;
	string KW[33] = {"auto", "break", "case", "char", "const", "continue",
		"default", "do", "double", "else", "enum", "extern", "float",
		"for", "foto", "if", "int", "long", "main", "register", "return", "short",
		"signed", "sizeof", "static", "struct", "switch", "typeof", "union",
		"unsigned", "void", "volatile", "while"};
	string ifelse_KW[3] = {"else if","if","else"};
	int KW_count = 0;    
	int switch_count = 0;
	int case_count = 0;
	int ifelse_KW_count[3] = {0};
	vector<int> casenum;
	vector<string> ifelse; 
	int ifelse_count = 0;
	int ifelseif_count = 0;
	ifstream inFile;
	cout<<"Please enter the file name: ";
	cin>>filename;
	cout<<"Please choose the level(1,2,3,4): ";
	int level;
	cin>>level;
	inFile.open(filename.c_str());
	if(inFile.fail())
	{
		cout<<"The file was not successfully open!"<<endl;
		exit(1);
	}
	string buf;
	while (getline(inFile,buf))
	{
		int i = 1, j = 1;    
		while(i < int(buf.size()) && j < int(buf.size())) 
		{
			if (isalpha(buf[i])) 
			{
				if (!isalpha(buf[j] )) 
				{
					string s = buf.substr(i, j-i);
					nums.push_back(s);//The vector () function adds a new element to the end of a vector, one element after the current last element
					for (int k = 0; k < 33; k++) {
						if (s == KW[k]) {
							KW_count += 1;
						}
					}
					i = j+1;
					j = i;
				}
				else
					j++;
			}
			else{
				i++;
				j = i;
			}
		}
	}
	if(level >= 1)
		cout<<"total num: "<<KW_count<<endl;
	if(level > 1)
	{
		for(int i = 0;i < int(nums.size());i++)
		{
			if(nums[i] == "switch")
			{
				switch_count += 1;
				
				for(int j = i+1;j < int(nums.size());j++)
				{
				
					if (nums[j] == "case")
						case_count += 1;
					else if(nums[j] == "switch" )
					{
						i=j-1;
						casenum.push_back(case_count);
						case_count = 0;
						break;
					}
					else if(j == int(nums.size()-1))
					{
						i = j;
						casenum.push_back(case_count);
						break;
					}
				}
			}
		} 
		cout<<"switch num: "<<switch_count<<endl;
		cout<<"case num: ";
		for(int i = 0;i < int(casenum.size());i++)
		{
			cout<<casenum[i]<<"  ";
		}
		cout<<endl;
		inFile.close();
	}
	if(level>2)
	{
		inFile.open(filename.c_str());
		if(inFile.fail())
		{
			cout<<"The file was not successfully open!";
			exit(1);
		}
		while (getline(inFile,buf))
		{
			for(int i = 0;i < 3;i++)
			{
				if(int(buf.find(ifelse_KW[i]) != -1))
					ifelse_KW_count[i] = 1;
				else
					ifelse_KW_count[i] = 0;
			}    
			if(ifelse_KW_count[1] == 1 && ifelse_KW_count[2] == 1)
			{
				ifelse_KW_count[0]=1;
				ifelse_KW_count[1]=0;
				ifelse_KW_count[2]=0;
			}    
			for(int i = 0;i < 3;i++)
			{
				if(ifelse_KW_count[i] == 1)
					ifelse.push_back(ifelse_KW[i]);    
			}
		}
		for(int i=0;i<int(ifelse.size())-1;i++)
		{
			if(ifelse[i] == "if" && ifelse[i+1] == "else")
			{
				ifelse_count += 1;
			}
			if(ifelse[i] == "if" && ifelse[i+1] == "else")
			{
				ifelseif_count += 1;
			}    
		}
		if(level>2)
			cout<<"if-else num: "<<ifelse_count<<endl;
		if(level>3)
			cout<<"if-elseif-else num: "<<ifelseif_count<<endl;
	}
	return 0;
}


