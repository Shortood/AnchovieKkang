#include <bits/stdc++.h>
#define xx first
#define yy second
using namespace std;
using pii = pair<int, int>;
using dpi = pair<pii, pii>;

int N, M;
int m[200][200];
bool vi[200][200][1 << 16];
int dy[4] = {-1, 1, 0, 0};
int dx[4] = {0, 0, -1, 1};

int bfs(int sty, int stx, int K) {
    memset(vi, 0, sizeof(vi));
    queue<dpi> q;
    q.push({{0, 0}, {sty, stx}});
    vi[sty][stx][0] = false;

    while (!q.empty()) {
        int cd = q.front().xx.xx;
        int ck = q.front().xx.yy;
        int cy = q.front().yy.xx;
        int cx = q.front().yy.yy;
        // cout << "pop" << endl;
        q.pop();

        // cout << "ck " << ck << " " << ((1 << K) - 1) << endl;
        if (ck == (1 << K) - 1) {
            return cd;
        }
        for (int i = 0; i < 4; i++) {
            int nd = cd + 1;
            int nk = ck;
            int ny = cy + dy[i];
            int nx = cx + dx[i];
            if (ny < 0 || nx < 0 || ny >= N || nx >= M || m[ny][nx] == -1) continue;
            if (m[ny][nx] > 0) nk |= (1 << (m[ny][nx] - 1));
            if (vi[ny][nx][nk]) continue;
            q.push({{nd, nk}, {ny, nx}});
            vi[ny][nx][nk] = true;
        }
    }
    cout << "bfs done " << endl;
    return 24;
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    int tmp = 0;
    int cnt = 0;
    while (1) {
        cin >> N >> M;
        if (!N) break;
        memset(m, -1, sizeof(m));
        int sty, stx, K = 0;
        string str;
        m[0][0] = 0;
        m[0][1] = 0;
        m[0][2] = 0;
        m[0][3] = 1;
        m[0][4] = 0;
        m[0][5] = 0;
        m[0][6] = 1;
        m[0][7] = 0;
        m[0][8] = 0;
        m[0][9] = 0;
        m[1][0] = 0;
        m[1][1] = 0;
        m[1][2] = 0;
        m[1][3] = 1;
        m[1][4] = 0;
        m[1][5] = 0;
        m[1][6] = 1;
        m[1][7] = 0;
        m[1][8] = 0;
        m[1][9] = 0;
        m[2][0] = 0;
        m[2][1] = 0;
        m[2][2] = 0;
        m[2][3] = 1;
        m[2][4] = 0;
        m[2][5] = 0;
        m[2][6] = 1;
        m[2][7] = 0;
        m[2][8] = 0;
        m[2][9] = 0;
        m[3][0] = 0;
        m[3][1] = 0;
        m[3][2] = 0;
        m[3][3] = 1;
        m[3][4] = 0;
        m[3][5] = 0;
        m[3][6] = 1;
        m[3][7] = 0;
        m[3][8] = 0;
        m[3][9] = 0;
        m[4][0] = 0;
        m[4][1] = 0;
        m[4][2] = 0;
        m[4][3] = 1;
        m[4][4] = 0;
        m[4][5] = 0;
        m[4][6] = 1;
        m[4][7] = 0;
        m[4][8] = 0;
        m[4][9] = 0;
        m[5][0] = 0;
        m[5][1] = 0;
        m[5][2] = 0;
        m[5][3] = 1;
        m[5][4] = 0;
        m[5][5] = 0;
        m[5][6] = 1;
        m[5][7] = 0;
        m[5][8] = 0;
        m[5][9] = 0;
        m[6][0] = 0;
        m[6][1] = 0;
        m[6][2] = 0;
        m[6][3] = 1;
        m[6][4] = 0;
        m[6][5] = 0;
        m[6][6] = 1;
        m[6][7] = 0;
        m[6][8] = 0;
        m[6][9] = 1;
        m[7][0] = 0;
        m[7][1] = 0;
        m[7][2] = 0;
        m[7][3] = 1;
        m[7][4] = 0;
        m[7][5] = 0;
        m[7][6] = 1;
        m[7][7] = 0;
        m[7][8] = 0;
        m[7][9] = 0;
        m[8][0] = 1;
        m[8][1] = 0;
        m[8][2] = 0;
        m[8][3] = 1;
        m[8][4] = 0;
        m[8][5] = 0;
        m[8][6] = 1;
        m[8][7] = 0;
        m[8][8] = 1;
        m[8][9] = 0;
        m[9][0] = 0;
        m[9][1] = 0;
        m[9][2] = 0;
        m[9][3] = 0;
        m[9][4] = 0;
        m[9][5] = 0;
        m[9][6] = 0;
        m[9][7] = 0;
        m[9][8] = 0;
        m[9][9] = 1;
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < M; j++) {
                // m[i][j] = tmp = rand() % 6;
                tmp = m[i][j];
                cout << m[i][j] << " ";
                if ((tmp > 0) && (i != 0 || j != 0)) {
                    m[i][j] = ++K;
                }
            }
            cout << endl;
        }
        sty = 0, stx = 0, m[0][0] = 0;
        cout << "출력 " << bfs(sty, stx, K) << endl;
    }
}
