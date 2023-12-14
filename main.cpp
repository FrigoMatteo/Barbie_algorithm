#include <iostream>
#include <fstream>
#include <cstdlib>
#include <map>
#include <vector>

using namespace std;

struct adjs{
    int node;
    int distance;
    adjs(int val, int dist){
        node=val;
        distance=dist;
    }
};

map<int,vector<adjs>> grafo;
map<int,bool> occupied;
int C,S,k;
int * previous;
int * distances;
bool * reached;


int min_from_distance(int node){
    int base=distances[node];
    int index=0;
    int min=-1;
    for (auto i:grafo[node]) {
        if(!reached[i.node] && distances[i.node]>i.distance+base){
            printf("Entered from %d for %d\n",node,i.node);
            distances[i.node]=i.distance+base;
            previous[i.node]=node;
        }
        if (distances[i.node] == -1 && !reached[i.node]) {
            printf("Entered case base  from %d for %d\n",node,i.node);
            distances[i.node] = i.distance + base;
            previous[i.node]=node;
        }
    }
    for (int i=0; i<C;i++){
        if (!reached[i] && distances[i]!=-1){
            if (min==-1 || distances[i]<min){
                min=distances[i];
                index=i;
            }
        }
    }

    return index;
}

int barbie(){
    int node=0;
    map<int,int> adjs;
    for (int i=0; i<C;i++){
        previous[i]=-1;
        reached[i]=false;
        distances[i]=-1;
    }
    distances[0]=0;
    reached[0]=true;

    while (!reached[C-1]){
        int new_node= min_from_distance(node);
        printf("Reached node:%d with distance:%d from node:%d\n",new_node,distances[new_node],node);
        reached[new_node]=true;
        node=new_node;
    }
    vector<int> result;
    int j=C-1;
    result.push_back(j);
    while (previous[j]!=-1){
        result.push_back(previous[j]);
        j=previous[j];
    }

    printf("Result:\n");
    for(auto i:result){
        printf("Node:%d\n",i);
        if (occupied[i]){
            k=-2;
        }
    }

    for(int i=0; i<C;i++){
        printf("I got node[%d] which is %d with distance:%d and prev:%d\n",i,reached[i],distances[i],previous[i]);
    }


    printf("k:%d",k);
    return 0;

}

int main() {
    ifstream input("input.txt");
    ofstream output("output.txt");
    input>>C>>S;
    int first;
    int second;
    int length;
    for (int i=0; i<S;i++){
        input>>first>>second>>length;
        adjs ad1(second,length);
        grafo[first].push_back(ad1);
        adjs ad2(first,length);
        grafo[second].push_back((ad2));
    }
    input>>length;
    for(int i=0;i<C;i++){
        occupied[i]=false;
    }
    for (int i=0; i<length;i++){
        input>>first;
        occupied[first]=true;
    }
    for(int i=0;i<C;i++){
        printf("Occupied city %d is %d\n",i,occupied[i]);
    }
    reached=(bool*) malloc(C* sizeof(bool));
    previous=(int*)malloc(C*sizeof(int));
    distances=(int*)malloc(C*sizeof(int));
    for (auto i:grafo){
        printf("Val[%d]:\n",i.first);
        for (auto j:i.second){
            printf("%d distance:%d\n",j.node,j.distance);
        }
    }
    printf("\n\n\n");
    barbie();
    free(reached);
    free(previous);
    free(distances);
    return 0;
}
