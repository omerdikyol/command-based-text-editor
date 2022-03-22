#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include "codeStack.h"
#include "LinkedList.h"

using namespace std;

void reverseStr(string& str)
{
    int n = str.length();
    for (int i = 0; i < n / 2; i++)
        swap(str[i], str[n - i - 1]);
}

string getFirstWord(string str)
{
    string word = "";
    istringstream ss(str);
    while(ss >> word)
        return word;

}

void deleteFirstWord(string& str)
{
    string first = getFirstWord(str);
    reverseStr(str);

    for(int i = 0;i < first.size()+1; i++)
        str = str.substr(0, str.size()-1);

    reverseStr(str);
}

void printText(LinkedList* list, int page)
{
    if(list)
    {
        int pageNum = page*10;
        int lineCount = 1;
        cout << "\nCurrent State(Unsaved): " << endl;
        cout << "---Page " << page << "---" << endl;
        for(Node* tmp = list->head; tmp != NULL; tmp = tmp->next)
        {
            if(pageNum - 10 < lineCount && lineCount <= pageNum)
                cout << lineCount << ")" << tmp->info << "\n";
            lineCount++;
        }
        cout << "---Page " << page << "---" << endl;

    }
}

LinkedList* open(string filename){
    fstream file;
    file.open(filename.c_str(),ios::in);
    LinkedList* textFile = new LinkedList();
    if(file.is_open())
    {
        string line;
        while(getline(file,line))
        {
            textFile->addToTail(line);
        }
    }
    file.close();

    return textFile;
}

void save(string filename, LinkedList* textFile)
{
    fstream file;
    file.open(filename,ios::out);
    string line;
    if(file.is_open())
    {
        while(!textFile->isEmpty())
        {
            file << textFile->deleteFromHead() << "\n";
        }
    }
    file.close();
}

void insert(int position, string text, LinkedList* textFile)
{
    int count = 1;
    int len = textFile->GetSize();

    if(position > len + 1)
    {
        for(int i = len;i < position-1;i++)
        {
            textFile->addToTail("");
        }
        textFile->addToTail(text);
    }
    else if(position == 1)
    {
        textFile->addToHead(text);
    }
    else
    {
        for(Node* prev = textFile->head; prev->next != NULL; prev = prev->next)
        {
            Node* curr = prev->next;
            if(count == position-1)
            {
                Node* newNode = new Node;
                newNode->info = text;
                newNode->next = curr;
                prev->next = newNode;
            }
            count++;
        }
    }
}

void moveLine(int n, int m, LinkedList* textFile)
{
    //cout << "It should move from " << n << "to " << m << endl;
    if(n <= textFile->GetSize() && m <= textFile->GetSize())
    {
        string info = textFile->GetAt(n);
        //cout << "String at line " << n << ":" << info << endl;
        textFile->deleteNode(info);
        insert(m,info,textFile);
    }
    else
    {
        cout << "Invalid Input. Please try again." << endl;
    }
}

void replaceWith(int n, string text, LinkedList* textFile)
{
    if(n <= textFile->GetSize())
    {
        string info = textFile->GetAt(n);
        //cout << "String at line " << n << ":" << info << endl;
        textFile->deleteNode(info);
        insert(n,text,textFile);
    }
}

LinkedList* deleteLine(int position, LinkedList* textFile)
{
    if(position <= textFile->GetSize())
        textFile->deleteNode(textFile->GetAt(position));
    else
        cout << "Invalid number. Try again." << endl;

    return textFile;
}

LinkedList* createCopyList(LinkedList *src){
    LinkedList *dest = new LinkedList();
    LinkedList *temp = new LinkedList();
    while(!src->isEmpty())
    {
        string curr = src->deleteFromHead();
        dest->addToTail(curr);
        temp->addToHead(curr);
    }
    while(!temp->isEmpty())
    {
        src->addToHead(temp->deleteFromHead());
    }
    return dest;
};

LinkedList* strToLinkedList(string src)
{
    LinkedList* dest = new LinkedList();
    while(src.size() > 0)
    {
        string word = getFirstWord(src);
        deleteFirstWord(src);
        dest->addToTail(word);
    }
    return dest;
}

string linkedListToStr(LinkedList* textFile)
{
    LinkedList* src = createCopyList(textFile);
    string dest = "";
    while(!src->isEmpty())
    {
        dest += src->deleteFromHead() + " ";
    }
    //cout << "Dest: " << dest << endl;
    return dest;
}

void stackFile(LinkedList* textFile, codeStack* st)
{
    string fileStr = linkedListToStr(textFile);
    st->pushToStack(fileStr.c_str());
}

int main()
{
    string textInput;
    string filename;
    string command;
    int page = 1;

    LinkedList* textFile = new LinkedList();
    codeStack* undoStack = new codeStack();

    while(true)
    {
        cout << "What would you like to do?: ";
        getline(cin, textInput);
        command = getFirstWord(textInput);
        deleteFirstWord(textInput);

        if(command == "open")                           // DONE
        {
            filename = getFirstWord(textInput);
            textFile = open(filename);
            undoStack = new codeStack();
        }
        else if(command == "save")                      // DONE
        {
            string newFilename = getFirstWord(textInput);
            save(newFilename,textFile);
        }
        else if(command == "insert")                    // DONE
        {
            stackFile(textFile,undoStack);
            string posStr = getFirstWord(textInput);
            stringstream ss;
            int pos;
            ss << posStr;
            ss >> pos;
            deleteFirstWord(textInput);
            string text = getFirstWord(textInput);
            deleteFirstWord(textInput);
            //cout << "Pos:" << pos << " Text:" << text << endl;
            insert(pos,text,textFile);
        }
        else if(command == "delete")                    // DONE
        {
            stackFile(textFile,undoStack);
            string posStr = getFirstWord(textInput);
            int pos;
            stringstream ss;
            ss << posStr;
            ss >> pos;
            if(pos <= textFile->GetSize())
                textFile = deleteLine(pos,textFile);
            else if (textFile->GetSize() == 0)
                cout << "Current LinkedList is empty.";
            else
                cout << "Invalid number. Try again.";
        }
        else if(command == "move")                      // DONE
        {
            stackFile(textFile,undoStack);
            string source = getFirstWord(textInput);
            deleteFirstWord(textInput);
            string dest = getFirstWord(textInput);
            deleteFirstWord(textInput);
            stringstream ss, ss2;
            int src, dst;
            ss << source;
            ss >> src;
            ss2 << dest;
            ss2 >> dst;
            //cout << "Src: " << src << " Dst: " << dst << endl;
            moveLine(src,dst,textFile);
        }
        else if(command == "replace")                   // DONE
        {
            stackFile(textFile,undoStack);
            string posStr = getFirstWord(textInput);
            deleteFirstWord(textInput);
            string newText = getFirstWord(textInput);
            deleteFirstWord(textInput);
            int pos;
            stringstream ss;
            ss << posStr;
            ss >> pos;

            replaceWith(pos,newText,textFile);
        }
        else if(command == "next")                      // DONE
        {
            if(page <= textFile->GetSize() / 10)
                page++;
            else
                cout << "There is no next page.";
        }
        else if(command == "prev")                      // DONE
        {
            if(page > 1)
                page--;
            else
                cout << "You are at the first page." << endl;
        }
        else if(command == "undo")
        {
            /*cout << "undo" << endl;
            cout << "Before Undo: ";
            textFile->printAll();*/
            if(!undoStack->isEmpty())
            {
                textFile = strToLinkedList(undoStack->popFromStack());
            }
            else
            {
                cout << "There are no commands to go back." << endl;
            }

            /*cout << "After Undo: ";
            textFile->printAll();*/
        }
        else
        {
            cout << "Invalid Command. Try again." << endl;
        }

        //cout << "Stack: ";
        //undoStack->printStack();

        //cout << "\nTextFile(unsaved): ";
        //textFile->printAll();

        printText(textFile,page);
        cout << endl;
    }
    return 0;
}
