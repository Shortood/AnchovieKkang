#include <bits/stdc++.h>

#define min(x, y) (((x) < (y)) ? (x) : (y))
using namespace std;

struct node {
    char info;           //값
    struct node* l, * r;  //노드 포인터
};

template <typename itemType>
class Queue {
private:
    itemType* queue;       //포인트를 이용한 배열 생성
    int tail, size, head;  //끝부분, 크기, 앞부분

public:
    Queue(int max = 10000) {
        queue = new itemType[max];  //배열 동적 할당
        tail = 0;                   //끝부분과, 앞부분 초기화
        head = 0;
        size = max;  //사이즈 설정
    }
    ~Queue() {
        delete queue;  //동적할당 해제
    }
    inline void put(itemType v) {   //삽입
        queue[tail++] = v;          //뒷부분에 노드 삽입
        if (tail > size) tail = 0;  //만약 뒷부분이 배열 크기를 벗어나면 제일 앞으로 간다
    }
    inline itemType get() {  //앞부분 노드를 리턴
        itemType t = queue[head++];
        if (head > size) head = 0;  //만약 앞부분이 배열 크기를 벗어나면 앞으로 간다
        return t;
    }
    inline itemType front() {  //앞부분 노드를 리턴
        return queue[head];
    }
    inline int empty() {  //비어있는지 확인
        return head == tail;
    }
};

// using pii = pair<int, int>;

struct pii {
    int x;  // x좌표
    int y;  // y좌표
};

// using tpi = tuple<int, int, int>;

struct tpi {
    int d;  // depth
    int x;  // x좌표
    int y;  // y좌표
};

const int INF = 0x3f3f3f3f;

// K: 청소해야할 구역의 개수
// m: map
// v: 현재 위치

int N, M, K;
int m[20][20];
pii v[20];
int dist[20][20];

int dy[4] = { -1, 1, 0, 0 };
int dx[4] = { 0, 0, -1, 1 };

bool bfs(int st) {
    int vi[20][20];
    memset(vi, -1, sizeof(vi));
    tpi tmp;
    Queue<tpi> q(100000);

    tmp.d = 0;
    tmp.x = v[st].x;
    tmp.y = v[st].y;

    // q.push({ 0, v[st].xx, v[st].yy });
    q.put(tmp);

    vi[v[st].y][v[st].x] = 0;

    while (!q.empty()) {
        int cd, cx, cy;
        tmp = q.front();
        cd = tmp.d;
        cx = tmp.x;
        cy = tmp.y;
        q.get();

        for (int i = 0; i < 4; i++) {
            int nd = cd + 1;
            int nx = cx + dx[i];
            int ny = cy + dy[i];

            if (ny < 0 || nx < 0 || ny >= N || nx >= M || vi[ny][nx] != -1 || m[ny][nx] == -1) continue;
            tmp.d = nd;
            tmp.x = nx;
            tmp.y = ny;

            q.put(tmp);
            vi[ny][nx] = nd;
        }
    }

    for (int i = 0; i <= K; i++) {
        dist[st][i] = vi[v[i].y][v[i].x];
        if (dist[st][i] == -1) return false;
    }
    return true;
}

int ans = 0;

// vi: 간 곳에 플래그 찍는 배열
bool vi[20];
void dfs(int now, int sum, int dpt) {
    if (dpt == K) {
        ans = min(ans, sum);
        return;
    }

    for (int i = 1; i <= K; i++) {
        if (vi[i]) continue;
        vi[i] = true;
        sum += dist[now][i];
        dfs(i, sum, dpt + 1);
        sum -= dist[now][i];
        vi[i] = false;
    }
}

int main() {
    while (1) {
        cin >> M >> N;
        if(!N) break;
        memset(m, -1, sizeof(m));
        K = 0;

        int tmp = 0;

        for (int i = 0; i < 20; i++) {
            for (int j = 0; j < 20; j++) {
                dist[i][j] = -1;
            }
        }
        v[0].y = 0, v[0].x = 0;

        srand(time(NULL));

        // 0: 안치워도 되는데
        // 1 이상: 치워야 하는데
        // -1: 로봇청소기 위치
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < M; j++) {
                m[i][j] = tmp = rand() % 6;
                cout << m[i][j] << " ";
                if (tmp > 0) m[i][j] = ++K, v[K].y = i, v[K].x = j;
                else  m[i][j] = 0;
            }
            cout << endl;
        }

        m[0][0] = -2;

        bool chk = true;
        for (int i = 0; i <= K; i++) {
            if (!bfs(i)) {
                chk = false;
                break;
            }
        }
        if (!chk) {
            cout << -1 << '\n';
            continue;
        }

        ans = INF;
        dfs(0, 0, 0);
        cout << ans << '\n';        
    }
}