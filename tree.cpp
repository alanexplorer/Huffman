#include "tree.h"
#include <QDebug>

Tree::Tree(){
    root = 0;
}
//----------------------------------------------------------------------------------//
void Tree::add(Node *node){
    root = node;
}
//----------------------------------------------------------------------------------//
Node *Tree::getRoot(){
    return root;
}
//----------------------------------------------------------------------------------//
QByteArray Tree::treeRepresent(Node *node, QVector<QByteArray> &cod){

    if(!node->left && !node->right){
        QByteArray represent;
        if(node->content == 0x21){
            represent.append(0x2A).append(0x21);
        }
        else if(node->content == 0x2A){
            represent.append(0x2A).append(0x2A);
        }
        else
            represent.append(node->content);
        cod[node->content] = node->code;
        return represent;
    }
    else{
        QByteArray auxiliar(node->code);
        node->left->code = auxiliar.append("0");
        auxiliar.remove(auxiliar.size() - 1, 1);
        node->right->code = auxiliar.append("1");
    }
    return QByteArray().append(0x21).append(treeRepresent(node->left, cod)).append(treeRepresent(node->right, cod));
}
//----------------------------------------------------------------------------------//
void Tree::DescompressTree(Node *node, QByteArray &data){
   if(data.at(0) == 0x21){
       node->left = new Node;
       node->right = new Node;
       data.remove(0,1);
       DescompressTree(node->left, data);
       data.remove(0,1);
       DescompressTree(node->right, data);
   }
   else if(data.at(0) == 0x2A){
       node->content = data.at(1);
       data.remove(0,1);
   }
   else
       node->content = data.at(0);
}
