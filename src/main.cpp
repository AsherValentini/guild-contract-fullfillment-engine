#include <iostream>
#include <vector>
#include <optional>
#include <unordered_map>
#include <algorithm>

using Item = std::string;

struct Recipe {
    Item output;
    std::vector<Item> inputs;
};

struct ContractFailure {
    Item blockedOn;
};

class CraftwrightEngine {
public:
    CraftwrightEngine(std::vector<Recipe> knownRecipes, std::unordered_map<Item, int> startingInventory)
        : m_inventory(std::move(startingInventory)) {

            for(auto recipe:knownRecipes) {
                m_recipes[recipe.output] = recipe.inputs;
            }
        }

    // You must implement this
    std::optional<ContractFailure> fulfillContract(const Item& requestedItem) {

        std::unordered_map<Item, int> tempInventory = m_inventory;

        auto failedAt = tryFillItem(requestedItem, tempInventory);

        if(failedAt.has_value()) {
            ContractFailure item{failedAt.value()};
            return item;
        }
        m_inventory = tempInventory;
        return std::nullopt;

    }

    // Debugging helpers
    void printInventory() const;

private:
    std::unordered_map<Item, int> m_inventory;
    std::unordered_map<Item, std::vector<Item>> m_recipes;

    std::optional<Item> tryFillItem (const Item& item, std::unordered_map<Item, int>& inventory) {

        auto it = inventory.find(item);
        if(it != inventory.end() && it->second > 0) {
            it->second--;
            return std::nullopt;
        }

        auto recipeIt = m_recipes.find(item);
        if(recipeIt == m_recipes.end()) {
            return item;
        }

        // try fill items that make this item?
        for(auto& subItem:recipeIt->second) {
            auto op = tryFillItem(subItem, inventory);
            if( op.has_value()) {
                return op.value();
            }

        }

        return std::nullopt;
    }

};


int main() {
	std::vector<Recipe> recipes = {
        {"IronSword", {"IronIngot", "WoodHandle"}},
        {"IronIngot", {"IronOre"}},
        {"WoodHandle", {"Plank"}},
        {"Plank", {"WoodLog"}}
    };

    std::unordered_map<Item, int> inventory = {
        {"IronOre", 1},
        {"WoodLog", 0}  // <-- Uh oh
    };

    CraftwrightEngine engine(recipes, inventory);

    auto result = engine.fulfillContract("IronSword");

    if (result.has_value()) {
        std::cout << "Blocked on: " << result->blockedOn << "\n";
    } else {
        std::cout << "Contract completed!\n";
    }

    //engine.printInventory();

	return 0;
}
