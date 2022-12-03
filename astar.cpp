//#include <iostream>
//#include <queue>
//#include <string>
//#include <cstdlib>
//#include <ctime>
//
//using namespace std;
//
//int N, M;               //���� ũ�� N, M, ���������� ����
//
//struct Node {
//    Node* parent;       //�θ� ���
//    int** state;        //��� ����
//    int x, y;           //��� ��ǥ
//    int g, h;           //����� �Լ�
//    string moves;       //����� ����
//
//    Node() {
//        moves = "";
//        state = new int* [N];
//        for (int i = 0; i < N; i++)
//            state[i] = new int[M];
//    }
//
//};
//
////���ο� ��� ���� �� ��ȯ
//Node* newNode(int** state, int x, int y, int dx, int dy, int g, Node* parent) {
//    Node* node = new Node;
//    node->parent = parent;
//
//    for (int i = 0; i < N; i++)
//        for (int j = 0; j < M; j++)
//            node->state[i][j] = state[i][j];
//
//
//    node->state[x][y] = 0;
//    node->state[dx][dy] = -1;
//
//    node->h = INT_MAX;
//    node->g = g;
//
//    node->x = dx;
//    node->y = dy;
//    return node;
//}
//
//// U, L, D, R
//int dx[4] = { -1, 0, 1, 0 };
//int dy[4] = { 0, -1, 0, 1 };
//
////������ �̵���� ����
//string solutionPath = "";
//
////��� state ���
//void printState(int** state) {
//    for (int i = 0; i < N; i++) {
//        for (int j = 0; j < M; j++)
//            cout << state[i][j] << '\t';
//        cout << '\n';
//    }
//}
//
////��ǥ ��忡 �����ϱ������ ���� ���
//void printSolutionPath(Node* node) {
//    if (node == NULL) return;
//    printSolutionPath(node->parent);
//    solutionPath += node->moves + " - ";
//    printState(node->state);
//    cout << "\n";
//}
//
////�޸���ƽ �Լ�
//int heuristic(int** state) {
//    int h = 0;
//    for (int i = 0; i < N; i++)
//        for (int j = 0; j < M; j++)
//            if (state[i][j] > 0)
//                h++;
//    return h;
//}
//
////�̵� ���� ���� �Ǵ�
//bool isValid(int x, int y) {
//    return (x >= 0 && x < N&& y >= 0 && y < M);
//}
//
////�Լ� ��� �� ��
//struct compare {
//    bool operator()(const Node* lhs, const Node* rhs) const {
//        return (lhs->h + lhs->g) > (rhs->h + rhs->g);
//    }
//};
//
////ASTAR
//Node* ASTAR(int** startState, int x, int y) {
//    //�Լ� �� ���� �ּ��� ��带 ã�� ���� �켱 ���� ť�� ���
//    priority_queue<Node*, vector<Node*>, compare> open;
//
//    Node* state = newNode(startState, x, y, x, y, 0, NULL);
//    open.push(state);
//
//    string move = "ULDR"; //�̵� ��ǥ �ε��� Ȱ��
//
//    while (!open.empty()) {
//        Node* currentNode = open.top();
//        open.pop();
//
//        if (currentNode->h == 0) //��ǥ ��� ����
//            return currentNode;
//
//        for (int i = 0; i < 4; i++) { //��� expand
//            if (!isValid(currentNode->x + dx[i], currentNode->y + dy[i])) continue;
//            Node* childNode = newNode(
//                currentNode->state,
//                currentNode->x,
//                currentNode->y,
//                currentNode->x + dx[i],
//                currentNode->y + dy[i],
//                currentNode->g + 1,
//                currentNode);
//
//            childNode->h = heuristic(childNode->state);
//            childNode->moves = move[i];
//            open.push(childNode);
//        }
//    }
//    return NULL;
//}
//
//int main() {
//    srand(time(NULL));
//
//    cout << "���� ũ�� �Է� : ";
//    cin >> N >> M;
//     
//    cout << "���� ��ǥ �Է� : ";
//    int x, y; cin >> x >> y;
//
//    //�����Ҵ�
//    int** startState = new int* [N];
//    for (int i = 0; i < N; i++)
//        startState[i] = new int[M];
//
//    //�������� ���� �Է�
//    for (int i = 0; i < N; i++)
//        for (int j = 0; j < M; j++)
//            startState[i][j] = rand() % 2;
//
//    Node* goalNode = ASTAR(startState, x, y); //���� state, ���� x��ǥ, y��ǥ 
//
//    if (goalNode == NULL) cout << "A* Failed \n";
//    else {
//        printSolutionPath(goalNode);
//        cout << "Solution Path" << solutionPath << "Finish\n";
//    }
//}