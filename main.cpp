#include "mainwindow.h"

#include <QVector>

#include <QApplication>
#include <QFile>
#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonObject>
#include <QJsonValue>
#include <QDebug>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;

    // Reading the json file before showing the user the GUI

    QString json_content;
    QFile json_file("./configuration/config.json");

    if (json_file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        json_content = json_file.readAll();
        json_file.close();

        QJsonDocument json = QJsonDocument::fromJson(json_content.toUtf8());
        QJsonObject json_obj = json.object();

        QJsonObject macros = json_obj.value(QString("macros")).toObject();
        QJsonArray list = macros["list"].toArray();

        qDebug() << list;

        w.macros_list = QVector<QString>();

        for (auto el : list) {
            w.macros_list.push_back(el.toString());
        }
    }

    if (w.macros_list.size() == 0) {
        w.update_status("No macros found. Look at the config.json file");
    }

    w.show();
    return a.exec();
}
