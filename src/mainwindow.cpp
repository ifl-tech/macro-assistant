#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <iostream>

#include <QClipboard>
#include <QProcess>
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    this->setWindowTitle("Macro Assistant");
    setFixedSize(this->size());
    setWindowFlags(Qt::Dialog | Qt::MSWindowsFixedSizeDialogHint | Qt::WindowCloseButtonHint);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::toggle_components() {
    ui->bt_run->setDisabled(ui->bt_run->isEnabled());
    ui->ta_data->setDisabled(ui->ta_data->isEnabled());
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
        int r = processes[i]->execute(this->macros_list[i]);

        if (r != 0) {
            QString message = QString::asprintf("The process was unable to finish successfully (%d).", r);
            QMessageBox::critical(this, tr("Process start error"), message);
        }
    }

    ui->ta_data->setText(tr(""));
    ui->bt_run->setDisabled(false);
    ui->bt_run->setText(tr("Run"));
}
