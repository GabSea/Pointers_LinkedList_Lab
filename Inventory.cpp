#include "Inventory.h"
#include <iostream>
#include <algorithm>

// Constructor
Inventory::Inventory() {
    // Vector is automatically initialized as empty
}

// Destructor - Important! Clean up dynamically allocated memory
Inventory::~Inventory() {
    // Delete all Book objects to prevent memory leaks
    Node* current = head;

    while (current != nullptr) {
        Node* temp = current->next;
        delete current;
        current = temp;
    }
}

// Add a book to the inventory (sorted by title alphabetically)
// THIS WAS LIKE THE WORST PART LOL
// but it works!!!!!!!!!!!
void Inventory::addBook(Book* bookPtr) {
    if (bookPtr == nullptr) {
        std::cout << "Error: Cannot add null book pointer.\n";
        return;
    }

    Node* new_node = new Node(bookPtr);

    // empty and we start a head
    if (head == nullptr) {
        head = new_node;
    }
    // theres already a head
    else {
        std::string
            title_to_compare = head->data->getTitle(),
            comparison = new_node->data->getTitle();

        // if this book happens to usurp the head
        if (comparison < title_to_compare) {
            // temp for taking a spot
            Node* temp = head;
            head = new_node;
            head->next = temp;
        }
        // otherwise we dig deeper
        else {
            Node* previous = head;
            Node* to_compare = head->next;
            if (to_compare != nullptr) {
                title_to_compare = to_compare->data->getTitle();
            }
            bool at_end = false, compare = (comparison < title_to_compare);

            if (to_compare != nullptr) {
                while (!compare && at_end == false) {
                    // if still nothing, start iterating thru the whoel thing
                    if (to_compare->next != nullptr) {
                        previous = to_compare;
                        to_compare = to_compare->next;
                        title_to_compare = to_compare->data->getTitle();
                        compare = (comparison < title_to_compare);
                    } else {
                        // just saves it from going any further and lets me know if it just goes in the back
                        at_end = true;
                    }

                }
            } else {
                at_end = true;
                to_compare = head;
            }


            if (at_end == false) {
                // temp for taking a spot
                Node* temp = to_compare;
                previous->next = new_node;
                new_node->next = temp;
            } else {
                // no temp needed if it just goes at the end
                to_compare->next = new_node;
            }

        }
    }

    std::cout << "Book '" << new_node->data->getTitle() << "' added to inventory.\n";
}

// Display all books in the inventory
void Inventory::displayAll() const {
    if (head == nullptr) {
        std::cout << "No books in inventory.\n";
        return;
    }

    std::cout << "\n=== INVENTORY CONTENTS ===\n";
    std::cout << "Total books: " << count() << "\n\n";
    
    for (size_t i = 0; i < count(); ++i) {
        std::cout << "Book #" << (i + 1) << ":\n";
        seek(i)->data->displayInfo();
    }
    std::cout << "\n";
}

// Remove a book by title
void Inventory::removeBook(const std::string& title) {
    Node* pick = search_before(title);

    if (pick != nullptr) {
        std::cout << "Removing book: " << pick->next->data->getTitle() << "\n";

        Node* temp = pick->next->next;

        delete pick->next->data;
        delete pick->next;

        pick->next = temp;

    } else {
        std::cout << "Book '" << title << "' not found in inventory.\n";
    }
}

// Get the number of books
size_t Inventory::getBookCount() const {
    return count();
}

// Search for a book by title
Book* Inventory::findBook(const std::string& title) const {

    Node* found = search(title);

    if (found != nullptr) {
        return found->data;
    }

    return nullptr;
}

// Check if inventory is empty
bool Inventory::isEmpty() const {
    return (head == nullptr);
}

Inventory::Node* Inventory::search(const std::string& title) const {
    Node* current = head;

    while (current != nullptr) {
        if (current->data->getTitle() == title) {
            return current;
        }
        current = current->next;
    }

    return nullptr;
}

Inventory::Node* Inventory::search_before(const std::string& title) const {
    Node* current = head;
    Node* previous = head;

    while (current != nullptr) {
        if (current->data->getTitle() == title) {
            return previous;
        }
        previous = current;
        current = current->next;
    }

    return nullptr;
}


int Inventory::count() const {
    Node* current = head;
    int total = 0;

    while (current != nullptr) {
        total++;
        current = current->next;
    }

    return total;
}

Inventory::Node *Inventory::seek(int index) const {
    Node* current = head;

    for (int i = 0; i < index; i++) {
        if (current->next != nullptr) {
            current = current->next;
        } else {
            std::cout << "!!--Seek() range higher than list ammount. returning last in list--!!" << std::endl;
            return current;
        }
    }

    return current;
}
