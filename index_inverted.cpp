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

void countWord(const string& filename, unordered_map<string, unordered_set<string>>& wordFrequency) {
    ifstream file(filename);
    if (!file.is_open()) {
        cout << "Error: No se pudo abrir el archivo " << filename << endl;
        return;
    }
    // 
    const int numThreads = omp_get_max_threads();

    //
    file.seekg(0, std::ios::end);
    std::streampos fileSize = file.tellg();
    std::streampos chunkSize = fileSize / numThreads;
    file.close();
    #pragma omp parallel num_threads(numThreads)
    {
        ifstream file(filename);
        std::streampos startPosition = chunkSize * omp_get_thread_num();
        std::streampos endPosition = (omp_get_thread_num() == numThreads - 1) ? fileSize : startPosition + chunkSize;

        
        file.seekg(startPosition, std::ios::beg);
        unordered_set<string> processedWords;
        std::string word;
        while (file.tellg() < endPosition && file >> word) {
            if (processedWords.find(word) == processedWords.end()) {
                processedWords.insert(word); 
                #pragma omp critical
                {
                    
                    wordFrequency[word].insert(filename);
                }

            }
        }
        file.close();
    }
    
}

int main() {
    //Archivos
    vector<string> filenames = {"texto_2.txt", "texto_3.txt" , "texto_4.txt" , "texto_5.txt" ,"textos_5.txt" , "textos_400.txt"};

    //Mapa para almacenar 
    unordered_map<string, unordered_set<string>> wordFrequency;

    // Archivo de salida
    ofstream outputFile("output.txt");
    cout<<wordFrequency.max_size()<<endl;
    if (!outputFile.is_open()) {
        cerr << "Error: No se pudo abrir el archivo de salida" << endl;
        return 1;
    }

    
    auto start = steady_clock::now(); // Momento inicial
   
    for (size_t i = 1; i < 11; ++i) {
        string filename1 = "ttt" + std::to_string(i) + ".txt";
        auto start1 = steady_clock::now(); // Momento inicial
         
    
        countWord(filename1, wordFrequency);
        auto end1 = steady_clock::now(); // Momento final
        auto duration1 = duration_cast<milliseconds>(end1 - start1); // Duración total del bucle en milisegundos
        cout << "Tiempo total de ejecucion " << i << " :"<< duration1.count() << " ms" << endl;
    }
    
    auto end = steady_clock::now(); // Momento final
    auto duration = duration_cast<milliseconds>(end - start); // Duración total del bucle en milisegundos
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