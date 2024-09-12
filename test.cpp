#include <fstream> 
#include <iostream> 
#include <string> 
#include <sstream>
#include <map>
#include <vector>
#include <algorithm>
using namespace std;
string englishFreq = "ETAOINSHRDLCUMWFGYPBVKJXQZ";
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
map<char, char> mapper(const vector<pair<char, int>> &freq, int n) {
    //string englishFreq = englishFreq.substr(1, englishFreq.length() -1) + englishFreq.front();
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
    int count = 0;
    // read word from stream and store it into word
    while (dictStream >> word) {
        if (decryptedText.find(word) != string::npos) {
            count++;
        }
    }
    cout << "Number of dictionary words: " << count << endl;
    return count;
}
// Improve the key by permutation


int main() {
    string cipher = readInput("ciphertext.txt");
    int n = 0;
    while( n < 26 ) {
    vector<pair<char, int>> sortedFreq = frequency(cipher);
    map<char, char> charMapping = mapper(sortedFreq, n);
    string decryptedText = decrypt(cipher, charMapping);

    cout << "Decrypted Text: " << decryptedText << endl;

    count(decryptedText, readInput("dictionary.txt"));

    //
    n++;
    }
    

    return 0;
}