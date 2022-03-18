#include"READ_MO.h"
#include"PM7.h"
#include <bits/stdc++.h>


int main(int argc , char** argv)
{
        string input_file=argv[1];
        string cursor, save_line;
        ifstream input_parse;  
        vector<string> input_lines;
        int time_steps;
        string debug;
        vector<int> active_space;
        vector<vector<int> > SD_basis;
        string hamiltonian,usingPM7, base_filename;

        input_parse.open(input_file, ios::in);
        string time_step_id="TIME STEPS:";
        string trajectory_directory_id="TRAJECTORY DIRECTORY:";
        string hamiltonian_id="HAMILTONIAN:";
        string active_space_id="ACTIVE SPACE RANGE:";
        string SD_id="SLATER DETERMINANT BASIS:";
        string debug_id = "DEBUG:";
        if(!input_parse){cout<<"can't open input file " << input_file << " make sure it has been created" << endl;}
        while( getline(input_parse, cursor) )
        {
            save_line=cursor;
            input_lines.push_back(save_line);
        }  
        for(int i=0; i<input_lines.size();i++)
        {
            string temp_string = input_lines[i];
            if(temp_string.find(debug_id) != std::string::npos )
            {
                cout << temp_string << endl;
                temp_string.erase(0,6);
                debug = temp_string;
                cout <<"Debug value " << debug << endl;
            }
            else if(temp_string.find(SD_id) != std::string::npos )
            {
                cout << temp_string << endl;
                istringstream stream(temp_string.erase(0,25));
                string str; 
                vector<string> elec_exc;                
                while(stream >> str)
                {
                    elec_exc.push_back(str);
                }
                cout << "Mat Dimensions " << elec_exc[0] << " " << elec_exc[2] << endl;
//                cout<< input_lines[10]<< endl;
                //vector<vector<int> > SD_basis(stoi(elec_exc[0]),vector<int>(stoi(elec_exc[2])));
                i++;
                for(int sdl=0; sdl< stoi(elec_exc[2]); sdl++)
                {
                    string orbital_ind;
                    vector<int> tempvec;
                    istringstream sdline(input_lines[sdl+i]);
                    while(sdline >> orbital_ind)
                    {
                        cout << orbital_ind << " ";
                        tempvec.push_back(stoi(orbital_ind));
                    }
                    SD_basis.push_back(tempvec);
                    cout << endl;
                }
                for(int ind1=0; ind1<SD_basis.size();ind1++)
                {
                    for(int ind2=0; ind2<SD_basis[0].size();ind2++)
                    {
                        cout << ind1 << ","<< ind2 << ":"<< SD_basis[ind1][ind2] << "  ";
                    }
                    cout << endl;
                }
            }
            else if(temp_string.find(time_step_id) != std::string::npos )
            {
                cout << temp_string << endl;
                temp_string.erase(0,11);
                time_steps = stoi(temp_string);
                cout <<"number of time steps " << time_steps << endl;
            }
            else if(temp_string.find(trajectory_directory_id) != std::string::npos )
            {
                temp_string.erase(0,21); 
                base_filename = temp_string;
                cout <<"trajectory files directory " << base_filename << endl;
            }
            else if(temp_string.find(hamiltonian_id) != std::string::npos )
            {
                temp_string.erase(0,12); 
                hamiltonian = temp_string;
                usingPM7="no";
                if(hamiltonian == "PM7")
                {
                    cout <<"Using PM7 Hamiltonian" << endl;
                    usingPM7="yes"; 
                }
                cout << "using Hamiltonian " << hamiltonian << endl;
            }
            else if(temp_string.find(active_space_id) != std::string::npos)
            {
                temp_string.erase(0,19);
                istringstream collect(temp_string);
                int orbital_in_active_space;
                while(collect >> orbital_in_active_space)
                {
                    active_space.push_back(orbital_in_active_space);
                }
                cout << "active_space " ;
                for(auto i:active_space)
                {
                    cout << i <<"  ";
                }
                cout << endl;
            }
            else
            {
                cout << input_lines[i] << " is not a valid input parameter and is being ignored..."<< endl;
            } 
        }

    //exit(1);

//    cout << "Are we using PM7? reply with a yes or no (match the case)..."<< endl;
//    cin >> usingPM7;
//    cout << "What is the base file name: " << endl;
//    cin >> base_filename;
//
//    cout << "how many time steps are in the trajectory " << endl; //    cin >> time_steps;
    
//    base_filename="../ethyleneTest/ethyl";
//    usingPM7="yes";
//    time_steps=1;



    if(usingPM7 =="yes")
    {
        cout << "using this part" << endl;
        int t=0;
        double step_size=0.48;
        //PM7 out1(base_filename+"_"+"0"+".out",debug);
        //int numbOfMOs = out1.numOfMOs;
//commenting starts here
        //double ihbar = -0.0483781328; // -i hbar units Ry * fs
        vector<vector<double>> MOs1, MOs2, Eig1, Eig2;
        //vector<vector<double> > MOs1, MOs2;
        //vector<vector<double>> t_overlap, nac_mat, avg_Eig;
        //vector<vector<double>> MO_Deriv_Avg;
        //vector<vector<double> > MO_DERIV(numbOfMOs,vector<double>(numbOfMOs,0.0));
        //vector<vector<double> > MO_DERIV_AVG(numbOfMOs,vector<double>(numbOfMOs,0.0));

        clock_t start, end;
        start = clock();
        ios_base::sync_with_stdio(true);

        do{
              vector<vector<double> > avg_SD_energy;
              vector<vector<double> > avg_CI_energy;
              vector<vector<double> > nac_mat;
              vector<vector<double> > t_overlap_mat, ovlp_mat, ci_mat;
              PM7 info1(base_filename+"_"+to_string(t)+".out",debug);
              cout << base_filename+"_"+to_string(t)+".out"<< endl;
              PM7 info2(base_filename+"_"+to_string(t+1)+".out",debug);
              cout << base_filename+"_"+to_string(t+1)+".out"<< endl;
              MOs1 = info1.OrbitalVectors;
              cout << "finished copying Orbitals from time " << t << endl;
              MOs2 = info2.OrbitalVectors;
              cout << "finished copying Orbitals from time " << t+1 << endl;
              Eig1 = info1.CI_Energies; 
              cout << "finished copying CI energies from time " << t << endl;
              Eig2 = info2.CI_Energies;
              cout << "finished copying CI energies from time " << t+1 << endl;
              t_overlap_mat=info1.time_overlap(info1.OrbitalVectors, info2.OrbitalVectors, step_size, info1.active_space);
              cout << "finished time overlap matrix" << endl;
              ovlp_mat = info1.overlap(info1.OrbitalVectors, info1.active_space);
              cout << "finished overlap matrix" << endl;
              //nac_mat=info1.central_diff_deriv(MOs1, MOs2, step_size, info1.active_space);
              ci_mat=info1.CI_Coeffs;
              cout << "finished CI matrix" << endl;
              //info1.write_Hvib_matrix_preCI(base_filename, t, info1.active_space, info1.SD_basis, nac_mat);
              //avg_CI_energy=info1.average_matrix(info1.CI_Energies,info2.CI_Energies,info1.active_space);              
              avg_SD_energy=info1.CI_midpoint(info1.SD_Energies,info2.SD_Energies);
              avg_CI_energy=info1.CI_midpoint(info1.CI_Energies,info2.CI_Energies);              
              cout << "finished CI midpoint energy matrix" << endl;
              info1.write_re_matrix(base_filename+"_St", t, t_overlap_mat); 
              info1.write_re_matrix(base_filename+"_SD_mid_E", t, avg_SD_energy);
              info1.write_re_matrix(base_filename+"_CI_mid_E", t, avg_CI_energy);
              info1.write_re_matrix(base_filename+"_S", t, ovlp_mat);
              //info1.write_im_matrix(base_filename+"_vib", t, nac_mat);
              info1.write_re_matrix(base_filename+"_T", t, ci_mat);
              t++;
          }while(t<time_steps);
     }
 }





//         ofstream DOT_FILE;
//         ofstream Energy_FILE;
//         Energy_FILE.open(base_filename+"_"+to_string(t)+"_re.txt");
//         DOT_FILE.open(base_filename+"_"+to_string(t)+"_im.txt");

//         for(int i=0; i<numbOfMOs; i++)
//         {
//             for(int j=0; j<numbOfMOs; j++)
//             {
//                 if(j>i)
//                 {
//                     DOT_FILE << MO_DERIV[j][i] << "  ";
////                     cout << MO_REAL[i][i] - MO_REAL[j][j] << endl;
////                     cout << MO_DERIV[i][j] << endl;
////                     cout << MO_DERIV[i][j]/(fabs(MO_REAL[i][i]) - fabs(MO_REAL[j][j])) << endl;
//                 }
//                 else
//                 {
////                     Energy_FILE << MO_REAL[i][j] << "  ";
//                     DOT_FILE << MO_DERIV[i][j] << "  ";
//                 }
//                 //DOT_FILE << MO_DERIV[i][j] <<" " << i << " " << j << "   "; prints the indices of mo dot products. commented out so matrix heat maps can be made
//             }
////             Energy_FILE << endl;
//             DOT_FILE << endl;
//         }
// 
//          t++;
//          }while(t<time_steps);
//
//          ofstream Avg_File_Der;
//          Avg_File_Der.open(base_filename+"_AvgIm.txt");
//          
//          for(int i=0; i < numbOfMOs; i++)
//          {
//              for(int j=0; j<numbOfMOs;j++)
//              {
//                  MO_DERIV_AVG[i][j] = MO_DERIV_AVG[i][j]/(time_steps+1);
//                  cout << MO_DERIV_AVG[i][j] << "  " ;
//              }
//              cout << endl;
//          }
//          for(int i=0; i < numbOfMOs; i++)
//	  {
//              for(int j=0; j< numbOfMOs;j++)
//              {
//                //  MO_AVG_Deriv[i][j] = MO_AVG_Deriv[i][j]/2700.0; 
//                //  MO_AVG_Energy[i][j] = MO_AVG_Energy[i][j]/2700.0;
//                //  if( j> i)
//                //  {
//                      //MO_AVG_Energy[i][j] *= 1/2700; 
//                      //MO_AVG_Deriv[j][i] = MO_AVG_Deriv[j][i]/2700.0;
//                //      Avg_File_Der << MO_AVG_Deriv[j][i] << "  ";
//                  //    Avg_File_Ene << MO_AVG_Energy[j][i] << " ";
//                //  }
//                //  else
//                //  {
//                  //    Avg_File_Ene << MO_AVG_Energy[i][j] << "  ";
//                      Avg_File_Der << MO_DERIV_AVG[i][j] << "  ";
//                //  }
//          
//              }
//              Avg_File_Der << endl;
//          }
//          Avg_File_Der.close();
//comment ending here
//    }
//
//
//}  
//
//
// 
//    if(usingPM7 =="no")
//    {
//    int t=0;
//    int orb1=0;
//    double step_size= 1;
//    vector<string> numberofMOs = MOs(base_filename+"_"+"1"+".out");
//    int numMOs = stoi(numberofMOs[1]);
//    double hbar = 0.658218; // units eV * fs
//    double Ry_to_eV = 13.60569253; // 1 Ry = Ry_to_eV eV
//    double Ha_to_eV = 13.60569253*2; 
//    double ihbar = -0.658218; // -i hbar units eV * fs
////    double ihbar = -0.0483781328; // -i hbar units Ry * fs
////    double ihbar = -2.417876; // -i hbar units ha * 10^-17
////    double ihbar = -1;
//    vector<vector<double> > MOs1, MOs2;
//    vector<double> Eval1, Eval2;
//    vector<vector<double> > MO_DERIV(numMOs,vector<double>(numMOs));
//    vector<vector<double> > MO_REAL(numMOs,vector<double>(numMOs));
//    
//    do{
//          MOs1 = MO_Matrix(base_filename+"_"+to_string(t)+".out");
//          MOs2 = MO_Matrix(base_filename+"_"+to_string(t+1)+".out");
//          Eval1 = MOEIGENVALUES(base_filename+"_"+to_string(t)+".out");
//          Eval2 = MOEIGENVALUES(base_filename+"_"+to_string(t+1)+".out");
//          cout << "file number: " << t << endl;
//          for(int orb1=0; orb1<numMOs;orb1++)
//          {
//              for(int orb2=0; orb2<numMOs; orb2++)
//              {
//                  MO_DERIV[orb1][orb2]=0;
//                  if( orb1 == orb2)
//                  {
//                      MO_REAL[orb1][orb2] = 0.5 * ( (Eval1[orb1] + Eval2[orb2])); ///Ha_to_eV ) ;
//                  }
//                  for(int i=0; i<numMOs; i++)
//                  {
////                      if(orb1 == 33 && orb2 == 34)
////                      {
////                          cout << "MO_Deriv "<< orb1<< " " << orb2 <<" "<< i<<" " << MO_DERIV[orb1][orb2] << endl;
////                      }
//                      MO_REAL[orb1][orb2] += 0.00;
//                      MO_DERIV[orb1][orb2] += ihbar * (0.5/step_size) * ( (MOs1[i][orb1] * MOs2[i][orb2]) - (MOs2[i][orb1] * MOs1[i][orb2])  );        
//                  }
//              }
//          }
//         ofstream DOT_FILE;
//         ofstream Energy_FILE;
//         Energy_FILE.open(base_filename+"_"+to_string(t)+"_re.txt");
//         DOT_FILE.open(base_filename+"_"+to_string(t)+"_im.txt");
//         
//
//
//
//
//         for(auto i:active_space)
////         for(int i=0; i<numMOs; i++)
////         for(int i=29; i<39;i++)
//         {
//             for(auto j:active_space)
////             for(int j=0; j<numMOs; j++)
////             for(int j=29; j<39;j++)
//             {
//                 if(j>i)
//                 {
//                     DOT_FILE << MO_DERIV[j][i] << "  ";
////                     cout << MO_REAL[i][i] - MO_REAL[j][j] << endl;
////                     cout << MO_DERIV[i][j] << endl;
////                     cout << MO_DERIV[i][j]/(fabs(MO_REAL[i][i]) - fabs(MO_REAL[j][j])) << endl;
//                 }
//                 else
//                 {
//                     Energy_FILE << MO_REAL[i][j] << "  ";
//                     DOT_FILE << MO_DERIV[i][j] << "  ";
//                 }
//                 //DOT_FILE << MO_DERIV[i][j] <<" " << i << " " << j << "   "; prints the indices of mo dot products. commented out so matrix heat maps can be made
//             }
//             Energy_FILE << endl;
//             DOT_FILE << endl;
//         }
//         t++;
//    }while(t<time_steps);
//  }
//
//
//
//
//}//END OF MAIN BRACKET    
//
//
///*
//MOs1 = MO_Matrix(base_filename+"_"+to_string(1)+".out");
//
//
//for(int j=0; j<numMOs; j++)
//{
//cout << MOs1[j][116] << "  " << j << endl;
//}
//*/
//
//
//     
//
//
///*    //vector<string> MOs = MO_VECTOR_LINES(filename); 
////    cout << MOs[0].size() << " " << MOs.size() << endl;
//    vector<vector<string> > MOs;
//    MOs =  MO_Matrix(filename);
//    for(int i=0; i < MOs.size(); i++)
//    {
////        for(int j=0; j < 30; j++)
////        {
//            cout << MOs[i][35] << "  " << i  << endl;
////        }
//    }
//
////    Eigenvectorlines_split(MOs[1]);
//}*/
