#include <bits/stdc++.h>
#define xx first
#define yy second
using namespace std;
using pii = pair<int, int>;
using dpi = pair<pii, pii>;

int N, M;
int m[200][200];
bool vi[200][200][1 << 16];  //위치 + 더러운 칸의 정보를 비트 마스킹으로 표현
int dy[4] = {-1, 1, 0, 0};
int dx[4] = {0, 0, -1, 1};

int bfs(int sty, int stx, int K) {
    cout << "ck " << (1 << K) - 1;
    memset(vi, 0, sizeof(vi));     //배열을 0으로 초기화
    queue<dpi> q;                  //큐 선언
    q.push({{0, 0}, {sty, stx}});  //큐에 0,0과 로봇의 위치 삽입
    vi[sty][stx][0] = false;       //로봇의 위치는 이미 갔다고 설정

    while (!q.empty()) {
        int cd = q.front().xx.xx;  //큐의 첫번째
        int ck = q.front().xx.yy;  //큐의 두번째
        int cy = q.front().yy.xx;  //큐의 세번째
        int cx = q.front().yy.yy;  //큐의 네번째
        q.pop();
        //총 4개라면 10000-1 => 1111
        // cout << "ck " << ck << " " << ((1 << K) - 1) << " " << (1 << 16) << endl;
        if (ck == (1 << K) - 1) {  //모든 오염된 위치를 지났으면
            return cd;             //몇 번 이동했는지 리턴
        }
        for (int i = 0; i < 4; i++) {  // 4방향 이동
            int nd = cd + 1;           //이동한 횟수 1증가
            int nk = ck;               //다시 nk를 복구
            int ny = cy + dy[i];       //다음 이동할 위치
            int nx = cx + dx[i];
            //못 가는 곳이라면 continue
            if (ny < 0 || nx < 0 || ny >= N || nx >= M || m[ny][nx] == -1) continue;
            //다음 확인할 위치가 오염되었다면 nk->0000->0001->0011->0111->1111
            if (m[ny][nx] > 0) nk |= (1 << (m[ny][nx] - 1));
            if (vi[ny][nx][nk]) continue;  //이미 간 곳이라면 countinue
            q.push({{nd, nk}, {ny, nx}});  //큐에 푸시
            cout << "nk " << nk << endl;
            vi[ny][nx][nk] = true;  //간 곳이라고 표시해줌
        }
    }
    // cout << "bfs done " << endl;
    return N * M - 1;
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    int X, Y;
    int tmp = 0;
    int cnt = 0;
    while (1) {
        cnt = 0;
        cout << "행, 열 수 입력 : ";
        cin >> N >> M;  //행, 열 수
        cout << "시작 위치 입력 : ";
        cin >> X >> Y;  //행, 열 수
        if (!N) break;
        memset(m, -1, sizeof(m));  // m 배열 초기화
        int sty, stx, K = 0;       //로봇 위치, 오염된 위치 수
        string str;

        for (int i = 0; i < N; i++) {
            for (int j = 0; j < M; j++) {
                m[i][j] = tmp = rand() % 2;  //랜덤 생성
                /*
                /if (tmp > 0) cnt++;
                if (cnt > 20) {
                    m[i][j] = 0;
                    tmp = 0;
                }*/
                cout << m[i][j] << " ";                 //방 상태 출력
                if ((tmp > 0) && (i != 0 || j != 0)) {  //시작위치가 아니고 오염되었다면
                    m[i][j] = ++K;                      //몇 번째로 확인했는지 입력
                }
            }
            cout << endl;
        }
        sty = X, stx = Y, m[X][Y] = 0;  //로봇 위치
        cout << "출력 " << bfs(sty, stx, K) << endl;
    }
}
