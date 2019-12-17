#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    /**
     * @brief update_status Updates the status of the running program
     */
    void update_status(QString status);

    QVector<QString> macros_list;

private slots:
    void on_bt_run_clicked();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
