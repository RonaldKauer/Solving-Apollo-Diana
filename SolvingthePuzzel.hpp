/*
  Author: Ron Kauer, U55234148
  Class: Analysis of Algorithms
  Description: the purpose of this Algorithm is to get a input filename
    from the user that consists of colored arrows and directions, gets
    all of that information and finds the the path to a bullseye in the
    end of the maze
*/

#include <iostream>
#include <string>
#include <queue>
#include <utility>
#include <vector>
#include <fstream>
#include <cmath>

using namespace std;

class SolvingthePuzzel{
public:
  SolvingthePuzzel();

  //gets all of the neighbors of the cur node for the search
  void AddingtheWay();

  //makes the adj graph
  void MakeGraph(int x, int y);

  //im using bfs on the graph
  void TheAlgo();

  // sets the path to a new file
  void printP();

  //gets the info form the file and puts it into the graph
  void SettingG(string info);
private:
  struct node{//struct with everything that i need
    char Color;
    string Dir;
    bool visited;
    pair <int, int> MamaNode;
  };

  //everything i need to make the magic happen
  int row, col;
  int x, y;
  node** AdjLst;
  queue <pair <int, int> > QParing;
  vector <pair <string, int> > theway;
};

SolvingthePuzzel::SolvingthePuzzel():row(0), col(0), x(-1), y(-1){
}

void SolvingthePuzzel::AddingtheWay(){
  //setting the variables for the direction, color, rowe and colum
  char NColor = AdjLst[QParing.front().first][QParing.front().second].Color;
  string Ndir = AdjLst[QParing.front().first][QParing.front().second].Dir;
  int Nrow = QParing.front().first;
  int Ncol = QParing.front().second;

//checks the directions and color for the next area that it needs to go
  if(Ndir == "N"){
    for(int i = Nrow; i >= 0; i--){
      if(AdjLst[i][Ncol].Color != NColor && AdjLst[i][Ncol].visited == false){
        QParing.push(make_pair(i, Ncol));
        AdjLst[i][Ncol].visited = true;
        AdjLst[i][Ncol].MamaNode = make_pair(Nrow, Ncol);
      }
    }
  }
  else if(Ndir == "E"){
    for(int i = Ncol; i < col; i++){
      if(AdjLst[Nrow][i].Color != NColor && AdjLst[Nrow][i].visited == false){
        QParing.push(make_pair(Nrow, i));
        AdjLst[Nrow][i].visited = true;
        AdjLst[Nrow][i].MamaNode = make_pair(Nrow, Ncol);
      }
    }
  }
  else if(Ndir == "S"){
    for(int i = Nrow; i < row; i++){
      if(AdjLst[i][Ncol].Color != NColor && AdjLst[i][Ncol].visited == false){
        QParing.push(make_pair(i, Ncol));
        AdjLst[i][Ncol].visited = true;
        AdjLst[i][Ncol].MamaNode = make_pair(Nrow, Ncol);
      }
    }
  }
  else if(Ndir == "W"){
    for(int i = Ncol; i >= 0; i--){
      if(AdjLst[Nrow][i].Color != NColor && AdjLst[Nrow][i].visited == false){
        QParing.push(make_pair(Nrow, i));
        AdjLst[Nrow][i].visited = true;
        AdjLst[Nrow][i].MamaNode = make_pair(Nrow, Ncol);
      }
    }
  }
  else if(Ndir == "SW"){
    for(int i = Nrow, j = Ncol; i < row && j >= 0; i++, j--){
      if(AdjLst[i][j].Color != NColor && AdjLst[i][j].visited == false){
        QParing.push(make_pair(i, j));
        AdjLst[i][j].visited = true;
        AdjLst[i][j].MamaNode = make_pair(Nrow, Ncol);
      }
    }
  }
  else if(Ndir == "SE"){
    for(int i = Nrow, j = Ncol; i < row && j < col; i++, j++){
      if(AdjLst[i][j].Color != NColor && AdjLst[i][j].visited == false){
        QParing.push(make_pair(i, j));
        AdjLst[i][j].visited = true;
        AdjLst[i][j].MamaNode = make_pair(Nrow, Ncol);
      }
    }
  }
  else if(Ndir == "NE"){
    for(int i = Nrow, j = Ncol; i >= 0 && j < col; i--, j++){
      if(AdjLst[i][j].Color != NColor && AdjLst[i][j].visited == false){
        QParing.push(make_pair(i, j));
        AdjLst[i][j].visited = true;
        AdjLst[i][j].MamaNode = make_pair(Nrow, Ncol);
      }
    }
  }
  else if(Ndir == "NW"){
    for(int i = Nrow, j = Ncol; i >= 0 && j >=0; i--, j--){
      if(AdjLst[i][j].Color != NColor && AdjLst[i][j].visited == false){
        QParing.push(make_pair(i, j));
        AdjLst[i][j].visited = true;
        AdjLst[i][j].MamaNode = make_pair(Nrow, Ncol);
      }
    }
  }

}

//makes the graph with the correct size
void SolvingthePuzzel::MakeGraph(int x, int y){
  AdjLst = new node*[x];
  for(int q = 0; q < x; q++){
    AdjLst[q] = new node[y];
  }
}

// i use BFS to go through the graph
void SolvingthePuzzel::TheAlgo(){
  QParing.push(make_pair(0,0));
  while (!QParing.empty()){
    AdjLst[QParing.front().first][QParing.front().second].visited = true;
    AddingtheWay();
    QParing.pop();
  }
}

void SolvingthePuzzel::printP(){
  int i = row - 1;
  int j = col - 1;
  int Prow, Pcol, Trow, Tcol;

  //open a file to save the answer
  string output_file = "output.txt";
  ofstream outfile;
  outfile.open(output_file.c_str());

  //i go from the bullseye to the begining where we started and put it in the vectoe
  for(;i!=0 || j !=0; i = Prow, j = Pcol){
    Prow = AdjLst[i][j].MamaNode.first;
    Pcol = AdjLst[i][j].MamaNode.second;

    Trow = i - AdjLst[i][j].MamaNode.first;
    Tcol = j - AdjLst[i][j].MamaNode.second;

    if (AdjLst[Prow][Pcol].Dir[0] == 'N'){
      theway.push_back(make_pair(AdjLst[Prow][Pcol].Dir,Trow *-1));
    }
    else if(AdjLst[Prow][Pcol].Dir == "E"){
      theway.push_back(make_pair(AdjLst[Prow][Pcol].Dir,Tcol));
    }
    else if(AdjLst[Prow][Pcol].Dir[0] == 'S'){
      theway.push_back(make_pair(AdjLst[Prow][Pcol].Dir,Trow*-1));
    }
    else if(AdjLst[Prow][Pcol].Dir == "W"){
      theway.push_back(make_pair(AdjLst[Prow][Pcol].Dir,Tcol ));
    }
  }

//print out the answer and save it to the text filename
// i use abs() in the second value so i dont get a negative number
  for (int a = theway.size()-1; a >= 0; a--){
    cout << abs(theway[a].second) << theway[a].first << " ";
    outfile << abs(theway[a].second) << theway[a].first << " ";
  }
  outfile << endl;
  cout << endl;
}

//where i get all of the info from the file and make and set the graph
void SolvingthePuzzel::SettingG(string filename){
  string str;
  //open the file so i can get all of the input
  string input_file = filename;
  ifstream infile;
  infile.open(input_file.c_str());

  //get the rows and the columms for the graph
  int x, y;
  infile >> x >> y;
  row = x;
  col = y;

  //call make graph to make the graph
  MakeGraph(x,y);

  //get all of the information of the file and start setting that info to my graph
  for(int i = 0; i < row; i++){
    for(int j = 0; j < col; j++){
      if(infile >> str){
        AdjLst[i][j].Color = str[0];
        AdjLst[i][j].Dir = str.substr(str.find('-')+1);
        AdjLst[i][j].visited = false;
      }
    }
  }

}
