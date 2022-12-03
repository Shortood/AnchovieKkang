#include <iostream>
#include <queue>
#include <string>
#include <cstdlib>
#include <ctime>

using namespace std;

int N, M;               //방의 크기 N, M, 전역변수로 선언

struct Node {
    Node* parent;       //부모 노드
    int **state;        //노드 상태
    int x, y;           //노드 좌표
    int g, h;           //노드의 함수
    string moves;       //노드의 방향

    Node() {
        moves = "";
        state = new int*[N];
        for (int i = 0; i < N; i++) 
            state[i] = new int[M];
    }

};

//새로운 노드 생성 후 반환
Node* newNode(int **state, int x, int y, int dx, int dy, int g, Node* parent) {
    Node* node = new Node;
    node->parent = parent;
    
    for (int i = 0; i < N; i++) 
        for (int j = 0; j < M; j++) 
            node->state[i][j] = state[i][j];

    
    node->state[x][y] = 0;
    node->state[dx][dy] = -1;

    node->h = INT_MAX;
    node->g = g;

    node->x = dx;
    node->y = dy;
    return node;
}

            // U, L, D, R
int dx[4] = { -1, 0, 1, 0 };
int dy[4] = { 0, -1, 0, 1 };

//최적의 이동경로 저장
string solutionPath = "";

//노드 state 출력
void printState(int **state) {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++)
            cout << state[i][j] << '\t';
        cout << '\n';
    }
}

//목표 노드에 도착하기까지의 과정 출력
void printSolutionPath(Node* node) {
    if (node == NULL) return;
    printSolutionPath(node->parent);
    solutionPath += node->moves + " - ";
    printState(node->state);
    cout << "\n";
}

//휴리스틱 함수
int heuristic(int **state) {
    int h = 0;
    for (int i = 0; i < N; i++)
        for (int j = 0; j < M; j++) 
            if (state[i][j] > 0)
                h++;
    return h;
}

//이동 가능 여부 판단
bool isValid(int x, int y) {
    return (x >= 0 && x < N && y >= 0 && y < M);
}

//함수 계산 및 비교
struct compare { 
    bool operator()(const Node* lhs, const Node* rhs) const {
        return (lhs->h + lhs->g) > (rhs->h + rhs->g);
    }
};

//ASTAR
Node* ASTAR(int **startState, int x, int y) {
    //함수 평가 값이 최소인 노드를 찾기 위해 우선 순위 큐를 사용
    priority_queue<Node*, vector<Node*>, compare> open; 

    Node* state = newNode(startState, x, y, x, y, 0, NULL);
    open.push(state);

    string move = "ULDR"; //이동 좌표 인덱스 활용
    
    while (!open.empty()) {
        Node* currentNode = open.top();
        open.pop();

        if (currentNode->h == 0) //목표 노드 도달
            return currentNode;
        
        for (int i = 0; i < 4; i++) { //노드 expand
            if (!isValid(currentNode->x + dx[i], currentNode->y + dy[i])) continue;
            Node* childNode = newNode(
                        currentNode->state, 
                        currentNode->x,
                        currentNode->y, 
                        currentNode->x + dx[i],
                        currentNode->y + dy[i],
                        currentNode->g + 1, 
                        currentNode);

            childNode->h = heuristic(childNode->state);
            childNode->moves = move[i];
            open.push(childNode);
        }
    }
    return NULL;
}

int main() {
    srand(time(NULL));

    cout << "방의 크기 N, M 입력 : ";
    cin >> N >> M;

    cout << "시작좌표 x, y 입력 : ";
    int x, y; cin >> x >> y;

    //동적할당
    int **startState = new int*[N];
    for (int i = 0; i < N; i++) 
        startState[i] = new int[M];
    
    //랜덤으로 상태 입력
    for (int i = 0; i < N; i++) 
        for (int j = 0; j < M; j++) 
            startState[i][j] = rand() % 2;

    Node* goalNode = ASTAR(startState, x, y); //시작 state, 시작 x좌표, y좌표 

    if (goalNode == NULL) cout << "A* Failed \n";
    else {
        cout << "A* Succeeded \n\n";
        printSolutionPath(goalNode);
        cout << "Solution Path" << solutionPath << "Finish\n";
    }

}