#ifndef TEXTEDIT_P_HPP
#define TEXTEDIT_P_HPP

#include <QFile>
#include <QObject>
#include <QThread>
#include <QUrl>

class TextEdit;
class TextReader : public QObject
{
    Q_OBJECT
public:
    TextReader(){}

signals:
    void readedError(QFile::FileError err, const QString &errorString);
    void readedLines(int lineCount, const QByteArray &lines);

public slots:
    void readLines(int lineCount, const QUrl &url) {
        if (url.isLocalFile()) {
            QFile file(url.toLocalFile());
            if (!file.open(QFile::ReadOnly)) {
                emit readedError(file.error(), file.errorString());
                return;
            }
            QByteArray lines;
            int linesNum = 0;
            while (file.canReadLine()) {
                lines += file.readLine();
                lineCount ++;
                if (linesNum == lineCount){
                    emit readedLines(linesNum, lines);
                    lines.clear();
                    linesNum = 0;
                }
            }
            if (linesNum > 0)
                emit readedLines(linesNum, lines);
        }
    }

protected:
    QFile localFile;
};

class TextEditPrivate : public QObject
{
    Q_OBJECT
    friend class TextEdit;
    TextEdit *const q;
    QThread readThread;
    TextReader reader;
public:
    TextEditPrivate(TextEdit *q);
    virtual ~TextEditPrivate();
    void loadFileAsyn(const QUrl &url, int lineCount);
signals:
    void readedLines(int lineCount, const QByteArray &lines);
    void readedError(QFile::FileError err, const QString &errorString);
};

#endif // TEXTEDIT_P_HPP
