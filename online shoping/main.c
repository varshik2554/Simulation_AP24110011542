#include <stdio.h>
#include <string.h>

#define MAX 20

// Product structure
struct Product {
    int id;
    char name[50];
    float price;
};

// Cart structure
struct CartItem {
    struct Product product;
    int quantity;
};

struct CartItem cart[MAX];
int cartCount = 0;

// Product List
struct Product products[] = {
    {1, "Laptop", 55000},
    {2, "Headphones", 1500},
    {3, "Keyboard", 800},
    {4, "Mouse", 500},
    {5, "Smartphone", 30000},
    {6, "Charger", 600}
};
int productCount = 6;


// Display available products
void displayProducts() {
    printf("\n--- Available Products ---\n");
    for (int i = 0; i < productCount; i++) {
        printf("%d. %s - ₹%.2f\n", products[i].id, products[i].name, products[i].price);
    }
}

// Add item to cart
void addToCart() {
    int id, qty;
    displayProducts();

    printf("\nEnter Product ID: ");
    scanf("%d", &id);

    printf("Enter quantity: ");
    scanf("%d", &qty);

    // Find product
    int found = -1;
    for (int i = 0; i < productCount; i++) {
        if (products[i].id == id) {
            found = i;
            break;
        }
    }

    if (found == -1) {
        printf("\nInvalid product ID!\n");
        return;
    }

    // Already in cart?
    for (int i = 0; i < cartCount; i++) {
        if (cart[i].product.id == id) {
            cart[i].quantity += qty;
            printf("\nQuantity updated in cart!\n");
            return;
        }
    }

    // Add new item
    cart[cartCount].product = products[found];
    cart[cartCount].quantity = qty;
    cartCount++;

    printf("\nItem added to cart!\n");
}

// Remove item from cart
void removeFromCart() {
    if (cartCount == 0) {
        printf("\nCart is empty!\n");
        return;
    }

    int id;
    printf("\nEnter Product ID to remove: ");
    scanf("%d", &id);

    int pos = -1;

    for (int i = 0; i < cartCount; i++) {
        if (cart[i].product.id == id) {
            pos = i;
            break;
        }
    }

    if (pos == -1) {
        printf("\nItem not found in cart!\n");
        return;
    }

    for (int i = pos; i < cartCount - 1; i++) {
        cart[i] = cart[i + 1];
    }

    cartCount--;
    printf("\nItem removed successfully!\n");
}

// View cart and return total
float viewCart() {
    if (cartCount == 0) {
        printf("\nCart is empty!\n");
        return 0;
    }

    printf("\n--- Your Cart ---\n");
    float total = 0;

    for (int i = 0; i < cartCount; i++) {
        float sub = cart[i].product.price * cart[i].quantity;
        printf("ID: %d | %s | Qty: %d | Price: ₹%.2f | Subtotal: ₹%.2f\n",
               cart[i].product.id,
               cart[i].product.name,
               cart[i].quantity,
               cart[i].product.price,
               sub);

        total += sub;
    }

    printf("\nCart Total = ₹%.2f\n", total);
    return total;
}

// (4) Search Product by name
void searchProduct() {
    char key[50];
    printf("\nEnter product name to search: ");
    scanf(" %[^\n]", key);

    int found = 0;

    printf("\nSearch Results:\n");

    for (int i = 0; i < productCount; i++) {
        if (strstr(products[i].name, key)) {
            printf("%d. %s - ₹%.2f\n",
                   products[i].id,
                   products[i].name,
                   products[i].price);
            found = 1;
        }
    }

    if (!found)
        printf("No matching product found.\n");
}

// (5) Checkout + Billing Summary (with GST)
void checkout() {
    if (cartCount == 0) {
        printf("\nYour cart is empty!\n");
        return;
    }

    float subtotal = viewCart();
    float gst = subtotal * 0.18;
    float grandTotal = subtotal + gst;

    printf("\n--- BILL SUMMARY ---\n");
    printf("Subtotal : ₹%.2f\n", subtotal);
    printf("GST 18%%  : ₹%.2f\n", gst);
    printf("Total    : ₹%.2f\n", grandTotal);

    printf("\nCheckout successful! Thank you for shopping.\n");

    cartCount = 0; // clear cart
}

int main() {
    int choice;

    while (1) {
        printf("\n======= ONLINE SHOPPING CART =======\n");
        printf("1. Add Item to Cart\n");
        printf("2. Remove Item\n");
        printf("3. View Cart\n");
        printf("4. Search Product\n");
        printf("5. Checkout\n");
        printf("6. Exit\n");
        printf("Enter choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1: addToCart(); break;
            case 2: removeFromCart(); break;
            case 3: viewCart(); break;
            case 4: searchProduct(); break;
            case 5: checkout(); break;
            case 6: return 0;
            default: printf("\nInvalid choice!\n");
        }
    }
}
