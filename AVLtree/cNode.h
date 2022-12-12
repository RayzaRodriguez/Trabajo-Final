//
// Created by paulo on 12/11/17.
//
template <typename  N>
class cNode{
public:
    N x;
    cNode<N> *m_nodes[2];
    int b;
    int h;
    cNode(N x){
        m_nodes[0]=m_nodes[1]=0;
        this->x = x;
        b = 0;
        h = 1;
    }
};