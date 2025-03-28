#include <string>

using namespace std;

class DynPageStack 
{
private:
    struct PageNode 
    {
        string page;
        PageNode* next;
        PageNode(const string& p, PageNode* n = nullptr) : page(p), next(n) {}
    };
    PageNode* top;

public:
    DynPageStack();
    void push(const string& page);
    bool pop(string& poppedPage);
    bool isEmpty();
};