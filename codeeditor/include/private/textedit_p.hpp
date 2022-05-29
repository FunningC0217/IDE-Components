#ifndef TEXTEDITPRIVATE_H
#define TEXTEDITPRIVATE_H

#include <QObject>

class TextEdit;
class TextEditPrivate : public QObject
{
    Q_OBJECT
    friend class TextEdit;
    const TextEdit *q;
    QString filePath;

    TextEditPrivate(TextEdit *q);
};

#endif // TEXTEDITPRIVATE_H
