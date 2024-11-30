#include "syntaxhighlighter.h"

SyntaxHighlighter::SyntaxHighlighter(QTextDocument* parent) : QSyntaxHighlighter(parent)
{}

void SyntaxHighlighter::highlightBlock(const QString& str)
{
    /*for(int i = 0; i < str.size(); i++){

        if(!str.at(i).isDigit() ){

            setFormat(i, 1, Qt::red);
        }
    }*/

    bool isOk = 1;
    str.toInt(&isOk, 10);

    if(!isOk){
        setFormat(0, str.size(), Qt::red);
    }
}
