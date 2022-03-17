#include<iostream>
#include<fstream>
#include<thread> //std::this_thread::sleep for
#include<chrono> //std::chrono::seconds
#include<string>
#include<sstream>
#include<vector>
#include<bits/stdc++.h>//insert function
#include"QE_READ.h"
#include"GAUSS_READ.h"
//#include"MOPAC_INST.h"
//#include<cstdlib>//make directories
//#include</opt/local/include/gcc/c++/filesystem>//get current working directory
using namespace std;

int main(int argc, char **argv) 
{ 

//###################VARIABLES FOR PULLING COORDINATES FROM TRAJECTORY FILE###################################################
//PRINTS THE FIRST ARGUMENT AFTER THE EXECUTABLE ON THE COMMAND LINE
//	cout << argv[1] << endl;

        string input_file=argv[1];
        string cursor, save_line;
        ifstream input_parse;  
        vector<string> input_lines;
        string parsing_file, trajectory_infiles, trajectory_directory, time_steps, charge, convergence_criteria;
        input_parse.open(input_file, ios::in);
        string time_step_id="TIME STEPS:";
        string trajectory_id="TRAJECTORY FILE:";
        string trajectory_directory_id="TRAJECTORY DIRECTORY:";
        string charge_id="CHARGE:";
        string convergence_id="SCF CONVERGENCE CRITERIA:";
        string mopac_prefix_id="MOPAC PREFIX:";
        if(!input_parse){cout<<"can't open input file " << input_file << " make sure it has been created" << endl;}
        while( getline(input_parse, cursor) )
        {
            save_line=cursor;
            input_lines.push_back(save_line);
        }  
        for(int i=0; i<input_lines.size();i++)
        {
            string temp_string = input_lines[i];
            if(temp_string.find(time_step_id) != std::string::npos )
            {
                cout << temp_string << endl;
                temp_string.erase(0,11);
                time_steps = temp_string;
                cout <<"number of time steps " << time_steps << endl;
            }
            else if(temp_string.find(convergence_id) != std::string::npos )
            {
                cout << temp_string << endl;
                temp_string.erase(0,25);
                convergence_criteria = temp_string;
                cout <<"scf convergence criteria " << convergence_criteria << endl;
            }
            else if(temp_string.find(trajectory_id) != std::string::npos )
            {
                temp_string.erase(0,16);
                parsing_file = temp_string;
                cout <<"trajectory file name "<< parsing_file  << endl;
            }
            else if(temp_string.find(trajectory_directory_id) != std::string::npos )
            {
                temp_string.erase(0,21); 
                trajectory_directory = temp_string;
                cout <<"trajectory files directory " << trajectory_directory << endl;
            }
            else if(temp_string.find(charge_id) != std::string::npos )
            {
                temp_string.erase(0,7); 
                charge= temp_string;
                cout << "charge of the system " <<charge << endl;
            }
            else if(temp_string.find(mopac_prefix_id) != std::string::npos )
            {
                temp_string.erase(0,13); 
                trajectory_infiles = temp_string;
                cout << "trajectory file name prefix " <<trajectory_infiles << endl;
            }
            else
            {
                cout <<input_lines[i] << " is not a valid input parameter and is being ignored..."<< endl;
            } 
        }
         
        
//        cout << "enter filename with trajectory: ";
//        cin >> parsing_file;
//        cout << "How many time steps are in this trajectory? ";
//        cin >> time_steps;
//        cout << "enter mopac input file prefix: ";
//        cin >> trajectory_infiles;
//        cout << "what do i call the directory that holds these input files? ";
//        cin >> trajectory_directory;
//        cout << "what is the charge of the system? ";
//        cin >> charge;
        
        //exit(1);

//    for(int i=1; i > 2501; i++)
//    {

//        QE_TO_MOPAC(argv[1], i, "test"+ to_string(i) +".mop", "test");        

//    }
write_mopac_directory(trajectory_directory);
copy_INDO_PAR(trajectory_directory);
int i = 0;
do{
string trajectory_infiles_function_in = trajectory_infiles +"_"+ to_string(i) +".mop";

QE_TO_MOPAC(parsing_file,1+i , trajectory_infiles_function_in , trajectory_directory, charge);
i++; 
if(i % 20 == 0) {std::this_thread::sleep_for(std::chrono::seconds(0) )  ;}

}while(i<stoi(time_steps));


} //END OF MAIN BRACKET








/*        if(program.compare("gaussian") == 0)
        {
//FUNCTION THAT READS GAUSSIAN INPUT FILE
        coords = read_gauss_inp(argv[1]);
        }

        if(program.compare("quantum-espresso") == 0)
        {
//FUNCTION THAT READS QUANUTM ESPRESSO OUTPUT FILE
         coords = read_quant_espress(argv[1]);
        }

//FUNCTION THAT SPLITS INPUT FILE COORDINATES
        vector<vector<string> > element_array; element_array=split_stream(coords, " ");

       for(int i=0; i < element_array[0].size(); i++)
       {
       cout << element_array[0][i] << "  " << element_array[1][i] << "  " << element_array[2][i] << "  " << element_array[3][i] << endl;
       } 
*/






