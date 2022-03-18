#include<iostream>
#include<fstream>
#include<math.h>
#include<iomanip>
#include<vector>
#include<iterator>
#include<fstream>
#include<sstream>
#include<string>
#include<map>
#include<bits/stdc++.h> 

using namespace std;
class MOPACFILE
{
  public:
  int AtomNum;
  int num_of_mos;
  int HOMO;
  vector<vector<double> > EigenvalueMatrix;
  vector<vector<double> > MO_Vectors;
  vector<string> AtomTypeVec;
  vector<string> OrbitalTypeVec;
  vector<int> AtomNumVec;
  void MOs(string filename);
  void AtomTypes(string filename);
  void Basis_size(string filename);

  map<string,int> atom_num_of_electrons ={	
  {"H",1},
  {"C",4},
  {"N",5},
  {"B",3},
  {"O",6},
  {"S",6},
  {"P",5},
  {"Al",3},
  {"Ag",11},
  };
  map<string,int> atom_num_of_basis_functions ={	
  {"H",1},
  {"C",4},
  {"N",4},
  {"B",4},
  {"O",4},
  {"S",4},
  {"P",4},
  {"Al",4},
  {"Ag",9},
  };
 

  MOPACFILE(string filename)
  {
      Basis_size(filename);
      MOs(filename);
      AtomTypes(filename);
  }
};





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






void MOPACFILE::Basis_size(string name)
{
  vector<string> lines;                           //###
  ifstream InFile;                                //###
  string runner, GrabLine;//Identifying strings     ###
  InFile.open(name, ios::in);                     //###
  //Variables to extract molecular coordinates info in file##########           //####
  string coordinate_find ="          CARTESIAN COORDINATES";                //####
  //converts cartesian coordinates in angstroms to atomic units             //####
  //vector<string> coordinate_lines;                                          //####
  //MOPACFILE m1(name);
  //int numMOs = m1.num_of_mos;//stoi(numberofMOs[1]);
  double ang2au=1.0/0.52918;                                                //####
  //Variables to extract molecular coordinates info in file##########
  
  //Contains all the lines of the output file##########
  //vector<string> lines = Read(name);              //###
  //Contains all the lines of the output file##########
  int basis_count=0;
  int elec_count=0;
  while(getline(InFile,runner))
  {
      
      GrabLine=runner;
      if(GrabLine.find(coordinate_find,0) != std::string::npos )            //####
      {
          getline(InFile,runner);
          getline(InFile,runner);
          
          
          GrabLine=runner;
          while(GrabLine.size() > 4)
          { 
          istringstream split(GrabLine);
          string tempString;
          vector<string> tempVec;
          while(split >> tempString)
          {
              //if(tempString == " ")
              //{ 
              //    break;
              //}
              tempVec.push_back(tempString);
              //cout << tempString << "  ";
          }
          cout << endl;
          if(tempVec.size() > 3)
          {
              //cout << tempVec[1] << endl;
              int bf = atom_num_of_basis_functions[tempVec[1]];
              int ele = atom_num_of_electrons[tempVec[1]];
              basis_count += bf;
              elec_count +=ele;
          }      
  //        for(int j=3; j < atomnumbers +4 ; j++)                            //####
  //        {                                                                 //####
  //            if(lines[i+j].size() == 1){continue;}                         //####
  //            if(lines[i+j].size() >= 5)                                    //####
  //            {                                                             //####
  //                coordinate_lines.push_back(lines[i+j]);                   //####
  //                //cout << lines[i+j] << endl;                               //####
  //            }
  //        }
          //cout << "num of basis func " << basis_count<< endl;
          //cout << "num of electrons " << elec_count<< endl;
          getline(InFile,runner); GrabLine=runner;
          }
      }
  }
  cout << "HOMO " << elec_count/2 << endl;
  cout << "num of basis func " << basis_count<< endl;
  HOMO=elec_count/2;
  num_of_mos = basis_count;

}










int AtomNums(string name)
{
//string name;
/*for later use *///cout << "enter file name" << endl;/*prompt user for the file name*/
//cin >> name;
//string name = FileName;
//Contains all the lines of the output file##########
vector<string> lines;                           //###
ifstream InFile;                                //###
string runner, GrabLine;//Identifying strings     ###
InFile.open(name, ios::in);                     //###
//Contains all the lines of the output file##########

//Identify the number of molecular orbitals//######
//int MOs;                                       //#######
vector<string> numberofatomsstring;                         //#######
int numofatoms;
string IdAtomNum = "atoms";                         //#######
int WrtCount = 0;                               //#######
//Identify the number of molecular orbitals#######

//Initial Getter from File###########################################################################################################
if (!InFile){cout << "Unable to open "<<name << "!!\n"; exit(1) ;} /*check if the file is open*/                                   //###
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




void MOPACFILE::AtomTypes(string filename)
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
    string IdNMOs ="SHELL";       //#######
    int EigvalCount = 1;                          //#######
    int WrtCount = 0;                          //#######
    //Identify the number of molecular orbitals#########
    
    //Initial Getter from File############################################################################################################
    if (!InFile){cout << "Unable to open "<<filename << "!!\n"; exit(1) ;} /*check if the file is open*/                                   //###
    //cout << name <<" is open!!" << endl;/*print something from the file stream*/                                                     //###
    //string runner, GrabLine;//Identifying strings     ###
    int orbitalCount=1;
    IdNMOs ="Root No.";       //#######
    vector<string> orbitalLines;
    while (getline(InFile,runner) )                                                                                                  //###
    {                                                                                                                                //###
        GrabLine = runner;                                                                                                           //###
        lines.push_back(GrabLine);                                                                                                   //###
                                                                                                                                     //###
        //if(GrabLine.find(IdNMOs,0) != string::npos && WrtCount < 1 )                                                                 //###
        if(GrabLine.find(IdNMOs,0) != string::npos  )                                                                 //###
        {                                                                                                                            //###
            getline(InFile,runner); getline(InFile,runner); getline(InFile,runner); //getline(InFile,runner);;
            getline(InFile,runner); getline(InFile,runner); getline(InFile,runner);
            GrabLine= runner;
            vector<string> tempVec;
            istringstream split(GrabLine); //split is a variable where GrabLine is split into individual string split by white space //##
            copy(istream_iterator<string>(split),
            istream_iterator<string>(),                                                                                              //###
            back_inserter(tempVec));

            //cout <<"first line " <<  GrabLine << endl;
            //cout <<"first vector element " <<  tempVec[0] << endl;
            int tempCount=0;
            while (tempCount < num_of_mos)// != stoi(tempVec[0]))
            {
                //cout<< "between found IDNMOs " <<GrabLine.size() <<  " |" << GrabLine << endl;                                                                   //###
                if (GrabLine.size()== 1)
                {
                    //cout<< "uing if statement"<< endl;
                    getline(InFile,runner);
                    GrabLine = runner;
                    break;
                }
                orbitalLines.push_back(GrabLine);
                //cout << GrabLine << endl;
                getline(InFile,runner);
                GrabLine = runner;
                tempCount++;
            }
        }                                                                                                                            //##
                                                                                                                                     //##
    }//loop over all lines of a file and save them to lines                                                                          ####
                                
                                                                                                    //##
    InFile.close();
    //for (int i=0;i<orbitalLines.size();i++)
    //{
    //    cout<< "orbline "  << orbitalLines[i] << endl;
    //}
    vector<string> MO_label_vec;
    vector<string> AtomTypes;
    vector<string> OrbitalTypes;
    vector<int> AtomNums; 
    int basis_count=0;
    int basis_combin=0;
    int vec_size=0;
    for(int sav_line=0;sav_line<num_of_mos;sav_line++)
    {
        //vector<string> tempVec;
        //istringstream split(GrabLine); //split is a variable where GrabLine is split into individual string split by white space //##
        //copy(istream_iterator<string>(split),
        //istream_iterator<string>(),                                                                                              //###
        //back_inserter(tempVec));//appends individual strings into the vector VecMOs        
        string line1=orbitalLines[sav_line];
        string line_element;
        istringstream split(line1);
        vector<string> tempVec;
        while(split >> line_element)
        {
            tempVec.push_back(line_element);
            //cout << line_element << endl;
        }
            string MolecularOrbital_label;
            MolecularOrbital_label=tempVec[0]+":" + tempVec[1] + tempVec[2];
            //cout << MolecularOrbital_label << endl;
            //tempVec.erase(tempVec.begin()+3,tempVec.end());
            //for(int i=0; i<tempVec.size();i++)
            //{
            //    cout << tempVec[i] << endl;
            //}
            OrbitalTypes.push_back(tempVec[0]);
            AtomTypes.push_back(tempVec[1]);
            AtomNums.push_back(stoi(tempVec[2]));
            //for(int i=0; i<tempVec.size(); i++)
            //{
            //    //cout <<" " <<  basis_count+i << "  " << basis_combin << "  " << tempVec[i] << " ";
            //    MolecularOrbital_matrix[basis_count+i][basis_combin]=stod(tempVec[i]);
            //    //cout <<" " <<  basis_count+i << "  " << basis_combin << "  " << tempVec[i] << " "<< tempVec.size();
            //}
            ////cout << endl;
            //vec_size = tempVec.size();
    }
    AtomTypeVec=AtomTypes;
    OrbitalTypeVec=OrbitalTypes;
    AtomNumVec=AtomNums;
    //for(int ele=0;ele < AtomTypeVec.size(); ele++)
    //{
    //    cout <<AtomNumVec[ele] << " "<<  AtomTypeVec[ele] <<" " <<  OrbitalTypeVec[ele] << endl;
    //}
}






void MOPACFILE::MOs(string filename)
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
    string IdNMOs ="SHELL";       //#######
    int EigvalCount = 1;                          //#######
    int WrtCount = 0;                          //#######
    int occupied_orbs=0;
    int virtual_orbs=0;
    //Identify the number of molecular orbitals#########
    
    //Initial Getter from File############################################################################################################
    if (!InFile){cout << "Unable to open "<<filename << "!!\n"; exit(1) ;} /*check if the file is open*/                                   //###
    //cout << name <<" is open!!" << endl;/*print something from the file stream*/                                                     //###
                                                                                                                                     //###
    while (getline(InFile,runner) )                                                                                                  //###
    {                                                                                                                                //###
        GrabLine = runner;                                                                                                           //###
        //lines.push_back(GrabLine);                                                                                                   //###
                                                                                                                                     //###
        //if(GrabLine.find(IdNMOs,0) != string::npos && WrtCount < 1 )                                                                 //###
        if(GrabLine.find(IdNMOs,0) != string::npos  )                                                                 //###
        {                  
            getline(InFile,runner);
            GrabLine = runner;                                                                                                           //###
            //cout<< "found " << IdNMOs << " |" << GrabLine << endl;                                                                   //###
            vector<string> tempVec;
            istringstream split(GrabLine); //split is a variable where GrabLine is split into individual string split by white space //##
            copy(istream_iterator<string>(split),
            istream_iterator<string>(),                                                                                              //###
            back_inserter(tempVec));//appends individual strings into the vector VecMOs                                               //###
            occupied_orbs = stoi(tempVec[1]);

            getline(InFile,runner);
            GrabLine = runner;                                                                                                           //###
            //cout<< "found " << IdNMOs << " |" << GrabLine << endl;                                                                   //###
            tempVec.clear();
            istringstream split2(GrabLine); //split is a variable where GrabLine is split into individual string split by white space //##
            copy(istream_iterator<string>(split2),
            istream_iterator<string>(),                                                                                              //###
            back_inserter(tempVec));//appends individual strings into the vector VecMOs                                               //###
            virtual_orbs = stoi(tempVec[1]);
            //MOs = (VecNDet[2]);//Stores the number of determinants generated as a variable                                         //###
            //cout << VecMOs << endl;                                                                                                  //##
            WrtCount++;
        }                                                                                                                            //##
                                                                                                                                     //##
    }//loop over all lines of a file and save them to lines                                                                          ####
                                                                                                                                     //##
    InFile.close();                                                                                                                  //##
    if(num_of_mos<=0 || HOMO<=0)
    {
        HOMO = occupied_orbs;
        num_of_mos = occupied_orbs + virtual_orbs;
    }
    //string runner, GrabLine;//Identifying strings     ###
    InFile.open(filename, ios::in);                     //###
    int orbitalCount=1;
    IdNMOs ="Root No.";       //#######
    vector<string> orbitalLines;
    while (getline(InFile,runner) )                                                                                                  //###
    {                                                                                                                                //###
        GrabLine = runner;                                                                                                           //###
        lines.push_back(GrabLine);                                                                                                   //###
                                                                                                                                     //###
        //if(GrabLine.find(IdNMOs,0) != string::npos && WrtCount < 1 )                                                                 //###
        if(GrabLine.find(IdNMOs,0) != string::npos  )                                                                 //###
        {                                                                                                                            //###
            getline(InFile,runner); getline(InFile,runner); getline(InFile,runner); //getline(InFile,runner);;
            getline(InFile,runner); getline(InFile,runner); getline(InFile,runner);
            GrabLine= runner;
            vector<string> tempVec;
            istringstream split(GrabLine); //split is a variable where GrabLine is split into individual string split by white space //##
            copy(istream_iterator<string>(split),
            istream_iterator<string>(),                                                                                              //###
            back_inserter(tempVec));

            //cout <<"first vector element " <<  tempVec[0] << endl;
            int tempCount=0;
            while (tempCount < num_of_mos)// != stoi(tempVec[0]))
            {
                //cout<< "between found IDNMOs " <<GrabLine.size() <<  " |" << GrabLine << endl;                                                                   //###
                if (GrabLine.size()== 1)
                {
                    //cout<< "uing if statement"<< endl;
                    getline(InFile,runner);
                    GrabLine = runner;
                    break;
                }
                orbitalLines.push_back(GrabLine);
                //cout << GrabLine << endl;
                getline(InFile,runner);
                GrabLine = runner;
                tempCount++;
            }
        }                                                                                                                            //##
                                                                                                                                     //##
    }//loop over all lines of a file and save them to lines                                                                          ####
                                
                                                                                                    //##
    InFile.close();
    //for (int i=0;i<orbitalLines.size();i++)
    //{
    //    cout<< "orbline "  << orbitalLines[i] << endl;
    //}
    vector<string> MO_label_vec;
    vector<vector<double> > MolecularOrbital_matrix(num_of_mos+1,vector<double>(num_of_mos+1));
    int basis_count=1;
    int basis_combin=0;
    int vec_size=0;
    for(int sav_line=0;sav_line<orbitalLines.size();sav_line++)
    {
        if(basis_combin == num_of_mos )
        {
            basis_count+=vec_size;
            basis_combin=0;
        }
        //vector<string> tempVec;
        //istringstream split(GrabLine); //split is a variable where GrabLine is split into individual string split by white space //##
        //copy(istream_iterator<string>(split),
        //istream_iterator<string>(),                                                                                              //###
        //back_inserter(tempVec));//appends individual strings into the vector VecMOs        
        string line1=orbitalLines[sav_line];
        string line_element;
        istringstream split(line1);
        vector<string> tempVec;
        while(split >> line_element)
        {
            tempVec.push_back(line_element);
            //cout << line_element << endl;
        }
        if (tempVec.size() > 3)
        {
            string MolecularOrbital_label;
            MolecularOrbital_label=tempVec[0]+":" + tempVec[1] + tempVec[2];
            //cout << MolecularOrbital_label << endl;
            tempVec.erase(tempVec.begin(),tempVec.begin()+3);
            //for(int i=0; i<tempVec.size();i++)
            //{
            //    cout << tempVec[i] << endl;
            //}
            for(int i=0; i<tempVec.size(); i++)
            {
                //cout <<" " <<  basis_count+i << "  " << basis_combin << "  " << tempVec[i] << " ";
                MolecularOrbital_matrix[basis_count+i][basis_combin]=stod(tempVec[i]);
                //cout <<" " <<  basis_count+i << "  " << basis_combin << "  " << tempVec[i] << " "<< tempVec.size();
            }
            //cout << endl;
            vec_size = tempVec.size();
            basis_combin++;
        }

    }
    MO_Vectors=MolecularOrbital_matrix;                                                                                                                  //##
//    for(int ele=0;ele < MolecularOrbital_matrix.size(); ele++)
//    {
//        vector<double> tempVector;
//        for(int ele2=0;ele2 < MolecularOrbital_matrix[0].size(); ele2++)
//        {
//            cout << ele << ",  " << ele2 << "  " << MolecularOrbital_matrix[ele][ele2] << endl;
//        }
//    }
}









//Factorial fuction#########
int fact(int num)
{
unsigned long long factorial = 1;  //####
    for(int i=1; i <=num; i++)     //####
    {                              //####
        factorial *= i;            //####
    }                              //####
return factorial;
}
//##########################

vector<vector<string> > MOLECULAR_COORDINATES_VECTOR(string name)
{
//Variables to extract molecular coordinates info in file##########           //####
string coordinate_find ="          CARTESIAN COORDINATES";                //####
//converts cartesian coordinates in angstroms to atomic units             //####
vector<string> coordinate_lines;                                          //####
MOPACFILE m1(name);
int numMOs = m1.num_of_mos;//stoi(numberofMOs[1]);
double ang2au=1.0/0.52918;                                                //####
int atomnumbers = AtomNums(name);                                         //####
vector<vector<string> > coordinates((atomnumbers), vector<string>(4));    //####
//Variables to extract molecular coordinates info in file##########

//Contains all the lines of the output file##########
vector<string> lines = Read(name);              //###
//Contains all the lines of the output file##########

for(int i=0; i < lines.size();i++)
{
    istringstream split(lines[i]);

    if(lines[i].find(coordinate_find,0) != std::string::npos )            //####
    {
        for(int j=3; j < atomnumbers +4 ; j++)                            //####
        {                                                                 //####
            if(lines[i+j].size() == 1){continue;}                         //####
            if(lines[i+j].size() >= 5)                                    //####
            {                                                             //####
                coordinate_lines.push_back(lines[i+j]);                   //####
                //cout << lines[i+j] << endl;                               //####
            }
        }
    }
}

for(int i=0; i < atomnumbers; i++)
{

    istringstream temp(coordinate_lines[i]);                             //####
    std::istream_iterator<std::string> begin(temp);                      //####
    std::istream_iterator<std::string> end;                              //####
    std::vector<std::string> coordinate_bytes(begin,end);                //####
    cout << (coordinate_bytes[0]) <<" "<< (coordinate_bytes[1]) <<       //#### places atom type, atom number, and x y z coordinates into an 4D vector
    " " << (coordinate_bytes[2]) << " " << (coordinate_bytes[3]) <<      //####
    " " << (coordinate_bytes[4]) << endl;                                //####
    coordinates[i][0] =(coordinate_bytes[0]); coordinates[i][1]=(coordinate_bytes[1]);
    coordinates[i][0]=(coordinate_bytes[1]);
    coordinates[i][1]=to_string(stod(coordinate_bytes[2])*ang2au);
    coordinates[i][2]=to_string(stod(coordinate_bytes[3])*ang2au);
    coordinates[i][3]=to_string(stod(coordinate_bytes[4])*ang2au);
}

//end of MOLECULAR_COORDINATES_VECTOR function
return coordinates;
}



void MK_CUBE(string name, int orbital_number)
{

//Pulling cartesian coordinates, atom numbers, and atom types
double ang2au=1.0/0.52918;
MOPACFILE m1(name);
int numMOs = m1.num_of_mos;//stoi(numberofMOs[1]);
vector<vector<double> > MOLECULAR_ORBITALS = m1.MO_Vectors;
double gap = 0.25*ang2au;  //*angstroms_2_au;
double extra = 5.0*ang2au; //*angstroms_2_au;  //#ADD changed the extension from 3 to 6
int HOMO = m1.HOMO;
int LUMO = m1.HOMO + 1;
cout << "HIGHEST OCCUPIED ORBITAL " << HOMO << " LOWEST OCCUPIED ORBITAL " << LUMO<<endl;
vector<string> OrbitalTypes = m1.OrbitalTypeVec;
vector<string> AtomTypes = m1.AtomTypeVec;
vector<int> AtomNumbers = m1.AtomNumVec;
vector<vector<string> >  molecule_coords;
molecule_coords = MOLECULAR_COORDINATES_VECTOR(name);
double max_mol_coords[3];
double min_mol_coords[3];
max_mol_coords[0]=stod(molecule_coords[AtomNumbers[0]-1][1]); max_mol_coords[1]=stod(molecule_coords[AtomNumbers[0]-1][2]); max_mol_coords[2]=stod(molecule_coords[AtomNumbers[0]-1][3]);
min_mol_coords[0]=stod(molecule_coords[AtomNumbers[0]-1][1]); min_mol_coords[1]=stod(molecule_coords[AtomNumbers[0]-1][2]); min_mol_coords[2]=stod(molecule_coords[AtomNumbers[0]-1][3]);

//cout << "min_mol_coords\n" << 
//           min_mol_coords[0] << "  " << min_mol_coords[1] << "  " << min_mol_coords[2] << endl; //checking the initial minimum molecular coordinate for x, y, and z
//cout << "max_mol_coords\n" << 
//           max_mol_coords[0] << "  " << max_mol_coords[1] << "  " << max_mol_coords[2] << endl; //checking the initial maximum molecular coordinate for x, y, and z

for(int i=0; i < numMOs; i++)
    {
    if(max_mol_coords[0] < stod(molecule_coords[AtomNumbers[i]-1][1])){max_mol_coords[0]=stod(molecule_coords[AtomNumbers[i]-1][1]);}
    if(max_mol_coords[1] < stod(molecule_coords[AtomNumbers[i]-1][2])){max_mol_coords[1]=stod(molecule_coords[AtomNumbers[i]-1][2]);}
    if(max_mol_coords[2] < stod(molecule_coords[AtomNumbers[i]-1][3])){max_mol_coords[2]=stod(molecule_coords[AtomNumbers[i]-1][3]);}
    if(min_mol_coords[0] > stod(molecule_coords[AtomNumbers[i]-1][1])){min_mol_coords[0]=stod(molecule_coords[AtomNumbers[i]-1][1]);}
    if(min_mol_coords[1] > stod(molecule_coords[AtomNumbers[i]-1][2])){min_mol_coords[1]=stod(molecule_coords[AtomNumbers[i]-1][2]);}
    if(min_mol_coords[2] > stod(molecule_coords[AtomNumbers[i]-1][3])){min_mol_coords[2]=stod(molecule_coords[AtomNumbers[i]-1][3]);}
//    cout << AtomNumbers[i] << " " << AtomTypes[i] << "  " << OrbitalTypes[i] << " ";
//    cout<< molecule_coords[AtomNumbers[i]-1][1] << " " << molecule_coords[AtomNumbers[i]-1][2] << " " << molecule_coords[AtomNumbers[i]-1][3] << " " << MOLECULAR_ORBITALS[2][i]<< endl;
    }

//cout << "min_mol_coords\n" << 
//           min_mol_coords[0] << "  " << min_mol_coords[1] << "  " << min_mol_coords[2] << endl; //checking the final minimum molecular coordinate for x, y, and z
//cout << "max_mol_coords\n" << 
//           max_mol_coords[0] << "  " << max_mol_coords[1] << "  " << max_mol_coords[2] << endl; //checking the final minimum molecular coordinate for x, y, and z




//BUILDING VOXEL MATRIX/ARRAY#################
cout << max_mol_coords[0] << "  " << 2*extra << "  " << gap << endl;
cout << "dimensions" << "  " << 
         (max_mol_coords[0] + 2*extra - min_mol_coords[0])/gap << " x " << // number of voxels in the x direction 
         (max_mol_coords[1] + 2*extra - min_mol_coords[1])/gap << " x " << // number of voxels in the y direction
         (max_mol_coords[2] + 2*extra - min_mol_coords[2])/gap << endl;    // number of voxels in the z direction

cout << (max_mol_coords[0] + 2*extra - min_mol_coords[0])/gap *            // 
        (max_mol_coords[1] + 2*extra - min_mol_coords[1])/gap *            // Total number of voxels in the voxel matrix
        (max_mol_coords[2] + 2*extra - min_mol_coords[2])/gap << endl;     //

double nvox[3];
nvox[0]=int((max_mol_coords[0] + 2*extra - min_mol_coords[0])/gap); // number of voxels in the x direction
nvox[1]=int((max_mol_coords[1] + 2*extra - min_mol_coords[1])/gap); // number of voxels in the y direction
nvox[2]=int((max_mol_coords[2] + 2*extra - min_mol_coords[2])/gap); // number of voxels in the z direction
min_mol_coords[0]=min_mol_coords[0]-extra; //starting point to calculate values for atomic orbitals in the x direction
min_mol_coords[1]=min_mol_coords[1]-extra; //starting point to calculate values for atomic orbitals in the y direction
min_mol_coords[2]=min_mol_coords[2]-extra; //starting point to calculate values for atomic orbitals in the z direction
//cout << nvox[0] << endl;

double hole_vox[int(nvox[0])][int(nvox[1])][int(nvox[2])]; //######

for(int i=0; i < nvox[0]; i++)                             //######
    {                                                      //###### 
    for(int j=0; j < nvox[1]; j++)                         //######
        {                                                  //######
        for(int k=0; k < nvox[2]; k++)                     //######
            {                                              //######
            hole_vox[i][j][k]=(0.0);                       //######
            }                                              //######
        }                                                  //######
    }                                                      //######
//BUILDING VOXEL MATRIX DONE#################


// VOX distances ######
double minvox[3]={0,0,0};
double maxvox[3]={double(nvox[0]),double(nvox[1]),double(nvox[2])}; 
int vdist = extra; //int vrange = int(vdist/(gap*2) +1);
double vcoord[3];
// VOX distances ######

for(int i=0;i < numMOs;i++)
{

    for(int one=int(minvox[0]); one < int(maxvox[0]);one++)
    {
        for(int two=int(minvox[1]); two < int(maxvox[1]);two++)
        {
            for(int three=int(minvox[2]); three < int(maxvox[2]);three++)
            {
                double r; double y;
                vcoord[0] = min_mol_coords[0] + one * gap; vcoord[1] = min_mol_coords[1] + two * gap; vcoord[2] = min_mol_coords[2] + three * gap;
                double dx = stod(molecule_coords[AtomNumbers[i]-1][1]) - vcoord[0];
                double dy = stod(molecule_coords[AtomNumbers[i]-1][2]) - vcoord[1];
                double dz = stod(molecule_coords[AtomNumbers[i]-1][3]) - vcoord[2];
                double rad = sqrt(pow(dx,2) + pow(dy,2) + pow(dz,2));
                //cout << rad << endl;
                if(rad < 0.0001){rad = 0.0001;}
                //cout << AtomTypes[i] << endl;
                //cout << AtomTypes[i] << " " << OrbitalTypes[i] << endl;
                if(AtomTypes[i] =="H")
                {
                    if(OrbitalTypes[i] =="S")
                    {
                        double zeta = 1.200000;
                        r = (2.0*zeta) * sqrt(2*zeta/(fact(2*1))) * pow(rad,0) * exp(-zeta*rad);
                        y = sqrt(1/M_PI)* 1/2;
                    }
                }
                if(AtomTypes[i] =="C")
                {
                    double zeta = 1.625000;
                    r = pow((2.0*zeta),2) * sqrt((2*zeta)/(fact(2*2))) * pow(rad,1) * exp(-zeta*rad);
                    if(OrbitalTypes[i] =="S")
                    {
                        y = sqrt(1/M_PI)* 1/2; 
                    }
                    if(OrbitalTypes[i] =="Px")
                    {
                        y = -sqrt(3.0/(4.0*M_PI)) * dx/rad;
                    }
                    if(OrbitalTypes[i] =="Py")
                    {
                        y = -sqrt(3.0/(4.0*M_PI)) * dy/rad;
                    }
                    if(OrbitalTypes[i] =="Pz")
                    {
                        y = -sqrt(3.0/(4.0*M_PI)) * dz/rad;
                    }
                }
                if(AtomTypes[i] =="O")
                {
                    double zeta = 2.275000;
                    r = pow((2.0*zeta),2) * sqrt(2*zeta/fact(2*2)) * pow(rad,1) * exp(-zeta*rad);
                    if(OrbitalTypes[i] =="S")
                    {
                        y = sqrt(1/M_PI) *1/2;
                    }
                    if(OrbitalTypes[i] =="Px")
                    {
                        y = -sqrt(3.0/(4.0*M_PI)) * dx/rad;
                    }
                    if(OrbitalTypes[i] =="Py")
                    {
                        y = -sqrt(3.0/(4.0*M_PI)) * dy/rad;
                    }
                    if(OrbitalTypes[i] =="Pz")
                    {
                        y = -sqrt(3.0/(4.0*M_PI)) * dz/rad;
                    }
                }

                if(AtomTypes[i] =="Ag")
                {
                    if(OrbitalTypes[i] == "S" || OrbitalTypes[i] == "Px" || OrbitalTypes[i] == "Py" || OrbitalTypes[i] == "Pz")
                    {
                        double zeta = 2.275000;
                        r = pow((2.0*zeta),5) * sqrt(2*zeta/fact(2*5)) * pow(rad,4) * exp(-zeta*rad);
                        if(OrbitalTypes[i] =="S")
                        {
                            y = sqrt(1/M_PI) *1/2;
                            //cout << "Matched"<< endl;
                        }
                        if(OrbitalTypes[i] =="Px")
                        {
                            y = -sqrt(3.0/(4.0*M_PI)) * dx/rad;
                            //cout << "Matched"<< endl;
                        }
                        if(OrbitalTypes[i] =="Py")
                        {
                            y = -sqrt(3.0/(4.0*M_PI)) * dy/rad;
                            //cout << "Matched"<< endl;
                        }
                        if(OrbitalTypes[i] =="Pz")
                        {
                            y = -sqrt(3.0/(4.0*M_PI)) * dz/rad;
                            //cout << "Matched"<< endl;
                        }
                    }
                    if(OrbitalTypes[i] == "x2" || OrbitalTypes[i] == "xz" || OrbitalTypes[i] == "z2" || OrbitalTypes[i] == "yz" || OrbitalTypes[i] == "xy")
                    {
                        //n  5  spzeta   1.507  dzeta1  4.98896  dzeta2  2.58374  dcoef1  0.55763  dcoef2  0.55359
                        double spzeta = 1.507;
                        double dzeta1 = 4.98896;
                        double dzeta2 = 2.58374;
                        double dcoef1 = 0.55763;
                        double dcoef2 = 0.55359;
                        double r1 = pow((2*dzeta1),(5-1)) * sqrt(2*dzeta1/fact(2*(5-2))) * pow(rad,(5-2)) * exp(-dzeta1*rad);
                        double r2 = pow((2*dzeta2),(5-1)) * sqrt(2*dzeta2/fact(2*(5-2))) * pow(rad,(5-2)) * exp(-dzeta2*rad);
                        r = r1*dcoef1 + r2*dcoef2;
                        //cout << "radius " << r1*dcoef1 + r2*dcoef2 << endl;
                        //cout << OrbitalTypes[i] << endl;  
                        if(OrbitalTypes[i] == "z2")
                        {
                            y = sqrt(5.0/M_PI)/4.0 * (-pow(dx,2) - pow(dy,2) + 2 * pow(dz,2))/pow(rad,2);
                            //cout << "Matched"<< endl;
                        }
                        if(OrbitalTypes[i] =="x2")
                        {
                            y = sqrt(15.0/M_PI)/4.0 * (pow(dx,2) - pow(dy,2))/pow(rad,2);
                            //cout << "Matched"<< endl;
                        }
                        if(OrbitalTypes[i] =="xy")
                        {
                            y = sqrt(15.0/M_PI)/2.0 * (dx*dy)/pow(rad,2);
                            //cout << "Matched"<< endl;
                        }
                        if(OrbitalTypes[i] == "xz")
                        { 
                            y = sqrt(15.0/M_PI)/2.0 * (dx*dz)/pow(rad,2);
                            //cout << "Matched"<< endl;
                        }
                        if(OrbitalTypes[i] == "yz")
                        {
                            y = sqrt(15.0/M_PI)/2.0 * (dy*dz)/pow(rad,2);
                            //cout << "Matched"<< endl;
                        }
                    }
                } 
                hole_vox[one][two][three] += (r*y*MOLECULAR_ORBITALS[orbital_number][i]);
            }
        }

    }
}

  name.erase(name.end()-4,name.end());
  ofstream hole_cubefile;
  hole_cubefile.open(name +"_" +to_string(orbital_number) + "_orbital.cub");
  hole_cubefile <<"Test cube file" <<std::setprecision(6)<< "\n\n";
  hole_cubefile <<"   "<<molecule_coords.size() <<"  "<<min_mol_coords[0]<<"  "<<min_mol_coords[1]<<"  "<<min_mol_coords[2]<<endl;
  hole_cubefile <<"   "<<nvox[0]<<"  "<<gap<<"  "<<"0.000000"<<"  "<<"0.000000"<<endl;
  hole_cubefile <<"   "<<nvox[1]<<"  "<<"0.000000"<<"  "<<gap<<"  "<<"0.000000"<<endl;
  hole_cubefile <<"   "<<nvox[2]<<"  "<<"0.000000"<<"  "<<"0.000000"<<"  "<<gap<<endl;



  for(int i=0;i<molecule_coords.size();i++)
  {
      if(molecule_coords[i][0] == "C"){hole_cubefile<<"    6    0.000000"<<"    " <<molecule_coords[i][1]<<"    "<<molecule_coords[i][2]<<"    "<<molecule_coords[i][3]<<endl;}
      if(molecule_coords[i][0] == "H"){hole_cubefile<<"    1    0.000000"<<"    " <<molecule_coords[i][1]<<"    "<<molecule_coords[i][2]<<"    "<<molecule_coords[i][3]<<endl;}
      if(molecule_coords[i][0] == "O"){hole_cubefile<<"    8    0.000000"<<"    " <<molecule_coords[i][1]<<"    "<<molecule_coords[i][2]<<"    "<<molecule_coords[i][3]<<endl;}
      if(molecule_coords[i][0] == "Ag"){hole_cubefile<<"   47     0.000000"<<"    " <<molecule_coords[i][1]<<"    "<<molecule_coords[i][2]<<"    "<<molecule_coords[i][3]<<endl;}
  }
  int counter=0;
  int l=0; int m=0; int n=0;
  for(int p=0; p < nvox[0]*nvox[1]*nvox[2]; p++)
  {
              hole_cubefile <<"     "<< std::fixed << std::setprecision(6) << hole_vox[l][m][n]; 
              counter++;
              if(counter == 6){hole_cubefile << endl; counter=0;}
              n++;
              if(n>=nvox[2]){n=0; m++;}
              if(m>=nvox[1]){m=0; l++;}
  }
  hole_cubefile.close();
}



int main(int argc , char** argv){
string name;
name = argv[1];
int state; 
state = stol(argv[2]);
if(!argv[1]){cout << "Give me a file"; exit(0);}

MK_CUBE(name, state);


}//main bracket


