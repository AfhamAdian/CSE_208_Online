#include<iostream>
#include<vector>
#include<algorithm>

// #include <bits/stdc++.h>

using namespace std;

template<typename T> class Graph
{
   vector<vector<T>> edgegraph;
   int nodecount;

   vector<vector<T>> mst;  
   vector<T> parent;  
   vector<T> rank; 
   T cost;      

   vector<vector<vector<T>>> allcomb;
   vector<vector<vector<T>>> allCostComb;
   vector<vector<vector<T>>> allMstAns;



   public:

   Graph(T n)
   {
      nodecount = n;
      cost = 0;
      
      for( int i = 0;i<n; i++)      //initializing 
      {
         parent.push_back(-1);
         rank.push_back(1);
      }
   }

   void addEdge(T w, T a, T b)
   {
      edgegraph.push_back({w,a,b});
   }

   vector<vector<T>> getEdgeList(){
      return edgegraph;
   }
   
   void print(){
       for( auto edge : edgegraph){
         cout << "[ w:" << edge[0] << " a: " << edge[1] << " b: " << edge[2] << " ]" << endl;
      }
   }

   float get_cost()
   {
        return cost;
   }

   ////////////////////// Functions for all possible combination /////////////////
   
   void generateCombo(vector<vector<T>> arr) {

    int n = arr.size();

      for (int i = 0; i < (1 << n); ++i) {
         vector<vector<T>> currentCombination;
         for (int j = 0; j < n; ++j) {
               if (i & (1 << j)) {
                  currentCombination.push_back(arr[j]);
               }
         }
         allcomb.push_back(currentCombination);
      }


      // for( auto vv : allcomb){
      //    for( auto v: vv ){
      //       cout << "[ w:" << v[0] << " a: " << v[1] << " b: " << v[2] << " ]" << ", ";
      //    }
      //   cout << endl;
      // }

      // cout << "All possible combination generation complete" << endl;
   }



   /////////////////////// Functions For MST //////////////////////////

   int find( int i){
      if( parent[i] == -1) return i;

      return find(parent[i]);
   }

   void join(int a, int b)
   {
      parent[a] = b;
   }

   ///////////////// kruskal for MST /////////////////

   void kruskal()                              
   {     
      cost = 0;                     
      sort(edgegraph.begin(),edgegraph.end()); 

      for (auto edge : edgegraph)
      {
         int f1 = find((int)edge[1]);
         int f2 = find((int)edge[2]);

         if( f1 != f2 ){
            mst.push_back(edge);
            cost += edge[0];
            join(f1,f2);                     // As we should join the roots
         }
      }

      // for( auto edge : mst){
      //    cout << "[ w:" << edge[0] << " a: " << edge[1] << " b: " << edge[2] << " ]" << endl;
      // }
      // cout << "Cost : " << cost << endl; 
   }


   /////////////// Function for Cycle Detection ///////////////

   bool cycleDet( vector<vector<T>> tempGraph)            //return false if cycle found
   {
      //sort(tempGraph.begin(),tempGraph.end());
      for(int i = 0; i<nodecount; i++){
          parent[i] = -1;
      }
      
      for (auto edge : tempGraph)
      {
         int f1 = find(edge[1]);
         int f2 = find(edge[2]);

         if( f1 != f2 ){
            mst.push_back(edge);
        //cout << " a : " << edge[1] << " b: " << edge[2] << " ,";
        // += edge[0];
            join(f1,f2);                                  // As we should join the roots
         }
         else {
            return false;
         }
      }
        // cout << endl;
        // for(int i = 0; i<nodecount; i++){
        //     cout << parent[i] << " ";
        // }
        // cout << endl;
      return true;
   }

   //////////// Function for Finding All MST /////////////

   void allMst()
   {
      kruskal();
      generateCombo(edgegraph);

      // cout << "All combo size : " << allcomb.size() << endl;

      for( auto vv: allcomb)
      {
         int flag[nodecount] = {0},flag2 = 0;
         if( vv.size() != nodecount-1 ) continue;
         T tempcost = 0;
         for(auto v: vv)
         {
            tempcost += v[0];
            flag[v[1]]++;
            flag[v[2]]++;
         }
         for(int i = 0; i<nodecount; i++)
         {
            if(flag[i] == 0) flag2 = 1;
         }
         if(tempcost == cost && flag2 == 0) allCostComb.push_back(vv);
      }

      // cout << "Cost MSt : " << allCostComb.size() << endl;

      for( auto vv : allCostComb){
         if( cycleDet(vv) == true ){
            allMstAns.push_back(vv);
         }
      }
        
        int count  = 1;
       for( auto vv: allMstAns)
       {    
           int brCount = 0;
           cout << count << " : [";
          for(auto v: vv)
          {
             brCount++;
             cout << "[" << v[1] << ", " << v[2] << ", " << v[0] << "]"; 
             if(brCount != vv.size()) cout << ", ";
             
          }
          cout <<"]" << endl;
          count++;
       }
   }


};


int main()
{
   int node,edge;
//     int t ,n;
//    cin >> t >> n;
    
//     node = t+1;
//     edge = t+n;

//     Graph<int> graph(node);

//     for( int i = 1; i<=t; i++)
//     {
//         int temp;
//         cin >> temp;
//         graph.addEdge(temp,0,i);
//     }

//     for( int i = 0; i<n; i++)
//     {
//         int a,b,w;
//         cin >> a >> b >> w;
//         graph.addEdge(w,a,b);
//     }
//     graph.kruskal();
//     cout << graph.get_cost() << endl;

    cin >> node >> edge;
    float tel;
    cin >> tel;

    //cout << node << " " << edge << " " << tel << endl;


    Graph<float> graph(node);

    for( int i = 0; i<edge; i++)
    {
        int a,b,w;
        cin >> a >> b >> w;
        graph.addEdge(w,a,b);
    }

    //cout << "1" << endl;

    for( int i = 0; i<node; i++)
    {
        for( int j = 0 ; j<node; j++)
        {
            if( i == j) continue;
            graph.addEdge(tel,i,j);
        }
    }

    //cout << "2" << endl;


    graph.kruskal();
    cout << graph.get_cost() << endl;

    return 0;
}




