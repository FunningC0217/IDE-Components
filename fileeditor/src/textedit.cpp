#include "private/textedit_p.hpp"
#include "textedit.h"
#include <QUrl>

TextEdit::TextEdit(QWidget *parent)
    : QTextEdit(parent)
    , Edit()
    , d(new TextEditPrivate(this))
{
    QObject::connect(d, &TextEditPrivate::readedLines,
                     [=](int lineCount,  const QByteArray &lines){
        append(lines);
    });
}

TextEdit::~TextEdit()
{
     releaseFile();
     if (d)
         delete d;
}

bool TextEdit::loadFile()
{
    if (!fileUrl().isEmpty()) {
        d->loadFileAsyn(fileUrl(), 4);
        return true;
    }
    return false;
}

bool TextEdit::releaseFile()
{
    return true;
}

TextEditPrivate::TextEditPrivate(TextEdit *q)
    : q (q)
{
    readThread.setPriority(QThread::Priority::LowPriority);
    reader.moveToThread(&readThread);
    QObject::connect(&reader, &TextReader::readedLines,
                     this, &TextEditPrivate::readedLines);
    QObject::connect(&reader, &TextReader::readedError,
                     this, &TextEditPrivate::readedError);
}

TextEditPrivate::~TextEditPrivate()
{

}

void TextEditPrivate::loadFileAsyn(const QUrl &url, int lineCount)
{
    reader.readLines(lineCount, url);
}
