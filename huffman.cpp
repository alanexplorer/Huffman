#include "huffman.h"
#define ascii 256

Huffman::Huffman()
{

}
bool lessthan(Node *a, Node *b)
{
    if(a->frequency == b->frequency)
        return a->content < b->content;
    return a->frequency < b->frequency;
}
QByteArray Huffman::fileCod(QByteArray data, QVector<QByteArray> codes){
    QByteArray codification;
    for(int i = 0; i < data.size(); ++i)
        codification.append(codes[(unsigned char)data.at(i)]);
    return codification;
}


void Huffman::comprimir(QString entrada, QString saida){

    int count[ascii]={0};

    QFile file(entrada);

    if(!file.open(QIODevice::ReadOnly)){
        std::cout<<"O arquivo n"<<char(198)<<"o pode ser aberto\n";
        exit(1);
    }
    QByteArray Line, Data;
    while(!file.atEnd()){

        Line = file.readLine(1024);
        Data.append(Line);

        for (int i = 0; i < Line.size(); ++i) {
            ++count[(unsigned char)Line.at(i)];
        }
    }

    QList<Node*> ListNode;
    Node *node;
    for (int i = 0; i <ascii; ++i) {
        if(count[i]){
            node = new Node((unsigned char)i,0,0, count[i]);
            ListNode.append(node);
        }
    }
    Tree tree;

    while (ListNode.size()!=1) {
        qSort(ListNode.begin(), ListNode.end(), lessthan);
        node = new Node(0, ListNode[0], ListNode[1], ListNode[0]->frequency + ListNode[1]->frequency);
        ListNode.removeAt(0);
        ListNode.removeAt(0);
        ListNode.append(node);
    }
    tree.add(ListNode.at(0));
    //print(node,0);//Imprime a arvore
    QVector<QByteArray>cod(ascii);
    QByteArray Coding;
    QByteArray represent = tree.treeRepresentation(cod);
    QByteArray lixo;
    Coding = fileCod(Data, cod); //Vetor com os valores em byte

    for(int i = 0,  k = 7, j = 0; i < Coding.size(); ++i, --k){

        if(Coding.at(i) == 49)
            j = j + (1 << k);
        if(k==0 || i == Coding.size() -1){
            lixo.append(j);
            j = 0;
            k = 8;
        }
    }
    Line.clear();
    generateFileCod(Coding, Line, represent);
    Line.append(entrada.size()).append(entrada).append(represent).append(lixo);
    file.close(); // Fecha o arquivo original

    QString s;

    s = NameOut(entrada);
    QFile newfile(s); // Criação do arquivo comprimido
    if(!newfile.open(QIODevice::WriteOnly))
    {
        qDebug() << "Ocorreu um erro ao abrir o arquivo da compressão.";
        exit(1);
    }
    newfile.write(Line);
    newfile.close(); // Compressão concluída.

    //--------------------------------------------------------------------//

//        for (int i = 0; i < represent.size(); ++i) {
//            cout<<represent.at(i);
//        }
//        cout<<endl;
//        for (int i = 0; i < Coding.size(); ++i) {
//            cout<<Coding.at(i);
//        }
        cout<<endl;
        for (int i = 0; i < Line.size(); ++i) {
            cout<<Line.at(i);
        }
        cout<<endl;

    //-------------------------------------------------------------------//

    cout<<"Compress"<<char(198)<<"o realizada !\n";
}

void Huffman::generateFileCod(QByteArray &codification, QByteArray &fileData, QByteArray &treeSize){
    int lixo=0; // tamanho do lixo da codificação
    if(codification.size()%8 != 0)
        lixo = 8 - codification.size()%8;
    for(int i = 0, k = 2, j = 0, g = 0; i < 16; ++i, --k){
        if(i <= 2){
            if(g + (1 << k) <= lixo){
                j += (1 << (k + 5));
                g += (1 << k);
            }
            if(i == 2){
                g = 0;
                k = 13;
            }
        }
        else{
            if(g + (1 << k) <= treeSize.size()){
                if(i <= 7)
                    j += (1 << (k - 8));
                else
                    j += (1 << k);
                g += (1 << k);
            }
            if(i == 7){
                fileData.append(j);
                j = 0;
            }
            if(g == treeSize.size()){
                fileData.append(j);
                break;
            }
        }
    }
}

QString Huffman::NameOut(QString Out)
{
    QString nameFileOut;
    int i;
    for(i = Out.size()-1 ; i > 0 && Out.at(i)!= '/'; i--);
    if(i > 0 && Out.at(i) == '/') {
        i++;
    }
    for( ; i < Out.size() && Out.at(i) != '.'; i++) {
         nameFileOut.append(Out.at(i));
    }
    nameFileOut += ".huff";
    return nameFileOut;
}

void Huffman::print(Node *node,int depth)
{
    if(node == NULL){
        cout << std::endl;
        return;
    }
    print(node->right,depth+1);
    for(int i=0; i < depth; i++)
        cout << "\t";
    cout << node->content << std::endl;
    print(node->left,depth+1);
}
