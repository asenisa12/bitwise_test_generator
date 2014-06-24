#ifndef generate
#define generate

#include <iostream>
#include <fstream>
#include <stdlib.h> 
#include <string>
#include <sstream>
#include <time.h> 
#include <vector>
#include <cstring>



using namespace std;

extern string hex1,hex2,hex3,hex4;
extern vector<string> rows,res_rows;
extern int even[4],odd[4],count;

void create_files(int num, bool easy);
void generate_num(bool easy);
void add_to_file(string filename, bool easy);
int generate_tasktype1(bool a);
void gen_insert_orig();
void gen_a_b(bool AND);
int generate_tasktype3(bool number);
int generate_tasktype2(bool AND,bool fOR);
int generate_tasktype4(bool twoVar);
int generate_tasktype5();
void generate_test_answer();

#endif