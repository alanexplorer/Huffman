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
bool Tree::leaf(Node *node){
    if(node->left && node->left)
        return false;
    else
        return true;
}
//----------------------------------------------------------------------------------//
QByteArray Tree::buildTree(Node *node, QHash<int, QByteArray> &cod){

    if(leaf(node)){
        QByteArray represent;
        if(node->content == 0x2A){
            represent.append(0x21).append(0x2A);
        }
        else if(node->content == 0x21){
            represent.append(0x21).append(0x21);
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
    return QByteArray().append(0x2A).append(buildTree(node->left, cod)).append(buildTree(node->right, cod));
}
//----------------------------------------------------------------------------------//
void Tree::mountTree(Node *node, QByteArray &data){
   if(data.at(0) == 0x2A){
       node->left = new Node;
       node->right = new Node;
       data.remove(0,1);
       mountTree(node->left, data);
       data.remove(0,1);
       mountTree(node->right, data);
   }
   else if(data.at(0) == 0x21){
       node->content = data.at(1);
       data.remove(0,1);
   }
   else
       node->content = data.at(0);
}
