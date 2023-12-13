#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

enum class Unit {
    Piece,
    Gram,
    Mililiter,
    Cup,
    Tablespoon,
    Teaspoon,
};

class Ingredient {
private:
    static int nextId;
    int id;
    string name;
    Unit unit;

public:
    Ingredient(string n, Unit u) : id(nextId++), name(n), unit(u) {}

    int getId() const { return id; }
    string getName() const { return name; }
    Unit getUnit() const { return unit; }
};

int Ingredient::nextId = 0;

class Recipe {
private:
    static int nextId;
    int id;
    string name;
    vector<pair<Ingredient, float>> ingredientList;

public:
    Recipe(string n) : id(nextId++), name(n) {}

    string getName() const { return name; }
    int getId() const { return id; }

    void addIngredient(const Ingredient& ingredient, float quantity) {
        ingredientList.push_back(make_pair(ingredient, quantity));
    }

    void display() const {
        cout << "Recipe: " << name << endl;
        cout << "Ingredients:" << endl;

        for (const auto& pair : ingredientList) {
            cout << "  - " << pair.second << " " << unitToString(pair.first.getUnit())
                 << " of " << pair.first.getName() << endl;
        }
    }

private:
    string unitToString(Unit unit) const {
        switch (unit) {
            case Unit::Piece:
                return "pieces";
            case Unit::Gram:
                return "grams";
            case Unit::Mililiter:
                return "milliliters";
            case Unit::Cup:
                return "cups";
            case Unit::Tablespoon:
                return "tablespoons";
            case Unit::Teaspoon:
                return "teaspoons";
        }
        return "unknown unit";
    }
};

int Recipe::nextId = 0;

class Matrix {
private:
    vector<vector<int>> adjacencyMatrix;
    vector<string> items; // Ingredients and Recipes

public:
    Matrix() {}

    void addNode(const string& nodeName) {
        items.push_back(nodeName);
        // Update the adjacency matrix size
        updateMatrixSize();
    }

    void addEdge(const string& nodeName1, const string& nodeName2) {
        int index1 = findIndex(nodeName1);
        int index2 = findIndex(nodeName2);

        if (index1 != -1 && index2 != -1) {
            // Update the adjacency matrix
            updateMatrixSize();
            adjacencyMatrix[index1][index2] = 1;
            adjacencyMatrix[index2][index1] = 1;
        }
    }

    void displayMatrix() const {
        cout << "Adjacency Matrix:" << endl;
        cout << "\t\t\t\t";
        for (const auto& item : items) {
            cout << item << "\t";
        }
        cout << endl;

        for (size_t i = 0; i < adjacencyMatrix.size(); ++i) {
            cout << items[i] << "\t\t\t";

            for (size_t j = 0; j < adjacencyMatrix[i].size() - 1; ++j) {
                cout << adjacencyMatrix[i][j] << "\t";
            }
            cout << endl;
        }
    }

    void displayList() const {
        cout << "Adjacency List:" << endl;

        for (size_t i = 0; i < items.size(); ++i) {
            cout << items[i] << " -> ";
            for (size_t j = 0; j < items.size(); ++j) {
                if (adjacencyMatrix[i][j] == 1) {
                    cout << items[j] << " ";
                }
            }
            cout << endl;
        }
    }

private:
    int findIndex(const string& name) const {
        auto it = find(items.begin(), items.end(), name);
        if (it != items.end()) {
            return distance(items.begin(), it);
        }
        return -1; // Not found
    }

    void updateMatrixSize() {
        // Increase the size of the adjacency matrix if needed
        if (adjacencyMatrix.size() < items.size()) {
            adjacencyMatrix.push_back(vector<int>(items.size(), 0));
            for (auto& row : adjacencyMatrix) {
                row.push_back(0);
            }
        }
    }
};

void insertDummy(vector<Ingredient>& ingredients, vector<Recipe>& recipes) {
    recipes.push_back(Recipe("Omelette"));
    recipes.push_back(Recipe("Pancakes"));

    ingredients.push_back(Ingredient("Egg", Unit::Piece));
    ingredients.push_back(Ingredient("Sugar", Unit::Gram));
    ingredients.push_back(Ingredient("Flour", Unit::Gram));
    ingredients.push_back(Ingredient("Milk", Unit::Mililiter));
    ingredients.push_back(Ingredient("Butter", Unit::Gram));
    ingredients.push_back(Ingredient("Salt", Unit::Tablespoon));
    ingredients.push_back(Ingredient("Pepper", Unit::Tablespoon));

    recipes[0].addIngredient(ingredients[0], 3);  // 3 eggs
    recipes[0].addIngredient(ingredients[1], 20); // 20 grams of sugar
    recipes[0].addIngredient(ingredients[2], 100); // 100 grams of flour

    recipes[1].addIngredient(ingredients[2], 150); // 150 grams of flour
    recipes[1].addIngredient(ingredients[3], 200); // 200 milliliters of milk
    recipes[1].addIngredient(ingredients[4], 30);  // 30 grams of butter
}

void insertDummyMatrix(vector<Ingredient>& ingredients, vector<Recipe>& recipes, Matrix& adjacencyMatrix) {
    for (const auto& ingredient : ingredients) {
        adjacencyMatrix.addNode(ingredient.getName());
    }

    for (const auto& recipe : recipes) {
        adjacencyMatrix.addNode(recipe.getName());
    }

    adjacencyMatrix.addEdge(ingredients[0].getName(), recipes[0].getName());
    adjacencyMatrix.addEdge(ingredients[1].getName(), recipes[0].getName());
    adjacencyMatrix.addEdge(ingredients[2].getName(), recipes[0].getName());
    adjacencyMatrix.addEdge(ingredients[0].getName(), recipes[1].getName());
    adjacencyMatrix.addEdge(ingredients[2].getName(), recipes[1].getName());
    adjacencyMatrix.addEdge(ingredients[3].getName(), recipes[1].getName());
    adjacencyMatrix.addEdge(ingredients[4].getName(), recipes[1].getName());
}

int main() {
    vector<Recipe> recipes;
    vector<Ingredient> ingredients;
    Matrix adjacencyMatrix;
    
    insertDummy(ingredients, recipes);

    insertDummyMatrix(ingredients, recipes, adjacencyMatrix);

    adjacencyMatrix.displayMatrix();
    cout << endl;
    adjacencyMatrix.displayList();

    return 0;
}
