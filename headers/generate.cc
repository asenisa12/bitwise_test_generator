
#include "generate.hh"

int even[4],odd[4],count;
string hex1,hex2,hex3,hex4;
vector<string> rows,res_rows;

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

void generate_test_answer(string print){
	ofstream cfile("result.c");
	cfile <<"#include <stdio.h>\n int main(){\n";

	while(strcmp(rows[count].c_str(),"\n")){
		cfile <<(rows[count]).c_str();
		count++;
	}
	count+=2;
	cfile<<"printf("<<print.c_str()<<");";
	cfile <<"return 0;\n}\n";
	cfile.close();

	system("gcc result.c");
	system("./a.out > res.txt");
	ifstream in("res.txt");
	string str;
	in >> str;
	res_rows.push_back(str);
	system("rm a.out");
	system("rm result.c");
	system("rm res.txt");
}

int generate_tasktype1(bool a){
	stringstream row;	

	if(a){
		rows.push_back("a=?     ..........\n");
	}else 
		rows.push_back("b=?     ..........\n");
		gen_insert_orig();
	

	if(a){
		row<<"int a = orig | (insert << "<< even[0]<<");\n";
		rows.push_back(row.str());
		row.str("");
	}else {
		
		row<<"int b = orig | (insert << "<<even[1] <<");\n";
		rows.push_back(row.str());
		row.str("");
	}

	rows.push_back("\n");
	row.str("");
	if(a){
		generate_test_answer("\"1:%x\",a");
	}else generate_test_answer("\"2:%x\",b");
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
		row<<"int a = orig | (insert << "<<even[0] <<");\n";
		rows.push_back(row.str());
		row.str("");
		row<<"int b = orig | (insert << "<<even[1] <<");\n";
		rows.push_back(row.str());
		row.str("");
	}else{
		row<<"int a = orig | (insert << "<<even[0] <<");\n";
		rows.push_back(row.str());
		row.str("");
		row<<"int b = orig | (insert << "<<even[1] <<");\n";
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
		rows.push_back("\n");
		generate_test_answer("\"4:%x\",OR");
	}else if(AND && !fOR){
		rows.push_back("int AND=a&b;\n");
		rows.push_back("\n");
		generate_test_answer("\"3:%x\",AND");
	}else if(!AND && fOR){
		rows.push_back("int OR=a^b;\n");
		rows.push_back("\n");
		generate_test_answer("\"5:%x\",OR");
	}

	return 7;
}

int generate_tasktype3(bool number, bool XOR){
	stringstream row;

	rows.push_back("result =? ..........\n");
	if(number){
		row<<"long value1 ="<<even[4]<<";\n";
		rows.push_back(row.str());
		row.str("");
		row<<"long value2 ="<<odd[4]<<";\n";
		rows.push_back(row.str());
		row.str("");
	}else{
		row<<"long value1 ="<<hex2<<";\n";
		rows.push_back(row.str());
		row.str("");
		row<<"long value2 ="<<hex3<<";\n";
		rows.push_back(row.str());
		row.str("");
	} 


	if(XOR){
		row<<"int result = (value1 <<"<< even[3]<<") ^ (value2 >> "<<odd[3]<<");\n";
		rows.push_back(row.str());
		row.str("");
	}else{
		row<<"int result = (value1 <<"<< odd[3]<<")|(value2 >> "<<even[3]<<");\n";
		rows.push_back(row.str());
		row.str("");
	}
	rows.push_back("\n");

	if(!number && !XOR) generate_test_answer("\"7:%x\",result");
	if(!number && XOR)generate_test_answer("\"8:%x\",result");
	if(number && !XOR)generate_test_answer("\"11:%x\",result");
	if(number && XOR)generate_test_answer("\"12:%x\",result");


	return 5;	
}

int generate_tasktype4(bool twoVar){
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
		rows.push_back("if ( (result = testValue & testValue ^ testValue & \n");
		row<<"(1 << "<<even[3]<<")) ){\n";
		rows.push_back(row.str());
		row.str("");
	}else{
		row<<"if(testValue & (1<<"<<even[3]<<")){\n";
		rows.push_back(row.str());
		row.str("");
	}

	rows.push_back("a=1;\n");
	rows.push_back("} else {\n");
	rows.push_back("a=2;\n");
	rows.push_back("}\n");
	rows.push_back("\n");


	if(twoVar){
		generate_test_answer("\"9:result:%x,a:%x\",result,a");
		return 11;
	} else generate_test_answer("\"10:%x\",a");

	return 9;
}
int generate_tasktype5(){
	stringstream row;

	rows.push_back("left=?    ........\n");
	row<<"int i = "<<hex1<<";\n";
	rows.push_back(row.str());
	row.str("");
	row<<"int left = "<<hex1<<"| (1 << "<<even[3]<<");\n";
	rows.push_back(row.str());
	row.str("");
	rows.push_back("\n");
	generate_test_answer("\"6:%x\",left");
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
	
}

void create_files(int num, bool type, bool easy){
	

	for(int i=0;i<num;i++){
		stringstream filename;
		filename <<"mkdir test"<<i+1;
		system(filename.str().c_str());
		filename.str("");
		count=1;

		
		filename <<"test"<<i+1<<"/test"<<".txt";
		generate_num(true);
		rows.clear();

		
		time_t seconds;
		time(&seconds);
		srand((unsigned int) seconds);
		add_to_file(filename.str(),type,easy);
		filename.str("");
		filename <<"test"<<i+1<<"/result"<<".txt";
		ofstream resfile;
		resfile.open(filename.str().c_str());

		for(vector<string>::iterator it=res_rows.begin();it!=res_rows.end();it++)	
			resfile<< (*it) <<endl;
		resfile.close();
		res_rows.clear();
	}
	
}


