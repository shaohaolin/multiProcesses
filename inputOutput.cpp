#include <iostream>
#include <string>
#include <fstream>
#include "unistd.h"
#include "sys/wait.h"
#include "stdlib.h"

using namespace std;

int returnFileSize(){
	streampos begin,end, fsize; //a specific type used for buffer and file positioning
	ifstream myfile("input.txt", ios::binary); // reading a file
	begin = myfile.tellg(); //a member function return a value of member type streampos, a type representing the current get postion
	myfile.seekg(0, ios::end); // allow to change the location of the get positions.
	end = myfile.tellg();
	int size = end - begin;
	myfile.close();
	return size;
}

int main() {
	pid_t process;

	process = fork();

	if (process > 1) 
	{
		//parent 
		//get input, write to file
		cout<<"Process parent starts!"<<endl;
		// while () get input, write to file
		cout << "Hello!" << endl;
		ofstream myfile;
		myfile.open("input.txt");
		string input = "";

		do{
			cout<<"input a string: ";
			getline(cin,input);
			myfile<<input<<endl;

			usleep(1000000); //process sleep for 1 second
		} while (input != "done");

	}
	else if (process == 0) 
	{
		// cchild
		// check file, and update output
		cout<<"Process child starts!"<<endl;
		string temp="";
		
		ofstream writeFile; // writing a file
		writeFile.open("output.txt"); // make a file called output.txt
		ifstream retreFile ("input.txt");

		int currentSize = 0;
		int fileSize;
			fileSize = returnFileSize();
			cout<<fileSize<<endl;

		string previousLine = "firstLine";
			while(getline(retreFile,temp)){

				if(temp != ""){
					previousLine = temp;
				}
			}

		if ((fileSize - currentSize) !=0) {

			cout<<"The input is:"<<temp<<endl;

			writeFile<<temp<<endl; // writing new user input to output.txt
		}

		currentSize = fileSize;
		fileSize = returnFileSize();
		if(temp == "done"){
				exit(0);
		}
		else {
				usleep(1000000); // process sleep for 1 second
		}		
	}
	else 
	{
		std::cout << "ERROR" << std::endl;
	}
}