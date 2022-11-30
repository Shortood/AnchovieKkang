#include <memory.h>
#include <stdio.h>

#include <algorithm>
#include <ctime>
#include <iostream>
#include <queue>
#include <string>
#include <vector>

using namespace std;

int dx[] = {1, -1, 0, 0};
int dy[] = {0, 0, -1, 1};

int map[21][21];
bool check[21][21];
int dist[21][21];

int dirtdist[12][12];

int h, w;

int bfs(int a, int b, int fx, int fy) {
    // cout << "bfs " << a << " " << b << " " << fx << " " << fy << endl;
    memset(check, false, sizeof(check));
    memset(dist, 0, sizeof(dist));

    queue<pair<int, int>> q;

    q.push({a, b});
    check[a][b] = true;

    while (!q.empty()) {
        int x = q.front().first;
        int y = q.front().second;
        q.pop();

        for (int i = 0; i < 4; i++) {
            int nx = x + dx[i];
            int ny = y + dy[i];
            if (nx >= 0 && nx < h && ny >= 0 && ny < w) {
                if (check[nx][ny] == false) {
                    check[nx][ny] = true;
                    dist[nx][ny] = dist[x][y] + 1;
                    // cout << nx << " " << ny << " " << dist[nx][ny] << endl;
                    q.push({nx, ny});
                }
            }
        }
    }
    // cout << "bfs done " << endl;
    return dist[fx][fy];
}

int main() {
    srand(time(NULL));

    while (1) {
        memset(dirtdist, 0, sizeof(dirtdist));

        cin >> w >> h;

        if (w == 0 && h == 0) {
            break;
        }

        int dirt = 0;
        bool can = true;
        int ssx = 0;
        int ssy = 0;

        vector<pair<int, int>> dirtxy;

        for (int i = 0; i < h; i++) {
            for (int j = 0; j < w; j++) {
                map[i][j] = rand() % 6;
                cout << map[i][j] << " ";
                if (map[i][j] > 0 && (i != 0 || j != 0)) {
                    dirt++;
                    dirtxy.push_back({i, j});
                }
                ssx = 0;
                ssy = 0;
            }
            cout << endl;
        }
        for (int i = 0; i < dirt; i++) {
            int sx = dirtxy[i].first;
            int sy = dirtxy[i].second;

            int tmp = bfs(ssx, ssy, sx, sy);

            if (tmp == 0) {
                can = false;
                break;
            } else {
                dirtdist[11][i] = tmp;
            }

            for (int j = i + 1; j < dirt; j++) {
                if (i != j) {
                    int sx = dirtxy[i].first;
                    int sy = dirtxy[i].second;
                    int fx = dirtxy[j].first;
                    int fy = dirtxy[j].second;

                    int tmp = bfs(sx, sy, fx, fy);

                    dirtdist[i][j] = tmp;
                    dirtdist[j][i] = tmp;
                }
            }
        }

        vector<int> order;

        for (int i = 0; i < dirt; i++) {
            order.push_back(i);
        }

        int min = -1;

        do {
            int sx = ssx;
            int sy = ssy;

            int ans = 0;

            if (can == false || dirt == 0) break;

            ans += dirtdist[11][order[0]];

            for (int i = 0; i < dirt - 1; i++) {
                ans += dirtdist[order[i]][order[i + 1]];
            }

            if (min > ans || min == -1) {
                min = ans;
            }
        } while (next_permutation(order.begin(), order.end()));

        if (dirt == 0) {
            cout << 0 << endl;
        } else {
            if (can == false || min == 0) {
                cout << -1 << endl;
            } else {
                cout << min << endl;
            }
        }
    }
}
