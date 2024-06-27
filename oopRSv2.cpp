#include <iostream>
#include <fstream>
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

    static void displayMenu() {
        std::cout << "Welcome to Restaurant Solution!" << std::endl;
        std::cout << "1. Inventory" << std::endl;
        std::cout << "2. Recipes" << std::endl;
        std::cout << "3. Catering" << std::endl;
        std::cout << "4. Quit" << std::endl;
    }

private:
    std::string filePath_;
};

std::string getFilePath(int choice) {
    if (choice == 1) {
        return "C:\\Users\\franc\\Downloads\\inventory.txt";
    }
    else if (choice == 2) {
        return "C:\\Users\\franc\\Downloads\\recipes.txt";
    }
    else {
        return ""; // Handle invalid choice (optional)
    }
}

int main() {
    int choice;

    do {
        TextFileReader::displayMenu();

        do {
            std::cout << "Enter your choice (1-4): ";
            std::cin >> choice;
        } while (choice < 1 || choice > 4); // Validate user input

        if (choice == 1) {
            std::cout << "You selected Inventory." << std::endl;

            TextFileReader inventoryReader(getFilePath(choice));
            inventoryReader.ReadAndDisplayFileContents();
        }
        else if (choice == 2) {
            std::cout << "You selected Recipes." << std::endl;

            TextFileReader recipesReader(getFilePath(choice));
            recipesReader.ReadAndDisplayFileContents();
        }
        else if (choice == 3) {
            std::cout << "You selected Catering." << std::endl;
            // Add your catering logic here
        }
        else {
            std::cout << "Goodbye! Thanks for using Restaurant Solution." << std::endl;
        }
    } while (choice != 4);

    return 0;
}
