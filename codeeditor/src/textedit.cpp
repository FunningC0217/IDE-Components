#include "textedit.hpp"
#include "private/textedit_p.hpp"

TextEdit::TextEdit(QWidget *parent)
    : QTextEdit(parent)
    , d (new TextEditPrivate(this))
{

}

TextEdit::~TextEdit()
{

}

void TextEdit::setFilePath(const QString &filePath)
{
    d->filePath = filePath;
}

QString TextEdit::filePath()
{
    return d->filePath;
}

void TextEdit::setFileUrl(const QUrl &url)
{
    setFilePath(url.toLocalFile());
}

QUrl TextEdit::fileUrl()
{
    return QUrl::fromLocalFile(filePath());
}

bool TextEdit::loadFile()
{
    return true;
}

bool TextEdit::releaseFile()
{
    return true;
}
