
#include <iostream>
#include <string>
#include <stack>
using namespace std;

class FarmerMarketplace {
private:
    struct Product {
        string name;
        int quantity;
        float price;
    };

    // Arrays to hold products
    Product products[100];
    int productCount;  // To keep track of the number of products added

    // Stack to handle undo (added and removed products)
    stack<Product> undoStack;

public:
    FarmerMarketplace() : productCount(0) {}

    // Add a new product to the store
    void addProduct(const string& name, int quantity, float price) {
        if (productCount >= 100) {
            cout << "Store is full. Cannot add more products.\n";
            return;
        }
        products[productCount] = {name, quantity, price};
        productCount++;
        cout << "Product added successfully: " << name << endl;
    }

    // Remove a product from the store
    void removeProduct(const string& name) {
        bool found = false;
        for (int i = 0; i < productCount; i++) {
            if (products[i].name == name) {
                // Push the product onto the undo stack before removing
                undoStack.push(products[i]);

                // Shift remaining products to remove the selected product
                for (int j = i; j < productCount - 1; j++) {
                    products[j] = products[j + 1];
                }
                productCount--;
                found = true;
                cout << "Product removed successfully: " << name << endl;
                break;
            }
        }
        if (!found) {
            cout << "Product not found.\n";
        }
    }

    // Undo the last action (either add or remove a product)
    void undoLastAction() {
        if (undoStack.empty()) {
            cout << "Nothing to undo.\n";
            return;
        }

        Product lastActionProduct = undoStack.top();
        undoStack.pop();
        // Push the product back if it was removed
        addProduct(lastActionProduct.name, lastActionProduct.quantity, lastActionProduct.price);
        cout << "Undo successful: " << lastActionProduct.name << " has been restored.\n";
    }

    // Display all products in the store
    void displayProducts() const {
        if (productCount == 0) {
            cout << "No products available in the store.\n";
            return;
        }
        cout << "Product List: \n";
        for (int i = 0; i < productCount; i++) {
            cout << "Product Name: " << products[i].name
                 << "\nQuantity: " << products[i].quantity
                 << "\nPrice: " << products[i].price
                 << "\n----------------------------" << endl;
        }
    }
};

int main() {
    FarmerMarketplace marketplace;
    int choice;
    string name;
    int quantity;
    float price;

    do {
        cout << "\nFarmer Marketplace Menu:\n";
        cout << "1. Add Product\n";
        cout << "2. Remove Product\n";
        cout << "3. Display Products\n";
        cout << "4. Undo Last Action\n";
        cout << "5. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                cout << "Enter Product Name: ";
                cin.ignore();  // to ignore the leftover newline character from previous input
                getline(cin, name);
                cout << "Enter Quantity: ";
                cin >> quantity;
                cout << "Enter Price: ";
                cin >> price;
                marketplace.addProduct(name, quantity, price);
                break;
            case 2:
                cout << "Enter Product Name to Remove: ";
                cin.ignore();
                getline(cin, name);
                marketplace.removeProduct(name);
                break;
            case 3:
                marketplace.displayProducts();
                break;
            case 4:
                marketplace.undoLastAction();
                break;
            case 5:
                cout << "Exiting program...\n";
                break;
            default:
                cout << "Invalid choice. Please try again.\n";
        }
    } while (choice != 5);

    return 0;
}
