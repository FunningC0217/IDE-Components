#ifndef TEXTEDITOR_H
#define TEXTEDITOR_H

#include "edit.hpp"
#include <QTextEdit>

class TextEditPrivate;
class TextEdit : public QTextEdit, public Edit
{
    Q_OBJECT
    TextEditPrivate *const d;
public:
    explicit TextEdit(QWidget *parent = nullptr);
    virtual ~TextEdit();

protected:
    virtual bool loadFile();
    virtual bool releaseFile();
};

#endif // TEXTEDITOR_H
