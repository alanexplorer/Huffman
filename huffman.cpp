#include "huffman.h"
#include <QDebug>
#define ascii 256

Huffman::Huffman(){

}
bool lessthan(Node *a, Node *b){
    if(a->frequencia == b->frequencia)
        return a->content < b->content;
    return a->frequencia < b->frequencia;
}
//----------------------------------------------------------------------------------//

QByteArray Huffman::fileCod(QByteArray data, QByteArray &trash, QHash<int, QByteArray> codes){

    //Codifica o arquivo com os valores da árvore

    QByteArray codification;
    for(int i = 0; i < data.size(); ++i)
        codification.append(codes[(unsigned char)data.at(i)]);

    //Guarda o lixo em valores de bytes

    for (int i = 0, sum = 0, index = 7; i < codification.size(); ++i, --index) {
        if(codification.at(i) == 49)
            sum+=(1 << index);
        if(index == 0 || i == codification.size()-1){
            trash.append(sum);
            sum = 0;
            index = 8;
        }
    }

    return codification;
}
//----------------------------------------------------------------------------------//
bool Huffman::ifHuffman(QString Huffman){

    QString test1 = ".huff";
    QString test2;
    for (int i = (Huffman.size()-5); i < Huffman.size(); ++i)
        test2.append(Huffman.at(i));

    if(test1 == test2)
        return true;
    else
        return false;
}

//----------------------------------------------------------------------------------//

void Huffman::comprimir(QString entrada, QString saida){

    int count[ascii]={0};

    QFile file(entrada);

    if(!file.open(QIODevice::ReadOnly)){
        cout<<"O arquivo n"<<char(198)<<"o pode ser aberto\n";
        exit(1);
    }
    QByteArray Data; //Recebe todo o conteúdo do arquivo
    while(!file.atEnd()){
        Data.append(file.readLine(1024));
    }
    for (int i = 0; i < Data.size(); ++i) {//guarda a frenquência
        ++count[(unsigned char)Data.at(i)];
    }
    file.close(); // Fecha o arquivo original

    QList<Node*> ListNode; //armazenao conteúdo e a frequência
    Node *node;
    //percorre o array count e guarda no node o conteúdo e a frequência //
    for (int i = 0; i < ascii; ++i) {
        if(count[i]){
            node = new Node((unsigned char)i,0,0, count[i]);
            ListNode.append(node);
        }
    }
    Tree tree; //Criar uma árvore para inserção dos nodes

    while (ListNode.size()!=1) {
        qSort(ListNode.begin(), ListNode.end(), lessthan);
        node = new Node(0, ListNode[0], ListNode[1], ListNode[0]->frequencia + ListNode[1]->frequencia);
        ListNode.removeFirst();
        ListNode.removeFirst();
        ListNode.append(node);
    }
    tree.add(ListNode.at(0));
    //print(node,0);//Imprime a arvore
    QHash<int, QByteArray> cod;

    QByteArray Coding, lixo;
    QByteArray represent = tree.buildTree(node, cod);
    Coding = fileCod(Data, lixo, cod); //representação binária da árvore

    QByteArray DataOut; // recebe o conteúdo codificado
    Size(Coding, DataOut, represent);
    DataOut.append(entrada.size()).append(entrada).append(represent).append(lixo);

    if(saida.isEmpty())
        saida = NameOut(entrada);

    QFile newfile(saida); // Criação do arquivo comprimido
    if(!newfile.open(QIODevice::WriteOnly)){
        cout<< "Ocorreu um erro ao criar o arquivo comprimido !\n";
        exit(1);
    }
    newfile.write(DataOut);
    newfile.close(); // Compressão concluída.

    cout<<"Compress"<<char(198)<<"o realizada !\n";
}

//----------------------------------------------------------------------------------//

//Função q calcula o tamanho do lixo e o tamanho da arvore
void Huffman::Size(QByteArray &codification, QByteArray &Data, QByteArray &represent){
    int lixo = 0; // tamanho do lixo da codificação
    int tree = represent.size(); //tamanho da árvore
    QBitArray binary(16);
    if(codification.size()%8 != 0)
        lixo = 8 - codification.size()%8;
    for (int i = 2; i >= 0; --i) {
        binary.setBit(i, (lixo%2));
        lixo = (lixo >> 1);
    }
    for (int i = 15; i >= 3; --i) {
        binary.setBit(i, (tree%2));
        tree = (tree>>1);
    }
    int value = 0;
    for (int i = 0; i < 8; ++i)
        if(binary.at(i))
            value+=(1 << (7-i));
    Data.append(value);
    value = 0;

    for (int i = 8, c = 1; i < 16; ++i, c+=2)
        if(binary.at(i))
            value+=(1 << (i - c));
    Data.append(value);
}
//----------------------------------------------------------------------------------//

QString Huffman::NameOut(QString Out){

    QDir path(Out);
    QString nameFileOut;
    nameFileOut = path.dirName();
    int i = nameFileOut.size()-1;
    while (nameFileOut.at(i) != '.') {
        nameFileOut.chop(1);
        --i;
    }
    nameFileOut +="huff";
    return nameFileOut;
}
//----------------------------------------------------------------------------------//

void Huffman::print(Node *node,int depth){
    if(node == NULL){
        cout<<endl;
        return;
    }
    print(node->right,depth+1);
    for(int i=0; i < depth; i++)
        cout << "\t";
    cout << node->content <<endl;
    print(node->left,depth+1);
}
//----------------------------------------------------------------------------------//

void Huffman::getHead(QByteArray bytes, int &sizeTrash, int &sizeTree, int &sizeName){

    QBitArray bits(24);
    // Converte de QByteArray para QBitArray
    for(int i=0; i<3; ++i) {
        for(int b=0; b<8;++b) {
            bits.setBit( i*8+b, bytes.at(i)&(1<<(7-b)) );
        }
    }
    for (int i = 0; i < 3; ++i) {
        if(bits.at(i))
            sizeTrash+=(1 << (2 - i) );
    }
    for (int i = 3; i < 16; ++i){
        if(bits.at(i))
            sizeTree+=(1 << (15-i));
    }
    for (int i = 16; i < 24; ++i) {
        if(bits.at(i))
            sizeName+=(1 << (23 - i));
    }
}

//----------------------------------------------------------------------------------//

void Huffman::NewFile(QString Out, Tree &arvore, Node *node,QBitArray bit, QByteArray &code, int trash){

    QFile NewFile(Out);
    if(!NewFile.open(QIODevice::WriteOnly)){
        qFatal("houve um problema para escrever o arquivo");
        //exit(1);
    }
    node = arvore.getRoot();

    const int limit = bit.size() - trash;
    for (int i = 0; i < limit; ++i) {
        if(arvore.leaf(node)){
            code.append(node->content);
            node = arvore.getRoot();
        } else {
            if(bit[i])
                node = node->right;
            else
                node = node->left;
        }
    }
    NewFile.write(code);
    NewFile.close();
//    exit(0);
}

//----------------------------------------------------------------------------------//

void Huffman::descomprimir(QString saida, QString local){
    QFile file(saida);
    if(!file.open(QIODevice::ReadOnly)){
        cout<<"O arquivo comprimido n"<<char(198)<<"o p"<<char(147)<<"de ser aberto !\n";
        exit(1);
    }
    QByteArray CodeCompress, CodTree, Final;
    while(!file.atEnd()){
        CodeCompress.append(file.readLine(1024));
    }
    file.close();
    int sizeTrash = 0, sizeTree = 0, sizeName = 0;
    getHead(CodeCompress, sizeTrash, sizeTree, sizeName);

    for (int i = (3 + sizeName); i < 3 + sizeName + sizeTree; ++i) {
        CodTree.append(CodeCompress.at(i)); //Guarda a codificaçãO do arquivo
    }
    Tree tree_2;
    Node *node = new Node;
    tree_2.add(node);
    tree_2.mountTree(node, CodTree);
    //print(node,0);//Imprime a arvore

    //Decodificação do Lixo -- bit to byte

    int index = CodeCompress.size() - (CodeCompress.size()-3-sizeName-sizeTree);
    QBitArray DecTrash((CodeCompress.size()-3-sizeName-sizeTree)*8);

    for (int j = index, i = 0; j < CodeCompress.size(); ++j, ++i) {
        for (int b = 0; b < 8; ++b)
            DecTrash.setBit(i*8+b, CodeCompress.at(j)&(1<<(7-b)) );
    }

    CodeCompress.remove(0, 3);
    CodeCompress.remove(sizeName, CodeCompress.size()-sizeName);

    QString Out = CodeCompress; //guarda o nome original do arquivo
    if(!local.isEmpty())
        Out = local + Out;

    NewFile(Out, tree_2, node, DecTrash,Final, sizeTrash);

    cout<<"Descompress"<<char(198)<<"o realizada !\n";
}
