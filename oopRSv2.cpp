#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>

class FoodItem {
public:
    int code;
    std::string name;
    double quantity;
    bool isLiquid;

    FoodItem() : code(0), quantity(0.0), isLiquid(false) {}

    void readFromLine(const std::string& line) {
        std::istringstream iss(line);
        std::string metric;
        iss >> code >> name >> quantity >> metric;
        isLiquid = (metric == "milliliters");
    }

    std::string toLine() const {
        std::ostringstream oss;
        std::string metric = isLiquid ? "milliliters" : "grams";
        oss << code << "\t" << name << "\t" << quantity << " " << metric;
        return oss.str();
    }
};

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

    void addNewItem() {
        FoodItem item;
        item.code = getLastItemCode() + 1;

        std::cout << "Generated item code: " << item.code << std::endl;
        std::cout << "Enter item name: ";
        std::cin.ignore(); // Clear newline from previous input
        std::getline(std::cin, item.name);
        std::cout << "Enter quantity: ";
        std::cin >> item.quantity;
        std::cout << "Is it a liquid? (1 for yes, 0 for no): ";
        std::cin >> item.isLiquid;

        std::ofstream outFile(filePath_, std::ios::app); // Append mode
        if (outFile.is_open()) {
            outFile << item.toLine() << "\n";
            outFile.close();
            std::cout << "Item added to the file." << std::endl;
        }
        else {
            std::cerr << "Error opening file for writing." << std::endl;
        }
    }

    void removeItem() {
        std::vector<FoodItem> items;
        std::ifstream inFile(filePath_);
        if (!inFile.is_open()) {
            std::cerr << "Error opening file: " << filePath_ << std::endl;
            return;
        }

        // Read data from the file
        std::string line;
        while (getline(inFile, line)) {
            FoodItem item;
            item.readFromLine(line);
            items.push_back(item);
        }
        inFile.close();

        // Get the ID code from the user
        int userCode;
        std::cout << "Enter the ID code to remove: ";
        std::cin >> userCode;

        // Remove the item with the matching ID code and shift remaining items
        bool found = false;
        for (auto it = items.begin(); it != items.end(); ++it) {
            if (it->code == userCode) {
                items.erase(it);
                found = true;
                break;
            }
        }

        if (found) {
            // Shift remaining items' codes
            for (size_t i = 0; i < items.size(); ++i) {
                items[i].code = static_cast<int>(i) + 1;
            }

            // Save the updated data back to the file
            std::ofstream outFile(filePath_);
            if (outFile.is_open()) {
                for (const auto& item : items) {
                    outFile << item.toLine() << std::endl;
                }
                outFile.close();
                std::cout << "Item removed successfully." << std::endl;
            }
            else {
                std::cerr << "Error opening file for writing." << std::endl;
            }
        }
        else {
            std::cout << "Item with ID code '" << userCode << "' not found." << std::endl;
        }
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

    int getLastItemCode() {
        // Read the last item code from the file (if available)
        std::ifstream inFile(filePath_);
        int lastCode = 0;
        if (inFile.is_open()) {
            std::string line;
            while (getline(inFile, line)) {
                int code;
                std::istringstream iss(line);
                if (iss >> code) {
                    lastCode = code;
                }
            }
            inFile.close();
        }
        return lastCode;
    }
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

            // Additional options for Inventory
            std::cout << "Options:" << std::endl;
            std::cout << "1. Add new item" << std::endl;
            std::cout << "2. Remove an item" << std::endl;
            std::cout << "3. Return to main menu" << std::endl;
            int inventoryOption;
            std::cout << "Enter your choice (1-3): ";
            std::cin >> inventoryOption;

            if (inventoryOption == 1) {
                inventoryReader.addNewItem();
            }
            else if (inventoryOption == 2) {
                inventoryReader.removeItem();
            }
            // No need to handle option 3; it will loop back to the main menu
        }
        else if (choice == 2) {
            std::cout << "You selected Recipes." << std::endl;

            TextFileReader recipesReader(getFilePath(choice));
            recipesReader.ReadAndDisplayFileContents();
            // Add your recipe logic here
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
