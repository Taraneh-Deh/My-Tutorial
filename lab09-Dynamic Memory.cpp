#include <iostream>
#include <fstream>
#include <sstream>

using namespace std;

string* bitSequences = nullptr;
int numSequences = 0;

int readFile(const string& filename) {
    ifstream file(filename);

    if (file.is_open()) {
        string line;
        int lineCount = 0;

        while (getline(file, line)) {
            // Resize the bitSequences array if necessary
            string* tempArray = new string[lineCount + 1];
            for (int i = 0; i < lineCount; ++i) {
                tempArray[i] = bitSequences[i];
            }
            delete[] bitSequences;
            bitSequences = tempArray;

            bitSequences[lineCount++] = line;
        }

        file.close();
        return lineCount;
    }

    return 0; // Return 0 if file cannot be opened
}

void writeFile(const string& filename, string stuffedBits) {
    ofstream file(filename);

    if (file.is_open()) {
        file << stuffedBits << endl;
        file.close();
    }
}

void searchBitSequence(const string& query) {
    for (int i = 0; i < numSequences; i++) {
        if (bitSequences[i].find(query) != string::npos) {
            cout << "Found bit sequence at index " << i << ": " << bitSequences[i] << endl;
        }
    }
}

void enterNewBitSequence() {
    string newSequence;
    
    cout << "Enter a new bit sequence: ";
    cin >> newSequence;

    // Resize the bitSequences array to fit the new entry
    string* tempArray = new string[numSequences + 1];
    for (int i = 0; i < numSequences; ++i) {
        tempArray[i] = bitSequences[i];
    }
    delete[] bitSequences;
    bitSequences = tempArray;

    bitSequences[numSequences++] = newSequence;

    cout << "Bit sequence added successfully!" << endl;
}

void viewAllBitSequences() {
    cout << "Bit Sequences:" << endl;
    for (int i = 0; i < numSequences; i++) {
        cout << i << ": " << bitSequences[i] << endl;
    }
}

string performBitStuffing() {
    string delimiter = "01111110";
    string result = "";

    for (int i = 0; i < numSequences; i++) {
        string sequence = bitSequences[i];
        string stuffedSequence = "";

        int consecutiveOnes = 0;
        for (char c : sequence) {
            stuffedSequence += c;

            if (c == '1') {
                consecutiveOnes++;
                if (consecutiveOnes == 5) {
                    stuffedSequence += '0';
                    consecutiveOnes = 0;
                }
            } else {
                consecutiveOnes = 0;
            }
        }

        result += stuffedSequence;
        result += delimiter;
    }

    return result;
}

void destuffBitSequence() {
    ifstream file("data_transfer.txt");

    if (file.is_open()) {
        string fileContent;
        getline(file, fileContent);
        file.close();

        string delimiter = "01111110";
        numSequences = 0;
        
        //Update the number of sequences
        int lastDelim = fileContent.find(delimiter);
        while (lastDelim != string::npos){
            numSequences++;
            lastDelim = fileContent.find(delimiter, lastDelim + delimiter.length());
        }
        
        delete[] bitSequences;
        bitSequences = new string[numSequences];

        int sequenceCount = 0;
        int startPos = 0;
        int endPos = fileContent.find(delimiter);
        while (endPos != string::npos) {
            string sequence = fileContent.substr(startPos, endPos - startPos);

            bitSequences[sequenceCount] = sequence;
            sequenceCount++;

            startPos = endPos + delimiter.length();
            endPos = fileContent.find(delimiter, startPos);
        }

        // Remove excess zeros after five consecutive ones
        for (int i = 0; i < numSequences; i++) {
            string& sequence = bitSequences[i];
            string destuffedSequence;
            int consecutiveOnes = 0;

            for (int j = 0; j < sequence.length(); j++){
                char c = sequence[j];
                if (c == '1') {
                    destuffedSequence += c;
                    consecutiveOnes++;

                    if (consecutiveOnes == 5) {
                        consecutiveOnes = 0;
                        j++;
                    }
                } else {
                    destuffedSequence += c;
                    consecutiveOnes = 0;
                }
            }

            sequence = destuffedSequence;
        }
    } else {
        cout << "Failed to open file: data_transfer.txt" << endl;
    }
}

int main() {
    string filename = "bit_sequences.txt";
    string transferFilename = "data_transfer.txt";
    string option;

    numSequences = readFile(filename);

    while (true) {
        cout << "Options:\n";
        cout << "1. Search bit sequences for a substring\n";
        cout << "2. Enter a new bit sequence\n";
        cout << "3. View all bit sequences\n";
        cout << "4. Examine stuffed bit sequence\n";
        cout << "5. Store stuffed bit sequence to file\n";
        cout << "6. Destuff bit sequence from file\n";
        cout << "Enter your option (or 'q' to quit): ";

        cin >> option;

        if (option == "1") {
            string query;
            cout << "Enter the substring to search for: ";
            cin >> query;
            searchBitSequence(query);
        } else if (option == "2") {
            enterNewBitSequence();
        } else if (option == "3") {
            viewAllBitSequences();
        } else if (option == "4") {
            string stuffedData = performBitStuffing();
            cout << "Bit-stuffed data: " << stuffedData << endl;
        } else if (option == "5") {
            string stuffedData = performBitStuffing();
            cout << "Generated data: " << stuffedData << endl;
            writeFile(transferFilename, stuffedData);
            cout << "Data written to file: " << transferFilename << endl;
        } else if (option == "6") {
            cout << "Destuffing bit sequences... ";
            destuffBitSequence();
            cout << "Destuffed. " << endl;
            viewAllBitSequences();
        } else if (option == "q") {
            break;
        } else {
            cout << "Invalid option. Please try again.\n";
        }

        cout << endl;
    }

    delete[] bitSequences;

    return 0;
}