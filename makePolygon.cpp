#include <ctime>
#include <iostream>
#define MAXINT 101
using namespace std;

int N;
struct point {
    int x, y;     // x, y ��
    float angle;  //����
    char c;
    point(int x = 0, int y = 0, char c = ' ') {
        this->x = x;
        this->y = y;
        this->c = c;
    }
};

struct line {
    struct point p1, p2;
};
void Swap(struct point* a, struct point* b) {  //�� �ٲٱ�
    struct point t;
    t = *a;
    *a = *b;
    *b = t;
}
float ComputeAngle(struct point p1, struct point p2) {  //���� ���
    int dx, dy, ax, ay;                                 // x���� ,y����, x���� ����, y���� ����
    float t;                                            //��
    dx = p2.x - p1.x;                                   // x����
    ax = abs(dx);                                       //����
    dy = p2.y - p1.y;                                   // y����
    ay = abs(dy);                                       //����

    t = (ax + ay == 0) ? 0 : (float)dy / (ax + ay);  // 1��и� or ���� ��ġ
    if (dx < 0)
        t = 2 - t;    // 2��и�
    else if (dy <= 0)  // 4��и�
        t = 4 + t;

    return t * 90.0;  //�� ����
}


int partition(struct point a[], int l, int r) {  //������
    int i, j;                                    //��ȯ �� �� ã�� �ٲٱ�
    int v;                                       //Ű ��
    if (r > l) {
        v = a[l].x;  //���� ���� ���� Ű ������
        i = l;       // i�� �ʱⰪ�� ���� ���� �ε����� ����
        j = r + 1;   // j�� �ʱⰪ�� ���� ������ �ε������� ��ĭ ������ ����
        for (;;) {   //���� ������ ����� �ʵ��� ��
            while (i + 1 < N && a[++i].x < v)
                ;  //Ű ������ ū ���� ���� ������ i�� ����
            while (a[--j].x > v)
                ;                //Ű ������ ���� ���� ���� ������ i�� ����
            if (i >= j)          //���� i�� j���� Ŀ���� ���������Ƿ�
                break;           //������
            Swap(&a[i], &a[j]);  // a[i]�� a[j]���� �ٲ��ش�
        }
    }
    Swap(&a[j], &a[l]);  //Ű���� a[j]���� �ٲ��ش�.
    return j;            //���� ������ ������ �Ǵ� �ε��� ����
}

void quicksort(struct point a[], int l, int r) {  //������ x��ǥ �������� ����
    int j;
    if (r > l)  //���� ������ �ε����� ���� �ε��� ���� �����ʿ� �ִٸ�
    {
        j = partition(a, l, r);  //��ȯ�� �� ã��
        quicksort(a, l, j - 1);  //���� ������ ������ ����
        quicksort(a, j + 1, r);
    }
}

void printMap(int** map, int row, int col) {
    for (int j = 0; j < row; j++) {
        for (int k = 0; k < col; k++) {
            cout << map[j][k] << '\t';
        }
        cout << endl;
    }
    cout << endl;
}

int main() {
    int miny = 100, checki;
    int x, y = 0, result, row, col, count = 1;
    char c;
    srand(time(NULL));
    cout << "���� ũ�� �Է� : ";
    cin >> row >> col;
    int** map = new int* [row];
    for (int i = 0; i < row; i++) {
        map[i] = new int[col];
    }

    N = col * row;
    struct point* polygon = new struct point[N + 2], z;
    checki = 0;

    for (int i = 0; i < row; i++) {
        for (int j = 0; j < col; j++) {
            map[i][j] = rand() % 2;
            cout << map[i][j] << "\t";

            if (map[i][j] && !(i == 0 && j == 0)) {
                if (miny > j) {
                    miny = y;
                    checki = count;
                }
                else if (j == miny && polygon[checki].x > i)  // y���� ���ٸ� x���� ���� ���� ���� ã�´�
                    checki = count;
                polygon[count++] = point(i, j, 'A');
            }
        }
        cout << '\n';
    }

    for (int i = 1; i < count; i++) {  //������ ���� ���
        polygon[i].angle = ComputeAngle(polygon[checki], polygon[i]);
    }

    quicksort(polygon, 0, count - 1);  //������ �������� ����

    cout << endl;
    for (int i = 0; i < count; i++) {  //�ٰ��� ������� ���
        
        map[polygon[i].x][polygon[i].y] = -1;
        printMap(map, row, col);
        map[polygon[i].x][polygon[i].y] = 0;
    }
    cout << "Solution Path";

    for (int i = 0; i < count; i++) {
        cout << " - (" << polygon[i].x << ", " << polygon[i].y << ")";
    }
}
