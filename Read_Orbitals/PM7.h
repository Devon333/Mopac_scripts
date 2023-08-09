#include<iostream> 
#include<iterator>
#include<map>
#include<fstream>
#include<sstream>
#include<vector>
#include<utility>
#include<bits/stdc++.h>//insert function

using namespace std; 

class PM7{
    private:

    public:
        string debug;
        int numOfMOs;
        vector<string> lines; // file lines in vector element
        vector<string> MOLines;
        vector<vector<double> > OrbitalVectors;
        vector<vector<double> > EigenvalueMatrix;
        map<int, double> Eigenvals;
        map<int, vector<double>> MolecularOrbitals;
        
       //CLASS FUNCTIONS
        void Read(string name);
        void MOs(string filename);
        void numMOs(vector<string> MOs);
        int str2int(string element);
        void getMOLines();
        vector<vector<double> > MOs();
        void print_map(string comment, map<int, double> m);
        void print_map(string comment, map<string, double> m);
        void print_map(string comment, map<int, vector<double> > m);
        void write_eigenvalues(string file_path, map<int, double>); 
        void write_im_matrix(string file_path, int time, vector<vector<double> > matrix);
        void write_re_matrix(string file_path, int time, vector<vector<double> > matrix);
        vector<vector<double> > copy_map(map<int, double > m);
        vector<vector<double> > average_matrix(vector<vector<double> > mat1, vector<vector<double> > mat2, vector<int> active_space);
        vector<vector<double> > copy_map(map<int, vector<double> > m);
        vector<vector<double> > time_overlap(vector<vector<double> > time_point1, vector<vector<double> > time_point2, vector<int> active_space);
        vector<vector<double> > central_diff_deriv(vector<vector<double> > time_point1, vector<vector<double> > time_point2, double step_size, vector<int> active_space);
//        vector<vector<string> > MOvec(numOfMOs,vector<string>(numOfMOs));

      //CLASS CONSTRUCTORS 
       PM7(string filename, string debug){
           //vector<string>formulaLine;
           Read(filename);
           MOs(filename); 
//           getMOLines();
//           MOs();
//           for(int i=0; i<MOvec.size(); i++)
//           {
//               for(int j=0; j<MOvec[0].size(); j++)
//               {
//                   cout << MOvec[i][j] << "  ";
//               }
//               cout << endl;
//           }
//           for(int i=0; i<MOLines.size(); i++)
//           {
//               cout <<i << " " << MOLines[i].size() << " "<< MOLines[i] << " "<< endl ;
//           }
//           cout << endl;
       }


};


vector<vector<double> > PM7::average_matrix(vector<vector<double> > mat1, vector<vector<double> > mat2, vector<int> active_space)
{
    vector<vector<double> > average_eigenvalues(active_space.size()+1, vector<double>(active_space.size()+1));
    cout << "midpoint Eigenvalues ";
    for(int i=0; i<active_space.size(); i++)
    {
        average_eigenvalues[i+1][i+1] = mat1[active_space[i]][active_space[i]] + mat2[active_space[i]][active_space[i]];
        cout << average_eigenvalues[i+1][i+1] << "  ";
    }
    cout << endl;
    
    return average_eigenvalues;
}


void PM7::write_re_matrix(string file_path, int time, vector<vector<double> > matrix)
{
    ofstream mat_file; 
    mat_file.open(file_path+ "_" + to_string(time)+"_re.txt");
    for(int i=1; i<matrix.size(); i++)
    {
        for(int j=1; j<matrix.size(); j++)
        {
            mat_file << matrix[i][j] << "  ";
        }
        mat_file << endl;
    }
    mat_file.close();
}

void PM7::write_im_matrix(string file_path, int time, vector<vector<double> > matrix)
{
    ofstream mat_file; 
    mat_file.open(file_path+ "_" + to_string(time)+"_im.txt");
    for(int i=1; i<matrix.size(); i++)
    {
        for(int j=1; j<matrix.size(); j++)
        {
                mat_file << matrix[i][j] << "  ";
        }
        mat_file << endl;
    }
    mat_file.close();
}


vector<vector<double> > PM7::time_overlap(vector<vector<double> > time_point1, vector<vector<double> > time_point2, vector<int> active_space)
{
    clock_t start, end;
    start = clock();
    ios_base::sync_with_stdio(true);
    vector<vector<double> > time_ov(active_space.size()+1, vector<double>(active_space.size()+1)); 

              for(int index1=0;index1<active_space.size(); index1++)
              {
                  for(int index2=0; index2<active_space.size(); index2++)
                  {    
                      for(int coeff=1;coeff<=numOfMOs; coeff++)
                      {
                          //cout << " MO "<< active_space[index1] << " "<< time_point1[active_space[index1]][coeff] << endl;
                          time_ov[index1+1][index2+1] +=
                          ( time_point1[active_space[index1]][coeff] * time_point2[active_space[index2]][coeff]) ;
                      }
//                      if(debug.find("1"))
//                      {
//                          time_ov[index1+1][index2+1] = 1/pow((active_space.size() * active_space.size()),0.5) * time_ov[index1+1][index2+1]; 
                          cout << active_space[index1] << ", "<< active_space[index2] << ":"<< time_ov[index1+1][index2+1] << "\t";
//                      }
		  }
//                  if(debug.find("1"))
//                  {
                      cout << endl;
                      
//                  }
	      }
    end = clock();
    double time_taken = double(end-start)/double(CLOCKS_PER_SEC);
    cout << "norm constant " << 1/pow((active_space.size() * active_space.size()),0.5) << endl;
    cout << "time to calculate overlap matrix " << time_taken << endl;
    //exit(0);
    return time_ov;
}




vector<vector<double> > PM7::central_diff_deriv(vector<vector<double> > time_point1, vector<vector<double> > time_point2, double step_size, vector<int> active_space)
{
    double hbar = 0.658218; // units eV * fs
    double ihbar = -0.658218; // -i hbar units eV * fs
    clock_t start, end;
    start = clock();
    ios_base::sync_with_stdio(true);
    vector<vector<double> > central_difference_deriv(active_space.size()+1, vector<double>(active_space.size()+1)); 

              for(int index1=0;index1<active_space.size();index1++)
              {
                  for(int index2=0;index2<active_space.size();index2++)
                  {    
                      for(int coeff=1;coeff<=numOfMOs; coeff++)
                      {
                         //cout << time_point1[active_space[index1]][coeff] << endl;
                          central_difference_deriv[index1+1][index2+1] += ihbar * 1/(2*step_size)
                          * ( ( time_point1[active_space[index1]][coeff] * time_point2[active_space[index2]][coeff]) 
                          - 
                              ( time_point2[active_space[index1]][coeff] * time_point1[active_space[index2]][coeff]) );
                      }
                      if(debug=="1")
                      {
                          cout << active_space[index1] << ", "<< active_space[index2] << ":"<< central_difference_deriv[index1][index2] << "    ";
                      }
		  }
                  if(debug=="1")
                  {
                      cout << endl;
                  }
	      }
    end = clock();
    double time_taken = double(end-start)/double(CLOCKS_PER_SEC);
    cout << "time to calculate tdc matrix " << time_taken << endl;
    return central_difference_deriv;
}


vector<vector<double> > PM7::copy_map(map<int, vector<double> > m)
{
    vector<vector<double> > orbitalVectors(numOfMOs+1,vector<double>(numOfMOs+1));
    int index1 = 0; 
    int index2 = 0;
    double value;
    for (map<int, vector<double>>::const_iterator key=m.begin();key != m.end(); key++) 
    {
        index1++;
        index2=0;
        for(vector<double>::const_iterator val=key->second.begin(); val != key->second.end(); val++)
        {
            index2++;
            value = *val;
            orbitalVectors[index1][index2] = value ; 
        }
    }
    return orbitalVectors;    
}

vector<vector<double> > PM7::copy_map(map<int, double > m)
{
    vector<vector<double> > eigenvalue_matrix(numOfMOs+1,vector<double>(numOfMOs+1));
    for(int i=0; i<=numOfMOs; i++)
    {
            int index = i;
            double value= m[i];
            eigenvalue_matrix[index][index] = value;
            //cout << "copying eigenvalue " << index <<" " << index << ": "<<value<< endl;
    }
    return eigenvalue_matrix;    
}

void PM7::print_map(string comment, map<int, vector<double> > m)
{
    cout << comment << "{ " ;
    for (map<int, vector<double>>::const_iterator key=m.begin();key != m.end(); key++) 
    {
        cout <<"\""<< key->first<< "\"" << " : [";
        for(vector<double>::const_iterator val=key->second.begin(); val != key->second.end(); val++)
        {
            if (val == key->second.end()-1)
            {
                cout << *val ;
            }
            else
            {
                cout << *val << ",  ";
            }
        }
        cout << "],\n";
    }
    cout << "}\n";
}


void PM7::print_map(string comment, map<int, double> m)
{
    std::cout << comment;
    for (const auto& [key, value] : m) {
        std::cout << key << " = " << value << "; ";
    }
    std::cout << "\n";
}



void PM7::Read(string name)
{
//Contains all the lines of the output file##########
//vector<string> lines;                           //###
ifstream InFile;                                //###
string runner, GrabLine;//Identifying strings     ###
InFile.open(name, ios::in);                     //###
//Contains all the lines of the output file##########

//Identify the number of configurations generated//######
int NDet;                                       //#######
vector<string> VecNDet;                         //#######
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

//lielines;

}


void PM7::MOs(string filename)
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
    string IdNMOs ="eigvals";       //#######
    int EigvalCount = 1;                          //#######
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
        //if(GrabLine.find(IdNMOs,0) != string::npos && WrtCount < 1 )                                                                 //###
        if(GrabLine.find(IdNMOs,0) != string::npos  )                                                                 //###
        {                                                                                                                            //###
            //cout<< "found " << IdNMOs << " |" << GrabLine << endl;                                                                   //###
            vector<string> tempVec;
            istringstream split(GrabLine); //split is a variable where GrabLine is split into individual string split by white space //##
            copy(istream_iterator<string>(split),
            istream_iterator<string>(),                                                                                              //###
            back_inserter(tempVec));//appends individual strings into the vector VecMOs                                               //###
            for(int eig_line=1; eig_line<tempVec.size(); eig_line++)
            {
               Eigenvals[EigvalCount]=stod(tempVec[eig_line]);
               EigvalCount++; 
            }
            //MOs = (VecNDet[2]);//Stores the number of determinants generated as a variable                                         //###
            //cout << VecMOs << endl;                                                                                                  //##
            WrtCount++;
        }                                                                                                                            //##
                                                                                                                                     //##
    }//loop over all lines of a file and save them to lines                                                                          ####
                                                                                                                                     //##
    InFile.close();                                                                                                                  //##
    if(debug=="1")
    {
        cout<< "got eigenvalues " << endl;
    }
    string label="Eigenvalue Map ";
    int num_of_basis_func; 
    map<int,double>::iterator itr;
    itr=Eigenvals.end(); --itr;
    if(debug=="1")
    {
        cout << "last element of iterator for eigenvalue map  " << itr->first << "  " << itr->second << endl;
    }
    num_of_basis_func=itr->first;
    numOfMOs=num_of_basis_func;

    if(debug=="1")
    {
        print_map(label, Eigenvals);
        cout << " using MOs " << endl;                                                                          //##
    }
    //if (!InFile){cout << name <<" closed"<<endl;} //check if the file is open                                                        ####
    //else {cout << name << " is still open"; exit(1);}//print something from the file stream                                          ####
    //Initial Getter from File###########################################################################################################
    EigenvalueMatrix=copy_map(Eigenvals);
    if(debug=="1")
    { 
        cout<< "copied eigenvalues " << endl;
    }
    //string runner, GrabLine;//Identifying strings     ###
    InFile.open(filename, ios::in);                     //###
    int orbitalCount=1;
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
            getline(InFile,runner);
            GrabLine= runner;
            vector<string> tempVec;
            istringstream split(GrabLine); //split is a variable where GrabLine is split into individual string split by white space //##
            copy(istream_iterator<string>(split),
            istream_iterator<string>(),                                                                                              //###
            back_inserter(tempVec));

           // cout <<"first vector element " <<  tempVec[0] << endl;
            int tempCount=0;
            while (tempCount < num_of_basis_func)// != stoi(tempVec[0]))
            {
                //cout<< "between found IDNMOs " <<GrabLine.size() <<  " |" << GrabLine << endl;                                                                   //###
                if (GrabLine.size()== 1)
                {
                    //cout<< "uing if statement"<< endl;
                    getline(InFile,runner);
                    GrabLine = runner;
                     
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
    for (int i=0;i<orbitalLines.size();i++)
    {
        //cout<< "orbline "  << orbitalLines[i] << endl;
    }
    vector<string> MO_label_vec;
    vector<vector<double> > MolecularOrbital_matrix(num_of_basis_func,vector<double>(num_of_basis_func));
    int basis_count=0;
    int basis_combin=0;
    int vec_size=0;
    for(int sav_line=0;sav_line<orbitalLines.size();sav_line++)
    {
        if(basis_combin >= num_of_basis_func )
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
        string MolecularOrbital_label;
        MolecularOrbital_label=tempVec[0]+":" + tempVec[1] + tempVec[2];
        //cout << MolecularOrbital_label << endl;
        tempVec.erase(tempVec.begin(),tempVec.begin()+4);
        for(int i=0; i<tempVec.size(); i++)
        {
            MolecularOrbital_matrix[basis_count+i][basis_combin]=stod(tempVec[i]);
            //cout <<" " <<  basis_count+i << "  " << basis_combin << "  " << tempVec[i] << " ";
            vec_size = tempVec.size();
        }
        basis_combin++;
        //cout << endl;


    }
                                                                                                                  //##
    for(int ele=0;ele < MolecularOrbital_matrix.size(); ele++)
    {
        vector<double> tempVector;
        for(int ele2=0;ele2 < MolecularOrbital_matrix[0].size(); ele2++)
        {
            //cout << ele << ",  " << ele2 << "  " << MolecularOrbital_matrix[ele][ele2] << endl;
            tempVector.push_back(MolecularOrbital_matrix[ele][ele2]);
        }
        MolecularOrbitals[ele+1]=tempVector;
    }
    //print_map("molecular orbital", MolecularOrbitals);
    if(debug=="1")
    {
        cout<< "got eigenvectors " << endl;
    }
 
    OrbitalVectors = copy_map( MolecularOrbitals);

    if(debug=="1")
    {
        cout<< "copied eigenvectors " << endl;
    }
}

//void PM7::numMOs(vector<string> VecMOs)
//{
//    vector<string> atoms; 
//    vector<int> numOfAtoms;
//    vector<string> cutPart;
//    cout << "this it the size of the vector " << VecMOs.size() << endl;
////    for(int i=0; i<VecMOs.size();i++)
////    {
////        cout << VecMOs[i] << endl;
////
////    }
// 
//    for(int i=2; i<VecMOs.size();i++)
//    {
//        if(VecMOs[i]== "="){break;}
//        cutPart.push_back(VecMOs[i]); 
//    }
//    
//    for(int i=0; i<cutPart.size(); i++)
//    {
//      for(int j=0; j<cutPart[i].size(); j++)
//      {
//        //cout << "i " << i << " j " << j<< endl;
//        if(isalpha(cutPart[i][j]) && isalpha(cutPart[i][j+1]))
//        {
//            cout << cutPart[i][j] << cutPart[i][j+1] << endl;
//            string temp; 
//            temp.push_back(cutPart[i][j] + cutPart[i][j+1]); 
//            atoms.push_back(temp);
//            j++;
//        }
////        if(isalpha(cutPart[i][j]) && isdigit(cutPart[i][j+1]))
//        else if(isalpha(cutPart[i][j]) )
//        {
//            cout << cutPart[i][j] << endl;
//            string temp2;
//            temp2.push_back(cutPart[i][j]); 
//            atoms.push_back(temp2);
//        }
//        else if(isdigit(cutPart[i][j]))
//        {
//           string temp3;
//           if(isdigit(cutPart[i][j]) && isdigit(cutPart[i][j+1]))
//             {
//               cout<<"digits " << cutPart[i][j] << cutPart[i][j+1] << endl;
//               temp3 += cutPart[i][j];
//               temp3 += cutPart[i][j+1];
//               numOfAtoms.push_back(stoi(temp3));
//               j++;
//             }
//           else{
//               cout << "digit" << cutPart[i][j] << endl;
//               temp3.push_back(cutPart[i][j]);
//               numOfAtoms.push_back(stoi(temp3));
//               }
//        } 
//      }
//    }
//
////    for(int i=0; i<numOfAtoms.size();i++)
////    {
////        cout << "printing atom numbers" << endl;
////        cout << numOfAtoms[i] << endl;
////        cout << "printing atom numbers" << endl;
////    }
//   
//    int num=0;
//    for(int i=0; i<atoms.size(); i++)
//    {
//       //cout << str2int(atoms[i]) << endl;
//       switch(str2int(atoms[i]))
//       {
//           case 4:
//               num += 4 * numOfAtoms[i];
//               //cout << num << endl;
//               break;
//
//           case 1:
//               //cout << "num of hydrogens " << numOfAtoms[i] << endl;
//               //cout << "adding hydrogens " << num << "then " ; 
//               num += 1 * numOfAtoms[i] ;
//               //cout << num << endl;
//               break;
//           default:
//               cout << "No matching case" << endl; 
//       }
//        //cout << num << endl;
//    }
//    numOfMOs = num;
//    cout << "number of MOs " << numOfMOs << endl;
//}
//
//int PM7::str2int(string element)
//{
//   int atomicNumber;
//   if(element == "C"){atomicNumber=4;}
//   if(element == "H"){atomicNumber=1;}
//   if(element == "Ag"){atomicNumber=6;}
//   return atomicNumber;
//}
//
//
//void PM7::getMOLines()
//{
//    cout << lines.size() << endl;
//    int checkLine;
//    for(int i=0; i<lines.size(); i++)
//    {
//        vector<string> tempLine;
//        istringstream line(lines[i]);
//        for(int ele=0; ele < lines[i].size(); ele++)
//        {
//            string splitLine;
//            line >> splitLine;
//            if(splitLine != "")
//            {
//                tempLine.push_back(splitLine);
//            }
//        }
//
//        for(int bits=0; bits < tempLine.size(); bits++)
//        {
//            //cout << tempLine.size()<< "  ";
//            if(tempLine[bits] =="Root")
//            {
//                checkLine= i+5;
//                for(int k=checkLine+1; k<checkLine+numOfMOs+1 ; k++)
//                {
//                    if(lines[k] == ""){continue;}
//                    else{MOLines.push_back(lines[k]);}
//                }
//            }
////            if(i >= checkLine && i < checkLine + numOfMOs+1 && checkLine != 0 )
////            {
////                MOLines.push_back(lines[i]);
//////                cout<< bits << "/" << tempLine[bits] << "  " << endl;
////            }
//        }
////            cout << endl;
//        
//    }
//}
//

//vector<vector<double> > PM7::MOs()
//{
//    vector<vector<double> > MOvec2(numOfMOs,vector<double>(numOfMOs));
//    cout << "size " << MOLines.size() << endl;
//    int k=0;
//    int loopCount=0;
//    int counter=0;
//    for(int i=0; i<MOLines.size() ; i++)
//    {
//        istringstream splitLine(MOLines[i]);
//        for(int j=0; j<MOLines[i].size() ; j++)
//        {
//            string element;
//            splitLine >> element;
//            if(j>=3)
//            {
//                if(element==""){break;}
//                if(counter == numOfMOs){counter=0 ; loopCount++;}
//                //cout <<" gt i " <<counter<<" "<< (j-3)+(loopCount*8) << "  "<< element << "  " ;
//                MOvec2[counter][j-3+(loopCount*8)]= stod(element);          
//            }
//        }
//        counter++;
//        //cout << endl;
//    }
//    return this->MOvec = MOvec2;
//
//}







