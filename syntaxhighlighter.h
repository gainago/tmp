#ifndef SYNTAXHIGHLIGHTER_H
#define SYNTAXHIGHLIGHTER_H

#include <QSyntaxHighlighter>

class SyntaxHighlighter : public QSyntaxHighlighter
{
    Q_OBJECT
public:
    SyntaxHighlighter(QTextDocument* parent = 0);

    void highlightBlock(const QString&);

};

#endif // SYNTAXHIGHLIGHTER_H
