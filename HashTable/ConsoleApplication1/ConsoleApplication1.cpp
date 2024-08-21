#include <iostream>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <sstream>
#include <cmath>
#include <algorithm>
#include <functional>
#include <numeric>

using namespace std;

template <typename T>
struct Point {
    T X, Y;

    static void Print(const Point<T>& point) {
        cout << "X: " << point.X << " Y: " << point.Y << endl;
    }
};

int N, M, L;
vector<Point<int>> Spots;
vector<Point<int>> Orcs;
unordered_map<int, pair<int, int>> PathPointsIndices;
int StartPointIndice, StopPointIndice;
bool init = false;

double CalcDistance(const Point<int>& P1, const Point<int>& P2) {
    double dd = pow(P1.X - P2.X, 2) + pow(P1.Y - P2.Y, 2);
    return sqrt(dd);
}

bool isPossible(const Point<int>& from, const Point<int>& to, const vector<Point<int>>& Orcs) {
    double d1 = CalcDistance(from, to);
    for (const auto& o : Orcs) {
        double d2 = CalcDistance(o, to);
        if (d2 <= d1) return false;
    }
    return true;
}

unordered_set<string> FindPaths(unordered_map<int, pair<int, int>> routes, unordered_map<int, pair<int, int>> pathPointsIndices,
    const vector<Point<int>>& orcs, const vector<Point<int>>& spots,
    int startPointIndice, int stopPointIndice, string indices) {
    unordered_set<string> stringRoutes;
    unordered_map<int, pair<int, int>> _pathPointsIndices(pathPointsIndices);
    unordered_map<int, pair<int, int>> _routes(routes);

    if (!init) {
        vector<int> indexesToReverse;
        for (const auto& p : _routes) {
            if (p.second.second == startPointIndice) {
                indexesToReverse.push_back(p.first);
            }
        }

        for (const auto& i : indexesToReverse) {
            _routes[i] = { _routes[i].second, _routes[i].first };
        }
        _routes.erase(
            remove_if(_routes.begin(), _routes.end(),
                [startPointIndice](const auto& p) { return p.second.first != startPointIndice; }),
            _routes.end()
        );

        for (const auto& r : _routes) {
            _pathPointsIndices.erase(r.first);
        }
        init = true;
    }

    for (const auto& r : _routes) {
        if (r.second.second == stopPointIndice && isPossible(spots[r.second.first], spots[r.second.second], orcs)) {
            string _indices = indices + " " + to_string(r.second.second);
            stringRoutes.insert(_indices);
            cerr << "Finished success of route: " << _indices << endl;
            break;
        }

        vector<int> indexesToReverse;
        for (const auto& p : _pathPointsIndices) {
            if (p.second.second == r.second.second) {
                indexesToReverse.push_back(p.first);
            }
        }

        for (const auto& i : indexesToReverse) {
            _pathPointsIndices[i] = { _pathPointsIndices[i].second, _pathPointsIndices[i].first };
        }

        unordered_map<int, pair<int, int>> newRoutes;
        for (const auto& p : _pathPointsIndices) {
            if (p.second.first == r.second.second && isPossible(spots[p.second.first], spots[p.second.second], orcs)) {
                newRoutes[p.first] = p.second;
            }
        }

        for (const auto& e : newRoutes) {
            _pathPointsIndices.erase(e.first);
        }

        if (!newRoutes.empty()) {
            auto subRoutes = FindPaths(newRoutes, _pathPointsIndices, orcs, spots, startPointIndice, stopPointIndice, indices + " " + to_string(r.second.second));
            stringRoutes.insert(subRoutes.begin(), subRoutes.end());
        }
    }

    return stringRoutes;
}

int main() {
    cin >> N >> M >> L;

    Spots.resize(N);
    Orcs.resize(M);

    for (int i = 0; i < N; ++i) {
        cin >> Spots[i].X >> Spots[i].Y;
    }

    for (int i = 0; i < M; ++i) {
        cin >> Orcs[i].X >> Orcs[i].Y;
    }

    for (int i = 0; i < L; ++i) {
        int N1, N2;
        cin >> N1 >> N2;
        PathPointsIndices[i] = { N1, N2 };
    }

    cin >> StartPointIndice >> StopPointIndice;

    cerr << "Starting Point: " << endl;
    Point<int>::Print(Spots[StartPointIndice]);
    cerr << "Spots Points: " << endl;
    for (const auto& spot : Spots) {
        Point<int>::Print(spot);
    }

    for (const auto& p : PathPointsIndices) {
        cerr << p.second.first << " " << p.second.second << endl;
    }

    for (const auto& orc : Orcs) {
        Point<int>::Print(orc);
    }

    cerr << "Start: " << StartPointIndice << "." << endl;
    cerr << "Stop: " << StopPointIndice << "." << endl;

    unordered_map<int, pair<int, int>> routes(PathPointsIndices);
    auto result = FindPaths(routes, PathPointsIndices, Orcs, Spots, StartPointIndice, StopPointIndice, to_string(StartPointIndice));
    cerr << "Result:" << endl;

    if (!result.empty()) {
        for (const auto& res : result) {
            cerr << res << endl;
        }

        vector<vector<int>> paths;
        for (const auto& res : result) {
            istringstream iss(res);
            vector<int> path((istream_iterator<int>(iss)), istream_iterator<int>());
            paths.push_back(path);
        }

        vector<int> distances(paths.size());
        for (size_t i = 0; i < paths.size(); ++i) {
            distances[i] = std::accumulate(paths[i].begin(), paths[i].end(), 0);
        }

        for (size_t i = 0; i < paths.size(); ++i) {
            cerr << "Distance for path: ";
            for (const auto& p : paths[i]) {
                cerr << p << " ";
            }
            cerr << "= " << distances[i] << "." << endl;
        }

        auto ans = *min_element(result.begin(), result.end(), [](const string& a, const string& b) { return a.length() < b.length(); });
        cerr << "Answer:" << endl;
        cout << ans << endl;
    }
    else {
        cout << "IMPOSSIBLE" << endl;
    }

    return 0;
}
