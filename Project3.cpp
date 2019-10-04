/*
  Author: Ron Kauer, U55234148
  Class: Analysis of Algorithms
  Description: the purpose of this Algorithm is to get a input filename
    from the user that consists of colored arrows and directions, gets
    all of that information and finds the the path to a bullseye in the
    end of the maze
*/

#include <string>
#include <iostream>
#include <fstream>
#include "SolvingthePuzzel.hpp"

using namespace std;

int main(int argc, char *argv[]){
  SolvingthePuzzel problem; // create a object of the class

  if (argc == 1){
    cout << "Please put the name of the file with the graph to run after the ./maze"<<endl;
  }
  else{
    problem.SettingG(argv[1]);// getting the file name and making the graph with it
    problem.TheAlgo();// calling the BFS algo to solve the maze
    problem.printP();//printing the path
  }
  return 0;
}
