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

  // read ciphertext and dictionary
std::string readFile(const std::string &filename) {
    std::ifstream file(filename);
    std::string text((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
    return text;
}
// compute frequency of each letter in ciphertext and sort them
std::map<char, int> frequency(const std::string &text) {
    std::map<char, int> freq;
    
        }
    }
    return freq;
}
// map the sorted frequency of ciphertext letters to the standard English letter frequency

// decrypt the ciphertext

// Count the number of dictionary words in the decrypted text

// Improve the key by permutation
}



