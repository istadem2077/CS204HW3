/*
 * Name-Surname-ID: Ismayil Taghi-Zada 00033582
 */

#include "TabsDLL.h"
#include <iostream>


//Private
void TabsDLL::insSorted(TabNode *node) {
    TabNode* prev = nullptr;
    TabNode* current = root;

    while (current && (current->count_of_open_pages < node->count_of_open_pages ||
                      (current->count_of_open_pages == node->count_of_open_pages && current->tab_id < node->tab_id))) {
        prev = current;
        current = current->next;
    }

    node->prev = prev;
    node->next = current;

    if (!prev) {
        root= node;
        tail = (tail == nullptr) ? node : tail;
    } else {
        prev->next = node;
    }

    if (current) {
        current->prev = node;
    } else {
        tail = node;
    }

    getTail(root);
}

void TabsDLL::unlink(TabNode *node) {
    if (!root) {
        return;
    }

    if (root->tab_id == node->tab_id) {
        root = root->next;
        if (root) root->prev = nullptr;
    }
    else if (tail == node) {
        tail = tail->prev;
        if (tail) tail->next = nullptr;
    } else {
        if (node->prev) node->prev->next = node->next;
        if (node->next) node->next->prev = node->prev;
    }
    if (!root) tail = nullptr;
}

void TabsDLL::getTail(TabNode* node) {
    if (!root) {
        tail = nullptr;
        return;
    }
    while (node->next) {
        node = node->next;
    }
    tail = node;
    tail->next = nullptr;
}

void TabsDLL::delList(TabNode *node) {
    if (!node) return;
    delList(node->next);
    delete node;
}

// end Private



// Public
bool TabsDLL::tabExists(int tab_id) {
    TabNode *current = root;

    while (current && current->tab_id != tab_id) {
        current = current->next;
    }

    if (current) {
        return true;
    }

    return false;
}

string TabsDLL::newTab(int tab_id, const string &page) {
    TabNode *temp = new TabNode(tab_id);
    temp->page_stack = DynPageStack();
    temp->page_stack.push(page);
    insSorted(temp);
    return page;
}

string TabsDLL::update(int tab_id, const string &page) {
    TabNode *current = root;
    while (current && current->tab_id != tab_id) {
        current = current->next;
    }
    current->page_stack.push(page);
    current->count_of_open_pages += 1;
    unlink(current);
    insSorted(current);
    return page;
}

void TabsDLL::backTab(int tab_id) {
    TabNode *current = root;
    while (current && current->tab_id != tab_id) {
        current = current->next;
    }
    if (current) {
        cout << "Removing from tab with ID: " << tab_id << endl;
        string poppedPage; // to be displayed
        current->page_stack.pop(poppedPage);
        current->count_of_open_pages -= 1;
        if (current->count_of_open_pages > 0) {
            cout << "Removed page: " << poppedPage << ". Remaining number of pages: " << current->count_of_open_pages << endl;
            unlink(current);
            insSorted(current);
        } else {
            cout << "Removed page: " << poppedPage << ". Stack is now empty. Deleting tab." << endl;
            unlink(current);
            delete current;
        }
    }
    else {
        cout << "Error: Tab " << tab_id << " not found." << endl;
    }
}

void TabsDLL::closeTab(int tab_id) {
    TabNode *current = root;

    while (current && current->tab_id != tab_id) {
        current = current->next;
    }
    if (current) {
        cout << "Closing tab " << tab_id << " and removing all pages:" << endl;
        string poppedPage;
        while (current->page_stack.pop(poppedPage)) {
            cout << "Removed page: " << poppedPage << endl;
        }
        unlink(current);
        delete current;
        getTail(root);
    }
    else {
        cout << "Error: Tab " << tab_id << " not found." << endl;
    }
}

void TabsDLL::display() {
    cout << "Displaying tabs from head to tail:" << endl;
    TabNode *current = root;
    while (current) {
        cout << "Tab " << current->tab_id << " has " << current->count_of_open_pages << " pages open."<< endl;
        current = current->next;
    }

    cout << "Displaying tabs from tail to head:" << endl;
    current = tail;
    while (current) {
        cout << "Tab " << current->tab_id << " has " << current->count_of_open_pages << " pages open."<< endl;
        current = current->prev;
    }
}

void TabsDLL::quitAndDisplay() {
    cout << "Closing all tabs:" << endl;
    TabNode *current = root;
    while (current) {
        cout << "Closing tab " << current->tab_id << " and removing all pages: " << endl;
        string poppedPage;
        while (current->page_stack.pop(poppedPage)) {
            cout << "Removed page: " << poppedPage << endl;
        }
        TabNode *next = current->next;
        delete current;
        current = next;
    }
    root = nullptr;
}

TabsDLL::~TabsDLL() {
    delList(root);
}


// end Public


