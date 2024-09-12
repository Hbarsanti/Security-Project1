#include <fstream> 
#include <iostream> 
#include <string> 
#include <sstream>
#include <map>
#include <vector>
#include <algorithm>
using namespace std;
// read ciphertext and dictionary
string readInput(string fileName){
    ifstream inputFile(fileName);
    stringstream buffer;
    string inputText;

    buffer << inputFile.rdbuf();
    inputText = buffer.str();
    inputFile.close(); 
    return inputText;
}

// compute frequency of each letter in ciphertext and sort them
vector<pair<char, int>> frequency(const string &text) {
    map<char, int> freq;


    for (char ch : text) {
        freq[ch]++;
    }


    vector<pair<char, int>> elems(freq.begin(), freq.end());

    sort(elems.begin(), elems.end(), [](const pair<char, int>& a, const pair<char, int>& b) {
        return a.second > b.second;
    });

    for (const auto& entry : elems) {
        cout << entry.first << ":" << entry.second << " ";
    }
    cout << endl;

    return elems;
}

// map the sorted frequency of ciphertext letters to the standard English letter frequency
map<char, char> mapper(const vector<pair<char, int>> &freq, string englishFreq) {
    map<char, char> mapping;
    for (size_t i = 0; i < freq.size() && i < englishFreq.size(); ++i) {
        mapping[freq[i].first] = englishFreq[i];
    }

    for (const auto& entry : mapping) {
        cout << entry.first << ":" << entry.second << " ";
    }
    cout << endl;

    return mapping;
}

// decrypt the ciphertext using the character mapping
string decrypt(const string &cipher, const map<char, char> &charMapping) {
    string decryptedText = cipher;

    for (char &ch : decryptedText) {
        if (charMapping.find(ch) != charMapping.end()) {
            ch = charMapping.at(ch);
        }
    }

    return decryptedText;
}

// Count the number of dictionary words in the decrypted text
int count(const string &decryptedText, const string &dictionary) {
    istringstream dictStream(dictionary);
    string word;
    int counts = 0;
    // read word from stream and store it into word
    while (dictStream >> word) {
        if (decryptedText.find(word) != string::npos) {
            counts++;
        }
    }
    cout << "Number of dictionary words: " << counts << endl;
    return counts;
}
// Improve the key by permutation

string swapKey(string key, int i, int j) {
    string newKey = key;
    char temp = newKey[i];
    newKey[i] = newKey[j];
    newKey[j] = temp;
    return newKey;
}
int main() {
    string englishFreq = "ETAOINSHRDLCUMWFGYPBVKJXQZ";
    string cipher = readInput("ciphertext.txt");
    int currentWords;
    int previousWords = 0;
    int n = 0;
    int m = 0;
    int k = 1;
    while( n < 26 ) {
     cout << englishFreq << endl;
    vector<pair<char, int>> sortedFreq = frequency(cipher);
    map<char, char> charMapping = mapper(sortedFreq, englishFreq);
    string decryptedText = decrypt(cipher, charMapping);

    cout << "Decrypted Text: " << decryptedText << endl;

   currentWords = count(decryptedText, readInput("dictionary.txt"));
   //
   if (currentWords >= previousWords) {
       previousWords = currentWords;
        
       englishFreq=swapKey(englishFreq, m, k);
        m++;
        k++;
    } else {
        m--;
        k--;
        englishFreq=swapKey(englishFreq, m, k);
        k++;
        englishFreq=swapKey(englishFreq, m, k);
    }


    
    //cout << englishFreq << endl;


    //englishFreq = englishFreq.substr(1, englishFreq.length() -1) + englishFreq.front();

    //
    n++;
    }
    

    return 0;
}