/*
  Amber Wallace
  alw218
  cse109
  Program 7
*/

#include <iostream>
#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <map>
#include <fstream>
#include <sstream>

using namespace std;

int main(int argc, char *argv[]){
  //create map with operation -> bytecode pairs
  map<string, string> operationMap;
  operationMap["ADD"] = "a0";
  operationMap["SUB"] = "a1";
  operationMap["MULT"] = "a2";
  operationMap["DIV"] = "a3";
  operationMap["REM"] = "a4";
  operationMap["DUP"] = "a5";

  operationMap["AND"] = "b0";
  operationMap["OR"] = "b1";
  operationMap["NOT"] = "b2";
  operationMap["ISEQ"] ="b3";
  operationMap["ISNE"] ="b4";
  operationMap["ISGT"] ="b5";
  operationMap["ISGE"] = "b6";
  operationMap["ISLT"] = "b7";
  operationMap["ISLE"] = "b8";
  
  operationMap["LOADL"] ="c0";
  operationMap["LOADV"] ="c1";
  operationMap["STOREV"] = "c2";
  
  operationMap["JUMP"] = "d0";
  operationMap["JUMPF"] = "d1";
  
  operationMap["PRINT"] ="e0";
  operationMap["PRINTLN"] ="e1";
  operationMap["PRINTS"] ="e2";

  //get file names from command line args
  string myFiles[argc];
  int numFiles = 0;
  int i;
  for (i = 1; i < argc; i++){
    if(*argv[i] != '-'){
      myFiles[numFiles] = argv[i];
      numFiles++;
    }
  }

  //get selected commandline option
  int hflag = 0;
  int iflag = 0;
  int lflag = 0;
  int aflag = 0;
  int pflag = 0;
  int c;
  while((c = getopt(argc, argv, "hilap")) != -1){
    switch(c){
    case 'h':
      hflag = 1;
      break;
    case 'i':
      iflag = 1;
      break;
    case 'l':
      lflag = 1;
      break;
    case 'a':
      aflag = 1;
      break;
    case 'p':
      pflag = 1;
      break;
    case '?':
      return 1;
    default:
      abort ();
    }
  }

  //if -h has been selected display usage information once
  if(hflag){
    cout << "-h display this usage information" << endl << "-i prints all the .sasm instructions as well as their bytecode representation."
	 << endl << "-l prints the label map. The decimal value of the 1 byte hex string on the left and the respective label on the right."
	 << endl << "-a prints the instruction arguments. The decimal value of the 1 byte hex string on the left and the respective argument on the right."
	 << endl << "-p prints the bytecode of the .sasm program. It prints every instruction on its own line, mirroring the .sasm that was input." << endl;
  }
  if(iflag){
    map<string,string>::const_iterator iter;
    for(iter = operationMap.begin(); iter != operationMap.end(); iter++){
      cout << iter->first << " -> " << iter->second << endl;
    }
  }

  int curFile;
  for (curFile = 0; curFile < numFiles; curFile++){
    char* name = strdup(myFiles[curFile].c_str());
    ifstream inFile;
    inFile.open(name,ios::in);

    int i = 0;
    string program[255];
    program[i] = "CAFEBE";
    i++;

    map<string,string> labelMap;
    map<string,string> argMap;
    map<string,int> frMap; //forward reference map (labelName, i)

    int argIndex = 1;
    string argArray[255];
    int lineCount = 0;
    string line;
    while(getline(inFile, line)){
      string comment = "#";
      size_t commentLoc = line.find(comment);
      line = line.substr(0,commentLoc);
      if(commentLoc != 0){
	lineCount++;
	//add new labels to label map, if label is already used report error
	size_t labelMark = line.find(":");
	if(labelMark != string::npos){
	  string labelName = line.substr(0,labelMark);
	  if(labelMap.find(labelName) != labelMap.end()){
	    fputs("Error: label names must be distinct\n", stderr);
	    exit(1);
	  }
	  else{
	    char hexLabel[2];
	    sprintf(hexLabel, "%.2x", lineCount);
	    labelMap[labelName] = hexLabel;
	    string val = labelMap.find(labelName)->second + "0000";
	    program[i] = val;
	    i++;
	    //check if label matches forward reference
	    if(frMap.find(labelName) != frMap.end()){
	      int frIndex = frMap.find(labelName)->second;
	      string newVal = program[frIndex].substr(0,4) + labelMap.find(labelName)->second;
	      program[frIndex] = newVal;
	      frMap.erase(frMap.find(labelName));
	    }
	  }
	}
	//if token is operator add its hex code to the current
	//instruction according to the given table
	else{
	  //get operator token
	  size_t tokenBreak = line.find(" ");
	  string op = line.substr(0, tokenBreak);
	  string argVal;
	  //if there is an arg
	  if(tokenBreak != string::npos){
	    string arg = line.substr(tokenBreak+1, string::npos);
	    arg = arg.substr(0, arg.find(" "));
	    //determine if the arg is label or not
	    if(op == "JUMP" || op == "JUMPF"){
	      //if arg is label
	      argVal = "LL";
	      //check if label is already in label map
	      if(labelMap.find(arg) != labelMap.end()){
		argVal = labelMap.find(arg)->second;
	      }
	      else{
		//deal with forward reference of
		//label****************************************
		frMap[arg] = i;
		argVal = "FR";
	      }
	    }
	    else{
	      if(argMap.find(arg) == argMap.end()){
		//add new arg
		char hexArg[2];
		sprintf(hexArg, "%.2x", argIndex);
		argMap[arg] = hexArg;
		argVal = hexArg;
		argArray[argIndex-1]=arg;
		argIndex++;
	      }
	      else{
		//get index from existing arg
		argVal = argMap.find(arg)->second;
	      }
	    }
	  }
	  else{
	    //arg val is 00
	    argVal = "00";
	  }
	  op = operationMap.find(op)->second;
	  string val = "00"+op+argVal;
	  program[i] = val;
	  i++;
	}
      }
    }

    /*-p prints the bytecode of the .sasm program. It prints every
    instruction on its own line,
    mirroring the .sasm that was input.
    */
    if(pflag){
      int j;
      for(j = 0; j < i; j++){
	cout << program[j] << endl;
      }
    }

    /*-l prints the label map. The decimal value of the 1 byte hex
  string on the left and the
  respective label on the right.
    */
    if(lflag){
      map<string,string>::const_iterator iterl;
      for(iterl = labelMap.begin(); iterl != labelMap.end(); iterl++){
	cout << iterl->second << " -> " << iterl->first << endl;
      }
    }

    /* -a prints the instruction arguments. The decimal value of the 1
  byte hex string on the left
  and the respective argument on the right.
    */
    if(aflag){
      map<string,string>::const_iterator iterl;
      for(iterl = argMap.begin(); iterl != argMap.end(); iterl++){
	cout << iterl->second << " -> " << iterl->first << endl;
      }
    }

    string outFile = name;
    outFile = outFile.substr(0, outFile.find("asm"));
    char* oFile = strdup(outFile.c_str());
    cout << "output file containing hexcode: " << outFile << endl;
    ofstream myOF;
    myOF.open(oFile);
    int j;
    for(j = 0; j < i; j++){
      myOF << program[j];
    }
    myOF << "000000";

    //print labelMap to .s file
    map<string,string>::const_iterator iterl;
    for(iterl = labelMap.begin(); iterl != labelMap.end(); iterl++){
      myOF << iterl->second;
      string a = strdup(iterl->first.c_str());
      for(int  k=0; (unsigned) k < a.size(); ++k){
        myOF << hex << static_cast<int>(a[k]);
      }
      myOF << "3aff"; 
    }

    //print argMap to .s file
    map<string,string>::const_iterator itera;
    int ai;
    for(ai = 0; ai < argIndex-1; ai++){ 
      itera = argMap.find(argArray[ai]);
      myOF << itera->second;
      string a = strdup(itera->first.c_str());
      for(int k=0; (unsigned)k<a.size(); ++k){
	myOF << hex << static_cast<int>(a[k]);
      }
      myOF << "ff";
    }
    myOF << "aa";
    

    myOF.close();
  } 
}
