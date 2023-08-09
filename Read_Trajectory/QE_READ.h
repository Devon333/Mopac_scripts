#include<iostream>
#include<fstream>
#include<string>
#include<sstream>
#include<vector>
#include<bits/stdc++.h>//insert function
//#include <filesystem>


//#include<cstdlib>//make directories
//#include</opt/local/include/gcc/c++/filesystem>//get current working directory
using namespace std;




vector<vector<string> > split_stream_QE(vector<string> input_vector_stream, string delimiter)//GREAT FOR MULTIPLE GEOMETRIES FROM A VECTOR
{   
    int num_of_atoms; num_of_atoms = input_vector_stream.size();

    vector<string> temp;
    string element;
    vector<vector<string> > elements_array(4,vector<string>(num_of_atoms));
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
   
       for(int i=0 ; i < temp.size()/4 ; i++)
       {   
//           cout <<temp[i*4] << "  " <<  temp[(i*4)+1] << "  " << temp[(i*4)+2] << "  " << temp[(i*4)+3] << endl;
           elements_array[0][i] = temp[i*4];
           elements_array[1][i] = temp[(i*4)+1];
           elements_array[2][i] = temp[(i*4)+2];
           elements_array[3][i] = temp[(i*4)+3];
       }
return elements_array;
}//END OF split_stream BRACKET










vector<string> Read_QE(string name, int geometry_num) //FILE NAME AND GEOMETRY NUMBER
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


//FUNCTION TO COPY INDO PARAMETERS INTO THE NEW DIRECTORY
void copy_INDO_PAR(string DirectoryName)
{
    string copy_str, path_to_par, traj_dir, copy_par;
    copy_str = "cp " ;
    traj_dir = " ./";
    path_to_par ="/home/alvadillon/scripts/INDO_ANAL/INDO1S.par";
    copy_par = copy_str + path_to_par + traj_dir; 
    const char *b_copy_par = copy_par.c_str();
    system(b_copy_par);

}
//FUNCTION TO COPY INDO PARAMETERS INTO THE NEW DIRECTORY


//FUNCTION TO RUN MOPAC CALCULATIONS#########################################
void run_mopac_calculation(string mopac_input_name, string DirectoryName)
{
    string mopac_exec_path, mopac_submit_script_path, path_begin, separator;
    path_begin = " ./"; separator = "/";
    mopac_exec_path ="/home/alvadillon/software/MOPAC_clean/MOPAC2016.exe";
    //mopac_exec_path ="/home/gieseking/Programs/MOPAC2016/MOPAC2016.exe";
    ifstream path;
    path.open(mopac_exec_path);
    if(path)
    {  
        cout << "exists"<< endl;
        mopac_submit_script_path ="/home/alvadillon/scripts/Run/mopac_sbatch.sh " +path_begin +DirectoryName +separator +mopac_input_name;
        const char *b_mopac_submit_script_path = mopac_submit_script_path.c_str();
        const char *b_mopac_exec_path = mopac_exec_path.c_str();
        //const char *b_file_path = file_path.c_str();
        system(b_mopac_submit_script_path);
    }
    else{
        cout << "does not exist" << endl;
    }
}
//FUNCTION TO RUN MOPAC CALCULATIONS#########################################




//WRITES THE INPUT FILES FOR MOPAC #######################################################################
void write_mopac_input(vector<vector<string> > atomic_coordinates, string FileName, string DirectoryName, string charge, string cutoff_criteria, string method)
{
     //string cutoff_criteria;//="0.000001";
     string name = FileName;
     string directory ="./"+ DirectoryName + "/";
     ofstream File;
     File.open(directory+name);
     //File << "INDO RCI MAXCI=4000 WRTCI=1000 CHARGE="<<charge << " RELSCF="<<cutoff_criteria<< endl;
     File << method <<" CHARGE="<<charge << " RELSCF="<<cutoff_criteria << " ALLVEC"<< endl;
     File << endl;
     File << endl;
     for(int i=0; i <atomic_coordinates[0].size(); i++)
     {
     File << "  " << atomic_coordinates[0][i] << "      " << atomic_coordinates[1][i] << " 1      " << atomic_coordinates[2][i] << " 1      " << atomic_coordinates[3][i] << " 1      " << endl;
     }
     File << endl;
}
//WRITES THE INPUT FILES FOR MOPAC #######################################################################



//STRINGS TOGETHER FUNCTIONS TO READ GEOMETRY FROM TRAJECTORY FILE, WRITE MOPAC INPUT FILE, AND RUN MOPAC CALCULATION.
void QE_TO_MOPAC(string filename,int geometry_num,string base_mopac_filename, string directory_name, string charge, string cutoff_criteria, string method)
{
    ofstream xyz_output;
    vector<string> coords;
    vector<vector<string> > element_array;
    coords = Read_QE(filename, geometry_num);
    element_array = split_stream_QE(coords," ");
    xyz_output.open("traj.xyz", std::ofstream::out | std::ofstream::app);
    xyz_output <<element_array[0].size() << endl;
    xyz_output << "step= "<< geometry_num << endl;
    for(int i=0; i < element_array[0].size(); i++)
    {
        xyz_output << "  " << element_array[0][i] << "      " << element_array[1][i] << "      " << element_array[2][i] << "      " << element_array[3][i] << "      " << endl;
    }
    write_mopac_input(element_array, base_mopac_filename, directory_name, charge, cutoff_criteria, method);
    run_mopac_calculation(base_mopac_filename, directory_name);
}
//STRINGS TOGETHER FUNCTIONS TO READ GEOMETRY FROM TRAJECTORY FILE, WRITE MOPAC INPUT FILE, AND RUN MOPAC CALCULATION.









