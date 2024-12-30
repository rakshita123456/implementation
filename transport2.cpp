#include <iostream>
#include <string>
using namespace std;

// Constants
const int MAX_PRODUCTS = 100; // Maximum number of products
const int MAX_STACK = 50;     // Maximum stack size for operation history

// Structure to represent a Product
struct Product {
    string name;
    int quantity;
    double price;

    // Constructor for easy initialization
    Product(string n = "", int q = 0, double p = 0.0)
        : name(n), quantity(q), price(p) {}
};

// Structure to represent an operation for undo
struct Operation {
    string type;       // "ADD" or "DELETE"
    Product product;   // Product involved in the operation
};

// Farmer Marketplace Class
class FarmerMarketplace {
private:
    Product products[MAX_PRODUCTS]; // Array to store products
    int productCount;               // Current number of products

    Operation operationStack[MAX_STACK]; // Stack for operation history
    int top;                             // Top of the stack

public:
    // Constructor
    FarmerMarketplace() : productCount(0), top(-1) {}

    // Add a product to the marketplace
    void addProduct(const string& name, int quantity, double price) {
        if (productCount >= MAX_PRODUCTS) {
            cout << "Error: Marketplace is full.\n";
            return;
        }

        products[productCount++] = Product(name, quantity, price);
        pushOperation("ADD", Product(name, quantity, price));
        cout << "Product added successfully: " << name << "\n";
    }

    // Remove a product by name
    void removeProduct(const string& name) {
        int index = -1;
        for (int i = 0; i < productCount; ++i) {
            if (products[i].name == name) {
                index = i;
                break;
            }
        }

        if (index == -1) {
            cout << "Error: Product not found.\n";
            return;
        }

        pushOperation("DELETE", products[index]);

        // Shift products to remove the one at index
        for (int i = index; i < productCount - 1; ++i) {
            products[i] = products[i + 1];
        }
        productCount--;

        cout << "Product removed successfully: " << name << "\n";
    }

    // Display all products
    void displayProducts() {
        if (productCount == 0) {
            cout << "No products available.\n";
            return;
        }

        cout << "Marketplace Products:\n";
        for (int i = 0; i < productCount; ++i) {
            cout << "  " << i + 1 << ". Name: " << products[i].name
                 << ", Quantity: " << products[i].quantity
                 << ", Price: $" << products[i].price << "\n";
        }
    }

    // Undo the last operation
    void undoLastOperation() {
        if (top == -1) {
            cout << "No operations to undo.\n";
            return;
        }

        Operation lastOp = operationStack[top--];

        if (lastOp.type == "ADD") {
            // Undo ADD: Remove the last added product
            for (int i = productCount - 1; i >= 0; --i) {
                if (products[i].name == lastOp.product.name) {
                    for (int j = i; j < productCount - 1; ++j) {
                        products[j] = products[j + 1];
                    }
                    productCount--;
                    break;
                }
            }
            cout << "Undo: Added product removed (" << lastOp.product.name << ")\n";
        } else if (lastOp.type == "DELETE") {
            // Undo DELETE: Re-add the deleted product
            if (productCount < MAX_PRODUCTS) {
                products[productCount++] = lastOp.product;
                cout << "Undo: Deleted product restored (" << lastOp.product.name << ")\n";
            } else {
                cout << "Error: Cannot undo delete, marketplace is full.\n";
            }
        }
    }

private:
    // Push an operation onto the stack
    void pushOperation(const string& type, const Product& product) {
        if (top >= MAX_STACK - 1) {
            cout << "Warning: Operation stack is full, cannot track further undo operations.\n";
            return;
        }
        operationStack[++top] = {type, product};
    }
};

// Main function
int main() {
    FarmerMarketplace marketplace;

    // Adding products
    marketplace.addProduct("Wheat", 100, 20.5);
    marketplace.addProduct("Rice", 200, 15.0);
    marketplace.addProduct("Corn", 150, 10.0);

    // Display products
    marketplace.displayProducts();

    // Remove a product
    marketplace.removeProduct("Rice");
    marketplace.displayProducts();

    // Undo last operation
    marketplace.undoLastOperation();
    marketplace.displayProducts();

    // Undo another operation
    marketplace.undoLastOperation();
    marketplace.displayProducts();

    return 0;
}
