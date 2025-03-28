#include "DynPageStack.h"

DynPageStack::DynPageStack() : top(nullptr) {}

void DynPageStack::push(const string& page) 
{
    top = new PageNode(page, top);
}

bool DynPageStack::pop(string& poppedPage) 
{
    if (isEmpty()) 
    {
        return false;
    }
    PageNode* temp = top;
    poppedPage = temp->page;
    top = top->next;
    delete temp;
    return true;
}

bool DynPageStack::isEmpty()  
{
	if (top == nullptr) 
    {
		return true;
	}
	return false;
}
