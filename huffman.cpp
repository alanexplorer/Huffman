#include "huffman.h"
#define ascii 256

Huffman::Huffman(){

}
bool lessthan(Node *a, Node *b){
    if(a->frequencia == b->frequencia)
        return a->content < b->content;
    return a->frequencia < b->frequencia;
}
//----------------------------------------------------------------------------------//

QByteArray Huffman::fileCod(QByteArray data, QVector<QByteArray> codes){
    QByteArray codification;
    for(int i = 0; i < data.size(); ++i)
        codification.append(codes[(unsigned char)data.at(i)]);
    return codification;
}
//----------------------------------------------------------------------------------//

void Huffman::comprimir(QString entrada){

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
        ListNode.removeAt(0);
        ListNode.removeAt(0);
        ListNode.append(node);
    }
    tree.add(ListNode.at(0));
    //print(node,0);//Imprime a arvore
    QVector<QByteArray>cod(ascii); //guarda o valor de cada byte em bit na árvore

    QByteArray Coding, lixo;
    QByteArray represent = tree.treeRepresent(node, cod);
    Coding = fileCod(Data, cod); //Vetor com a representação binária da árvore

    for(int i = 0,  k = 7, j = 0; i < Coding.size(); ++i, --k){

        if(Coding.at(i) == 49) // 49 = 1 na tabela ascii
            j = j + (1 << k);
        if(k==0 || i == Coding.size() -1){
            lixo.append(j);
            j = 0;
            k = 8;
        }
    }
    QByteArray DataOut; // recebe o conteúdo codificado
    Size(Coding, DataOut, represent);
    DataOut.append(entrada.size()).append(entrada).append(represent).append(lixo);
    QString s;
    s = NameOut(entrada);
    QFile newfile(s); // Criação do arquivo comprimido
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

    int i = Out.size()-1;
    while (Out.at(i) != '.') {
        Out.chop(1);
        --i;
    }
    Out += "huff";
    return Out;
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

void Huffman::decode(QBitArray &bit,QByteArray bytes, int index){

    for (int j = index, i = 0; j < bytes.size(); ++j, ++i) {
        for (int b = 0; b < 8; ++b) {
            bit.setBit(i*8+b, bytes.at(j)&(1<<(7-b)) );
        }
    }
}

//----------------------------------------------------------------------------------//

void Huffman::NewFile(QString Out, Tree &arvore, Node *node,QBitArray bit, QByteArray &code, int trash){

    QFile NewFile(Out);
    if(!NewFile.open(QIODevice::WriteOnly)){
        cout<<"O arquivo n"<<char(198)<<"o pode ser aberto\n";
        exit(1);
    }
    int i;
    for (node = arvore.getRoot(), i = 0; i < bit.size()- trash; ++i) {
        if(node->left && node->right){
            if(!bit[i])
                node = node->left;
            else
                node = node->right;
        }
        if(!node->left && !node->right){
            code.append(node->content);
            node = arvore.getRoot();
        }
    }
    NewFile.write(code);
    NewFile.close();
}

//----------------------------------------------------------------------------------//

void Huffman::descomprimir(QString saida){
    QFile file(saida);
    if(!file.open(QIODevice::ReadOnly)){
        cout<<"O arquivo comprimido n"<<char(198)<<"o p"<<char(147)<<"de ser aberto !\n";
        exit(1);
    }
    QByteArray CodeCompress, CodTree, Final;
    //CodeCompress = file.readAll();
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
    tree_2.DescompressTree(node, CodTree);
    //print(node,0);//Imprime a arvore
    int count = CodeCompress.size()-3-sizeTree - sizeName;
    int index = CodeCompress.size() - count;
    QBitArray DecTrash(count*8);
    decode(DecTrash,CodeCompress, index);
    CodeCompress.remove(0, 3);
    CodeCompress.remove(sizeName, CodeCompress.size()-sizeName);
    QString Out = CodeCompress;
    NewFile(Out, tree_2, node, DecTrash,Final, sizeTrash);
    cout<<"Descompress"<<char(198)<<"o realizada !\n";
}
