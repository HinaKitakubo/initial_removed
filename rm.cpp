#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <iomanip>
#include <random>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>

using namespace std;

int main() {
   std::ifstream stream("./initial_n10000.dat");
   string line;

   int row = 0;
   int col;
   int n;
   int i = 0;
   double data[10000][9];
   const string delim = " ";

   double E, L;
   double r_close;
   double r_min = 0.001;

   while ( getline(stream, line) ) {   //"vmax.dat"を数列として格納する
      col = 0;
      for ( string::size_type spos, epos = 0;
          (spos = line.find_first_not_of(delim, epos)) != string::npos;) {
             string token = line.substr(spos,(epos = line.find_first_of(delim, spos))-spos);
             data[row][col++] = stod(token);
      }
      ++row;
   }

   std::cout << "Enter the number of particles : n = " ;   //粒子数を入力
   std::cin >> n;

   while( i < n ){
      E = (data[i][5]*data[i][5]+data[i][6]*data[i][6]+data[i][7]*data[i][7])/2.0 - 1.0/sqrt(data[i][2]*data[i][2]+data[i][3]*data[i][3]+data[i][4]*data[i][4]);
      L = sqrt(pow(data[i][3]*data[i][7] - data[i][4]*data[i][6] ,2.0) + pow(data[i][4]*data[i][5] - data[i][2]*data[i][7] ,2.0) + pow(data[i][2]*data[i][6] - data[i][3]*data[i][5] ,2.0));   // L = r × mv
      r_close = L*L / (1.0 + sqrt(1.0+2.0*E*L*L));

      if( r_close > r_min ){   //吸収される粒子以外を出力する
         std::cout << std::setprecision(15);
         std::cout << data[i][0] << " " << data[i][1] << " " << data[i][2] << " " << data[i][3] << " " << data[i][4] << " " << data[i][5] << " " << data[i][6] << " " << data[i][7] << " " << data[i][8] << std::endl;
      }
      i++;
   }

   return 0;
}
