#include <fstream> 
#include <iostream> 
#include <string> 
#include <sstream>
using namespace std;

int main() {
  ifstream inputFile("ciphertext.txt");

  stringstream buffer;
  string line;
  string cipherText;

  buffer << inputFile.rdbuf();

  cipherText = buffer.str();
  
  //cout << "File Content: " << endl; 
   // while (getline(inputFile, line)) { 
     //   cout << line << endl; 
   // } 
  cout << cipherText << endl;
  


    
    inputFile.close(); 
  return 0;
}