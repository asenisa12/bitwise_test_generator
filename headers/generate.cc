
#include "generate.hh"

int even[4],odd[4];
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

void generate_tasktype1(bool a){
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
		row<<"int b = orig | (insert << "<<even[0] <<")\n";
		rows.push_back(row.str());
		row.str("");
		row<<"int b = orig | (insert << "<<even[1] <<")\n";
		rows.push_back(row.str());
		row.str("");
	}else{
		row<<"int b = orig | (insert << "<<even[0] <<")\n";
		rows.push_back(row.str());
		row.str("");
		row<<"int b = orig | (insert << "<<even[1] <<")\n";
		rows.push_back(row.str());
		row.str("");
	}
}


void generate_tasktype2(bool AND,bool fOR){
	if(AND){
		rows.push_back("AND=?     ..........\n");
	}else rows.push_back("OR=?     ..........\n");
	gen_insert_orig();
	gen_a_b(AND);
	

	if(fOR || AND){
		rows.push_back("int AND=a&b;\n");
	}else 
		rows.push_back("int AND=a^b;\n");
	rows.push_back("\n");
}

void generate_tasktype3(bool number, bool XOR){
	stringstream row;

	rows.push_back("result =? ..........\n");
	if(number){
		row<<"long value1 ="<<even[4]<<";\n";
		rows.push_back(row.str());
		row.str("");
		row<<"long value1 ="<<odd[4]<<";\n";
		rows.push_back(row.str());
		row.str("");
	}else{
		row<<"long value1 ="<<hex1<<";\n";
		rows.push_back(row.str());
		row.str("");
		row<<"long value1 ="<<hex2<<";\n";
		rows.push_back(row.str());
		row.str("");
	} 


	if(XOR){
		row<<"nt result = (value1 <<"<< even[3]<<") ^ (value2 >> "<<odd[3]<<");\n";
		rows.push_back(row.str());
		row.str("");
		rows.push_back("\n");
	}else{
		row<<"nt result = (value1 <<"<< odd[3]<<") ^ (value2 >> "<<even[3]<<");\n";
		rows.push_back(row.str());
		row.str("");
		rows.push_back("\n");
	}
		
}


void add_to_file(string filename, bool type, bool easy){
	ofstream file;
	file.open(filename.c_str());

	generate_tasktype1(true);
	generate_tasktype1(false);
	generate_tasktype2(true,true);
	generate_tasktype2(true,false);
	generate_tasktype3(true,false);
	generate_tasktype3(true,true);

	for(int i=0;i<23;i++)
		file <<(rows[i]).c_str();

	file.close();
}

void create_files(int num, bool type, bool easy){
	system("mkdir tests");

	for(int i=0;i<num;i++){
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


