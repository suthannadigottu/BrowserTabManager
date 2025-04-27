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
            