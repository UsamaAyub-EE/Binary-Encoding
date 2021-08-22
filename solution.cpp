#include<iostream>
#include<vector>
#include<cstring>
#include<algorithm>
using namespace std;
int decode(vector <string> code,string code_string)
{
	if(code_string.size()==0)
		return 1;
	auto codelength=code_string.size();
	int length=0;
	for(auto i=0;i<code.size();++i)
	{
		if(code_string.size() >= code[i].size() && (0 == code_string.compare(0, code[i].size(), code[i])))
		{
			length += decode(code,code_string.substr(code[i].size()));
		}
	}
	return length;
}
class BinaryCodes
{
	public:
	int ambiguous(vector <string> code)
	{
		for (auto i=0;i<code.size();++i)
    	{
      		if(code[i].length()==0)
			   return 0;
    	}
		bool is_not_ambiguous=true;
		vector <string> copy=code;
		string dangling_suffix;
		for(auto i=0;i<copy.size();++i)
		{
			if(!is_not_ambiguous)
				break;
			for(auto j=0;j<copy.size();++j)
			{
				if(i==j)
					continue;
				if(copy[j].size() >= copy[i].size() && (0 == copy[j].compare(0, copy[i].size(), copy[i])))
				{
					dangling_suffix = copy[j].substr(copy[i].size());
					if(dangling_suffix.size()>0)
					{
						if( (find(copy.begin(), copy.end(), dangling_suffix) == copy.end()))
						{
							copy.push_back(dangling_suffix);
						}
						if((find(code.begin(), code.end(), dangling_suffix) != code.end()))
						{
							is_not_ambiguous=false;
							break;
						}
					}
					else
					{
						is_not_ambiguous=false;
						break;
					}
				}
			}
		}
		if(is_not_ambiguous)
			return -1;
		string code_word;
		vector<string> temp(1,""),temp2;
		long long int smallest=99999999;
		while(1)
		{
			for(auto i=0;i<code.size();++i)
			{
				for(auto j=0;j<temp.size();++j)
				{
					auto test=temp[j]+code[i];
					if(test.size()<smallest)
		   				temp2.push_back(test);
				}
			}
			if(temp2.size()==0)
				break;
			for(auto j=0;j<temp2.size();++j)
			{
				if(decode(code,temp2[j])>=3)
				{
					if(temp2[j].size()<smallest)
					{
						smallest=temp2[j].size();
					}
				}
			}
			temp=temp2;
			temp2.clear();
		}
		return smallest;
	}
};
int main()
{
	BinaryCodes obj;
	vector<string> code={"","01101001001","111101011"};
	cout<<"ambiguous returns "<<obj.ambiguous(code);
	return 0;
}
