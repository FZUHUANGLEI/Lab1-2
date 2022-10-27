#include<iostream>
#include<string>
#include<vector>
#include<fstream>
#include<sstream>
#include<stack>
using namespace std;
string keywords[32]={"auto","double","int","struct","break","else","long","switch",
					 "case","enum","register","typedef","char","extern","return","union", 
					 "const","float","short","unsigned","continue","for","signed","void",
 					 "default","goto","sizeof","volatile","do","if","while","static"
					}; 
int peak =-1;	
int container[600]={0};				
int Total_Num=0;
int Switch_Num=0;
int Case_Num=0;
int if_else_Num=0;
int if_elseif_else_Num=0;
vector<int> Case; //Creates a one-dimensional vector with no specified length

int main() 
{	
	string C_file;
	string interim;
	int Level_Num;
	cout << "Print the path of C/C++ file: " << endl;
	cin >> C_file;
	cout << "Print the level of extract keywords: " << endl;					
	cout << "Level1: total keywords" << endl;
	cout << "Level2: switch case and case" << endl;
	cout << "Level3: if else" << endl;
	cout << "Level4: if, else if, else" << endl;
	cin >> Level_Num;
	ifstream readfile(C_file.c_str()); //read in the C/C++ file
	void First_Level(string cha);
	void Second_Level(string cha);
	int assess_fun1(string A, string B);
	int assess_fun2(char cha);
	
	while(getline(readfile,interim)){
		istringstream strl (interim);
		string z;
		if(Level_Num >=3){
			Second_Level(interim);	
		}
		while (strl >>z){
			First_Level(z);
		}
	}
	
	if(Level_Num >=1){
		cout << "total num: " << Total_Num << endl;
	}
	if(Level_Num >=2){
		cout << "switch num: " << Switch_Num << endl;
		if(Case.empty()){
			Case.push_back(0);
		}
		else{
			Case.push_back(Case_Num);
		} 
		cout << "case num: ";
		for(int x =1; x<=Switch_Num; x++){ 
			cout << Case[x] << " "; 
		}
		cout << endl;
	}
	if(Level_Num >=3){
		cout << "if-else num: " << if_else_Num << endl;	
	}
	if(Level_Num >=4){
		cout << "if-elseif-else num: " << if_elseif_else_Num << endl;
	} 
}

int assess_fun1(string A, string B){
	int pos = A.find(B,0);
	int Len = B.length();
	int assess_fun2(char cha);
	if(pos != string::npos){
		if(pos == 0){
			if(assess_fun2(A[pos+Len]) == 0 && assess_fun2(A[pos-1]) == 0){
				return 1;
			}
			else{
				return 0;
			}
		}	
		else{	
			if(assess_fun2(A[pos+Len]) == 0){
				return 1;
			}
			else{
				return 0;		
			}		
		}
	}
	return 0;
} 
	
int assess_fun2(char cha){  
	if((cha >='A' && cha <='Z') || (cha >='a' && cha <='z')){ 
		return 1;
	}
	else{
		return 0;
	}
}

void First_Level(string cha){ //stand for the first two level 1 and 2;
	for (int i =0; i<32; i++){
		if(assess_fun1(cha,keywords[i])==1){
			if(assess_fun1(cha,"switch")){
				Case.push_back(Case_Num);
				Switch_Num++;
				Case_Num = 0;
			}
			if(assess_fun1(cha,"case")){
				Case_Num++;
			}
			Total_Num++;
			break;			
		}
	}
}

void Second_Level(string cha){ //stand for the second two level 3 and 4;
	if(assess_fun1(cha,"else if")){
		peak++;
		container[peak] =2;	
	}
	
	else{
		if(assess_fun1(cha,"else")){
			if(container[peak]==1){
				if_else_Num++;
				peak--;
			}
			else{
				if(container[peak]==2){
					if_elseif_else_Num++;
					peak--;
				}
			}
		}
		else{
			if(assess_fun1(cha,"if")){
				peak++;
				container[peak]=1;
			}
		}
	}
}



	
	
	
	











