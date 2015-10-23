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
        this->content = 0;
        this->left = 0;
        this->right = 0;
        this->frequencia = 0;
    }
    Node(unsigned char content, Node* left, Node* right, int frequencia){
        this->content = content;
        this->left = left;
        this->right = right;
        this->frequencia = frequencia;
    }
};


#endif // NODE

