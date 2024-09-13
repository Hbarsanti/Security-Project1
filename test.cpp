#include <fstream>
#include <iostream>
#include <string>
#include <sstream>
#include <map>
#include <vector>
#include <algorithm>
using namespace std;

// read ciphertext and dictionary from a file
string readInput(const string& fileName) {
    ifstream inputFile(fileName);
    stringstream buffer;
    buffer << inputFile.rdbuf();
    inputFile.close();
    return buffer.str();
}

//compute the frequency of each letter in the ciphertext and sort them
vector<pair<char, int>> frequency(const string& text) {
    map<char, int> freq;
    for (char ch : text) {
        freq[ch]++;
    }
    vector<pair<char, int>> elems(freq.begin(), freq.end());
    sort(elems.begin(), elems.end(), [](const pair<char, int>& a, const pair<char, int>& b) {
        return a.second > b.second;
    });
    return elems;
}

// map the sorted frequency of ciphertext letters to standard English letter frequency
map<char, char> createMapping(const vector<pair<char, int>>& freq, const string& englishFreq) {
    map<char, char> mapping;
    size_t limit = min(freq.size(), englishFreq.size());
    for (size_t i = 0; i < freq.size() && i < englishFreq.size(); ++i) {
        mapping[freq[i].first] = englishFreq[i];
    }
    return mapping;
}

// decrypt the ciphertext using the character mapping
string decrypt(const string& cipher, const map<char, char>& charMapping) {
    string decryptedText = cipher;
    for (char& ch : decryptedText) {
        if (charMapping.find(ch) != charMapping.end()) {
            ch = charMapping.at(ch);
        }
    }
    return decryptedText;
}

// count the number of dictionary words in the decrypted text
int countWords(const string& decryptedText, const string& dictionary) {
    istringstream dictStream(dictionary);
    string word;
    int counts = 0;
    while (dictStream >> word) {
        if (decryptedText.find(word) != string::npos) {
            counts++;
        }
    }
    return counts;
}

// swap two characters in the key to generate a new one
string swapKey(string key, int i, int j) {
    swap(key[i], key[j]);
    return key;
}

int main() {
    string englishFreq = "ETAOINSHRDLCUMWFGYPBVKJXQZ";
    string cipher = readInput("ciphertext.txt");
    string dictionary = readInput("dictionary.txt");

    vector<pair<char, int>> sortedFreq = frequency(cipher);
    map<char, char> charMapping = createMapping(sortedFreq, englishFreq);
    string decryptedText = decrypt(cipher, charMapping);

    int previousWords = countWords(decryptedText, dictionary);
    int iterationLimit = 20;
    int maxWordCount = previousWords;

    bool improvement = true;
    int noImprovementCount = 0;

    while (improvement && noImprovementCount < iterationLimit) {
        improvement = false;
        for (int i = 0; i < englishFreq.size(); ++i) {
            for (int j = i + 1; j < englishFreq.size(); ++j) {
                string newKey = swapKey(englishFreq, i, j);
                map<char, char> newMapping = createMapping(sortedFreq, newKey);
                string newDecryptedText = decrypt(cipher, newMapping);

                int newWordCount = countWords(newDecryptedText, dictionary);

                if (newWordCount > maxWordCount) {
                    englishFreq = newKey;
                    decryptedText = newDecryptedText;
                    maxWordCount = newWordCount;
                    improvement = true;
                }
            }
        }

        if (!improvement) {
            noImprovementCount++;
        } else {
            noImprovementCount = 0;  // reset the counter if there is an improvement
        }

        cout << "Current key: " << englishFreq << endl;
        cout << "Words found: " << maxWordCount << endl;
        cout << "Decrypted text: " << decryptedText << endl << endl;
    }

    // final output
    cout << "Final key: " << englishFreq << endl;
    cout << "Final decrypted message: " << decryptedText << endl;
    cout << "Total words found: " << maxWordCount << endl;

    //manual key input
    string userInputKey;
    do {
        cout << "Enter a new key for manual decryption (or press Enter to keep the current key): ";
        getline(cin, userInputKey);

        if (!userInputKey.empty() && userInputKey.size() == englishFreq.size()) {
            map<char, char> userMapping = createMapping(sortedFreq, userInputKey);
            string userDecryptedText = decrypt(cipher, userMapping);
            int userWordCount = countWords(userDecryptedText, dictionary);

            // display the results with the user provided key
            cout << "User-provided key: " << userInputKey << endl;
            cout << "Decrypted message with user key: " << userDecryptedText << endl;
            cout << "Total words found with user key: " << userWordCount << endl;
        } else if (!userInputKey.empty()) {
            cout << "The provided key length does not match the required length. Please try again." << endl;
        }

    } while (!userInputKey.empty()); 

    cout << "Final key kept: " << englishFreq << endl;
    cout << "Final decrypted message with kept key: " << decryptedText << endl;
    cout << "Max words found with key: " << maxWordCount << endl;

    return 0;
}