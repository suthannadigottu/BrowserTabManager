#include<iostream>
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
    Tab() 
    {
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
       void closeCurrentTab(); 
       void showAllTabs();  
       void switchToTab(int tabNumber); 
       void visitPage(const string& url);
       void goBack();
       void goForward();
       void showCurrentPage() const;
       void showHistory();
};

void Tab::visitPage(const string& url) 
{
    if (!currentPage.empty()) backStack.push(currentPage);
    while (!forwardStack.empty()) forwardStack.pop(); 
    currentPage = url;
    history.push_back(url);
    string command = "start " + url;
    system(command.c_str());
    cout << "Visited: " << url << endl;
}

void Tab::goBack() 
{
    if (!backStack.empty()) 
    {
        forwardStack.push(currentPage);
        currentPage = backStack.top();
        backStack.pop();
        cout << "Went back to: " << currentPage << endl;
    } else 
    {
        cout << "No page to go back to.\n";
    }
}

void Tab::goForward()
 {
    if (!forwardStack.empty()) 
    {
        backStack.push(currentPage);
        currentPage = forwardStack.top();
        forwardStack.pop();
        cout << "Went forward to: " << currentPage << endl;
    } else 
    {
        cout << "No page to go forward to.\n";
    }
}

void Tab::showCurrentPage() const 
{
    cout << "Current Page: " << currentPage << endl;
}

void Tab::showHistory()
{
    cout << "\n   Browsing History   \n";
    for (const auto& page : history) 
    {
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

void Browser::closeCurrentTab()
{
    if(current==NULL)
    {
        cout<<"no tab to close"<<endl;
        return;
    }

    tabNode*toDelete=current;

    if(current->prev) current->prev->next=current->next;
    else head=current->next;

    if(current->next) current->next->prev=current->prev;

    if(current->next) current=current->next;
    else current=current->prev;

    delete toDelete->tab;
    delete toDelete;
}

void Browser::showAllTabs()
{
    tabNode*temp=head;
    int idx=1;

    cout<<"  Tabs  \n";

    while(temp)
    {
        cout<<idx<<(temp==current?"[current]":" ")<<endl;

        temp=temp->next;
        idx++;
    }
}
void Browser::switchToTab(int tabNumber)
{
  if(tabNumber<=0||tabNumber>tabCount)
  {
    cout<<"Invalid tab number \n";
    return;
  }

  tabNode*temp=head;
  int idx=1;
  while(temp&&idx!=tabNumber)
  {
    temp=temp->next;
    idx++;
  }
  current=temp;
  cout<<"Switched to tab number: "<<tabNumber<<endl;
}

void Browser::visitPage(const string &url)
{
    if(current) current->tab->visitPage(url);
}

void Browser::goBack()
{
    if(current) current->tab->goBack();
}

void Browser::goForward()
{
    if(current) current->tab->goForward();
}

void Browser::showCurrentPage()
{
    if(current) current->tab->showCurrentPage();
} 

void Browser::showHistory()
{
    if(current) current->tab->showHistory();
}

int main() 
{
    
    int choice,tabNumber;
    string url;
    Browser browser;


    do {
        cout << "\n   Browser Menu   \n";
        cout << "1. Visit new page\n";
        cout<<"2. Go back\n";
        cout<<"3. Go forward\n";
        cout<<"4. Show current page\n";
        cout<<"5. Exit\n6. Show History\n";
        cout<<"7. Open New Tab\n";
        cout<<"8. Close the current\n";
        cout<<"9. Show all tabs\n";
        cout<<"10. Switch to tab \n";
        cout << "Enter choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                cout << "Enter URL: ";
                cin >> url;
                browser.visitPage(url);
                break;
            case 2:
                browser.goBack();
                break;
            case 3:
                browser.goForward();
                break;
            case 4:
                browser.showCurrentPage();
                break;
            case 5:
                cout << "Exiting...\n";
                break;
            case 6:
                browser.showHistory();
                break; 
            case 7:
                browser.openNewTab();
                break;
            case 8:
                browser.closeCurrentTab();
                break;
            case 9:
                browser.showAllTabs();
                break;  
            case 10:
                cout<<"Enter tab number: ";
                cin>>tabNumber;
                browser.switchToTab(tabNumber);
                break;                 
            default:
                cout << "Invalid choice.\n";
        }
    } while (choice != 5);

    return 0;
}


