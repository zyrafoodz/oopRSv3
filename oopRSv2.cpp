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
    // Inventory text file path
    std::string filePathInventory = "C:\\Users\\franc\\Downloads\\inventory.txt";

    // Display inventory text file
    TextFileReader inventoryReader(filePathInventory);
    inventoryReader.ReadAndDisplayFileContents();

    // Recipe text file path
    std::string filePathRecipes = "C:\\Users\\franc\\Downloads\\recipes.txt";

    // Display recipes text file
    TextFileReader recipesReader(filePathRecipes);
    recipesReader.ReadAndDisplayFileContents();

    return 0;
}
