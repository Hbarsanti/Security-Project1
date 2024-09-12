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
        cout << entry.first << ": " << entry.second << " ";
    }
    cout << endl;

    return elems;
}

// map the sorted frequency of ciphertext letters to the standard English letter frequency
map<char, char> mapper(const vector<pair<char, int>> &freq) {
    map<char, char> mapping;
    string englishFreq = "ETAOINSHRDLCUMWFGYPBVKJXQZ";
    for (size_t i = 0; i < freq.size() && i < englishFreq.size(); ++i) {
        mapping[freq[i].first] = englishFreq[i];
    }

    for (const auto& entry : mapping) {
        cout << entry.first << ": " << entry.second << " ";
    }
    cout << endl;

    return mapping;
}

// decrypt the ciphertext using the character mapping
string decrypt(const string &cipher, const map<char, char> &charMapping) {
    string decryptedText = cipher;

    for (char ch : entry) {
        if (charMapping.find(ch) != charMapping.end()) {
            ch = charMapping.at(ch);
        }
    }

    return decryptedText;
}

// Count the number of dictionary words in the decrypted text

// Improve the key by permutation

int main() {
    string cipher = readInput("ciphertext.txt");

    vector<pair<char, int>> sortedFreq = frequency(cipher);
    map<char, char> charMapping = mapper(sortedFreq);
    string decryptedText = decrypt(cipher, charMapping);

    cout << "Decrypted Text: " << decryptedText << endl;

    return 0;
}