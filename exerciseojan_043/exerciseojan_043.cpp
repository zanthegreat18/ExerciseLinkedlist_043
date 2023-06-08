#include <iostream>
#include <string>
using namespace std;

class Node {
public:
    int rollNumber;
    string name;
    Node* next;
};

class CircularLinkedList {
private:
    Node* LAST;

public:
    CircularLinkedList() {
        LAST = NULL;
    }

    void addNode();
    bool search(int rollno, Node** previous, Node** current);
    bool listEmpty();
    bool delNode();
    void traverse();
};

void CircularLinkedList::addNode() {
    int rollno;
    string name;
    cout << "\nEnter roll number: ";
    cin >> rollno;
    cout << "Enter name: ";
    cin >> name;

    Node* new_node = new Node();
    new_node->rollNumber = rollno;
    new_node->name = name;

    if (LAST == NULL) {
        // Menambahkan node pertama pada list
        new_node->next = new_node;
        LAST = new_node;
    }
    else {
        // Menambahkan sebuah node pada bagian pertama sebuah list
        new_node->next = LAST->next;
        LAST->next = new_node;
    }
}

bool CircularLinkedList::search(int rollno, Node** previous, Node** current) {
    *previous = LAST->next;
    *current = LAST->next;

    while (*current != LAST) {
        if (rollno == (*current)->rollNumber) {
            return true;
        }
        *previous = *current;
        *current = (*current)->next;
    }

    if (rollno == LAST->rollNumber) {
        return true;
    }
    else {
        return false;
    }
}

bool CircularLinkedList::listEmpty() {
    return LAST == NULL;
}

bool CircularLinkedList::delNode() {
    if (listEmpty()) {
        cout << "\nList is empty\n";
        return false;
    }

    int rollno;
    cout << "\nEnter the roll number of the node to be deleted: ";
    cin >> rollno;

    Node* previous = NULL;
    Node* current = NULL;
    bool found = search(rollno, &previous, &current);

    if (found) {
        if (current == LAST) {
            // Menghapus sebuah node pada list
            if (current->next == current) {
                // Jika sebuah node dalam list adalah satu satunya node dalam list
                LAST = NULL;
                delete current;
                return true;
            }

            LAST->next = current->next;
            LAST = previous;
        }
        else {
            // Menghapus node lain dalam list
            previous->next = current->next;
        }

        delete current;
        return true;
    }
    else {
        cout << "Node not found\n";
        return false;
    }
}

void CircularLinkedList::traverse() {
    if (listEmpty()) {
        cout << "\nList is empty\n";
    }
    else {
        cout << "\nRecords in the list are:\n";
        Node* currentNode = LAST->next;

        do {
            cout << currentNode->rollNumber << " " << currentNode->name << endl;
            currentNode = currentNode->next;
        } while (currentNode != LAST);

        cout << LAST->rollNumber << " " << LAST->name << endl;
    }
}

int main() {
    CircularLinkedList obj;

    while (true) {
        try {
            cout << "\nMenu" << endl;
            cout << "1. Add a record to the list" << endl;
            cout << "2. Delete a record from the list" << endl;
            cout << "3. View all the records in the list" << endl;
            cout << "4. Exit" << endl;
            cout << "\nEnter your choice (1-5): ";
            char ch;
            cin >> ch;
            switch (ch) {
            case '1': {
                obj.addNode();
                break;
            }
            case '2': {
                obj.delNode();
                break;
            }
            case '3': {
                obj.traverse();
                break;
            }
            case '4': {
                return 0;
            }
            default: {
                cout << "Invalid option" << endl;
                break;
            }
            }
        }
        catch (exception& e) {
            cout << e.what() << endl;
        }
    }
    return 0;
}