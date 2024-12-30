#include <iostream>
#include <string>
using namespace std;

// Structure to represent farm data
struct Farm {
    string farmName;
    string soilQuality;
    string cropType;
    double yieldHistory;

    Farm(string name = "", string soil = "", string crop = "", double yield = 0.0)
        : farmName(name), soilQuality(soil), cropType(crop), yieldHistory(yield) {}
};

// HashTable Class
class HashTable {
private:
    static const int TABLE_SIZE = 10; // Size of the hash table
    Farm table[TABLE_SIZE];          // Array-based hash table
    bool isOccupied[TABLE_SIZE];     // To track if a slot is occupied

    // Hash function to compute the index
    int hashFunction(const string& key) {
        int hash = 0;
        for (char c : key) {
            hash += c;
        }
        return hash % TABLE_SIZE;
    }

public:
    // Constructor to initialize the hash table
    HashTable() {
        for (int i = 0; i < TABLE_SIZE; ++i) {
            isOccupied[i] = false;
        }
    }

    // Insert farm data
    void insertFarm(const string& name, const string& soil, const string& crop, double yield) {
        int index = hashFunction(name);

        // Linear probing to handle collisions
        int originalIndex = index;
        while (isOccupied[index]) {
            if (table[index].farmName == name) {
                cout << "Error: Farm with the name '" << name << "' already exists.\n";
                return;
            }
            index = (index + 1) % TABLE_SIZE;
            if (index == originalIndex) {
                cout << "Error: Hash table is full.\n";
                return;
            }
        }

        table[index] = Farm(name, soil, crop, yield);
        isOccupied[index] = true;
        cout << "Farm added successfully: " << name << "\n";
    }

    // Search for farm data by name
    void searchFarm(const string& name) {
        int index = hashFunction(name);
        int originalIndex = index;

        // Linear probing to find the farm
        while (isOccupied[index]) {
            if (table[index].farmName == name) {
                cout << "Farm Found:\n";
                cout << "  Name: " << table[index].farmName
                     << ", Soil Quality: " << table[index].soilQuality
                     << ", Crop Type: " << table[index].cropType
                     << ", Yield History: " << table[index].yieldHistory << " tons\n";
                return;
            }
            index = (index + 1) % TABLE_SIZE;
            if (index == originalIndex) break;
        }

        cout << "Error: Farm with the name '" << name << "' not found.\n";
    }

    // Delete farm data by name
    void deleteFarm(const string& name) {
        int index = hashFunction(name);
        int originalIndex = index;

        // Linear probing to find the farm
        while (isOccupied[index]) {
            if (table[index].farmName == name) {
                isOccupied[index] = false;
                cout << "Farm deleted successfully: " << name << "\n";
                return;
            }
            index = (index + 1) % TABLE_SIZE;
            if (index == originalIndex) break;
        }

        cout << "Error: Farm with the name '" << name << "' not found.\n";
    }

    // Display all farms in the hash table
    void displayFarms() {
        cout << "Farm Data:\n";
        for (int i = 0; i < TABLE_SIZE; ++i) {
            if (isOccupied[i]) {
                cout << "  Slot " << i << ": "
                     << "Name: " << table[i].farmName
                     << ", Soil Quality: " << table[i].soilQuality
                     << ", Crop Type: " << table[i].cropType
                     << ", Yield History: " << table[i].yieldHistory << " tons\n";
            } else {
                cout << "  Slot " << i << ": Empty\n";
            }
        }
    }
};

// Main Function
int main() {
    HashTable farmData;

    // Adding farms
    farmData.insertFarm("Farm1", "Loamy", "Wheat", 30.5);
    farmData.insertFarm("Farm2", "Clay", "Rice", 45.2);
    farmData.insertFarm("Farm3", "Sandy", "Corn", 25.8);

    // Display farms
    farmData.displayFarms();

    // Search for a specific farm
    cout << "\nSearching for 'Farm2':\n";
    farmData.searchFarm("Farm2");

    // Delete a farm
    cout << "\nDeleting 'Farm1':\n";
    farmData.deleteFarm("Farm1");

    // Display farms after deletion
    cout << "\nFarms after deletion:\n";
    farmData.displayFarms();

    return 0;
}
