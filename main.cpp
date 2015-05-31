#include <QCoreApplication>
#include "huffman.h"
#include "tree.h"

int main()
{
    Huffman Huff;

    Huff.comprimir("in.txt","out.huff");

    return 0;
}
