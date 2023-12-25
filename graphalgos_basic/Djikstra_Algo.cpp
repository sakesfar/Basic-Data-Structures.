#include <iostream>
#include <unordered_set>
#include "graphVertex.h"


void BFS(Vertex* s, const std::vector<Vertex*>& graph)
{
    //1. set dist and known of all verts to DEFAULT. In Vertex con-r it is by default.

    for (int i = 0; i < graph.size(); ++i)
    {
        graph[i]->dist = INFINITE;
        graph[i]->known = false;
    }

    s->dist = 0;
    std::queue<Vertex*> data;
    data.push(s);

    //2.Keep all the known in queue

    while (!data.empty())
    {
        Vertex* v = data.front();
        data.pop();
       
        for (int i = 0; i < v->adjVertices.size(); ++i)
        {
            Vertex* w = v->adjVertices[i];
            if (w->dist == INFINITE)
            {
                w->dist = v->dist + 1;
                w->known = true;
                w->path = v;
                data.push(w);
            }
        }
    }   
    
}


void djkstra(wVertex* s, const std::vector<wVertex*>& wgraph)
{
    auto compare
    {
        [](const auto& a, const auto& b)
        {
            return a->dist > b->dist;
        }
    };

    std::priority_queue<wVertex*, std::vector<wVertex*>, decltype(compare)> data(compare);
    
    s->dist = 0;
    data.push(s);
   

    for (int i = 0; i < wgraph.size(); ++i)
    {
        wVertex* v = wgraph[i];
        if (v != s)
        {
            v->dist = INFINITE;
            v->known = false;           
        }
    }


    //while there are unknwon vertices in the binary heap 'data'
    while (!data.empty())
    {
        wVertex* v = data.top();
        data.pop();

        if (v->known) continue;
        v->known = true;

       

        for (int i = 0; i < v->adjVertices.size(); ++i)
        {
            VertexAndWeight w = v->adjVertices[i];           

            int newDist = w.second + v->dist;

            if (newDist <w.first->dist )
            {
                w.first->dist = newDist;
                w.first->path = v;

                if(!w.first->known) data.push(w.first);
            }
            
        }      
                

        



    }

    
   

    


}


int main()
{
    //Unweighed graph
    Vertex v1(1), v2(2), v3(3), v4(4), v5(5), v6(6), v7(7);

    v1.adjVertices.push_back(&v4);
    v1.adjVertices.push_back(&v2);

    v2.adjVertices.push_back(&v4);
    v2.adjVertices.push_back(&v5);

    v3.adjVertices.push_back(&v1);
    v3.adjVertices.push_back(&v6);

    v4.adjVertices.push_back(&v3);
    v4.adjVertices.push_back(&v5);
    v4.adjVertices.push_back(&v6);
    v4.adjVertices.push_back(&v7);

    v5.adjVertices.push_back(&v7);

    v7.adjVertices.push_back(&v6);

    std::vector<Vertex*> graph{ &v1,&v2,&v3,&v4,&v5,&v6,&v7 };
    BFS(&v3,graph);
    //std::cout << *v2.path;
    //std::cout << "Shortest path to " << v2 << " from " <<v3<< " has length : " << v2.dist<<'\n';
    //printPath(&v2);


    ////Buidling a weighted graph

    wVertex wv1(1), wv2(2), wv3(3), wv4(4), wv5(5),wv6(6), wv7(7);
    wv1.addEdge(&wv2, 2);
    wv1.addEdge(&wv4, 1);

    wv2.addEdge(&wv5, 10);
    wv2.addEdge(&wv4, 3);

    wv3.addEdge(&wv1, 4);
    wv3.addEdge(&wv6, 5);

    wv4.addEdge(&wv3, 2);
    wv4.addEdge(&wv5, 2);
    wv4.addEdge(&wv6, 8);
    wv4.addEdge(&wv7, 4);

    wv5.addEdge(&wv7, 6);

    wv7.addEdge(&wv6, 1);
   
    std::vector<wVertex*> wgraph{ &wv1, &wv2, &wv3,&wv4, &wv5,&wv6,&wv7 };

    djkstra(&wv3, wgraph);
    std::cout << "Shortest path to " << wv5 << " has a cost:"<<wv5.dist<<" and path: \n";
    printPath(&wv5);


    
}

