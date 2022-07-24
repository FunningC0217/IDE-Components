#pragma once

#include <QUrl>

class EditPrivate;
class Edit
{
    EditPrivate *const d;
public:
    explicit Edit();
    virtual ~Edit();
protected:
    virtual void setFileUrl(const QUrl &url);
    virtual QUrl fileUrl();
    virtual bool loadFile();
    virtual bool releaseFile();
};
