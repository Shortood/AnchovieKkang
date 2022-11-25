#include <bits/stdc++.h>

#define min(x, y) (((x) < (y)) ? (x) : (y))
using namespace std;

struct node {
    char info;           //��
    struct node* l, * r;  //��� ������
};

template <typename itemType>
class Queue {
private:
    itemType* queue;       //����Ʈ�� �̿��� �迭 ����
    int tail, size, head;  //���κ�, ũ��, �պκ�

public:
    Queue(int max = 10000) {
        queue = new itemType[max];  //�迭 ���� �Ҵ�
        tail = 0;                   //���κа�, �պκ� �ʱ�ȭ
        head = 0;
        size = max;  //������ ����
    }
    ~Queue() {
        delete queue;  //�����Ҵ� ����
    }
    inline void put(itemType v) {   //����
        queue[tail++] = v;          //�޺κп� ��� ����
        if (tail > size) tail = 0;  //���� �޺κ��� �迭 ũ�⸦ ����� ���� ������ ����
    }
    inline itemType get() {  //�պκ� ��带 ����
        itemType t = queue[head++];
        if (head > size) head = 0;  //���� �պκ��� �迭 ũ�⸦ ����� ������ ����
        return t;
    }
    inline itemType front() {  //�պκ� ��带 ����
        return queue[head];
    }
    inline int empty() {  //����ִ��� Ȯ��
        return head == tail;
    }
};

// using pii = pair<int, int>;

struct pii {
    int x;  // x��ǥ
    int y;  // y��ǥ
};

// using tpi = tuple<int, int, int>;

struct tpi {
    int d;  // depth
    int x;  // x��ǥ
    int y;  // y��ǥ
};

const int INF = 0x3f3f3f3f;

int N, M, K;
int m[20][20];
pii v[11];
int dist[11][11];
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

int ans;
bool vi[11];
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
        if (!N) break;
        memset(m, -1, sizeof(m));
        K = 0;
        string str;
        for (int i = 0; i < N; i++) {
            cin >> str;
            for (int j = 0; j < M; j++) {
                if (str[j] == 'o')
                    v[0].y = i, v[0].x = j, m[i][j] = 0;
                else if (str[j] == '*')
                    m[i][j] = ++K, v[K].y = i, v[K].x = j;
                else if (str[j] == 'x')
                    m[i][j] = -1;
                else
                    m[i][j] = 0;
            }
        }

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