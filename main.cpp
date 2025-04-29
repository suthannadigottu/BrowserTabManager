#include<iostream>
#include <stack>
#include <string>
using namespace std;

class Tab {
private:
    string currentPage;
    stack<string> backStack;
    stack<string> forwardStack;

public:
    Tab() {
        currentPage = "home";
    }

    void visitPage(const string& url) {
        if (!currentPage.empty()) backStack.push(currentPage);
        while (!forwardStack.empty()) forwardStack.pop(); // clear forward history
        currentPage = url;
        string command = "start " + url;
        system(command.c_str());
        cout << "Visited: " << url << endl;
    }

    void goBack() {
        if (!backStack.empty()) {
            forwardStack.push(currentPage);
            currentPage = backStack.top();
            backStack.pop();
            cout << "Went back to: " << currentPage << endl;
        } else {
            cout << "No page to go back to.\n";
        }
    }

    void goForward() {
        if (!forwardStack.empty()) {
            backStack.push(currentPage);
            currentPage = forwardStack.top();
            forwardStack.pop();
            cout << "Went forward to: " << currentPage << endl;
        } else {
            cout << "No page to go forward to.\n";
        }
    }

    void showCurrentPage() const {
        cout << "Current Page: " << currentPage << endl;
    }
};

int main() {
    Tab browserTab;
    int choice;
    string url;

    do {
        cout << "\n=== Browser Menu ===\n";
        cout << "1. Visit new page\n2. Go back\n3. Go forward\n4. Show current page\n5. Exit\n";
        cout << "Enter choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                cout << "Enter URL: ";
                cin >> url;
                browserTab.visitPage(url);
                break;
            case 2:
                browserTab.goBack();
                break;
            case 3:
                browserTab.goForward();
                break;
            case 4:
                browserTab.showCurrentPage();
                break;
            case 5:
                cout << "Exiting...\n";
                break;
            default:
                cout << "Invalid choice.\n";
        }
    } while (choice != 5);

    return 0;
}
[7:11 PM, 4/29/2025] Snehitha J: #include<iostream>
#include <stack>
#include <string>
#include<vector>
using namespace std;

class Tab {
private:
    string currentPage;
    stack<string> backStack;
    stack<string> forwardStack;
    vector<string> history;

public:
    Tab() {
        currentPage = "home";
    }

    void visitPage(const string& url);
    void goBack();
    void goForward();
    void showCurrentPage() const;
    void showHistory();

};

class tabNode{
    public:
        Tab* tab;
        tabNode*next;
        tabNode*prev;

        tabNode(Tab*t)
        {
            tab=t;
            next=NULL;
            prev=NULL;
        }
};


class Browser{
      private:
           tabNode*head;
           tabNode*current;
           int tabCount;
       public:
              Browser()
              {
                head=NULL;
                current=NULL;
                tabCount=0;
                openNewTab();
              } 
              
       void openNewTab();       
};
// Function definitions outside the class using scope resolution operator
void Tab::visitPage(const string& url) {
    if (!currentPage.empty()) backStack.push(currentPage);
    while (!forwardStack.empty()) forwardStack.pop(); // clear forward history
    currentPage = url;
    history.push_back(url);
    string command = "start " + url;
    system(command.c_str());
    cout << "Visited: " << url << endl;
}

void Tab::goBack() {
    if (!backStack.empty()) {
        forwardStack.push(currentPage);
        currentPage = backStack.top();
        backStack.pop();
        cout << "Went back to: " << currentPage << endl;
    } else {
        cout << "No page to go back to.\n";
    }
}

void Tab::goForward() {
    if (!forwardStack.empty()) {
        backStack.push(currentPage);
        currentPage = forwardStack.top();
        forwardStack.pop();
        cout << "Went forward to: " << currentPage << endl;
    } else {
        cout << "No page to go forward to.\n";
    }
}

void Tab::showCurrentPage() const {
    cout << "Current Page: " << currentPage << endl;
}

void Tab::showHistory()
{
    cout << "\n--- Browsing History ---\n";
    for (const auto& page : history) {
        cout << page << endl;
    }  
}
void Browser::openNewTab()
{
    Tab*newTab=new Tab();
    tabNode*newNode=new tabNode(newTab);
    if(head==NULL)
    {
        head=newNode;
    }

    else{
        tabNode*temp=head;
        while(temp->next!=NULL)
        {
            temp=temp->next;
        }

        temp->next=newNode;
        newNode->prev=temp;
    }
        current=newNode;
        tabCount++;
       
        cout<<"Opened a new Tab with tab count: "<<tabCount<<endl;
    
}

int main() {
    
    int choice;
    string url;
    Browser browserTab;


    do {
        cout << "\n=== Browser Menu ===\n";
        cout << "1. Visit new page\n2. Go back\n3. Go forward\n4. Show current page\n5. Exit\n6. Show History\n7. Open New Tab\n";
        cout << "Enter choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                cout << "Enter URL: ";
                cin >> url;
                browserTab.visitPage(url);
                break;
            case 2:
                browserTab.goBack();
                break;
            case 3:
                browserTab.goForward();
                break;
            case 4:
                browserTab.showCurrentPage();
                break;
            case 5:
                cout << "Exiting...\n";
                break;
            case 6:
                browserTab.showHistory();
                break; 
            case 7:
                browserTab.openNewTab();
                break;       
            default:
                cout << "Invalid choice.\n";
        }
    } while (choice != 5);

    return 0;
}


