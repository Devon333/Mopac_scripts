#include<iostream>
#include<fstream>
#include<string>
#include<sstream>
#include<vector>
#include<bits/stdc++.h>//insert function

//#include<cstdlib>//make directories
//#include</opt/local/include/gcc/c++/filesystem>//get current working directory
using namespace std;




vector<vector<double> > split_stream_QE_TIME(vector<string> input_vector_stream, string delimiter)//GREAT FOR MULTIPLE GEOMETRIES FROM A VECTOR
{   
    int num_of_atoms; num_of_atoms = input_vector_stream.size();

    vector<string> temp;
    string element;
    vector<vector<double> > elements_array(num_of_atoms,vector<double>(3));
    for(int i=0; i < input_vector_stream.size() ; i++)
    {
    istringstream stream(input_vector_stream[i]);
//    cout << input_vector_stream.size() << endl;
    while(stream >> element)
    {
//        cout << element << endl;
        if(element.size() == 0){cout << "end of geometry" << endl;}
        temp.insert(temp.end(),element);
    }
//    if(input_vector_stream[i].size() == 0) {continue;}
//        else
//        {
//            while(stream >> element)
//            {     
//            temp.insert(temp.end(),element);
//            };//THE DELIMITER IS IN THE FUNCTION BECAUSE YOU HAVE THE OPTION TO USE ONE EX.  getline(stream, element, delimiter) 
//        }
    }

       for(int i=0 ; i < num_of_atoms ; i++)
       {   
//           cout <<temp[i*4] << "  " <<  temp[(i*4)+1] << "  " << temp[(i*4)+2] << "  " << temp[(i*4)+3] << endl;//Atom types will not be stored
           //elements_array[0][i] = temp[i*4];//Atom types will not be stored 
           elements_array[i][0] = stod(temp[(i*4)+1]);
           elements_array[i][1] = stod(temp[(i*4)+2]);
           elements_array[i][2] = stod(temp[(i*4)+3]);
       }
return elements_array;
}//END OF split_stream BRACKET










vector<string> Read_QE_TIME(string name, int geometry_num) //FILE NAME AND GEOMETRY NUMBER
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



//FUNCTION TO MAKE A NEW DIRECTORY TO HOLD MOPAC INPUT FILES#####
void write_mopac_directory(string DirectoryName)
{
    string folder = DirectoryName;
    string mk_directory = "mkdir -p "+ folder;
    const char *make_dir = mk_directory.c_str();
    cout << make_dir << endl;
    system(make_dir);
//     cout << fs::current_path() << endl;
}
//FUNCTION TO MAKE A NEW DIRECTORY TO HOLD MOPAC INPUT FILES#####




//FUNCTION TO RUN MOPAC CALCULATIONS#########################################
void run_mopac_calculation(string mopac_input_name)
{
    string mopac_exec_path, mopac_submit_script_path;
    mopac_exec_path ="/home/gieseking/Programs/MOPAC2016/MOPAC2016.exe";
    mopac_submit_script_path ="/home/alvadillon/scripts/Run/mopac_sbatch.sh " + mopac_input_name;
    const char *b_mopac_submit_script_path = mopac_submit_script_path.c_str();
    const char *b_mopac_exec_path = mopac_exec_path.c_str();
    system(b_mopac_submit_script_path);
}
//FUNCTION TO RUN MOPAC CALCULATIONS#########################################




//WRITES THE INPUT FILES FOR MOPAC #######################################################################
void write_mopac_input(vector<vector<string> > atomic_coordinates, string FileName, string DirectoryName)
{
     string name = FileName;
     string directory ="./"+ DirectoryName + "/";
     ofstream File;
     File.open(directory+name);
     File << "INDO CHARGE=0 RCI MAXCI=4000 WRTCI=1000" << endl;
     File << endl;
     File << endl;
     for(int i=0; i <atomic_coordinates.size(); i++)
     {
     File << "  " << atomic_coordinates[0][i] << "      " << atomic_coordinates[1][i] << " 1      " << atomic_coordinates[2][i] << " 1      " << atomic_coordinates[3][i] << " 1      " << endl;
     }
     File << endl;
}
//WRITES THE INPUT FILES FOR MOPAC #######################################################################



//STRINGS TOGETHER FUNCTIONS TO READ GEOMETRY FROM TRAJECTORY FILE, WRITE MOPAC INPUT FILE, AND RUN MOPAC CALCULATION.
vector<vector<double> > QE_TIMESTEPS(string filename,int geometry_num,string base_mopac_filename, string directory_name)
{

    vector<string> coords1, coords2;
    vector<vector<double> > element_array1, element_array2 ;

    coords1 = Read_QE_TIME(filename, geometry_num);
    coords2 = Read_QE_TIME(filename, geometry_num+1);

    element_array1 = split_stream_QE_TIME(coords1," ");
    element_array2 = split_stream_QE_TIME(coords2," ");
    vector<vector<double> > element_array(element_array2.size(),vector<double>(3));
//    cout << element_array1.size() << "  " << element_array[0].size() << endl;
    for(int i=0; i<element_array1.size(); i++)
    {
        for(int j=0; j<3;j++)
        {
            element_array[i][j] = element_array2[i][j] - element_array1[i][j]; 
        }
    }


    for(int i=0; i<element_array1.size(); i++)
    {
        cout << element_array[i][0] << "  " << element_array[i][1] << "  " << element_array[i][2] << endl; 
    }

//    write_mopac_input(element_array, base_mopac_filename, directory_name);
//    run_mopac_calculation(base_mopac_filename);
return element_array;
}
//STRINGS TOGETHER FUNCTIONS TO READ GEOMETRY FROM TRAJECTORY FILE, WRITE MOPAC INPUT FILE, AND RUN MOPAC CALCULATION.









