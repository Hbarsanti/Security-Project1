#include <fstream> 
#include <iostream> 
#include <string> 
#include <sstream>
#include <map>
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

map<char, int> freqq(const string &text) {
    map<char, int> freq;
    

  for (char ch : text) {
        freq[ch]++;
        
    }


   for (const auto& entry : freq) {
        cout << entry.first << ": " << entry.second << " ";
    }
    cout << endl;
  
    return freq;
}
    
// map the sorted frequency of ciphertext letters to the standard English letter frequency

// decrypt the ciphertext

// Count the number of dictionary words in the decrypted text

// Improve the key by permutation

int main() {

  string cipher = readInput("ciphertext.txt");

  string hello = "Hello";
  freqq(cipher);
  return 0;
}








