#include <iostream>
#include <fstream>
#include <string>

class FileReader {
private:
    std::string filename;

public:
    FileReader(const std::string& filename) : filename(filename) {}

    bool readAndDisplay() {
        std::ifstream file(filename);
        if (!file.is_open()) {
            std::cerr << "Error opening file: " << filename << std::endl;
            return false;
        }

        std::string line;
        while (std::getline(file, line)) {
            std::cout << line << std::endl;
        }

        file.close();
        return true;
    }
};

int main() {
    std::string filename = "your_text_file.txt"; // Replace with the actual file name
    FileReader reader(filename);

    if (reader.readAndDisplay()) {
        std::cout << "File read successfully!" << std::endl;
    }
    else {
        std::cerr << "Failed to read file." << std::endl;
    }

    return 0;
}
