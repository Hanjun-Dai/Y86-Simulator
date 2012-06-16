#ifndef ASMHIGHLIGHTER_H
#define ASMHIGHLIGHTER_H

#include <QSyntaxHighlighter>

class QTextDocument;
class ASMHighlighter : public QSyntaxHighlighter
{
    Q_OBJECT
public:
    explicit ASMHighlighter(QTextDocument * parent);

protected:
    void highlightBlock(const QString &text);

signals:
    
public slots:

private:
    struct HighlightingRule
    {
        QRegExp pattern;
        QTextCharFormat format;
    };

    QVector<HighlightingRule> highlightingRules;

    QRegExp commentStartExpression;
    QRegExp commentEndExpression;

    QTextCharFormat singleLineCommentFormat;
    QTextCharFormat multiLineCommentFormat;
    QTextCharFormat commentFormat;
    QTextCharFormat keywordFormat;

};

#endif // ASMHIGHLIGHTER_H
