#pragma once

#include <QTextEdit>

class TextEditPrivate;
class TextEdit : public QTextEdit
{
    Q_OBJECT
    TextEditPrivate *const d;

public:
    explicit TextEdit(QWidget *parent = nullptr);
    virtual ~TextEdit();
    void setFilePath(const QString &filePath);
    QString filePath();
    void setFileUrl(const QUrl &url);
    QUrl fileUrl();

protected:
    virtual bool loadFile();
    virtual bool releaseFile();
};
