#ifndef CPP_H
#define CPP_H

#include <QObject>
#define PROPERTY(name,type) \
    Q_PROPERTY(type name READ name WRITE set##name NOTIFY name##Changed)\
    private:\
    type m_##name;\
    public:\
    type name() const{\
    return m_##name;\
    }\
    void set##name(const type &v){\
    if (m_##name!=v){\
    m_##name=v;\
    emit name##Changed();\
    }\
    }
class CPP : public QObject
{
    Q_OBJECT
public:
    PROPERTY(result,QString)
    PROPERTY(name,QString)
    explicit CPP(QObject *parent = 0);
    Q_INVOKABLE void gen(const QString& input,const QString& func);
    Q_INVOKABLE QString readFile(const QUrl& url);
    Q_INVOKABLE void saveFile(const QString& str);
    Q_INVOKABLE void run();
signals:
    void resultChanged();
    void nameChanged();
public slots:
};

#endif // CPP_H
