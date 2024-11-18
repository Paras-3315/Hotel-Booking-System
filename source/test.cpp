#include <iostream>
#include <fstream>

using namespace std;

int main() {
    ifstream loginFile("data/login.txt");
    if (!loginFile) {
        cerr << "Error: Could not open login.txt" << endl;
        return 1;
    }
    cout << "File opened successfully!" << endl;
    return 0;
}