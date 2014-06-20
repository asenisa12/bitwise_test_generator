
#include "generate.hh"

int even[4],odd[4],count;
string hex1,hex2,hex3,hex4;
vector<string> rows;

void generate_num(bool easy){
	using namespace std;
	stringstream number1;
	stringstream number2;
	stringstream number3;
	stringstream number4;

	number1<<"0x";
	number2<<"0x";
	number3<<"0x";
	number4<<"0x";

	if(easy){
		char alphanum[] ="ABCDEF";
		char a = alphanum[rand()%6];
		char b = alphanum[rand()%6];

		even[0]=(rand()/(RAND_MAX/3)+1)*4;


		do {
			even[1]=(rand()/(RAND_MAX/10)+1);
		} while(even[1]%4==0);

		even[3]=(rand()/(RAND_MAX/3)+1)*4;

		odd[3] = (rand()/(RAND_MAX/10)+1);

		
		number1 << a<<0<<a<<0;
		number2 << a<<a<<0<<0<<a<<a<<0<<0;
		number3 << a<<0<<0<<a<<b<<0<<0<<b;
		number4 << 0<<0<<0<<b;
	}

	hex1= number1.str();
	hex2= number2.str();
	hex3= number3.str();
	hex4= number4.str();
}

void generate_test_answer(){
	ofstream cfile("tests/result.c");
	cfile <<"#include <stdio.h>\n";
	cfile <<"int main(){\n";
	int i=count;
	while(!strcmp(rows[i].c_str(),"\n")){
		cfile <<(rows[i]).c_str();
		i++;
	}
	cfile <<"return 0;\n";
	cfile <<"}\n";
	cfile.close();
}

int generate_tasktype1(bool a){
	stringstream row;	

	if(a){
		rows.push_back("a=?     ..........\n");
	}else 
		rows.push_back("b=?     ..........\n");
		gen_insert_orig();
	

	if(a){
		row<<"int a = orig | (insert << "<< even[0]<<")\n";
		rows.push_back(row.str());
		row.str("");
	}else {
		
		row<<"int b = orig | (insert << "<<even[1] <<")\n";
		rows.push_back(row.str());
		row.str("");
	}

	rows.push_back("\n");
	row.str("");
	return 5;
}

void gen_insert_orig(){
	stringstream row;	
	row<<"int orig ="<<hex1.c_str()<<";\n";
	rows.push_back(row.str());
	row.str("");
	row<<"int insert ="<<hex4<<";\n";
	rows.push_back(row.str());
	row.str("");
}

void gen_a_b(bool AND){
	stringstream row;

	if(AND){
		row<<"int a = orig | (insert << "<<even[0] <<")\n";
		rows.push_back(row.str());
		row.str("");
		row<<"int b = orig | (insert << "<<even[1] <<")\n";
		rows.push_back(row.str());
		row.str("");
	}else{
		row<<"int a = orig | (insert << "<<even[0] <<")\n";
		rows.push_back(row.str());
		row.str("");
		row<<"int b = orig | (insert << "<<even[1] <<")\n";
		rows.push_back(row.str());
		row.str("");
	}
}


int generate_tasktype2(bool AND,bool fOR){
	if(AND){
		rows.push_back("AND=?     ..........\n");
	}else rows.push_back("OR=?     ..........\n");
	gen_insert_orig();
	gen_a_b(AND);
	
	if(!AND && !fOR){
		rows.push_back("int OR=a&b;\n");
	}else if(AND && !fOR){
		rows.push_back("int AND=a&b;\n");
	}else if(!AND && fOR){
		rows.push_back("int OR=a^b;\n");
	}
	rows.push_back("\n");

	return 7;
}

int generate_tasktype3(bool number, bool XOR){
	stringstream row;
	cout << "lala"<<endl;

	rows.push_back("result =? ..........\n");
	if(number){
		row<<"long value1 ="<<even[4]<<";\n";
		rows.push_back(row.str());
		row.str("");
		row<<"long value2 ="<<odd[4]<<";\n";
		rows.push_back(row.str());
		row.str("");
	}else{
		row<<"long value1 ="<<hex2<<";\n";
		rows.push_back(row.str());
		row.str("");
		row<<"long value2 ="<<hex3<<";\n";
		rows.push_back(row.str());
		row.str("");
	} 


	if(XOR){
		row<<"int result = (value1 <<"<< even[3]<<") ^ (value2 >> "<<odd[3]<<");\n";
		rows.push_back(row.str());
		row.str("");
	}else{
		row<<"int result = (value1 <<"<< odd[3]<<") | (value2 >> "<<even[3]<<");\n";
		rows.push_back(row.str());
		row.str("");
	}
	rows.push_back("\n");
	return 5;	
}

int generate_tasktype4(bool twoVar){
	cout << "lala"<<endl;
	stringstream row;
	if(twoVar){
		rows.push_back("a,result =? ..........\n");
	}else{
		rows.push_back("a =? ..........\n");
	}
	row<<"long testValue ="<<hex2<<";\n";
	rows.push_back(row.str());
	row.str("");
	rows.push_back("int a =0;\n");
	if(twoVar){
		rows.push_back("int result =0;\n");
		rows.push_back("if ( (result = testValue & testValue ^ testValue\n");
		row<<"(1 << "<<even[3]<<")) )\n";
		rows.push_back(row.str());
		row.str("");
	}else{
		row<<"if (testValue & (1 << "<<even[3]<<")) )\n";
		rows.push_back(row.str());
		row.str("");
	}

	rows.push_back("a=1;\n");
	rows.push_back("} else {\n");
	rows.push_back("a=2;\n");
	rows.push_back("}\n");
	rows.push_back("\n");

	if(twoVar) return 11;
	return 9;
}
int generate_tasktype5(){
	stringstream row;

	rows.push_back("left=?    ........\n");
	row<<"int i = 0x"<<hex1<<";\n";
	rows.push_back(row.str());
	row.str("");
	row<<"int left = "<<hex1<<"| (1 << "<<even[3]<<");\n";
	rows.push_back(row.str());
	row.str("");
	rows.push_back("\n");
	return 4;
}


void add_to_file(string filename, bool type, bool easy){
	ofstream file;
	file.open(filename.c_str());
	int rows_num=0;
	rows_num+=generate_tasktype1(true);
	rows_num+=generate_tasktype1(false);
	rows_num+=generate_tasktype2(true,false);
	rows_num+=generate_tasktype2(false,false);
	rows_num+=generate_tasktype2(false,true);
	rows_num+=generate_tasktype5();
	rows_num+=generate_tasktype3(false,false);
	rows_num+=generate_tasktype3(false,true);
	rows_num+=generate_tasktype4(true);
	rows_num+=generate_tasktype4(false);
	rows_num+=generate_tasktype3(true,false);
	rows_num+=generate_tasktype3(true,true);

	for(int i=0;i<rows_num;i++)
		file <<(rows[i]).c_str();

	file.close();
	generate_test_answer();
}

void create_files(int num, bool type, bool easy){
	system("mkdir tests");

	for(int i=0;i<num;i++){
		count=1;
		std::stringstream filename;
		filename <<"tests/file"<<i+1<<".txt";
		generate_num(true);
		rows.clear();

		
		time_t seconds;
		time(&seconds);
		srand((unsigned int) seconds);
		add_to_file(filename.str(),type,easy);
	}
	
}


