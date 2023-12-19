#include<iostream>
#include<vector>
#include<algorithm>

// #include <bits/stdc++.h>

using namespace std;


template<typename T> class Graph
{
    vector<vector<T>> graph;
    vector<vector<int>> disMatr;
    vector<vector<int>> nextStop;
    int nodes;
    int edges;

    public :

    Graph( int nodes )
    {
        this->nodes = nodes;
        graph.resize(nodes,vector<T>(nodes, INT16_MAX));
        disMatr.resize(nodes,vector<int>(nodes, INT16_MAX));
        nextStop.resize(nodes,vector<int>(nodes));

    }

    void addEdge(T a , T b, T w)        /// bidirectional
    {
        graph[a-1][b-1] = w;
        graph[b-1][a-1] = w;
    }

    void addEdgeDir(T a , T b, T w)        /// directional
    {
        graph[a-1][b-1] = w;
        //graph[b-1][a-1] = w;
    }



    // void floydWar()
    // {
    //     int i,j,k;
    //     disMatr = graph;

    //     //printDist();

    //     for( int i = 0; i<nodes; i++)                   // making the diogonal 0
    //     {
    //         for( int j = 0; j<nodes; j++)
    //         {
    //             if( i == j ) disMatr[i][j] = 0;
    //         }
    //     }


    //     for( int k = 0; k<nodes; k++)                   // 
    //     {
    //         for( int i = 0; i<nodes; i++)
    //         {
    //             for( int j = 0; j<nodes; j++)
    //             {
    //                 if( i == j ) continue;
    //                 if( disMatr[i][k] != INT16_MAX && disMatr[k][j] != INT16_MAX)
    //                 {
    //                     disMatr[i][j] =  min( disMatr[i][j], disMatr[i][k]+disMatr[k][j] );
    //                 }
    //             }
    //         }
    //     }

    //     return;
    // }

    void printDist()
    {
        for( int i = 0; i<nodes; i++)                   // making the diogonal 0
        {
            for( int j = 0; j<nodes; j++)
            {
                cout << disMatr[i][j] <<  " ";
            }
            cout << endl;
        }
    }

    void findAns( int limit )
    {
        
        floydWar();
        int ans[nodes] = {0};
        int min = INT16_MAX;

        //cout <<limit << endl;
        
        for( int i = 0; i<nodes; i++)                 
        {
            int count = 0;
            for( int j = 0; j<nodes; j++)
            {
                if( i == j) continue;
                if( disMatr[i][j] <= limit ) count++;
            }
            //cout << count << endl;
            if( count < min ) min = count;
            ans[i] = count;
        }

        //cout << min << endl;

        for( int i = 0; i<nodes; i++)
        {
            if( ans[i] == min ) cout << i+1 << " ";
        }
        cout << endl;
    }







    ////////////////////////////// /////////////////////////////////////////////////


    void floydWar()
    {
        int i,j,k;
        disMatr = graph;

        //printDist();

        for( int i = 0; i<nodes; i++)                   // making the diogonal 0
        {
            for( int j = 0; j<nodes; j++)
            {
                if( i == j ) disMatr[i][j] = 0;

                if( disMatr[i][j] == INT16_MAX ) nextStop[i][j] = -1;           /// initializing 
                else    nextStop[i][j] = j;

            }
        }


        for( int k = 0; k<nodes; k++)                   // 
        {
            for( int i = 0; i<nodes; i++)
            {
                for( int j = 0; j<nodes; j++)
                {
                    if( i == j ) continue;
                    if( disMatr[i][k] != INT16_MAX && disMatr[k][j] != INT16_MAX)
                    {
                        //disMatr[i][j] =  min( disMatr[i][j], disMatr[i][k]+disMatr[k][j] );

                        // if( i <= k && j <= k){
                        //     if( disMatr[i][k]+disMatr[k][j] < disMatr[i][j] )
                        //     {
                        //         pathMatr[i][j].push_back( k );
                        //     }
                        // }
                        if( disMatr[i][j] > disMatr[i][k]+disMatr[k][j] )
                        {
                            disMatr[i][j] = disMatr[i][k]+disMatr[k][j] ;
                            nextStop[i][j] = nextStop[i][k];
                        }
                    }
                }
            }
        }

        return;
    }

    void printPath( int s, int d )
    {
        int u = nextStop[s][d];
        if( u == -1 ){
            return;
        }
        //cout << s+1 << "->";
        
        while( u != d)
        {
            cout << u+1 << "->";
            u = nextStop[u][d];
        }
        cout << d+1;
    }



    void mustEdge( int s, int d, int w1, int w2)
    {
        if( (disMatr[s][w1] == INT16_MAX || disMatr[w2][d] == INT16_MAX) && (disMatr[s][w2] == INT16_MAX || disMatr[w1][d] == INT16_MAX) )
        {
            cout << "No path from " << s+1 << " to " << d+1 << endl;
            return;
        }

        // cout << s << " d "<<  d << " w1 "<< w1 << " w2 " <<w2 << endl;
        // cout << disMatr[s][w1] << endl;
        // cout << disMatr[w2][d] << endl;

        int cost = min( (disMatr[s][w1] + disMatr[w2][d] + disMatr[w1][w2]) , (disMatr[s][w2] + disMatr[w1][d]+ disMatr[w1][w2]) );

        if( cost > INT16_MAX ) cout << "vul " << endl;

        cout << "Shortest Path Weight: " << cost << endl;
        
        cout << s+1 << "->";

        if ((disMatr[s][w1] + disMatr[w2][d] + disMatr[w1][w2]) > (disMatr[s][w2] + disMatr[w1][d]+ disMatr[w1][w2]) )
        {
            printPath( s,w1 );
            cout << "->";
            cout << w2+1 << "->";
            printPath( w2,d );
            return;
        }
        else
        {
            printPath( s,w2 );
            cout << "->";
            cout << w1+1 << "->";
            printPath( w1,d );
        }
        cout << endl;

    }



    void ans()
    {
        floydWar();

        for( int i = 0; i<nodes; i++)
        {
            for( int j = 0; j<nodes; j++)
            {
                if( disMatr[i][j] + disMatr[j][i] < 0 )
                {
                    cout << "YES" << endl;
                    return;
                }
            }
        }
        cout << "NO" << endl;

    }




};

int main()
{

    int city,roads,threshold;
    cin >> city >> roads;

    Graph<int> graph(city);

    for( int i = 0; i< roads; i++)
    {
        int a ,b ,w ;
        cin >> a >> b >> w;
        graph.addEdgeDir(a,b,w);
    }

    //cin >> threshold;
    //graph.findAns( threshold );
    //graph.printDist();
    graph.ans();
   

}






