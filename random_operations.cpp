#include <iostream>
#include <fstream>
#include <random>
#include <string>
#include <chrono>

using namespace std::chrono;

std::ofstream plik;
std::random_device rdev;

int MIN_LENGTH_OF_NUMBER = 4;
int MAX_LENGTH_OF_NUMBER = 9;

int generateRandomNumber(int min, int max) {
    std::mt19937 rgen(rdev());
    std::uniform_int_distribution < int > idist(min, max);
    return idist(rgen);
}

std::string generateRandomString(int len) {
    std::string s;
    for (int i = 1; i <= len; i++) {
        int random_number = generateRandomNumber(1, 9);
        s += std::to_string(random_number);
    }
    return s;
}



int main() {
    plik.open("operations.txt");
    if (!plik.good()) {
        std::cout << "Error while opening file!\n";
        return 0;
    }
    int num_counter = 0;
    std::string sign_array[4] = {
      "+",
      "-",
      "*",
      "/"
    };
    std::cout << "Ile wygenerowac operacji do pliku?\n";
    std::cin >> num_counter;
    auto start = high_resolution_clock::now();
    for (int i = 0; i < num_counter; i++) {
        int random_length_number = generateRandomNumber(MIN_LENGTH_OF_NUMBER, MAX_LENGTH_OF_NUMBER);
        int random_index_sign = generateRandomNumber(0, 3);
        std::string first_random_number = generateRandomString(random_length_number);
        random_length_number = generateRandomNumber(MIN_LENGTH_OF_NUMBER, MAX_LENGTH_OF_NUMBER);
        std::string second_random_number = generateRandomString(random_length_number);
        std::string random_sign = sign_array[random_index_sign];
        plik << first_random_number + random_sign + second_random_number + "\n";
    }
    plik.close();
    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<milliseconds>(stop - start);
    plik.good() ? std::cout << "Successfully saved " << num_counter << " operations\n" : std::cout << "Error while saving\n";
    std::cout << "Time taken by put to file operations: " << duration.count() << " ms\n";
    return 0;
}
