#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <cmath> // for sqrt()
using namespace std;

////////////////////////////////////////////////////////////////////////////////////////////////////////////

template<class Type>
void Merge(Type* a, int n, bool (*IsBefore)(Type& a, Type& b)) {
    Type* temp = new Type[n];
    int mid = n / 2;
    int i = 0, j = mid, k = 0;

    while (i < mid && j < n) {
        if (IsBefore(a[i], a[j]))
            temp[k++] = a[i++];
        else
            temp[k++] = a[j++];
    }

    while (i < mid) temp[k++] = a[i++];
    while (j < n) temp[k++] = a[j++];

    for (i = 0; i < n; i++) a[i] = temp[i];
    delete[] temp;
}

template<class Type>
void MergeSort(Type* a, int n, bool (*IsBefore)(Type& a, Type& b)) {
    if (n <= 1) return;
    int mid = n / 2;
    MergeSort(a, mid, IsBefore);
    MergeSort(a + mid, n - mid, IsBefore);
    Merge(a, n, IsBefore);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////

struct Point {
    double x, y;
};

bool IsBeforeX(Point& a, Point& b) {
    return a.x < b.x || (a.x == b.x && a.y < b.y);
}

bool IsBeforeY(Point& a, Point& b) {
    return a.y < b.y;
}

double dist(Point& a, Point& b) {
    return sqrt((a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y));
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////

double ClosestPair(Point* p, int n) {
    if (n <= 1) return 1e20; // Large number as infinity
    if (n == 2) return dist(p[0], p[1]);

    int mid = n / 2;
    Point midPoint = p[mid];

    double leftMin = ClosestPair(p, mid);
    double rightMin = ClosestPair(p + mid, n - mid);

    double d = min(leftMin, rightMin);

    // Build the strip
    Point* strip = new Point[n];
    int stripSize = 0;

    for (int i = 0; i < n; i++) {
        if (fabs(p[i].x - midPoint.x) < d) {
            strip[stripSize++] = p[i];
        }
    }

    // Sort the strip by Y coordinate
    MergeSort(strip, stripSize, IsBeforeY);

    // Find the minimum distance in the strip
    for (int i = 0; i < stripSize; ++i) {
        for (int j = i + 1; j < stripSize && (strip[j].y - strip[i].y) < d; ++j) {
            d = min(d, dist(strip[i], strip[j]));
        }
    }

    delete[] strip;

    return d;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////

int main() {
    int n;
    while (scanf("%d", &n) && n) {
        Point* points = new Point[n];
        for (int i = 0; i < n; ++i)
            scanf("%lf %lf", &points[i].x, &points[i].y);

        MergeSort(points, n, IsBeforeX);

        double minDist = ClosestPair(points, n);
        if (minDist >= 10000.0)
            printf("INFINITY\n");
        else
            printf("%.4lf\n", minDist);

        delete[] points;
    }
    return 0;
}
