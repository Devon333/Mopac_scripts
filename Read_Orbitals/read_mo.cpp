#include"READ_MO.h"
//#include"PM7.h"
#include"MopacOutput.h"
#include <bits/stdc++.h>


int main(int argc , char** argv)
{
        string input_file=argv[1];
        string cursor, save_line;
        ifstream input_parse;  
        vector<string> input_lines;
        int time_steps;
        double step_size;
        string debug;
        vector<int> active_space;
        vector<vector<int> > SD_basis;
        string hamiltonian, usingINDO, base_filename;

        input_parse.open(input_file, ios::in);
        string time_step_id="TIME STEPS:";
        string step_size_id="STEP SIZE:";
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
            else if(temp_string.find(step_size_id) != std::string::npos )
            {
                cout << temp_string << endl;
                temp_string.erase(0,10);
                step_size = stoi(temp_string);
                cout <<"step size in fs: " << step_size << endl;
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
                usingINDO="no";
                if(hamiltonian == "INDO")
                {
                    cout <<"Using INDO Hamiltonian" << endl;
                    usingINDO="yes"; 
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



    if(usingINDO =="yes")
    {
        cout << "using this part" << endl;
        int t=0;
        //double step_size=1.0; //0.48;
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
              MopacOutput info1(base_filename+"_"+to_string(t)+".out", hamiltonian, debug);
              cout << base_filename+"_"+to_string(t)+".out"<< endl;
              MopacOutput info2(base_filename+"_"+to_string(t+1)+".out", hamiltonian, debug);
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
              nac_mat=info1.central_diff_deriv(MOs1, MOs2, step_size, active_space);
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
              info1.write_im_matrix(base_filename+"_vib", t, nac_mat);
              info1.write_re_matrix(base_filename+"_T", t, ci_mat);
              t++;
          }while(t<time_steps);
     }


    if(usingINDO =="no")
    {
        cout << "using this part" << endl;
        int t=0;
        //double step_size=1.0; //0.48;
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
              vector<vector<double> > avg_MO_energy;
              vector<vector<double> > nac_mat;
              vector<vector<double> > t_overlap_mat, ovlp_mat, ci_mat;
              MopacOutput info1(base_filename+"_"+to_string(t)+".out", hamiltonian, debug);
              cout << base_filename+"_"+to_string(t)+".out"<< endl;
              MopacOutput info2(base_filename+"_"+to_string(t+1)+".out", hamiltonian, debug);
              cout << base_filename+"_"+to_string(t+1)+".out"<< endl;
              MOs1 = info1.OrbitalVectors;
              cout << "finished copying Orbitals from time " << t << endl;
              MOs2 = info2.OrbitalVectors;
              cout << "finished copying Orbitals from time " << t+1 << endl;
              Eig1 = info1.EigenvalueMatrix; 
              cout << "finished copying MO energies from time " << t << endl;
              Eig2 = info2.EigenvalueMatrix;
              cout << "finished copying MO energies from time " << t+1 << endl;
              t_overlap_mat=info1.time_overlap(info1.OrbitalVectors, info2.OrbitalVectors, step_size, active_space);
              cout << "finished time overlap matrix" << endl;
              ovlp_mat = info1.overlap(info1.OrbitalVectors, active_space);
              cout << "finished overlap matrix" << endl;
              nac_mat=info1.central_diff_deriv(MOs1, MOs2, step_size, active_space);
              //info1.write_Hvib_matrix_preCI(base_filename, t, info1.active_space, info1.SD_basis, nac_mat);
              avg_MO_energy=info1.average_matrix(info1.EigenvalueMatrix,info2.EigenvalueMatrix,active_space);              
              //avg_CI_energy=info1.average_matrix(info1.CI_Energies,info2.CI_Energies,info1.active_space);              
              avg_MO_energy=info1.CI_midpoint(info1.SD_Energies,info2.SD_Energies);
              //avg_CI_energy=info1.CI_midpoint(info1.CI_Energies,info2.CI_Energies);              
              //cout << "finished CI midpoint energy matrix" << endl;
              info1.write_re_matrix(base_filename+"_St", t, t_overlap_mat); 
              info1.write_re_matrix(base_filename+"_MO_mid_E", t, avg_MO_energy);
              //info1.write_re_matrix(base_filename+"_CI_mid_E", t, avg_CI_energy);
              info1.write_re_matrix(base_filename+"_S", t, ovlp_mat);
              //info1.write_im_matrix(base_filename+"_vib", t, nac_mat);
              //info1.write_re_matrix(base_filename+"_T", t, ci_mat);
              t++;
          }while(t<time_steps);
     }
 }

