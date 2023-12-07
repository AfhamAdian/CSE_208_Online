#include<iostream>
#include<vector>
#include<algorithm>

// #include <bits/stdc++.h>

using namespace std;

template<typename T> class Graph
{
   vector<vector<int>> edgegraph;
   int nodecount;

   vector<vector<int>> mst;  
   vector<int> parent;  
   vector<int> rank; 
   int cost;      

   vector<vector<vector<int>>> allcomb;
   vector<vector<vector<int>>> allCostComb;
   vector<vector<vector<int>>> allMstAns;



   public:

   Graph(int n)
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
    int getCost()
    {
        return cost;
    }
   ////////////////////// Functions for all possible combination /////////////////
   
   void generateCombo(vector<vector<int>> arr) {

    int n = arr.size();

      for (int i = 0; i < (1 << n); ++i) {
         vector<vector<int>> currentCombination;
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

   /////////////////// kruskal for MST /////////////////

   void kruskal()                              
   {     
      cost = 1;                     
      sort(edgegraph.rbegin(),edgegraph.rend()); 

      for (auto edge : edgegraph)
      {
         int f1 = find(edge[1]);
         int f2 = find(edge[2]);

         if( f1 != f2 ){
            mst.push_back(edge);
            cost *= edge[0];
            join(f1,f2);                     // As we should join the roots
         }
      }

      // for( auto edge : mst){
      //    cout << "[ w:" << edge[0] << " a: " << edge[1] << " b: " << edge[2] << " ]" << endl;
      // }
      // cout << "Cost : " << cost << endl; 
   }


   ///////// Function for Cycle Detection ///////////

   bool cycleDet( vector<vector<int>> tempGraph)            //return false if cycle found
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
         int tempcost = 0;
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
         if(tempcost==cost && flag2 == 0) allCostComb.push_back(vv);
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

   cin >> node >> edge;
   Graph<int> graph(node);

   while(edge--)
   {
      int w,a,b;
      cin >> a >> b >> w;

      graph.addEdge(w,a,b);
   }
   
   //graph.print();
   //graph.generateCombinations(graph.getEdgeList());
   graph.kruskal();
   cout << graph.getCost() << endl;

   return 0;
}




