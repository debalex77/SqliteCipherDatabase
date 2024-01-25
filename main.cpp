#include <QCoreApplication>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QDebug>
#include <QString>
#include <QDir>

int main(int argc, char *argv[]) {

    QCoreApplication a(argc, argv);

    qDebug() << QSqlDatabase::drivers();

    QDir dir;
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLCIPHER");
    db.setDatabaseName(dir.toNativeSeparators("/home/alex/Qt_projects/Database/encrypted.sqlite3"));
    db.open();

    QSqlQuery q;
    q.exec("PRAGMA key = 'testkey';");
    if (! q.exec("SELECT count(*) FROM sqlite_master;")) {
        qDebug() << "Password not correct !!!";
        db.close();
        return 0;
    }

    q.exec("CREATE TABLE testtable ("
           "id INTEGER NOT NULL PRIMARY KEY AUTOINCREMENT, "
           "name TEXT (50));");
    q.exec("insert into testtable (id,name) values(1,'dummy')");
    q.exec("SELECT id,name anz FROM testtable");

    while (q.next()) {
        QString id = q.value(0).toString();
        QString name = q.value(1).toString();
        qDebug() << "id=" << id << ",  name=" << name;
    }

    db.close();

    return 0;
}
