#ifndef NODE
#define NODE
#include<QByteArray>

class Node
{
public:
    Node *left;
    Node *right;
    unsigned char content;
    int frequencia;
    QByteArray code;
    Node(){
        content = 0;
        left = 0;
        right = 0;
        frequencia = 0;
    }
    Node(unsigned char content, Node* left, Node* right, int frequencia){
        this->content = content;
        this->left = left;
        this->right = right;
        this->frequencia = frequencia;
    }
};


#endif // NODE

