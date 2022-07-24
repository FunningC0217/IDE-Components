#include "edit.hpp"
#include "private/edit_p.hpp"

Edit::Edit()
    : d (new EditPrivate(this))
{

}

Edit::~Edit()
{
    if (d)
        delete d;
}

void Edit::setFileUrl(const QUrl &url)
{
    d->fileUrl = url;
}

QUrl Edit::fileUrl()
{
    return d->fileUrl;
}

bool Edit::loadFile()
{
    return true;
}

bool Edit::releaseFile()
{
    return true;
}
