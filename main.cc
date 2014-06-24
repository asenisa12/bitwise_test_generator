#include "headers/generate.hh"

int main(int argc, char* argv[]){
	
	bool html_pdf=false,easy_hard=false;
	int num;
	string type;

	for(;;){
		cout<<"input [ p ] for pdf and [ h ] for html: ";
		cin>>type;
		cout<<endl;
		if(type.c_str()[0] == 'p'){
			html_pdf=false;
			break;
		}else if(type.c_str()[0] == 'h'){
			html_pdf=true;
			break;
		}else cout<<"Error: Wrong Parameter!!!"<<endl;
		cout<<endl;
	}


	for(;;){
		cout<<"input [ e ] for easy test and [ h ] for hard: ";
		cin>>type;
		cout<<endl;
		if(type.c_str()[0] == 'h'){
			easy_hard=false;
			break;
		}else if(type.c_str()[0] == 'e'){
			easy_hard=true;
			break;
		}else cout<<"Error: Wrong Parameter!!!"<<endl;
		cout<<endl;
	}

	for(;;){
			cout<<"For numbers of tests input number bigger than [1]: ";
			cin>>type;
			num=atoi(type.c_str());
			cout<<endl;
			if(num>0){
				break;
			}else cout<<"Error: Wrong Parameter!!!"<<endl;
			cout<<endl;
	}


	for(int i=0;i<num;i++)
		create_files(i,html_pdf,easy_hard);

	return 0;
}
