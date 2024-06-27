#include <iostream>
#include <fstream> // For file I/O
#include <string>

class TextFileReader {
public:
    TextFileReader(const std::string& filePath) : filePath_(filePath) {}

    void ReadAndDisplayFileContents() {
        std::ifstream inputFile(filePath_);
        if (!inputFile.is_open()) {
            std::cerr << "Error opening file: " << filePath_ << std::endl;
            return;
        }

        std::string line;
        while (getline(inputFile, line)) {
            std::cout << line << std::endl;
        }

        inputFile.close();
    }

private:
    std::string filePath_;
};

int main() {
    std::string filePath = "C:\\Users\\franc\\Downloads\\inventory.txt";

    TextFileReader reader(filePath);
    reader.ReadAndDisplayFileContents();

    return 0;
}

