#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <map>
#include <vector>

// Define a struct to hold inventory data
struct InventoryItem {
    std::string name;
    int quantity;
    std::string metric;
};

// Read inventory data from a file
std::map<int, InventoryItem> readInventory(const std::string& filename) {
    std::map<int, InventoryItem> inventory;
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Error opening inventory file: " << filename << std::endl;
        return inventory;
    }

    std::string line;
    while (std::getline(file, line)) {
        std::istringstream iss(line);
        int id;
        InventoryItem item;

        // Assuming format: "01 / chicken / 500 / grams"
        iss >> id >> item.name >> item.quantity >> item.metric;

        if (iss.fail()) {
            std::cerr << "Error parsing inventory line: " << line << std::endl;
            continue;
        }

        inventory[id] = item;
    }

    file.close();
    return inventory;
}

int main() {
    // Read inventory data from the inventory file
    std::map<int, InventoryItem> inventory = readInventory("inventory.txt"); // Replace with your actual file name

    // Read recipe data from the recipe file
    std::ifstream recipeFile("recipe.txt"); // Replace with your actual file name
    if (!recipeFile.is_open()) {
        std::cerr << "Error opening recipe file." << std::endl;
        return 1;
    }

    std::string recipeLine;
    while (std::getline(recipeFile, recipeLine)) {
        std::istringstream recipeIss(recipeLine);
        int recipeId;
        std::string dishName;
        int servings;
        std::string ingredientIds;

        // Assuming format: "01 / fried chicken / 2 / 1,2"
        recipeIss >> recipeId >> dishName >> servings >> ingredientIds;

        if (recipeIss.fail()) {
            std::cerr << "Error parsing recipe line: " << recipeLine << std::endl;
            continue;
        }

        std::cout << "Dish ID: " << recipeId << ", Name: " << dishName << ", Servings: " << servings << std::endl;
        std::cout << "Ingredients:" << std::endl;

        std::istringstream ingredientIss(ingredientIds);
        int ingredientId;
        while (ingredientIss >> ingredientId) {
            const InventoryItem& ingredient = inventory[ingredientId];
            std::cout << "  - " << ingredient.name << ": " << ingredient.quantity << " " << ingredient.metric << std::endl;
        }
    }

    recipeFile.close();
    return 0;
}

