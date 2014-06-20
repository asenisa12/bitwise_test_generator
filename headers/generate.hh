#ifndef generate
#define generate

#include <iostream>
#include <fstream>
#include <stdlib.h> 
#include <string>
#include <sstream>
#include <time.h> 
#include <vector>

using namespace std;

extern string hex1,hex2,hex3,hex4;
extern vector<string> rows;
extern int even[4],odd[4];

void create_files(int num,bool type, bool easy);
void generate_num(bool easy);
void add_to_file(string filename, bool type, bool easy);
void generate_tasktype1(bool a);
void gen_insert_orig();
void gen_a_b(bool AND);
void generate_tasktype3(bool number);

#endif