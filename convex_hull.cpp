#include <bits/stdc++.h>
using namespace std;

struct Point {
    int x, y;

    bool operator==(const Point& p) const {
        return x == p.x && y == p.y;
    }

    bool operator<(const Point& p) const {
        return x < p.x || (x == p.x && y < p.y);
    }
};

int cross(const Point& O, const Point& A, const Point& B) {
    return (A.x - O.x) * (B.y - O.y) - (A.y - O.y) * (B.x - O.x);
}


bool onSegment(const Point& p, const Point& q, const Point& r) {
    if (cross(p, q, r) != 0) return false;
    return (r.x >= min(p.x, q.x) && r.x <= max(p.x, q.x)) &&
           (r.y >= min(p.y, q.y) && r.y <= max(p.y, q.y));
}

vector<Point> convexHullBruteForce(const vector<Point>& points) {
    vector<Point> hull;
    int n = points.size();

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            if (i == j) continue;

            bool valid = true;
            for (int k = 0; k < n; ++k) {
                if (k == i || k == j) continue;

                int orientation = cross(points[i], points[j], points[k]);
                if (orientation > 0 || onSegment(points[i], points[j], points[k])) {
                    valid = false;
                    break;
                }
            }

            if (valid) {
                if (find(hull.begin(), hull.end(), points[i]) == hull.end())
                    hull.push_back(points[i]);
                if (find(hull.begin(), hull.end(), points[j]) == hull.end())
                    hull.push_back(points[j]);
            }
        }
    }

    sort(hull.begin(), hull.end());

    return hull;
}

int main() {
    vector<Point> points = {{0, 3}, {1, 1}, {2, 2}, {4, 4}, {0, 0}, {1, 2}, {3, 1}, {3, 3}};
    
    vector<Point> hull = convexHullBruteForce(points);

    cout << "Convex Hull Points:\n";
    for (const auto& p : hull) {
        cout << "(" << p.x << ", " << p.y << ")\n";
    }

    return 0;
}