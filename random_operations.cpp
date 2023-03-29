#include <iostream>
#include <fstream>
#include <random>
#include <string>

using namespace std;

ofstream plik;
random_device rdev;

int MIN_LENGTH_OF_NUMBER = 4;
int MAX_LENGTH_OF_NUMBER = 9;

int generateRandomNumber(int min, int max) {
    mt19937 rgen(rdev());
    uniform_int_distribution<int> idist(min, max);
    return idist(rgen);
}

string generateRandomString(int len) {
    string s;
    for (int i = 1; i <= len; i++) {
        int random_number = generateRandomNumber(1, 9);
        s += to_string(random_number);
    }
    return s;
}



int main()
{
    plik.open("operations.txt");
    if (!plik.good()) {
        cout << "Error while opening file!" << endl;
        return 0;
    }
    int num_counter = 0;
    string sign_array[4] = {"+", "-", "*", "/"};
    cout << "Ile wygenerowac operacji do pliku?\n";
    cin >> num_counter;
    for (int i = 0; i <= num_counter; i++) {
        int random_length_number = generateRandomNumber(MIN_LENGTH_OF_NUMBER, MAX_LENGTH_OF_NUMBER);
        int random_index_sign = generateRandomNumber(0, 3);
        string first_random_number = generateRandomString(random_length_number);
        random_length_number = generateRandomNumber(MIN_LENGTH_OF_NUMBER, MAX_LENGTH_OF_NUMBER);
        string second_random_number = generateRandomString(random_length_number);
        string random_sign = sign_array[random_index_sign];
        plik << first_random_number + random_sign + second_random_number + "\n";
    }
    plik.close();
    plik.good() ? cout << "Poprawnie zapisano " << num_counter << " operacji" : cout << "Blad podczas zapisu";
    return 0;
}
