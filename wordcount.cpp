#include <iostream>
#include <fstream>
#include <string>
#include <ctime>
#include <omp.h>



int main() {
    const std::string filePath = "textos_400.txt";
    const int numThreads = omp_get_max_threads();
    long long totalWords = 0;

    std::clock_t start = std::clock();

    #pragma omp parallel num_threads(numThreads)
    {
        long long localCount = 0;
        std::ifstream file(filePath);
        file.seekg(0, std::ios::end);
        std::streampos fileSize = file.tellg();
        std::streampos chunkSize = fileSize / numThreads;
        std::streampos startPosition = chunkSize * omp_get_thread_num();
        std::streampos endPosition = omp_get_thread_num() == numThreads - 1 ? fileSize : startPosition + chunkSize;
        file.seekg(startPosition, std::ios::beg);

        std::string word;
        while (file.tellg() < endPosition && file >> word) {
            localCount++;
        }

        #pragma omp atomic
        totalWords += localCount;
    }

    std::clock_t end = std::clock();

    std::cout << "Total words: " << totalWords << std::endl;
    std::cout << "Word count completed in " << (end - start) / (double)CLOCKS_PER_SEC << " seconds\n";

    return 0;
}