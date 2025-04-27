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