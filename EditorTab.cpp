#include <QIcon>
#include <QTextEdit>
#include <QScrollArea>
#include <QSplitter>
#include <QGridLayout>
#include "EditorTab.h"
#include <QDebug>
#include "ASMHighlighter.h"
#include "Assembler.h"
#include "Constants.h"

class EditorTabPrivate
{
public:
    QIcon icon;
    QString title;
};

QString EditorTab::getASM()
{
    return asmEdit->toPlainText();
}

QString EditorTab::getBinary()
{
    return binaryEdit->toPlainText();
}

char* EditorTab::getMemory()
{
    return memory;
}

void EditorTab::changeState()
{
    isEmpty = false;
    isCompiled = false;
}

bool EditorTab::compile()
{
    QString binarycode = Assembler::Compile(asmEdit->toPlainText(), memory, MAX_ADD);

    if (!binarycode.isNull())
    {
        binaryEdit->setText(binarycode);
        return true;
    }
    return false;
}

EditorTab::EditorTab(QWidget *parent)
    : QWidget(parent)
{
    isEmpty = true;
    isCompiled = false;
    d = new EditorTabPrivate();

    QSplitter *mainsplitter = new QSplitter;

    QScrollArea *binaryarea = new QScrollArea;
    binaryEdit = new QTextEdit;
    binaryEdit->setLineWrapMode(QTextEdit::NoWrap);
    binaryEdit->setReadOnly(true);
    binaryarea->setWidget(binaryEdit);
    binaryarea->setWidgetResizable(true);

    QScrollArea *asmarea = new QScrollArea;
    asmEdit = new QTextEdit;
    asmEdit->setLineWrapMode(QTextEdit::NoWrap);
    asmarea->setWidget(asmEdit);
    asmarea->setWidgetResizable(true);
    ASMHighlighter *highlighter = new ASMHighlighter(asmEdit->document());

    mainsplitter->addWidget(asmarea);
    mainsplitter->addWidget(binaryarea);

    QGridLayout *layout = new QGridLayout;
    layout->addWidget(mainsplitter);

    setLayout(layout);

    connect(asmEdit, SIGNAL(textChanged()), SLOT(changeState()));
}

EditorTab::~EditorTab()
{
    delete d;
}

QIcon EditorTab::icon() const
{
    return d->icon;
}

void EditorTab::setIcon(const QIcon &icon)
{
    d->icon = icon;
    emit iconChanged();
}

QString EditorTab::title() const
{
    return d->title;
}

void EditorTab::setTitle(const QString &title)
{
    d->title = title;
    emit titleChanged();
}

QImage EditorTab::renderImage()
{
    QImage image(size(), QImage::Format_RGB32);
    render(&image, QPoint(0, 0), QRegion(0, 0, size().width(), size().height()));
    return image;
}
