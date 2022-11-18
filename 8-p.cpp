#include <iostream>
#include <sstream>
#include <fstream>
#include <time.h>
#include <string>
#include <vector>
#include <cmath>  //add
using namespace std;
class searchTree{
private:
    struct puzzle {
        puzzle* child1;
        puzzle* child2;
        puzzle* child3;
        puzzle* child4;
        puzzle* parent;
        int* state;
        int g, h, f;
        int index;
    };
    vector <puzzle*> stack;
    vector <int> initial;
    puzzle* root;
    int itemNum;
    int length;
    bool success;
public:
    searchTree() {
        root = NULL;
    }
    bool isEmpty() const { return root == NULL; }
    bool makeMove(puzzle*, puzzle*, char);
    void checkSuccess(puzzle*);
    void build();
    void setRoot(vector <int>);
    void insert();
    void makePuzzle();
    void sortList();
    void setHvalue(puzzle*);
    void printPuzzle(puzzle*);
};

void searchTree::build() {
    makePuzzle();
    setRoot(initial);
    while(!success) {
        insert();
    }
}

bool searchTree::makeMove(puzzle* curr, puzzle* next, char dir) {
    int temp, index = curr->index;
    next->state = (int*) malloc(sizeof(int) * length*length);
    for(int i = 0; i < itemNum; i++)
        next->state[i] = curr->state[i];

    switch (dir) {
    case 'u':
        next->index = index - length;
        if(curr->parent != NULL)
            if(next->index == curr->parent->index)
                return false;
        temp = next->state[index];
        next->state[index] = next->state[index-length];
        next->state[index-length] = temp;
        curr->child1 = next;
        break;
    case 'd':
        next->index = index + length;
        if(curr->parent != NULL)
            if(next->index == curr->parent->index)
                return false;
        temp = next->state[index];
        next->state[index] = next->state[index+length];
        next->state[index+length] = temp;
        curr->child2 = next;
        break;
    case 'l':
        next->index = index - 1;
        if(curr->parent != NULL)
            if(next->index == curr->parent->index)
                return false;
        temp = next->state[index];
        next->state[index] = next->state[index-1];
        next->state[index-1] = temp;
        curr->child3 = next;
        break;
    case 'r':
        next->index = index + 1;
        if(curr->parent != NULL)
            if(next->index == curr->parent->index)
                return false;
        temp = next->state[index];
        next->state[index] = next->state[index+1];
        next->state[index+1] = temp;
        curr->child4 = next;
        break;
    }
    return true;
}

void searchTree::insert() {
    puzzle* curr = stack.front();
    stack.erase(stack.begin());
    puzzle* c1 = new puzzle;
    puzzle* c2 = new puzzle;
    puzzle* c3 = new puzzle;
    puzzle* c4 = new puzzle;
    if(curr->index / length != 0 && makeMove(curr, c1, 'u')) { 
        c1->g = curr->g + 1;
        setHvalue(c1);
        c1->f = c1->h + c1->g;
        c1->child1 = NULL; c1->child2 = NULL; c1->child3 = NULL; c1->child4 = NULL;
        c1->parent = curr;
        stack.push_back(c1);
    }

    if(curr->index / length != length - 1 && makeMove(curr, c2, 'd')) {
        c2->g = curr->g + 1;
        setHvalue(c2);
        c2->f = c2->h + c2->g;
        c2->child1 = NULL; c2->child2 = NULL; c2->child3 = NULL; c2->child4 = NULL;
        c2->parent = curr;
        stack.push_back(c2);
    }

    if(curr->index % length != 0 && makeMove(curr, c3, 'l')) {
        c3->g = curr->g + 1;
        setHvalue(c3);
        c3->f = c3->h + c3->g;
        c3->child1 = NULL; c3->child2 = NULL; c3->child3 = NULL; c3->child4 = NULL;
        c3->parent = curr;
        stack.push_back(c3);
    }
    if(curr->index % length != length - 1 && makeMove(curr, c4, 'r')) {
        c4->g = curr->g + 1;
        setHvalue(c4);
        c4->f = c4->h + c4->g;
        c4->child1 = NULL; c4->child2 = NULL; c4->child3 = NULL; c4->child4 = NULL;
        c4->parent = curr;
        stack.push_back(c4);
    }
    checkSuccess(curr);
    sortList();
}

void searchTree::setRoot(vector <int> initial) {
    puzzle* root_p = new puzzle;
    root_p->state = (int*) malloc(sizeof(int) * length*length);
    for (int i = 0; i < itemNum; i++) {
        root_p->state[i] = initial[i];
    }
    root_p->child1 = NULL;
    root_p->child2 = NULL;
    root_p->child3 = NULL;
    root_p->child4 = NULL;
    root_p->parent = NULL;
    root_p->g = 0;
    setHvalue(root_p);
    root_p->f = root_p->g + root_p->h;
    for(int i = 0; i < itemNum; i++) {
        if(root_p->state[i] == 0)
            root_p->index = i;
    }

    if(isEmpty()) {
        root = root_p;
        stack.push_back(root);
    }
}
void searchTree::checkSuccess(puzzle* curr) {
    bool c1 = true, c2 = true, c3 = true, c4 = true;

    if(curr->child1 != NULL) {
        for (int i = 0; i < itemNum; i++)
            if(curr->child1->state[i] != i) {
                c1 = false;
                break;
            }
            } else
                c1 = false;

            if(curr->child2 != NULL) { 
                for (int i = 0; i < itemNum; i++)
                    if(curr->child2->state[i] != i) {
                        c2 = false;
                        break;
                    }
            } else
                c2 = false;

            if(curr->child3 != NULL) {
                for(int i = 0; i < itemNum; i++)
                    if(curr->child3->state[i] != i) {
                    c3 = false;
                    break;
                }
            } else
                c3 = false;

            if(curr->child4 != NULL) {
                for(int i = 0; i < itemNum; i++)
                    if(curr->child4->state[i] != i) {
                        c4 = false;
                        break;
                    }
            } else
                    c4 = false;

            if(c1 == true) {
                printPuzzle(curr->child1);
                success = true;
            }else if(c2 == true) {
                printPuzzle(curr->child2);
                success = true;
            }else if(c3 == true) {
                printPuzzle(curr->child3);
                success = true;
            }else if(c4 == true) {
                printPuzzle(curr->child4);
                success = true;
            }
            if(success)
                while(!stack.empty())
                    stack.erase(stack.begin());
}
void searchTree::printPuzzle(puzzle* curr) {
    ofstream fout("result.txt");
    vector <puzzle*> v;

    while(curr != NULL) {
        v.push_back(curr);
        curr = curr->parent;
    }
    for(int j = v.size() - 1; j >= 0; j--) {
        for(int i = 0; i < itemNum; i++) {
        //fout << v[j]->state[i] << " ";
            cout << v[j]->state[i] << " ";
            if (i % length == length - 1)
            //fout << endl;
                cout << endl;
        }
    //fout << endl;
    cout << endl;
    }
    fout.close();
}
void searchTree::makePuzzle() {
    ifstream instream;
    string line, item;
    itemNum = 0;
    success = false;
/*
    instream.open("puzzle.txt");
    while(getline(instream, line)) {
        istringstream linestream(line);
        while(getline(linestream, item, ' ')) {
            itemNum++;
            initial.push_back(atoi(item.c_str()));
        }
    }
 */
 //changed following

    itemNum++;initial.push_back(2);
    itemNum++;initial.push_back(3);
    itemNum++;initial.push_back(0);
    
    itemNum++;initial.push_back(1);
    itemNum++;initial.push_back(4);
    itemNum++;initial.push_back(5);
    
    itemNum++;initial.push_back(7);
    itemNum++;initial.push_back(8);
    itemNum++;initial.push_back(6);
    length = (int)sqrt((double)itemNum);
    instream.close();
}
void searchTree::sortList() {
    puzzle* temp;
    for(int i = 0; i < (signed)stack.size() - 1; i++) {
        for(int j = 0; j < (signed)stack.size() - 1; j++) {
            if(stack[j]->f > stack[j+1]->f) {
                temp = stack[j];
                stack[j] = stack[j+1];
                stack[j+1] = temp;
            }
        }
    }
}

void searchTree::setHvalue(puzzle* puzzle) {
    int h;
    puzzle->h = 0;
    for(int i = 0; i < itemNum; i++) {
    h = abs(puzzle->state[i] - i);
    h = (h % length) + (h / length);
    puzzle->h += h;
    }
}

int main() {
    searchTree B;
    clock_t start,end;

    start = clock();
    B.build();
    end = clock();
    cout << "time : " << (double)(end-start);
    return 0;
 //system("pause");
}
