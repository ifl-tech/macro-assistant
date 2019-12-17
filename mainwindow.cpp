#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <iostream>

#include <QClipboard>
#include <QProcess>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    this->setWindowTitle("Macro Assistant");
    setFixedSize(this->size());
    setWindowFlags(Qt::Dialog | Qt::MSWindowsFixedSizeDialogHint);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::update_status(QString status) {
    ui->bt_run->setDisabled(true);
    ui->lb_status->setText(status);
}

void MainWindow::on_bt_run_clicked()
{
    QString text = this->ui->ta_data->toPlainText();

    QClipboard *clipboard = QGuiApplication::clipboard();
    clipboard->setText(text);

    ui->bt_run->setText(QString("Running..."));
    ui->bt_run->setDisabled(true);

    QVector<QProcess*> processes = QVector<QProcess*>();

    // Execute the macro executable with the text from the macro list
    for (int i = 0; i < this->macros_list.size(); i++) {
        processes.push_back(new QProcess());
        processes[i]->execute(this->macros_list[i]);
    }

    ui->ta_data->setText(QString(""));
    ui->bt_run->setDisabled(false);
    ui->bt_run->setText(QString("Run"));
}
