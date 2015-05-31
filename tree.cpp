#include "tree.h"


Tree::Tree(){
    root = 0;
}
void Tree::add(Node *node){
    root = node;
}

Node *Tree::getRoot(){
    return root;
}
QByteArray Tree::treeRepresentation(Node *node, QVector<QByteArray> &cod)
{

    if(!node->left && !node->right)
    {
        QByteArray ret;
        if(node->content == 0x21)
        {
            ret.append(0x2A);
            ret.append(0x21);
        }
        else if(node->content == 0x2A)
        {
            ret.append(0x2A);
            ret.append(0x2A);
        }
        else
            ret.append(node->content);
        cod[node->content] = node->code;
        return ret;
    }
    else
    {
        QByteArray codd(node->code);
        node->left->code = codd.append("0");
        codd.remove(codd.size() - 1, 1);
        node->right->code = codd.append("1");
    }
    return QByteArray().append(0x21).append(treeRepresentation(node->left, cod))
            .append(treeRepresentation(node->right, cod));
}

QByteArray Tree::treeRepresentation(QVector<QByteArray> &cod)
{
    return treeRepresentation(root, cod);
}
