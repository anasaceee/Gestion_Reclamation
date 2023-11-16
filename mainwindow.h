#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include<QWidget>
#include <QMainWindow>
#include <reclamation.h>
#include <QtPrintSupport/QPrinter>
#include <QLabel>
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);

    ~MainWindow();

private slots:



    void on_pushButton_clicked();


    void on_pushButton_afficher_clicked();

    void on_pushButton_modifer_clicked();

    void on_pushButton_supprimer_clicked();

    void on_pushButton_triid_clicked();

    void on_pushButton_tritype_clicked();

    void on_pushButton_trip_clicked();


    void on_pushButton_stat_clicked();

    void on_pushButton_2_clicked();

    void on_lineEdit_rech_id_textChanged();

    void on_lineEdit_rech_type_textChanged();

    void on_lineEdit_rech_porc_textChanged();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
