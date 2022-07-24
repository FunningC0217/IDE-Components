#pragma once

#include <QObject>
#include <QUrl>

class Edit;
class EditPrivate : public QObject
{
    Q_OBJECT
    friend class Edit;
    Edit *const q;
    QUrl fileUrl;
    EditPrivate(Edit *q) : q(q) {}
};
