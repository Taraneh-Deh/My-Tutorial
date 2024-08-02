#include <iostream>
#include <iomanip>
#include <algorithm>

using namespace std;

const int MEMORY_SIZE = 10;  // Size of the computer memory

// Function to display the memory contents
void displayMemory(string* memory) {
    cout << "Memory Contents:" << endl;
    for (int i = 0; i < MEMORY_SIZE; i++) {
        cout << "Register " << i << " (0x" << &(memory[i]) << "): " << memory[i] << endl;
    }
    cout << endl;
}

// Function to read value from memory
void readValue(string* memory) {
    int readIndex;
    cout << "Enter the index of the register to read (0-9): ";
    cin >> readIndex;

    if (readIndex >= 0 && readIndex < MEMORY_SIZE) {
        string* ptr = &memory[readIndex];
        cout << "Value at register " << readIndex << " (0x" << ptr << ") is " << *ptr << endl;
    } else {
        cout << "Invalid register index!" << endl;
    }
}

// Function to write value to memory
void writeValue(string* memory) {
    int writeAddress;
    cout << "Enter the memory register to write (0-9): ";
    cin >> writeAddress;
    cin.ignore();  // Ignore the newline character from previous input

    cout << "Enter the value to write (press Enter on an empty line to finish):\n";
    string writeValue;
    string inputLine;
    while (true) {
        getline(cin, inputLine);
        if (inputLine.empty()) {
            break;
        }
        writeValue += inputLine + '\n';
    }

    if (writeAddress >= 0 && writeAddress < MEMORY_SIZE) {
        string* ptr = &memory[writeAddress];
        *ptr = writeValue;
        cout << "Value written to register " << writeAddress << endl;
    } else {
        cout << "Invalid memory register!" << endl;
    }
}

// Function to search and print memory values containing the entered string
void SearchMemory(string* memory) {
    string searchString;
    cout << "Enter the string to search for: ";
    cin >> searchString;

    bool found = false;
    for (int i = 0; i < MEMORY_SIZE; i++) {
        if (memory[i].find(searchString) != string::npos) {
            cout << "Register " << i << " (0x" << &(memory[i]) << "): " << memory[i] << endl;
            found = true;
        }
    }

    if (!found) {
        cout << "No memory values contain the entered string." << endl;
    }
}

void swapValues(string* str1, string* str2) {
    string temp = *str1;
    *str1 = *str2;
    *str2 = temp;
}

void rearrangeValues(string* memory){
    char choice;
    do {
        int address1, address2;
        cout << "Choose one memory register (0-9): ";
        cin >> address1;
        cout << "Choose another memory register to swap with: ";
        cin >> address2;

        swapValues(memory+address1, memory+address2);
        displayMemory(memory);

        cout << "Do you want to swap more memory values? (Y/N): ";
        cin >> choice;
        cout << endl;
    } while (choice == 'Y' || choice == 'y');
}

int main() {
    string memory[MEMORY_SIZE];  // Computer memory

    int choice;
    do {
        cout << "Memory Visualization Program" << endl;
        cout << "1. Read value from memory" << endl;
        cout << "2. Write value to memory" << endl;
        cout << "3. Display memory contents" << endl;
        cout << "4. Search values in memory" << endl;
        cout << "5. Rearrange values in memory" << endl;
        cout << "6. Exit" << endl;
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                readValue(memory);
                break;
            case 2:
                writeValue(memory);
                break;
            case 3:
                displayMemory(memory);
                break;
            case 4:
                SearchMemory(memory);
                break;
            case 5:
                rearrangeValues(memory);
                break;
            case 6:
                cout << "Exiting program..." << endl;
                break;
            default:
                cout << "Invalid choice!" << endl;
                break;
        }

        cout << endl;
    } while (choice != 6);

    return 0;
}