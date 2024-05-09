#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>
#include <chrono>
#include <omp.h>
#include <map>
using namespace std;
using namespace chrono;
int main() {
    unordered_map<string, unordered_set<string>> wordFrequency;
    const int numThreads = omp_get_max_threads();
    cout<<numThreads;    // Archivo de salida
    ofstream outputFile("output.txt");
    if (!outputFile.is_open()) {
        cerr << "Error: No se pudo abrir el archivo de salida" << endl;
        return 1;
    }

    auto start = steady_clock::now(); 

    #pragma omp parallel for
    for (size_t i = 0; i < 10; ++i) {
        string filename1 = "t" + std::to_string(i) + ".txt";
        auto start1 = steady_clock::now(); 
        ifstream file(filename1);
        if (!file.is_open()) {
            cout << "Error: No se pudo abrir el archivo " << filename1 << endl;
            
        }
        unordered_map<string, unordered_set<string>> wordFrequency_local;
        unordered_map<string, bool> processedWords;
        string word;
        while (file >> word) {
        /*if (processedWords.find(word) == processedWords.end()) {
            processedWords.insert(word); 
            
            wordFrequency[word].insert(filename1);
           
        }*/
        if (!processedWords[word]) {
            processedWords[word] = true; 
        }
    }
         #pragma omp critical 
    {
        for (const auto& pair : processedWords) {
            if (pair.second) {
                wordFrequency[pair.first].insert(filename1);
            }
        }
    }
        file.close();
        auto end1 = steady_clock::now(); 
        auto duration1 = duration_cast<milliseconds>(end1 - start1); //duration inner loop
        cout << "Tiempo total de ejecucion " << filename1 << ": " << duration1.count() << " ms" << endl;
    }

    auto end = steady_clock::now(); //
    auto duration = duration_cast<milliseconds>(end - start); //Duration
    outputFile << "Tiempo total de ejecucion: " << duration.count() << " ms" << endl;

    // Mostrar la frecuencia de las palabras
    for (const auto& pair : wordFrequency) {
        outputFile << pair.first << ": ";
        for (const auto& filename : pair.second) {
            outputFile << filename << " ";
        }
        outputFile << endl;
    }

    outputFile.close();
    
    return 0;
}
