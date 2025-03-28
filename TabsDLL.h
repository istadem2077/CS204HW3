#include "DynPageStack.h"

#ifndef TABSDLL_H
#define TABSDLL_H

struct TabNode
{
    int tab_id;
    DynPageStack page_stack;
    int count_of_open_pages;
    TabNode* next;
    TabNode* prev;

    TabNode(int tab_id, int page_count = 1) : tab_id(tab_id), count_of_open_pages(page_count), next(nullptr), prev(nullptr) {}
};

class TabsDLL {
    private:
        TabNode* root;
        TabNode* tail;

        // Sorted insertion, used in newTab, update, backTab.
        void insSorted(TabNode* node);
        void unlink(TabNode *node);
        void getTail(TabNode* node);
        void getTail();
        void delList(TabNode* node);
    public:
    TabsDLL() : root(nullptr), tail(nullptr) {};
    ~TabsDLL();

    bool tabExists(int tab_id);
    string newTab(int tab_id, const string& page);
    string update(int tab_id, const string& page);
    void backTab(int tab_id);
    void closeTab(int tab_id);
    void display();
    void quitAndDisplay();
};


#endif //TABSDLL_H
