#include <iostream>
#include <vector>
#include <queue>
#include <utility>
#include <bits/stdc++.h>

using namespace std;

template<typename T>
class Edge
{
public:
    int v;
    T wght;

    Edge(int v, T wght)
    {
        this->v = v;
        this->wght = wght;
    }
    void printEgde()
    {
        cout << "(" << v << "," << wght <<")" << " ";
    }
};

template<typename T>
class Graph
{
    int **nodeArr;
    int capacity, city, road;

    vector<int> cost;
    vector<vector<Edge<T>>> adjCity;
    vector<vector<Edge<T>>> finalGraph;


public:

    Graph(int city, int road)
    {
        this->city = city ;
        this->road = road ;
        adjCity.resize(this->city+1);
    }

    Graph(int city, int road, int cap, vector<int>& cost)
    {
        this->city = city ;
        this->road = road ;
        this->capacity = cap;
        this->cost = cost;
        adjCity.resize(this->city+1);

        nodeArr = new int*[this->city+1];
        for (int i = 0; i < this->city+1; i++)
        {
            nodeArr[i] = new int[capacity+1];
        }

        int count = 0;
        for (int i = 1; i < this->city+1; i++)
        {
            for (int j = 0; j < capacity+1; j++)
            {
                //cout << count << " ";
                nodeArr[i][j] = count;
                count++;
            }
            //cout << endl;
        }
    }

    void printArr()
    {
        for (int i = 1; i < city+1; i++)
        {
            for (int j = 0; j < capacity+1; j++)
            {
                cout << nodeArr[i][j] << " ";
            }
            cout << endl;
        }
    }

    void addEdgeDir( int a, int b, T w)
    {
        adjCity[a].push_back(Edge<T>(b, w));
    }

    void addCityEdge(int a, int b, T w)
    {
        adjCity[a].push_back(Edge<T>(b, w));              ///////// undirected edge
        adjCity[b].push_back(Edge<T>(a, w));
    }

    void addFinalEdge( int a, int b, T w)                 //////// adds directed graph
    {
        finalGraph[a].push_back(Edge<T>(b, w));
    }

    void makeFinalGraph()                                 //////// Final Grid Graph Maker
    {
        finalGraph.clear();
        finalGraph.resize((city)*(capacity+1));

        for (int i = 1; i < city+1; i++)
        {
            for (int j = 0; j < capacity+1; j++)
            {
                if( j < capacity ) {
                    addFinalEdge( nodeArr[i][j], nodeArr[i][j+1], cost[i] );
                }

                for( auto e : adjCity[i] ){
                    if(e.wght > j) continue;
                    else{
                        addFinalEdge( nodeArr[i][j], nodeArr[e.v][j-e.wght] , 0 );
                    }
                }
            }
        }

    }

    void finalGraphPrint()
    {
        cout << finalGraph.size() << endl;
        for( int i = 0; i<finalGraph.size(); i++)
        {
            cout << i << " : ";
            for( int j = 0; j<finalGraph[i].size(); j++ )
            {
                cout << finalGraph[i][j].v << "(" << finalGraph[i][j].wght << ")" << ", ";
            }
            cout << endl;
        }
    }

    //////////////////// Djkstra algo //////////////////

    void minDistHelper( int src, int des)
    {
        //cout << " final kaj kore na " << endl;
        makeFinalGraph();
        //cout <<"finalgraph sze    " <<  finalGraph.size() << endl;
        minDist( src, des, finalGraph );
    }

    void minDist(int src, int des, vector<vector<Edge<T>>> adjList)          /// basically djaktra on any adjlist graph
    {
        //cout << adjList.size() << endl;
        int mincost = 0;

        vector<int> visit( adjList.size(), -1 );
        vector<int> dist ( adjList.size(), INT32_MAX );

        priority_queue< pair<int,int>, vector<pair<int,int>>, greater<pair<int,int>> > pq;

        dist[src-1] = 0;
        pq.push(make_pair(0,src-1));


        while( !pq.empty() )
        {
            int u = pq.top().second;
            pq.pop();

            //cout << "popped " << u << ", ";

            for( auto e : adjList[u] )
            {
                int v = e.v;
                int roadDist = e.wght;
                if( visit[v] == 1) continue;


                if( dist[v] > dist[u] + roadDist ) {
                    dist[v] = dist[u]+roadDist;
                    pq.push( make_pair(dist[v],v) );
                }
            }
            visit[u] = 1;
        }

        cout << dist[ des-1 ] << endl;

        //cout << (capacity+1)*(des-1) << endl;

        // if( dist[ (capacity+1)*(des-1) ] == INT32_MAX){
        //     cout << "impossible" << endl;
        //     return;
        // }
        // cout << dist[ (capacity+1)*(des-1) ] << endl;
    }


    void printAdjList()
    {
        for( int i = 0; i< adjCity.size(); i++)
        {
            cout << i << " : ";
            for( auto v : adjCity[i])
            {
                v.printEgde();
            }
            cout << endl;
        }
    }


    ///// returns minimum distance between two pairs
    // will work on adjcity
    int shortestPathDis(int src, int des)                          /////// adjCity Graph er src and des er shrotest path ber kore dibe
    {
        priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;

        vector<int> dist(adjCity.size(), INT32_MAX);
        vector<int> parent(adjCity.size(), -1);

        pq.push({0, src});
        dist[src] = 0;

        while (!pq.empty()) {
            int u = pq.top().second;
            pq.pop();

            for (const Edge<T>& edge : adjCity[u]) {
                int v = edge.v;
                int weight = edge.wght;

                if (dist[v] > dist[u] + weight) {
                    dist[v] = dist[u] + weight;
                    parent[v] = u;
                    pq.push( make_pair(dist[v],v) );
                }
            }
        }
        //cout << "Shortest Distance from " << src << " to " << des << ": " << dist[des] << endl;
        return dist[des];
    }


    /// returns the parent array for path
    vector<int> shortestPathParent(int src, int des)                          /////// adjCity Graph er src and des er shrotest path ber kore dibe
    {
        priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;

        vector<int> dist(adjCity.size(), INT32_MAX);
        vector<int> parent(adjCity.size(), -1);

        pq.push({0, src});
        dist[src] = 0;

        while (!pq.empty()) {
            int u = pq.top().second;
            pq.pop();

            for (const Edge<T>& edge : adjCity[u]) {
                int v = edge.v;
                int weight = edge.wght;

                if (dist[v] > dist[u] + weight) {
                    dist[v] = dist[u] + weight;
                    parent[v] = u;
                    pq.push( make_pair(dist[v],v) );
                }
            }
        }
        //cout << "Shortest Distance from " << src << " to " << des << ": " << dist[des] << endl;
        return parent;
    }




    void solve( int src)
    {
        vector<int> count(city+1, INT32_MAX);
        int min = INT32_MAX;
        int temp;


        for( int i = 0; i<city; i++)
        {
            if( i == src ) continue;
            count[i] = shortestPathDis(src,i)+shortestPathDis(i,src);
            //cout << count[i]
            if( count[i] < min){
                min = count[i];
                temp = i;
            }
        }
        //cout << shortestPathDis( src, src);
        // for( int i = 0; i<count.size();i++)
        // {
        //     cout << count[i] << " ";
        // }
        //cout << endl;
        cout << "Minimum Total Times: " << min << endl;

        vector<int> parent = shortestPathParent( src, temp);
        vector<int> ans = printPath(src,temp,parent);

        for( int i = 0; i<ans.size(); i++)
        {
            cout << ans[i] << " ";
        }
        cout << endl;
    }

    vector<int> printPath( int src, int des, vector<int> & parent)
    {
        vector<int> ans;

        int k = des;
        while( k>=0 )           // = kata
        {
            ans.push_back( k );
            k = parent[k];
        }

        reverse( ans.begin(), ans.end());
        return ans;
    }

};

int main()
{
    int city,road;

    cin >> city >> road;

    Graph<int> graph(city,road);

    for( int i = 0; i<road; i++)
    {
        int a,b,w;
        cin >> a >> b >> w;
        graph.addEdgeDir(a,b,w);
    }
    int src;
    cin >> src;

    cout << src << endl;
    cout << graph.shortestPathDis(0,1) << endl;
    cout << graph.shortestPathDis(1,0) << endl;
    graph.solve(src);
    return 0;
}
