#include "cpp.h"
#include <QUrl>
#include <QFile>
#include <QTextStream>
#include <QDebug>
#include <QProcess>
CPP::CPP(QObject *parent) : QObject(parent)
{

}

void CPP::gen(const QString& input,const QString &func){
    QFile gen("gen.cpp");
    qDebug()<<gen.open(QIODevice::WriteOnly);
    QTextStream gens(&gen);
    gens<<"#include <iostream>\n"
          "using namespace std;\n"
       <<func<<
         "\n\int main(int argc, char *argv[])\n\
    {\n\
         cout<<getTrueForm("<<input<<");\n\
         return 0;\n\
}";
         gen.close();
}
QString CPP::readFile(const QUrl& url){
    QFile src(url.toLocalFile());
    qDebug()<<src.open(QIODevice::ReadOnly);
    return QString::fromLocal8Bit(src.readAll());
}
void CPP::saveFile(const QString &str){
    QFile f("func.cpp");
    f.open(QIODevice::WriteOnly);
    QTextStream s(&f);
    s<<str;
    f.close();
}

void CPP::run(){
    QProcess pro;
    pro.start("clang++ -o gen.exe gen.cpp");
    pro.waitForReadyRead();
    qDebug()<<QString::fromLocal8Bit(pro.readAllStandardOutput());
    pro.waitForFinished();
    pro.setProgram("gen.exe");
    pro.start("gen.exe");
    pro.waitForReadyRead();
    setresult(QString::fromLocal8Bit(pro.readAllStandardOutput()));
}
