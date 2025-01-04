
#include <iostream>
#include <map>
#include <string>
using namespace std;

class FarmDataManagement {
private:
    struct Farm {
        string name;
        string soilQuality;
        string cropType;
        float yieldHistory;  // Yield in tons
        string location;
        float size;         // Size in hectares
        string farmerName;
    };

    map<int, Farm> farmTable;  // Store farms using unique farm ID

public:
    void addFarm(int id, const string& name, const string& soilQuality, const string& cropType,
                 float yieldHistory, const string& location, float size, const string& farmerName) {
        Farm newFarm = {name, soilQuality, cropType, yieldHistory, location, size, farmerName};
        farmTable[id] = newFarm;
        cout << "Farm added successfully: " << name << endl;
    }

    void displayFarms() const {
        if (farmTable.empty()) {
            cout << "No farms available." << endl;
            return;
        }
        for (map<int, Farm>::const_iterator it = farmTable.begin(); it != farmTable.end(); ++it) {
            cout << "ID: " << it->first
                 << "\nName: " << it->second.name
                 << "\nSoil Quality: " << it->second.soilQuality
                 << "\nCrop Type: " << it->second.cropType
                 << "\nYield History: " << it->second.yieldHistory << " tons"
                 << "\nLocation: " << it->second.location
                 << "\nSize: " << it->second.size << " hectares"
                 << "\nFarmer Name: " << it->second.farmerName << endl;
            cout << "---------------------------------------" << endl;
        }
    }

    void searchFarm(int id) const {
        map<int, Farm>::const_iterator it = farmTable.find(id);
        if (it != farmTable.end()) {
            cout << "Farm Found: ID " << it->first
                 << "\nName: " << it->second.name
                 << "\nSoil Quality: " << it->second.soilQuality
                 << "\nCrop Type: " << it->second.cropType
                 << "\nYield History: " << it->second.yieldHistory << " tons"
                 << "\nLocation: " << it->second.location
                 << "\nSize: " << it->second.size << " hectares"
                 << "\nFarmer Name: " << it->second.farmerName << endl;
        } else {
            cout << "Farm not found with ID: " << id << endl;
        }
    }

    void deleteFarm(int id) {
        map<int, Farm>::iterator it = farmTable.find(id);
        if (it != farmTable.end()) {
            cout << "Farm deleted successfully: " << it->second.name << endl;
            farmTable.erase(it);
        } else {
            cout << "Farm not found with ID: " << id << endl;
        }
    }
};

int main() {
    FarmDataManagement manager;
    int choice, id;
    string name, soilQuality, cropType, location, farmerName;
    float yieldHistory, size;

    do {
        cout << "\nFarm Data Management Menu:\n";
        cout << "1. Add Farm\n";
        cout << "2. Display Farms\n";
        cout << "3. Search Farm by ID\n";
        cout << "4. Delete Farm by ID\n";
        cout << "5. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                cout << "Enter Farm ID: ";
                cin >> id;
                cin.ignore();  // To ignore the newline character left by `cin`
                cout << "Enter Farm Name: ";
                getline(cin, name);
                cout << "Enter Soil Quality: ";
                getline(cin, soilQuality);
                cout << "Enter Crop Type: ";
                getline(cin, cropType);
                cout << "Enter Yield History (in tons): ";
                cin >> yieldHistory;
                cin.ignore();
                cout << "Enter Location: ";
                getline(cin, location);
                cout << "Enter Farm Size (in hectares): ";
                cin >> size;
                cin.ignore();
                cout << "Enter Farmer's Name: ";
                getline(cin, farmerName);
                manager.addFarm(id, name, soilQuality, cropType, yieldHistory, location, size, farmerName);
                break;
            case 2:
                manager.displayFarms();
                break;
            case 3:
                cout << "Enter Farm ID to search: ";
                cin >> id;
                manager.searchFarm(id);
                break;
            case 4:
                cout << "Enter Farm ID to delete: ";
                cin >> id;
                manager.deleteFarm(id);
                break;
            case 5:
                cout << "Exiting program..." << endl;
                break;
            default:
                cout << "Invalid choice. Please try again.\n";
        }
    } while (choice != 5);

    return 0;
}
