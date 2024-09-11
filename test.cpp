#include <fstream> 
#include <iostream> 
#include <string> 
using namespace std;

int main() {
  ifstream inputFile("ciphertext.txt");

  string line;
  
  cout << "File Content: " << endl; 
    while (getline(inputFile, line)) { 
        cout << line << endl; 
    } 
  
    
    inputFile.close(); 
  return 0;
}