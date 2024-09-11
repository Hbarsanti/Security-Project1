#include <fstream> 
#include <iostream> 
#include <string> 
#include <sstream>
using namespace std;

// read ciphertext and dictionary

string readInput(string fileName){
  ifstream inputFile(fileName);

  stringstream buffer;
  string inputText;

  buffer << inputFile.rdbuf();

  inputText = buffer.str();
  
  
  //cout << inputText << endl;
  inputFile.close(); 
  return inputText;

}

// compute frequency of each letter in ciphertext and sort them
/*std::map<char, int> frequency(const std::string &text) {
    std::map<char, int> freq;
    
        }
    }
    return freq;
}*/
// map the sorted frequency of ciphertext letters to the standard English letter frequency

// decrypt the ciphertext

// Count the number of dictionary words in the decrypted text

// Improve the key by permutation

int main() {

  readInput("ciphertext.txt");

  return 0;
}








