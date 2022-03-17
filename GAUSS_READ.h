#include<iostream>
#include<fstream>
#include<string>
#include<sstream>
#include<vector>
#include <bits/stdc++.h>//insert function
//#include<cstdlib>//make directories
//#include</opt/local/include/gcc/c++/filesystem>//get current working directory
using namespace std;



vector<string> read_gauss_inp(string input_name)
{
//STRING THAT HOLDS THE SPIN AND MULTIPLICITY OF THE MOLECULE
        string spin_mul = "0 1";

//INPUT FILE STREAM THAT READS GAUSSIAN INPUT FILE
        ifstream geometry;
        geometry.open(input_name);

//STRING THAT HOLDS THE LINE FROM THE INPUT FILE STREAM
        string line;
//STRING THAT HOLDS ALL THE COORDINATES FROM THE INPUT FILE
        vector<string> coords;
//COUNTERS TO PRINT GEOMETRY FROM GAUSSIAN INPUT FILE
        int counter=0;
        int spin_mult_count=0;
        int spin_mul_line=0;
//###################VARIABLES FOR PULLING COORDINATES FROM GAUSSIAN INPUT FILE###################################################


            while(getline(geometry,line))
            {
               if(spin_mul.compare(line)!= 0)
                {
                    counter++;
                    spin_mul_line++;
                }
                if(spin_mul.compare(line) == 0 )
                {
                    spin_mul_line = counter;
                    spin_mul_line++;
                }
                if(counter < spin_mul_line)
                {
                    if(spin_mul.compare(line) == 0){continue;}
                    if(line.compare("") == 0){continue;} //MUST BE AN EMPTY LINE AT THE END OF THE GEOMETRY
                    coords.push_back(line);
//                    cout << line << "  " << spin_mul_line << " " << counter << endl;
                }
            }
return coords;
}//END OF read_gauss_inp BRACKET




vector<vector<string> > split_stream(vector<string> input_vector_stream, string delimiter)//GREAT FOR SINGLE A SINGLE GEOMETRY FROM A VECTOR
{
    int num_of_atoms; num_of_atoms = input_vector_stream.size();
    
    vector<string> temp; 
    string element;
    vector<vector<string> > elements_array(4,vector<string>(num_of_atoms));
    for(int i=0; i < input_vector_stream.size() ; i++)
    {
    istringstream stream(input_vector_stream[i]); 
    while(stream >> element){     
       temp.insert(temp.end(),element);
      };//THE DELIMITER IS IN THE FUNCTION BECAUSE YOU HAVE THE OPTION TO USE ONE EX.  getline(stream, element, delimiter) 
    }

       for(int i=0 ; i < temp.size()/4 ; i++)
       {
           //cout <<temp[i*4] << "  " <<  temp[(i*4)+1] << "  " << temp[(i*4)+2] << "  " << temp[(i*4)+3] << endl;
           elements_array[0][i] = temp[i*4];
           elements_array[1][i] = temp[(i*4)+1];
           elements_array[2][i] = temp[(i*4)+2];
           elements_array[3][i] = temp[(i*4)+3];
       }
return elements_array;
}//END OF split_stream BRACKET










//NEEDS TO BE MODIFIED FOR GAUSSIAN OUTPUT
vector<string> Read_GAUSS(string name, int geometry_num) //FILE NAME AND GEOMETRY NUMBER
{
//Contains all the lines of the output file##########
vector<string> lines;                           //###
ifstream InFile;                                //###
string runner, GrabLine;//Identifying strings     ###
InFile.open(name, ios::in);                     //###
//Contains all the lines of the output file##########

//Identify the number of configurations generated//######
//int NDet;                                       //#######
vector<string> geometry;                         //#######
string Idcoords = "ATOMIC_POSITIONS";             //#######
int WrtCount = 0;                               //#######
//Identify the neumber of configurations generated#######

//Initial Getter from File###########################################################################################################
if (!InFile){cout << "Unable to open "<<name << "!!\n"; exit(1) ;} /*check if the file is open*/                                  //###
cout << name <<" is open!!" << endl;/*print something from the file stream*/                                                    //###
int line_counter=0;                                                                                                                                //###
while (getline(InFile,runner) )                                                                                                 //###
{                                                                                                                               //###
    GrabLine = runner;                                                                                                          //###
    lines.push_back(GrabLine);                                                                                                  //###
    line_counter++;
    if(GrabLine.find(Idcoords,0) != string::npos && WrtCount < 100000 )                                                              //###
    {                                                                                                                         //###
        WrtCount++;                                                                                                           //###
//        cout<< "found " << Idcoords << " |" << GrabLine << endl;                                                                //###
    if(WrtCount == geometry_num)
      {
        do{
           getline(InFile,runner);
           GrabLine = runner;                                                                                                   //###
           lines.push_back(GrabLine);
           line_counter++;
           geometry.push_back(lines[line_counter-1]); 
          }while(lines[line_counter-1].size() > 3);
      }  
    }                                                                                                                         //###
                                                                                                                                //###
}//loop over all lines of a file and save them to lines                                                                         //###
//cout << WrtCount << endl;
//for(int i=0;i < geometry.size(); i++){cout << geometry[i] << endl;}
InFile.close();                                                                                                                 //###
//Initial Getter from File###########################################################################################################
geometry.pop_back();
return geometry;
}












