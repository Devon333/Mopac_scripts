#include<iostream>
#include<iterator>
#include<fstream>
#include<sstream>
#include<vector>
#include<bits/stdc++.h>//insert function

using namespace std; 


vector<string> Read(string name)
{
//Contains all the lines of the output file##########
vector<string> lines;                           //###
ifstream InFile;                                //###
string runner, GrabLine;//Identifying strings     ###
InFile.open(name, ios::in);                     //###
//Contains all the lines of the output file##########

//Identify the number of configurations generated//######
int NDet;                                       //#######
vector<string> VecNDet;                         //#######
string IdNDet = "WRTCI";                        //#######
int WrtCount = 0;                               //#######
//Identify the neumber of configurations generated#######

//Initial Getter from File###########################################################################################################
if (!InFile){cout << "Unable to open "<<name << "!!\n"; exit(1) ;} /*check if the file is open*/                                  //###
//cout << name <<" is open!!" << endl;/*print something from the file stream*/                                                    //###
                                                                                                                                //###
while (getline(InFile,runner) )                                                                                                 //###
{                                                                                                                               //###
    GrabLine = runner;                                                                                                          //###
    lines.push_back(GrabLine);                                                                                                  //###
                                                                                                                                //###
//    if(GrabLine.find(IdNDet,0) != string::npos && WrtCount < 1 )                                                              //###
//    {                                                                                                                         //###
//        cout<< "found " << IdNDet << " |" << GrabLine << endl;                                                                //###
//        istringstream split(GrabLine); //split is a variable where GrabLine is split into individual string split by white space//##
//        back_inserter(VecNDet));//appends individual strings into the vector VecNDet                                          //###
//        NDet = stoi(VecNDet[3]);//Stores the number of determinants generated as a variable                                   //###
//        cout << NDet << endl;                                                                                                 //###
//        WrtCount++;                                                                                                           //###
//    }                                                                                                                         //###
                                                                                                                                //###
}//loop over all lines of a file and save them to lines                                                                         //###
//cout << "using ReadFile" << endl;                                                                                             //###
InFile.close();                                                                                                                 //###
//if (!InFile){cout << name <<" closed"<<endl;} //check if the file is open                                                       //###
//else {cout << name << " is still open"; exit(1);}//print something from the file stream                                         //###
//Initial Getter from File###########################################################################################################

return lines;
}


vector<string> PM7MOs(string filename)
{
//Contains all the lines of the output file##########
vector<string> lines;                           //###
ifstream InFile;                                //###
string runner, GrabLine;//Identifying strings     ###
InFile.open(filename, ios::in);                     //###
//Contains all the lines of the output file##########

//Identify the number of molecular orbitals//#######
//int MOs;                                 //#######
vector<string> VecMOs;                     //#######
string IdNMOs ="Empirical Formula:";       //#######
int WrtCount = 0;                          //#######
//Identify the number of molecular orbitals#########

//Initial Getter from File############################################################################################################
if (!InFile){cout << "Unable to open "<<filename << "!!\n"; exit(1) ;} /*check if the file is open*/                                   //###
//cout << name <<" is open!!" << endl;/*print something from the file stream*/                                                     //###
                                                                                                                                 //###
while (getline(InFile,runner) )                                                                                                  //###
{                                                                                                                                //###
    GrabLine = runner;                                                                                                           //###
    lines.push_back(GrabLine);                                                                                                   //###
                                                                                                                                 //###
    if(GrabLine.find(IdNMOs,0) != string::npos && WrtCount < 1 )                                                                 //###
    {                                                                                                                            //###
        cout<< "found " << IdNMOs << " |" << GrabLine << endl;                                                                   //###
        istringstream split(GrabLine); //split is a variable where GrabLine is split into individual string split by white space //##
        copy(istream_iterator<string>(split),
        istream_iterator<string>(),                                                                                              //###
        back_inserter(VecMOs));//appends individual strings into the vector VecMOs                                               //###
        //MOs = (VecNDet[2]);//Stores the number of determinants generated as a variable                                         //###
        //cout << VecMOs << endl;                                                                                                  //##
        WrtCount++;
        cout << " using MOs " << endl;                                                                          //##
    }                                                                                                                            //##
                                                                                                                                 //##
}//loop over all lines of a file and save them to lines                                                                          ####
                                                                                                                                 //##
InFile.close();                                                                                                                  //##
//if (!InFile){cout << name <<" closed"<<endl;} //check if the file is open                                                        ####
//else {cout << name << " is still open"; exit(1);}//print something from the file stream                                          ####
//Initial Getter from File###########################################################################################################

return VecMOs;
}




vector<string> MOs(string filename)
{
//Contains all the lines of the output file##########
vector<string> lines;                           //###
ifstream InFile;                                //###
string runner, GrabLine;//Identifying strings     ###
InFile.open(filename, ios::in);                     //###
//Contains all the lines of the output file##########

//Identify the number of molecular orbitals//#######
//int MOs;                                 //#######
vector<string> VecMOs;                     //#######
string IdNMOs = "TOTAL";                   //#######
int WrtCount = 0;                          //#######
//Identify the number of molecular orbitals#########

//Initial Getter from File############################################################################################################
if (!InFile){cout << "Unable to open "<<filename << "!!\n"; exit(1) ;} /*check if the file is open*/                                   //###
//cout << name <<" is open!!" << endl;/*print something from the file stream*/                                                     //###
                                                                                                                                 //###
while (getline(InFile,runner) )                                                                                                  //###
{                                                                                                                                //###
    GrabLine = runner;                                                                                                           //###
    lines.push_back(GrabLine);                                                                                                   //###
                                                                                                                                 //###
    if(GrabLine.find(IdNMOs,0) != string::npos && WrtCount < 1 )                                                                 //###
    {                                                                                                                            //###
        cout<< "found " << IdNMOs << " |" << GrabLine << endl;                                                                   //###
        istringstream split(GrabLine); //split is a variable where GrabLine is split into individual string split by white space //##
        copy(istream_iterator<string>(split),
        istream_iterator<string>(),                                                                                              //###
        back_inserter(VecMOs));//appends individual strings into the vector VecMOs                                               //###
        //MOs = (VecNDet[2]);//Stores the number of determinants generated as a variable                                         //###
        //cout << VecMOs << endl;                                                                                                  //##
        WrtCount++;
        cout << " using MOs " << endl;                                                                          //##
    }                                                                                                                            //##
                                                                                                                                 //##
}//loop over all lines of a file and save them to lines                                                                          ####
                                                                                                                                 //##
InFile.close();                                                                                                                  //##
//if (!InFile){cout << name <<" closed"<<endl;} //check if the file is open                                                        ####
//else {cout << name << " is still open"; exit(1);}//print something from the file stream                                          ####
//Initial Getter from File###########################################################################################################

return VecMOs;
}



int AtomNums(string filename)
{
//string name;
/*for later use *///cout << "enter file name" << endl;/*prompt user for the file name*/
//cin >> name;
//string name = FileName;
//Contains all the lines of the output file##########
vector<string> lines;                           //###
ifstream InFile;                                //###
string runner, GrabLine;//Identifying strings     ###
InFile.open(filename, ios::in);                     //###
//Contains all the lines of the output file##########

//Identify the number of molecular orbitals//######
//int MOs;                                       //#######  
vector<string> numberofatomsstring;                         //#######
int numofatoms;
string IdAtomNum = "atoms";                         //#######
int WrtCount = 0;                               //#######
//Identify the number of molecular orbitals#######

//Initial Getter from File###########################################################################################################
if (!InFile){cout << "Unable to open "<< filename << "!!\n"; exit(1) ;} /*check if the file is open*/                                   //###
//cout << name <<" is open!!" << endl;/*print something from the file stream*/                                                     //###
                                                                                                                                 //###
while (getline(InFile,runner) )                                                                                                  //###
{                                                                                                                                //###
    GrabLine = runner;                                                                                                           //###
    lines.push_back(GrabLine);                                                                                                   //###
                                                                                                                                 //###
    if(GrabLine.find(IdAtomNum,0) != string::npos && WrtCount < 1 )                                                                 //###
    {                                                                                                                            //###
        cout<< "found " << IdAtomNum << " |" << GrabLine << endl;                                                                   //###
        istringstream split(GrabLine); //split is a variable where GrabLine is split into individual string split by white space //##
        copy(istream_iterator<string>(split),                                                                                    
        istream_iterator<string>(),                                                                                              //###
        back_inserter(numberofatomsstring));//appends individual strings into the vector VecMOs                                               //###
        //MOs = (VecNDet[2]);//Stores the number of determinants generated as a variable                                         //###
        //cout << NDet << endl;                                                                                                  //##
        WrtCount++; 
        int index = numberofatomsstring.size(); 
        cout << numberofatomsstring[index-2] << endl;
        numofatoms = stoi(numberofatomsstring[index-2]);                                                             
        cout << " using AtomNums " << endl;                                                                          //##        
    }                                                                                                                            //##
                                                                                                                                 //##
}//loop over all lines of a file and save them to lines                                                                          ####
                                                                                                                                 //##
InFile.close();                                                                                                                  //##
//if (!InFile){cout << name <<" closed"<<endl;} //check if the file is open                                                        ####
//else {cout << name << " is still open"; exit(1);}//print something from the file stream                                          ####
//Initial Getter from File###########################################################################################################

return numofatoms;
}


vector<vector<string> > MO_arrange(int line_size, int set, int i, int numMOs, vector<string> MOEigenvectorbytes)
{
vector<vector<string> > MOCoeffs;

        switch(line_size)
        {
            case 19:
                MOCoeffs[0+(set*15)][i]= (MOEigenvectorbytes[4]); MOCoeffs[1+(set*15)][i]= (MOEigenvectorbytes[5]); MOCoeffs[2+(set*15)][i]= (MOEigenvectorbytes[6]);
                MOCoeffs[3+(set*15)][i]= (MOEigenvectorbytes[7]); MOCoeffs[4+(set*15)][i]= (MOEigenvectorbytes[8]);
                MOCoeffs[5+(set*15)][i]= (MOEigenvectorbytes[9]); MOCoeffs[6+(set*15)][i]= (MOEigenvectorbytes[10]); MOCoeffs[7+(set*15)][i]= (MOEigenvectorbytes[11]);
                MOCoeffs[8+(set*15)][i]= (MOEigenvectorbytes[12]); MOCoeffs[9+(set*15)][i]= (MOEigenvectorbytes[13]);
                MOCoeffs[10+(set*15)][i]= (MOEigenvectorbytes[14]); MOCoeffs[11+(set*15)][i]= (MOEigenvectorbytes[15]); MOCoeffs[12+(set*15)][i]= (MOEigenvectorbytes[16]);
                MOCoeffs[13+(set*15)][i]= (MOEigenvectorbytes[17]); MOCoeffs[14+(set*15)][i]= (MOEigenvectorbytes[18]);
                break;
            case 6:
                MOCoeffs[numMOs-2][i] = (MOEigenvectorbytes[4]); MOCoeffs[numMOs-1][i] = (MOEigenvectorbytes[5]);
                break;

            case 7:
                MOCoeffs[numMOs-3][i] = (MOEigenvectorbytes[4]); MOCoeffs[numMOs-2][i] = (MOEigenvectorbytes[5]); MOCoeffs[numMOs-1][i] = (MOEigenvectorbytes[6]);
                break;

            case 8:
                MOCoeffs[numMOs-4][i] = (MOEigenvectorbytes[4]); MOCoeffs[numMOs-3][i] = (MOEigenvectorbytes[5]); MOCoeffs[numMOs-2][i] = (MOEigenvectorbytes[6]); MOCoeffs[numMOs-1][i] = (MOEigenvectorbytes[7]);
                break;

            case 9:
                MOCoeffs[numMOs-5][i] = (MOEigenvectorbytes[4]); MOCoeffs[numMOs-4][i] = (MOEigenvectorbytes[5]); MOCoeffs[numMOs-3][i] = (MOEigenvectorbytes[6]); MOCoeffs[numMOs-2][i] = (MOEigenvectorbytes[7]); MOCoeffs[numMOs-1][i] = (MOEigenvectorbytes[8]);
                break;

            case 10:
                MOCoeffs[numMOs-6][i] = (MOEigenvectorbytes[4]); MOCoeffs[numMOs-5][i] = (MOEigenvectorbytes[5]); MOCoeffs[numMOs-4][i] = (MOEigenvectorbytes[6]); MOCoeffs[numMOs-3][i] = (MOEigenvectorbytes[7]); MOCoeffs[numMOs-2][i] = (MOEigenvectorbytes[8]); MOCoeffs[numMOs-1][i] = (MOEigenvectorbytes[9]);
                break;

            case 11:
                MOCoeffs[numMOs-7][i] = (MOEigenvectorbytes[4]); MOCoeffs[numMOs-6][i] = (MOEigenvectorbytes[5]); MOCoeffs[numMOs-5][i] = (MOEigenvectorbytes[6]); MOCoeffs[numMOs-4][i] = (MOEigenvectorbytes[7]); MOCoeffs[numMOs-3][i] = (MOEigenvectorbytes[8]); MOCoeffs[numMOs-2][i] = (MOEigenvectorbytes[9]); MOCoeffs[numMOs-1][i] = (MOEigenvectorbytes[10]);
                break;


            case 12:
                MOCoeffs[numMOs-8][i] = (MOEigenvectorbytes[4]); MOCoeffs[numMOs-7][i] = (MOEigenvectorbytes[5]); MOCoeffs[numMOs-6][i] = (MOEigenvectorbytes[6]); MOCoeffs[numMOs-5][i] = (MOEigenvectorbytes[7]); MOCoeffs[numMOs-4][i] = (MOEigenvectorbytes[8]); MOCoeffs[numMOs-3][i] = (MOEigenvectorbytes[9]); MOCoeffs[numMOs-2][i] = (MOEigenvectorbytes[10]);  MOCoeffs[numMOs-1][i] = (MOEigenvectorbytes[11]);
                break;

            case 13:
                MOCoeffs[numMOs-9][i] = (MOEigenvectorbytes[4]); MOCoeffs[numMOs-8][i] = (MOEigenvectorbytes[5]); MOCoeffs[numMOs-7][i] = (MOEigenvectorbytes[6]); MOCoeffs[numMOs-6][i] = (MOEigenvectorbytes[7]); MOCoeffs[numMOs-5][i] = (MOEigenvectorbytes[8]); MOCoeffs[numMOs-4][i] = (MOEigenvectorbytes[9]); MOCoeffs[numMOs-3][i] = (MOEigenvectorbytes[10]);  MOCoeffs[numMOs-2][i] = (MOEigenvectorbytes[11]); MOCoeffs[numMOs-1][i] = (MOEigenvectorbytes[12]);
                break;

            case 14:
                MOCoeffs[numMOs-10][i] = (MOEigenvectorbytes[4]); MOCoeffs[numMOs-9][i] = (MOEigenvectorbytes[5]); MOCoeffs[numMOs-8][i] = (MOEigenvectorbytes[6]); MOCoeffs[numMOs-7][i] = (MOEigenvectorbytes[7]); MOCoeffs[numMOs-6][i] = (MOEigenvectorbytes[8]); MOCoeffs[numMOs-5][i] = (MOEigenvectorbytes[9]); MOCoeffs[numMOs-4][i] = (MOEigenvectorbytes[10]); MOCoeffs[numMOs-3][i] = (MOEigenvectorbytes[11]);  MOCoeffs[numMOs-2][i] = (MOEigenvectorbytes[12]); MOCoeffs[numMOs-1][i] = (MOEigenvectorbytes[13]);
                break;

            case 15:
                MOCoeffs[numMOs-11][i] = (MOEigenvectorbytes[4]); MOCoeffs[numMOs-10][i] = (MOEigenvectorbytes[5]); MOCoeffs[numMOs-9][i] = (MOEigenvectorbytes[6]); MOCoeffs[numMOs-8][i] = (MOEigenvectorbytes[7]); MOCoeffs[numMOs-7][i] = (MOEigenvectorbytes[8]); MOCoeffs[numMOs-6][i] = (MOEigenvectorbytes[9]); MOCoeffs[numMOs-5][i] = (MOEigenvectorbytes[10]); MOCoeffs[numMOs-4][i] = (MOEigenvectorbytes[11]); MOCoeffs[numMOs-3][i] = (MOEigenvectorbytes[12]);  MOCoeffs[numMOs-2][i] = (MOEigenvectorbytes[13]); MOCoeffs[numMOs-1][i] = (MOEigenvectorbytes[14]);
                break;

            case 16:
                MOCoeffs[numMOs-12][i] = (MOEigenvectorbytes[4]); MOCoeffs[numMOs-11][i] = (MOEigenvectorbytes[5]); MOCoeffs[numMOs-10][i] = (MOEigenvectorbytes[6]); MOCoeffs[numMOs-9][i] = (MOEigenvectorbytes[7]); MOCoeffs[numMOs-8][i] = (MOEigenvectorbytes[8]); MOCoeffs[numMOs-7][i] = (MOEigenvectorbytes[9]); MOCoeffs[numMOs-6][i] = (MOEigenvectorbytes[10]); MOCoeffs[numMOs-5][i] = (MOEigenvectorbytes[11]); MOCoeffs[numMOs-4][i] = (MOEigenvectorbytes[12]); MOCoeffs[numMOs-3][i] = (MOEigenvectorbytes[13]);  MOCoeffs[numMOs-2][i] = (MOEigenvectorbytes[14]); MOCoeffs[numMOs-1][i] = (MOEigenvectorbytes[15]);
                break;

            case 17:
                MOCoeffs[numMOs-13][i] = (MOEigenvectorbytes[4]); MOCoeffs[numMOs-12][i] = (MOEigenvectorbytes[5]); MOCoeffs[numMOs-11][i] = (MOEigenvectorbytes[6]); MOCoeffs[numMOs-10][i] = (MOEigenvectorbytes[7]); MOCoeffs[numMOs-9][i] = (MOEigenvectorbytes[8]); MOCoeffs[numMOs-8][i] = (MOEigenvectorbytes[9]); MOCoeffs[numMOs-7][i] = (MOEigenvectorbytes[10]); MOCoeffs[numMOs-6][i] = (MOEigenvectorbytes[11]); MOCoeffs[numMOs-5][i] = (MOEigenvectorbytes[12]); MOCoeffs[numMOs-4][i] = (MOEigenvectorbytes[13]); MOCoeffs[numMOs-3][i] = (MOEigenvectorbytes[14]);  MOCoeffs[numMOs-2][i] = (MOEigenvectorbytes[15]); MOCoeffs[numMOs-1][i] = (MOEigenvectorbytes[16]);
                break;
        }
return MOCoeffs;
}


vector<string> MO_VECTOR_LINES(string filename)
{
//Variables to extract molecular orbital info in file##########
string eigval_find ="eigval";
int atomnumbers = AtomNums(filename);
vector<string> numberofMOs = MOs(filename);
int numMOs = stoi(numberofMOs[1]);
vector<string> MOEigenvectorlines;
//Variables to extract molecular orbital info in file##########

//Contains all the lines of the output file##########
vector<string> lines = Read(filename);              //###
//Contains all the lines of the output file##########
int WrtCount=0;
for(int i=0; i < lines.size();i++)
{   
    istringstream split(lines[i]);
    
    if(lines[i].find(eigval_find,0) != std::string::npos )                             //####
    {  
       WrtCount++;       
       // cout << " found " << eigval_find << "\t " << lines[i] << endl;
       // MOEigenvalsLines.push_back(lines[i]);
       // cout << MOEigenvalsLines[i] << endl;
        for(int j=4; j < stoi(numberofMOs[1]) + atomnumbers +4 ; j++)
        {   
            if(lines[i+j].size() == 1){continue;}
            if(lines[i+j].size() >= 5)
            {
                MOEigenvectorlines.push_back(lines[i+j]);//<< "  " <<  MOEigenvectorlines[i+j][3] << "  " << MOEigenvectorlines[i+j][4] << endl;
//                cout << lines[i+j] << endl;
            }
        }
    }
}
cout << WrtCount << endl;
return MOEigenvectorlines;
}


vector<string> Eigenvectorlines_split(string MOEigenvectorlines)
{
    vector<vector<string> > MO_MATRIX;
    vector<string> Byte;
    string element;
    int num_lines = 0;

        istringstream temp(MOEigenvectorlines);
        while(temp >> element)
        {
            Byte.insert(Byte.end(),element);
//            cout << element << "   ";
        }

//        for(int len=0; len < Byte.size(); len++){cout << Byte[len] << "  " << len << endl;}
return Byte;
}


//FUNCTION TO PARSE FILE FOR MOs THAT HAVE D ORBITALS
bool HasDOrb(vector<string> MO_element){
const string MO_char = MO_element[1];
//cout << MO_element[0] << " " << MO_element[1] << endl;
//cout << "element size " <<  MO_char.length() << endl; 
    for(int i=0; i < MO_char.length();i++)
    {
        //cout << MO_char[i] << endl;
        if( !(MO_char[i] >= '0' && MO_char[i] <='9')){ /*cout << " this is not an integer" << endl;*/ return false;}
        //cout << "this is not an integer" << endl; return false; continue;}
    } 
return true;}
//FUNCTION TO PARSE FILE FOR MOs THAT HAVE D ORBITALS



vector<vector<double> > MO_Matrix( string filename)
{
    vector<string> numberofMOs = MOs(filename);
    int numMOs = stoi(numberofMOs[1]);
    vector<vector<double> > MO_MATRIX(numMOs,vector<double>(numMOs)) ;
    vector<string> LINES;
    vector<string> MO_line;
    LINES = MO_VECTOR_LINES(filename);
    int size = LINES.size();
    int size2 = size;
    cout << size << endl;
    int set = 0;   

    for(int l=0; l < 10; l++){if(size2 % numMOs ==0){break;} else size2=size2-1;}
    int looptimes = size2/numMOs;

    for(int k=0 ; k < looptimes; k++)
    {
    for(int i=0 ; i < numMOs; i++)
     {
        MO_line = Eigenvectorlines_split(LINES[i+(set*numMOs)]);
//        for(int j=0; j < numMOs; j++)
//        {
           int numElements = Eigenvectorlines_split(LINES[i+(set*numMOs)]).size();
           //cout << numElements << endl;
           if(HasDOrb(MO_line) == 0)
           {
               if(numElements == 18)
               {
                   MO_MATRIX[i][0+(set*15)] =stod(MO_line[3]) ; MO_MATRIX[i][1+(set*15)]  =stod(MO_line[4]) ; MO_MATRIX[i][2+(set*15)]  =stod(MO_line[5]) ;
                   MO_MATRIX[i][3+(set*15)] =stod(MO_line[6]) ; MO_MATRIX[i][4+(set*15)]  =stod(MO_line[7]) ; MO_MATRIX[i][5+(set*15)]  =stod(MO_line[8]) ;
                   MO_MATRIX[i][6+(set*15)] =stod(MO_line[9]) ; MO_MATRIX[i][7+(set*15)]  =stod(MO_line[10]) ; MO_MATRIX[i][8+(set*15)] =stod(MO_line[11]) ;
                   MO_MATRIX[i][9+(set*15)] =stod(MO_line[12]) ;MO_MATRIX[i][10+(set*15)] =stod(MO_line[13]) ; MO_MATRIX[i][11+(set*15)]=stod(MO_line[14]) ;
                   MO_MATRIX[i][12+(set*15)]=stod(MO_line[15]) ; MO_MATRIX[i][13+(set*15)]=stod(MO_line[16]) ; MO_MATRIX[i][14+(set*15)]=stod(MO_line[17]);
               }
             
               if(numElements == 17)
               {
                   MO_MATRIX[i][0+(set*15)] =stod(MO_line[2]) ; MO_MATRIX[i][1+(set*15)]  =stod(MO_line[3]) ; MO_MATRIX[i][2+(set*15)]  =stod(MO_line[4]) ;
                   MO_MATRIX[i][3+(set*15)] =stod(MO_line[5]) ; MO_MATRIX[i][4+(set*15)]  =stod(MO_line[6]) ; MO_MATRIX[i][5+(set*15)]  =stod(MO_line[7]) ;
                   MO_MATRIX[i][6+(set*15)] =stod(MO_line[8]) ; MO_MATRIX[i][7+(set*15)]  =stod(MO_line[9]) ; MO_MATRIX[i][8+(set*15)]  =stod(MO_line[10]) ;
                   MO_MATRIX[i][9+(set*15)] =stod(MO_line[11]) ;MO_MATRIX[i][10+(set*15)] =stod(MO_line[12]) ; MO_MATRIX[i][11+(set*15)]=stod(MO_line[13]) ;
                   MO_MATRIX[i][12+(set*15)]=stod(MO_line[14]) ; MO_MATRIX[i][13+(set*15)]=stod(MO_line[15]) ; MO_MATRIX[i][14+(set*15)]=stod(MO_line[16]);
               }

               if(numElements == 15)
               {
                   MO_MATRIX[i][numMOs-12]=stod(MO_line[3]); MO_MATRIX[i][numMOs-11]=stod(MO_line[4]); MO_MATRIX[i][numMOs-10]=stod(MO_line[5]);
                   MO_MATRIX[i][numMOs-9]=stod(MO_line[6]);  MO_MATRIX[i][numMOs-8]=stod(MO_line[7]); MO_MATRIX[i][numMOs-7]=stod(MO_line[8]);
                   MO_MATRIX[i][numMOs-6]=stod(MO_line[9]);  MO_MATRIX[i][numMOs-5]=stod(MO_line[10]); MO_MATRIX[i][numMOs-4]=stod(MO_line[11]);
                   MO_MATRIX[i][numMOs-3]=stod(MO_line[12]); MO_MATRIX[i][numMOs-2]=stod(MO_line[13]); MO_MATRIX[i][numMOs-1]=stod(MO_line[14]);
               }

               if(numElements == 14)
               {
                   MO_MATRIX[i][numMOs-12]=stod(MO_line[2]); MO_MATRIX[i][numMOs-11]=stod(MO_line[3]); MO_MATRIX[i][numMOs-10]=stod(MO_line[4]);
                   MO_MATRIX[i][numMOs-9]=stod(MO_line[5]); MO_MATRIX[i][numMOs-8]=stod(MO_line[6]); MO_MATRIX[i][numMOs-7]=stod(MO_line[7]);
                   MO_MATRIX[i][numMOs-6]=stod(MO_line[8]); MO_MATRIX[i][numMOs-5]=stod(MO_line[9]); MO_MATRIX[i][numMOs-4]=stod(MO_line[10]);
                   MO_MATRIX[i][numMOs-3]=stod(MO_line[11]); MO_MATRIX[i][numMOs-2]=stod(MO_line[12]); MO_MATRIX[i][numMOs-1]=stod(MO_line[13]);

               }
 
               if(numElements == 9)
               {
                   MO_MATRIX[i][numMOs-6]=stod(MO_line[3]); MO_MATRIX[i][numMOs-5]=stod(MO_line[4]); MO_MATRIX[i][numMOs-4]=stod(MO_line[5]);
                   MO_MATRIX[i][numMOs-3]=stod(MO_line[6]); MO_MATRIX[i][numMOs-2]=stod(MO_line[7]); MO_MATRIX[i][numMOs-1]=stod(MO_line[8]);
               }

               if(numElements == 8)
               {
                   MO_MATRIX[i][numMOs-6]=stod(MO_line[2]); MO_MATRIX[i][numMOs-5]=stod(MO_line[3]); MO_MATRIX[i][numMOs-4]=stod(MO_line[4]);
                   MO_MATRIX[i][numMOs-3]=stod(MO_line[5]); MO_MATRIX[i][numMOs-2]=stod(MO_line[6]); MO_MATRIX[i][numMOs-1]=stod(MO_line[7]);
               }

           }

//           cout << MO_line[4] << " " << MO_line[5] << " " << MO_line[6] << " " << MO_line[7] << " " << MO_line[8] << " " << MO_line[9] << " " << MO_line[10] << " " << MO_line[11] << " " << MO_line[12] << " " << MO_line[13] << " " << MO_line[14] << " " << MO_line[15] << " " << MO_line[16] << " " << MO_line[17] << " " << MO_line[18] <<  endl;
       if(HasDOrb(MO_line) == 1)
       {    
           if(numElements == 19)
           {
            MO_MATRIX[i][0+(set*15)] =stod(MO_line[4]) ; MO_MATRIX[i][1+(set*15)]  =stod(MO_line[5]) ; MO_MATRIX[i][2+(set*15)]  =stod(MO_line[6]) ; 
            MO_MATRIX[i][3+(set*15)] =stod(MO_line[7]) ; MO_MATRIX[i][4+(set*15)]  =stod(MO_line[8]) ; MO_MATRIX[i][5+(set*15)]  =stod(MO_line[9]) ; 
            MO_MATRIX[i][6+(set*15)] =stod(MO_line[10]) ; MO_MATRIX[i][7+(set*15)] =stod(MO_line[11]) ; MO_MATRIX[i][8+(set*15)] =stod(MO_line[12]) ;
            MO_MATRIX[i][9+(set*15)] =stod(MO_line[13]) ;MO_MATRIX[i][10+(set*15)] =stod(MO_line[14]) ; MO_MATRIX[i][11+(set*15)]=stod(MO_line[15]) ;
            MO_MATRIX[i][12+(set*15)]=stod(MO_line[16]) ; MO_MATRIX[i][13+(set*15)]=stod(MO_line[17]) ; MO_MATRIX[i][14+(set*15)]=stod(MO_line[18]);
            }
            if(numElements == 17)
            {
                MO_MATRIX[i][numMOs-13]=stod(MO_line[4]);  MO_MATRIX[i][numMOs-12]=stod(MO_line[5]);  MO_MATRIX[i][numMOs-11]=stod(MO_line[6]);
                MO_MATRIX[i][numMOs-10]=stod(MO_line[7]);  MO_MATRIX[i][numMOs-9] =stod(MO_line[8]);  MO_MATRIX[i][numMOs-8] =stod(MO_line[9]); 
                MO_MATRIX[i][numMOs-7] =stod(MO_line[10]); MO_MATRIX[i][numMOs-6] =stod(MO_line[11]); MO_MATRIX[i][numMOs-5] =stod(MO_line[12]);
                MO_MATRIX[i][numMOs-4] =stod(MO_line[13]); MO_MATRIX[i][numMOs-3] =stod(MO_line[14]); MO_MATRIX[i][numMOs-2] =stod(MO_line[15]); 
                MO_MATRIX[i][numMOs-1] =stod(MO_line[16]);
            }
            if(numElements == 16)
            { 
                MO_MATRIX[i][numMOs-12]=stod(MO_line[4]);    MO_MATRIX[i][numMOs-11]=stod(MO_line[5]);  MO_MATRIX[i][numMOs-10]=stod(MO_line[6]);
                MO_MATRIX[i][numMOs-9] =stod(MO_line[7]);   MO_MATRIX[i][numMOs-8]  =stod(MO_line[8]);  MO_MATRIX[i][numMOs-7] =stod(MO_line[9]);
                MO_MATRIX[i][numMOs-6] =stod(MO_line[10]);  MO_MATRIX[i][numMOs-5]  =stod(MO_line[11]); MO_MATRIX[i][numMOs-4] =stod(MO_line[12]);
                MO_MATRIX[i][numMOs-3] =stod(MO_line[13]);  MO_MATRIX[i][numMOs-2]  =stod(MO_line[14]); MO_MATRIX[i][numMOs-1] =stod(MO_line[15]);
            }
            if(numElements == 15)
            {
                MO_MATRIX[i][numMOs-11]=stod(MO_line[4]);  MO_MATRIX[i][numMOs-10]=stod(MO_line[5]);  MO_MATRIX[i][numMOs-9]=stod(MO_line[6]);
                MO_MATRIX[i][numMOs-8] =stod(MO_line[7]);  MO_MATRIX[i][numMOs-7] =stod(MO_line[8]);  MO_MATRIX[i][numMOs-6]=stod(MO_line[9]);
                MO_MATRIX[i][numMOs-5] =stod(MO_line[10]); MO_MATRIX[i][numMOs-4] =stod(MO_line[11]); MO_MATRIX[i][numMOs-3]=stod(MO_line[12]);
                MO_MATRIX[i][numMOs-2] =stod(MO_line[13]); MO_MATRIX[i][numMOs-1] =stod(MO_line[14]);
            }
            if(numElements == 14)
            {
                MO_MATRIX[i][numMOs-10]=stod(MO_line[4]);  MO_MATRIX[i][numMOs-9]=stod(MO_line[5]);   MO_MATRIX[i][numMOs-8]=stod(MO_line[6]);
                MO_MATRIX[i][numMOs-7] =stod(MO_line[7]);  MO_MATRIX[i][numMOs-6]=stod(MO_line[8]);   MO_MATRIX[i][numMOs-5]=stod(MO_line[9]);
                MO_MATRIX[i][numMOs-4] =stod(MO_line[10]); MO_MATRIX[i][numMOs-3]=stod(MO_line[11]);  MO_MATRIX[i][numMOs-2]=stod(MO_line[12]);
                MO_MATRIX[i][numMOs-1] =stod(MO_line[13]);
            }            
            if(numElements == 13)
            {
                MO_MATRIX[i][numMOs-9]=stod(MO_line[4]);  MO_MATRIX[i][numMOs-8]=stod(MO_line[5]);  MO_MATRIX[i][numMOs-7]=stod(MO_line[6]);
                MO_MATRIX[i][numMOs-6]=stod(MO_line[7]);  MO_MATRIX[i][numMOs-5]=stod(MO_line[8]);  MO_MATRIX[i][numMOs-4]=stod(MO_line[9]);
                MO_MATRIX[i][numMOs-3]=stod(MO_line[10]); MO_MATRIX[i][numMOs-2]=stod(MO_line[11]); MO_MATRIX[i][numMOs-1]=stod(MO_line[12]);
            }
            if(numElements == 12)
            {
                MO_MATRIX[i][numMOs-8]=stod(MO_line[4]);  MO_MATRIX[i][numMOs-7]=stod(MO_line[5]); MO_MATRIX[i][numMOs-6]=stod(MO_line[6]);
                MO_MATRIX[i][numMOs-5]=stod(MO_line[7]);  MO_MATRIX[i][numMOs-4]=stod(MO_line[8]); MO_MATRIX[i][numMOs-3]=stod(MO_line[9]);
                MO_MATRIX[i][numMOs-2]=stod(MO_line[10]); MO_MATRIX[i][numMOs-1]=stod(MO_line[11]);
            }
            if(numElements == 11)
            {
                MO_MATRIX[i][numMOs-7]=stod(MO_line[4]); MO_MATRIX[i][numMOs-6]=stod(MO_line[5]); MO_MATRIX[i][numMOs-5]=stod(MO_line[6]);
                MO_MATRIX[i][numMOs-4]=stod(MO_line[7]); MO_MATRIX[i][numMOs-3]=stod(MO_line[8]); MO_MATRIX[i][numMOs-2]=stod(MO_line[9]);
                MO_MATRIX[i][numMOs-1]=stod(MO_line[10]);
            }
            if(numElements == 10)
            {
                MO_MATRIX[i][numMOs-6]=stod(MO_line[4]); MO_MATRIX[i][numMOs-5]=stod(MO_line[5]); MO_MATRIX[i][numMOs-4]=stod(MO_line[6]);
                MO_MATRIX[i][numMOs-3]=stod(MO_line[7]); MO_MATRIX[i][numMOs-2]=stod(MO_line[8]); MO_MATRIX[i][numMOs-1]=stod(MO_line[9]);
            }
            if(numElements == 9)
            {
                MO_MATRIX[i][numMOs-5]=stod(MO_line[4]); MO_MATRIX[i][numMOs-4]=stod(MO_line[5]); MO_MATRIX[i][numMOs-3]=stod(MO_line[6]);
                MO_MATRIX[i][numMOs-2]=stod(MO_line[7]); MO_MATRIX[i][numMOs-1]=stod(MO_line[8]);
            }
            if(numElements == 8)
            {
                MO_MATRIX[i][numMOs-4]=stod(MO_line[4]); MO_MATRIX[i][numMOs-3]=stod(MO_line[5]); MO_MATRIX[i][numMOs-2]=stod(MO_line[6]);
                MO_MATRIX[i][numMOs-1]=stod(MO_line[7]);
            }
            if(numElements == 7)
            {
                MO_MATRIX[i][numMOs-3]=stod(MO_line[4]); MO_MATRIX[i][numMOs-2]=stod(MO_line[5]); MO_MATRIX[i][numMOs-1]=stod(MO_line[6]);
            }
            if(numElements == 6)
            {
                MO_MATRIX[i][numMOs-2]=stod(MO_line[4]); MO_MATRIX[i][numMOs-1]=stod(MO_line[5]);
            }
            if(numElements == 5)
            {
                MO_MATRIX[i][numMOs-1]=stod(MO_line[4]);
            }
     }
//        }
     }
set++;    }
//cout << MO_MATRIX.size() << endl;


return MO_MATRIX;
}



vector<double> MOEIGENVALUES(string name)
{
//Contains all the lines of the output file##########
vector<string> lines = Read(name);              //###
//Contains all the lines of the output file##########
//Variables to extract molecular orbital info in file##########
string eigval_find ="eigval";                            //####
vector<string> MOEigenvalsLines;                         //####
vector<string> MOEigenvalsByte;                          //####
vector<double> MOEigenvals;                              //####
//Variables to extract molecular orbital info in file##########
for( int i=0; i < lines.size();i++)
{
    istringstream split(lines[i]);

    if(lines[i].find(eigval_find,0) != std::string::npos )
    {
      MOEigenvalsLines.push_back(lines[i]);
    }
}

for(int lines=0; lines < MOEigenvalsLines.size(); lines++)
    {
        istringstream temp(MOEigenvalsLines[lines]);                       
        std::istream_iterator<std::string> begin(temp);                    
        std::istream_iterator<std::string> end;                            
        std::vector<std::string> MOEigenvalsByte(begin,end);               
        for(int bytes=0; bytes < MOEigenvalsByte.size(); bytes++)          
        {                                                              
           if(MOEigenvalsByte[bytes] != "eigvals(Ev)")                    
            {   
              MOEigenvals.push_back(stod(MOEigenvalsByte[bytes]));       
            }
        }
    }

return MOEigenvals;
}

/*
int line_size = MOEigenvectorlines.size() ;
vector<string> MOEigenvectorbytes;
vector<vector<string> > MOCoeffs((numMOs), vector<string>(numMOs));
int nextgroup = 0;
cout << line_size << endl;
string element;
vector<string> temp_array;
int loop_counter=1;
//vector<vector<string> > element_matrix((numMOs+4), vector<string>(numMOs)); 
//int set=0;
int set2=0;
int checkMOvec=numMOs;
if(numMOs > 15)
{
for(int cycle=0; cycle <= 10; cycle++)
{
   if(checkMOvec % 15 != 0){checkMOvec = checkMOvec-1; nextgroup++; cout << checkMOvec<< endl; if(checkMOvec % 15 == 0){break;} }
}
cout << checkMOvec/15 << endl;
}
else{int checkMOvec=1;}

//for(int set=0; set <= checkMOvec/15;set++)
//{
for(int i=0;i <numMOs; i++)
{
    set2++;
       
    for(int j=0;j<MOEigenvectorlines.size();j++)
       {
        istringstream temp(MOEigenvectorlines[j]);
        cout << MOEigenvectorlines[j] << endl;
        while(temp >> element)
        {
            MOEigenvectorbytes.insert(MOEigenvectorbytes.end(),element);
//            cout << element << "   ";
        } 
//    cout << MOEigenvectorbytes.size() << endl;        
    int size = MOEigenvectorbytes.size();
        MOCoeffs[0][i] = MO_arrange(size, set,i,numMOs );
loop_counter++;    
cout << MOEigenvectorbytes.size() << " " << loop_counter << " " << set << endl;
MOEigenvectorbytes.clear();
//    if(loop_counter % numMOs==0){set++;set2++;}
//    if(i > numMOs){set2=-numMOs;}
      }
//      }
//    for(int j=0; j < line_size; j++)
//    {
//        MOCoeffs[i][0] = temp_array[j-4]; MOCoeffs[i][1] = temp_array[j-3]; 
//        MOCoeffs[i][2] = temp_array[j-2]; MOCoeffs[i][3] = temp_array[j-1]; 
//        MOCoeffs[i][4] = temp_array[j];
//    }

}

//cout << WrtCount++ << "occurances of write id" << endl;
*/

/*
int checkMOvec=numMOs;
if(numMOs > 15)
{
for(int cycle=0; cycle <= 10; cycle++)
{  
   if(checkMOvec % 15 != 0){checkMOvec = checkMOvec-1; nextgroup++; cout << checkMOvec<< endl; if(checkMOvec % 15 == 0){break;} }
}
cout << checkMOvec/15 << endl;
}
else{int checkMOvec=1;}
for(int set=0; set <= checkMOvec/15; set++)
{
for(int i=0; i < numMOs; i++)
{

//    cout <<i<< " line number " <<  MOEigenvectorlines[i+(set*numMOs)]<< endl;
    istringstream temp(MOEigenvectorlines[i+(set*numMOs)]);                             //####
    std::istream_iterator<std::string> begin(temp);                                     //####
    std::istream_iterator<std::string> end;                                             //####
    std::vector<std::string> MOEigenvectorbytes(begin,end);
//    std::copy(MOEigenvectorbytes.begin(),MOEigenvectorbytes.end(),                    //####
//    std::ostream_iterator<std::string>(std::cout,"\n"));                              //####     //iterates through all of the strings on one line separated by white space. 
//          cout << MOEigenvectorbytes.size() <<" " << i<< endl;                        //####     //The if statement is necessary because zeros needed to be added into lines where 

    int size = MOEigenvectorbytes.size(); 
    for(int j=0; j <size; j++)
    { 
    for(int MO=0; MO < numMOs; MO++)
    {
//        cout << j << " " << MO<< endl;
        switch(size)
        {
            case 19:
                MOCoeffs[0+(set*15)][i]= (MOEigenvectorbytes[4]); MOCoeffs[1+(set*15)][i]= (MOEigenvectorbytes[5]); MOCoeffs[2+(set*15)][i]= (MOEigenvectorbytes[6]);
                MOCoeffs[3+(set*15)][i]= (MOEigenvectorbytes[7]); MOCoeffs[4+(set*15)][i]= (MOEigenvectorbytes[8]);
                MOCoeffs[5+(set*15)][i]= (MOEigenvectorbytes[9]); MOCoeffs[6+(set*15)][i]= (MOEigenvectorbytes[10]); MOCoeffs[7+(set*15)][i]= (MOEigenvectorbytes[11]);
                MOCoeffs[8+(set*15)][i]= (MOEigenvectorbytes[12]); MOCoeffs[9+(set*15)][i]= (MOEigenvectorbytes[13]);
                MOCoeffs[10+(set*15)][i]= (MOEigenvectorbytes[14]); MOCoeffs[11+(set*15)][i]= (MOEigenvectorbytes[15]); MOCoeffs[12+(set*15)][i]= (MOEigenvectorbytes[16]);
                MOCoeffs[13+(set*15)][i]= (MOEigenvectorbytes[17]); MOCoeffs[14+(set*15)][i]= (MOEigenvectorbytes[18]);
                break;
            case 6:
                MOCoeffs[numMOs-2][i] = (MOEigenvectorbytes[4]); MOCoeffs[numMOs-1][i] = (MOEigenvectorbytes[5]);
                break;

            case 7:
                MOCoeffs[numMOs-3][i] = (MOEigenvectorbytes[4]); MOCoeffs[numMOs-2][i] = (MOEigenvectorbytes[5]); MOCoeffs[numMOs-1][i] = (MOEigenvectorbytes[6]);
                break;

            case 8:
                MOCoeffs[numMOs-4][i] = (MOEigenvectorbytes[4]); MOCoeffs[numMOs-3][i] = (MOEigenvectorbytes[5]); MOCoeffs[numMOs-2][i] = (MOEigenvectorbytes[6]); MOCoeffs[numMOs-1][i] = (MOEigenvectorbytes[7]);
                break;

            case 9:
                MOCoeffs[numMOs-5][i] = (MOEigenvectorbytes[4]); MOCoeffs[numMOs-4][i] = (MOEigenvectorbytes[5]); MOCoeffs[numMOs-3][i] = (MOEigenvectorbytes[6]); MOCoeffs[numMOs-2][i] = (MOEigenvectorbytes[7]); MOCoeffs[numMOs-1][i] = (MOEigenvectorbytes[8]);
                break;

            case 10:
                MOCoeffs[numMOs-6][i] = (MOEigenvectorbytes[4]); MOCoeffs[numMOs-5][i] = (MOEigenvectorbytes[5]); MOCoeffs[numMOs-4][i] = (MOEigenvectorbytes[6]); MOCoeffs[numMOs-3][i] = (MOEigenvectorbytes[7]); MOCoeffs[numMOs-2][i] = (MOEigenvectorbytes[8]); MOCoeffs[numMOs-1][i] = (MOEigenvectorbytes[9]);
                break;

            case 11:
                MOCoeffs[numMOs-7][i] = (MOEigenvectorbytes[4]); MOCoeffs[numMOs-6][i] = (MOEigenvectorbytes[5]); MOCoeffs[numMOs-5][i] = (MOEigenvectorbytes[6]); MOCoeffs[numMOs-4][i] = (MOEigenvectorbytes[7]); MOCoeffs[numMOs-3][i] = (MOEigenvectorbytes[8]); MOCoeffs[numMOs-2][i] = (MOEigenvectorbytes[9]); MOCoeffs[numMOs-1][i] = (MOEigenvectorbytes[10]);
                break;


            case 12:
                MOCoeffs[numMOs-8][i] = (MOEigenvectorbytes[4]); MOCoeffs[numMOs-7][i] = (MOEigenvectorbytes[5]); MOCoeffs[numMOs-6][i] = (MOEigenvectorbytes[6]); MOCoeffs[numMOs-5][i] = (MOEigenvectorbytes[7]); MOCoeffs[numMOs-4][i] = (MOEigenvectorbytes[8]); MOCoeffs[numMOs-3][i] = (MOEigenvectorbytes[9]); MOCoeffs[numMOs-2][i] = (MOEigenvectorbytes[10]);  MOCoeffs[numMOs-1][i] = (MOEigenvectorbytes[11]);
                break;

            case 13:
                MOCoeffs[numMOs-9][i] = (MOEigenvectorbytes[4]); MOCoeffs[numMOs-8][i] = (MOEigenvectorbytes[5]); MOCoeffs[numMOs-7][i] = (MOEigenvectorbytes[6]); MOCoeffs[numMOs-6][i] = (MOEigenvectorbytes[7]); MOCoeffs[numMOs-5][i] = (MOEigenvectorbytes[8]); MOCoeffs[numMOs-4][i] = (MOEigenvectorbytes[9]); MOCoeffs[numMOs-3][i] = (MOEigenvectorbytes[10]);  MOCoeffs[numMOs-2][i] = (MOEigenvectorbytes[11]); MOCoeffs[numMOs-1][i] = (MOEigenvectorbytes[12]);
                break;

            case 14:
                MOCoeffs[numMOs-10][i] = (MOEigenvectorbytes[4]); MOCoeffs[numMOs-9][i] = (MOEigenvectorbytes[5]); MOCoeffs[numMOs-8][i] = (MOEigenvectorbytes[6]); MOCoeffs[numMOs-7][i] = (MOEigenvectorbytes[7]); MOCoeffs[numMOs-6][i] = (MOEigenvectorbytes[8]); MOCoeffs[numMOs-5][i] = (MOEigenvectorbytes[9]); MOCoeffs[numMOs-4][i] = (MOEigenvectorbytes[10]); MOCoeffs[numMOs-3][i] = (MOEigenvectorbytes[11]);  MOCoeffs[numMOs-2][i] = (MOEigenvectorbytes[12]); MOCoeffs[numMOs-1][i] = (MOEigenvectorbytes[13]);
                break;

            case 15:
                MOCoeffs[numMOs-11][i] = (MOEigenvectorbytes[4]); MOCoeffs[numMOs-10][i] = (MOEigenvectorbytes[5]); MOCoeffs[numMOs-9][i] = (MOEigenvectorbytes[6]); MOCoeffs[numMOs-8][i] = (MOEigenvectorbytes[7]); MOCoeffs[numMOs-7][i] = (MOEigenvectorbytes[8]); MOCoeffs[numMOs-6][i] = (MOEigenvectorbytes[9]); MOCoeffs[numMOs-5][i] = (MOEigenvectorbytes[10]); MOCoeffs[numMOs-4][i] = (MOEigenvectorbytes[11]); MOCoeffs[numMOs-3][i] = (MOEigenvectorbytes[12]);  MOCoeffs[numMOs-2][i] = (MOEigenvectorbytes[13]); MOCoeffs[numMOs-1][i] = (MOEigenvectorbytes[14]);
                break;

            case 16:
                MOCoeffs[numMOs-12][i] = (MOEigenvectorbytes[4]); MOCoeffs[numMOs-11][i] = (MOEigenvectorbytes[5]); MOCoeffs[numMOs-10][i] = (MOEigenvectorbytes[6]); MOCoeffs[numMOs-9][i] = (MOEigenvectorbytes[7]); MOCoeffs[numMOs-8][i] = (MOEigenvectorbytes[8]); MOCoeffs[numMOs-7][i] = (MOEigenvectorbytes[9]); MOCoeffs[numMOs-6][i] = (MOEigenvectorbytes[10]); MOCoeffs[numMOs-5][i] = (MOEigenvectorbytes[11]); MOCoeffs[numMOs-4][i] = (MOEigenvectorbytes[12]); MOCoeffs[numMOs-3][i] = (MOEigenvectorbytes[13]);  MOCoeffs[numMOs-2][i] = (MOEigenvectorbytes[14]); MOCoeffs[numMOs-1][i] = (MOEigenvectorbytes[15]);
                break;

            case 17:
                MOCoeffs[numMOs-13][i] = (MOEigenvectorbytes[4]); MOCoeffs[numMOs-12][i] = (MOEigenvectorbytes[5]); MOCoeffs[numMOs-11][i] = (MOEigenvectorbytes[6]); MOCoeffs[numMOs-10][i] = (MOEigenvectorbytes[7]); MOCoeffs[numMOs-9][i] = (MOEigenvectorbytes[8]); MOCoeffs[numMOs-8][i] = (MOEigenvectorbytes[9]); MOCoeffs[numMOs-7][i] = (MOEigenvectorbytes[10]); MOCoeffs[numMOs-6][i] = (MOEigenvectorbytes[11]); MOCoeffs[numMOs-5][i] = (MOEigenvectorbytes[12]); MOCoeffs[numMOs-4][i] = (MOEigenvectorbytes[13]); MOCoeffs[numMOs-3][i] = (MOEigenvectorbytes[14]);  MOCoeffs[numMOs-2][i] = (MOEigenvectorbytes[15]); MOCoeffs[numMOs-1][i] = (MOEigenvectorbytes[16]);
                break;
        }
    }
    }
}
}
*/
//return MOCoeffs;
//}




