//

//
#include <iostream>
#include <algorithm>
#include <stack>
#include <queue>
#include "cNode.h"
using namespace std;
template <typename T>
class cAvlTrees{
public:
    cNode<T> *root = nullptr;
    cAvlTrees(T x){
        root = new cNode<T>(x);
    }
    bool Find(T x,cNode<T> **&p,stack< cNode<T>* > &path){
        for(p=&root;*p&&(*p)->x!=x;p=&((*p)->m_nodes[(*p)->x<x])){
            path.push(*p);
        }
        return *p != 0;
    }
    void CalcBalance(cNode<T> *node){
        //cout<<"Calc Balance: "<<node->x<<endl;
        //cout<<"Hijos: "<<node->m_nodes[0]<<" - "<<node->m_nodes[1]<<endl;
        if(node->m_nodes[0]!=0&&node->m_nodes[1]!=0){
            //cout<<"Entro 1"<<endl;
            node->b = node->m_nodes[1]->h - node->m_nodes[0]->h;
        }else if(node->m_nodes[1]!=0&&node->m_nodes[0]==0){
            //cout<<"Entro 2"<<endl;
            node->b = node->m_nodes[1]->h;
        }else if (node->m_nodes[0]!=0&&node->m_nodes[1]==0){
            //cout<<"Entro 3"<<endl;
            node->b = node->m_nodes[0]->h*-1;
        }else{
            node->b=0;
        }
        //cout<<"New Balance: "<<node->b<<endl;

    }
    void CalcHeigth(cNode<T> *node){
        //cout<<"Calc Heigth: "<<node->x<<endl;
        //cout<<"Hijos: "<<node->m_nodes[0]<<" - "<<node->m_nodes[1]<<endl;
        if(node->m_nodes[0]!=0&&node->m_nodes[1]!=0){
            node->h = max(node->m_nodes[0]->h,node->m_nodes[1]->h)+1;
        }else if(node->m_nodes[1]!=0&&node->m_nodes[0]==0){
            node->h = node->m_nodes[1]->h +1;
        }else if (node->m_nodes[0]!=0&&node->m_nodes[1]==0){
            node->h = node->m_nodes[0]->h +1;
        }else{
            node->h=1;
        }
        //cout<<"New Heigth: "<<node->h<<endl;
    }
    void RotateLeft(cNode<T> * oldFather, cNode<T> * father, cNode<T> * son,stack<cNode<T> *>path){
        //cout<<"start balance"<<endl;
        cNode <T> *temp = father;
        father=son;
        temp->m_nodes[1] = son->m_nodes[0];
        father->m_nodes[0] = temp;
        CalcHeigth(temp);
        CalcBalance(temp);
        CalcHeigth(father);
        CalcBalance(father);
        if(temp==root){
            root=father;
        }else{
            oldFather->m_nodes[oldFather->x<father->x] = father;
        }
        updateHeigthsBalance(path);
    }
    void RotateRigth(cNode<T> * oldFather, cNode<T> * father, cNode<T> * son,stack<cNode<T> *>path){
        cNode <T> *temp = father;
        father=son;
        temp->m_nodes[0] = son->m_nodes[1];
        father->m_nodes[1] = temp;
        CalcHeigth(temp);
        CalcBalance(temp);
        CalcHeigth(father);
        CalcBalance(father);
        if(temp==root){
            root=father;
        }else{
            oldFather->m_nodes[oldFather->x<father->x] = father;
        }
        updateHeigthsBalance(path);
    }
    void RotateLeftRigth(cNode<T> * oldFather, cNode<T> * father, cNode<T> * son,stack<cNode<T> *>path){
        cNode <T> *temp = son->m_nodes[0];
        cNode<T> *temp_subtree0 = temp->m_nodes[0];
        cNode<T> *temp_subtree01 = temp->m_nodes[1];
        cNode<T> *tempfather = father;
        father=temp;
        father->m_nodes[0] = tempfather;
        father->m_nodes[1] = son;
        tempfather->m_nodes[1] = temp_subtree0;
        son->m_nodes[0] = temp_subtree01;
        CalcHeigth(tempfather);
        CalcBalance(tempfather);
        CalcHeigth(son);
        CalcBalance(son);
        CalcHeigth(father);
        CalcBalance(father);
        //cout<<"Llego"<<endl;
        if(tempfather==root){
            root=father;
        }else{
            oldFather->m_nodes[oldFather->x<father->x] = father;
        }
        updateHeigthsBalance(path);

    }
    void RotateRigthLeft(cNode<T> * oldFather, cNode<T> * father, cNode<T> * son,stack<cNode<T> *>path){
        cNode <T> *temp = son->m_nodes[1];
        cNode<T> *temp_subtree0 = temp->m_nodes[0];
        cNode<T> *temp_subtree01 = temp->m_nodes[1];
        cNode<T> *tempfather = father;
        father=temp;
        father->m_nodes[0] = son;
        father->m_nodes[1] = tempfather;
        tempfather->m_nodes[0] = temp_subtree01;
        son->m_nodes[1] = temp_subtree0;
        CalcHeigth(tempfather);
        CalcBalance(tempfather);
        CalcHeigth(son);
        CalcBalance(son);
        CalcHeigth(father);
        CalcBalance(father);
        if(tempfather==root){
            root=father;
        }else{
            oldFather->m_nodes[oldFather->x<father->x] = father;
        }
        //cout<<"Llego"<<endl;
        updateHeigthsBalance(path);

    }
    void updateHeigthsBalance(stack< cNode<T> *>path){
        cNode<T> * temp = nullptr;
        //  cout<<"size"<<path.size()<<endl;

        while(!path.empty()){
            temp = path.top();
            path.pop();
            CalcHeigth(temp);
            CalcBalance(temp);
        }
    }
    void Balance(stack< cNode<T> *> path){
        cNode<T> *temp = nullptr;
        cNode<T> *temp2 = nullptr;
        cNode<T> *temp3 = nullptr;
        //cout<<"size: "<<path.size()<<endl;
        temp = path.top();
        path.pop();

        while(!path.empty()){
            temp2 = path.top();
            path.pop();
            CalcHeigth(temp2);
            CalcBalance(temp2);
            if(temp2->b==2&&temp->b==1){
                if (!path.empty()){
                    temp3 = path.top();
                }
                RotateLeft(temp3,temp2,temp,path);
                break;
            }else if(temp2->b==-2&&temp->b==-1){
                if (!path.empty()){
                    temp3 = path.top();
                }
                RotateRigth(temp3,temp2,temp,path);
                break;
            }else if(temp2->b==2&&temp->b==-1){
                if (!path.empty()){
                    temp3 = path.top();
                }
                RotateLeftRigth(temp3,temp2,temp,path);
                break;
            }else if(temp2->b==-2&&temp->b==1){
                if (!path.empty()){
                    temp3 = path.top();
                }
                RotateRigthLeft(temp3,temp2,temp,path);
                break;
            }
            temp = temp2;
        }
    }

    void BalanceDelete(stack< cNode<T> * > path){
        cNode<T> *temp = nullptr;
        cNode<T> *temp2 = nullptr;
        cNode<T> *temp3 = nullptr;
        int hIzquiera = 0;
        int hDerecha = 0;
        while(!path.empty()){
            temp2 = path.top();
            path.pop();
            CalcHeigth(temp2);
            CalcBalance(temp2);
            if(temp2->b==2) {
                if(temp2->m_nodes[0]&&temp2->m_nodes[1]){
                    hIzquiera=temp2->m_nodes[0]->h;
                    hDerecha = temp2->m_nodes[1]->h;
                }else if(temp2->m_nodes[1]){
                    hDerecha = temp2->m_nodes[1]->h;
                }else if(temp2->m_nodes[0]){
                    hIzquiera=temp2->m_nodes[0]->h;
                }
                if (hIzquiera >= hDerecha){
                    if (!path.empty()) {
                        temp3 = path.top();
                    }
                    temp = temp2->m_nodes[0];
                    RotateLeftRigth(temp3, temp2, temp, path);
                    break;
                }else{
                    if (!path.empty()){
                        temp3 = path.top();
                    }
                    temp = temp2->m_nodes[1];
                    RotateLeft(temp3,temp2,temp,path);
                    break;
                }
            }else if(temp2->b==-2){
                if(temp2->m_nodes[0]&&temp2->m_nodes[1]){
                    hIzquiera=temp2->m_nodes[0]->h;
                    hDerecha = temp2->m_nodes[1]->h;
                }else if(temp2->m_nodes[1]){
                    hDerecha = temp2->m_nodes[1]->h;
                }else if(temp2->m_nodes[0]){
                    hIzquiera=temp2->m_nodes[0]->h;
                }
                if(hIzquiera >= hDerecha){
                    if (!path.empty()) {
                        temp3 = path.top();
                    }
                    temp = temp2->m_nodes[0];
                    RotateRigthLeft(temp3,temp2,temp,path);
                    break;
                }else{
                    if (!path.empty()){
                        temp3 = path.top();
                    }
                    temp = temp2->m_nodes[1];
                    RotateRigth(temp3,temp2,temp,path);
                    break;
                }
            }
            temp = temp2;
        }
    }
    bool Insert(T x){
        cNode<T> **p;
        stack< cNode<T>* > path;
        cNode<T> *temp;
        //cout<<"Insert"<<x<<endl;
        if(Find(x,p,path)){
            return 0;
        }
        *p = new cNode<T>(x);
        path.push(*p);
        Balance(path);
        return 1;
    }
    bool Remove(T x){
        cNode<T> **p;
        stack< cNode<T>* > path;
        stack<cNode<T>*>deletePath;
        if(Find(x,p,path)) {
            if ((*p)->m_nodes[0] && (*p)->m_nodes[1]) {
                cNode<T> **q = Change(p, path);
                (*p)->x = (*q)->x;
                p = q;
            }
            cNode<T> *t = *p;
            *p = (*p)->m_nodes[(*p)->m_nodes[1] != 0];
            if (path.top() == 0) {
                path.pop();
            }
            updateHeigthsBalance(path);
            BalanceDelete(path);
            return 1;
        }
        return 0;

    }

    cNode<T> ** Change(cNode<T> **p,stack< cNode<T> *>&path){
        cNode<T> **temp = p;
        cNode<T> **tempAnt = nullptr;
        path.push(*temp);
        temp = &((*temp)->m_nodes[1]);
        while(*temp){
            path.push(*temp);
            tempAnt = temp;
            temp = &((*temp)->m_nodes[0]);
        }
        return tempAnt;
    }
    void imprimir() {
        cNode<T> * first = root;
        queue< cNode<T> *> nodes;
        nodes.push(first);
        nodes.push(nullptr);
        while(!nodes.empty()){
            if(nodes.front() == nullptr){
                cout<<endl;
            }else {
                //cout<< nodes.front()->x<<" ";
                cout << nodes.front()->x <<" b:"<<nodes.front()->b<< " "<<" h:"<<nodes.front()->h<<" ";
                if (nodes.front()->m_nodes[0] != 0)
                    nodes.push(nodes.front()->m_nodes[0]);
                if (nodes.front()->m_nodes[1] != 0)
                    nodes.push(nodes.front()->m_nodes[1]);
                nodes.push(nullptr);
            }
            nodes.pop();
        }
        cout<<"root actual: "<<root->x<<endl;

    }

};