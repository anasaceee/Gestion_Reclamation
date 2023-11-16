#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
#include <QDesktopServices>
#include <QUrl>
#include <QtPrintSupport/QPrinter>
#include <QPainter>
#include <QtCharts>
#include <QPieSeries>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}



void MainWindow::on_pushButton_clicked()
{
    int idReclamation = ui->lineEdit->text().toInt();

        QString titreReclamation = ui->lineEdit_2->text();
        QString descriptionReclamation = ui->lineEdit_5->text();
        QString statusReclamation = ui->lineEdit_6->text();

        Reclamation reclamation(idReclamation, titreReclamation, descriptionReclamation,statusReclamation);

        if (!titreReclamation.isEmpty() && !descriptionReclamation.isEmpty())
        {
            bool ajoutReussi = reclamation.ajouter();
            if (ajoutReussi)
            {
                QMessageBox::information(this, "Ajout réussi", "Le risque a été ajouté avec succès.");
                reclamation.notification_ajoutReclamation();
                ui->tableView->setModel(reclamation.afficher());
            }
            else
            {
                QMessageBox::critical(this, "Erreur d'ajout", "Une erreur est survenue lors de l'ajout du risque.");
            }
        }
        else
        {
            QMessageBox::warning(this, "Données manquantes", "Veuillez entrer le type et la discription.");
        }
}

void MainWindow::on_pushButton_afficher_clicked()
{
    Reclamation reclamation;
        ui->tableView->setModel(reclamation.afficher());
}

void MainWindow::on_pushButton_modifer_clicked()
{
    int idUp = ui->tableView->model()->data(ui->tableView->model()->index(ui->tableView->currentIndex().row(), 0)).toInt();
    QString titreReclamation = ui->lineEdit_2->text();
    QString descriptionReclamation = ui->lineEdit_5->text();
     QString statusReclamation = ui->lineEdit_6->text();
        Reclamation reclamation(idUp, titreReclamation, descriptionReclamation,statusReclamation);

        if (!titreReclamation.isEmpty() || !descriptionReclamation.isEmpty())
        {
            if (titreReclamation.isEmpty()) {

                QString ancienTitre = ui->tableView->model()->data(ui->tableView->model()->index(ui->tableView->currentIndex().row(), 1)).toString();
                reclamation.setTitre(ancienTitre);
            }

            if (descriptionReclamation.isEmpty()) {

                QString ancienDis = ui->tableView->model()->data(ui->tableView->model()->index(ui->tableView->currentIndex().row(), 2)).toString();
                reclamation.setDescription(ancienDis);
            }

            bool test = reclamation.modifier(idUp);
            if (test)
            {
                QMessageBox::information(this, "Modification réussie", "Les informations du risque ont été modifiées avec succès.");
                 reclamation.notification_modifReclamation();
                ui->tableView->setModel(reclamation.afficher());
            }
            else
            {
                QMessageBox::critical(this, "Erreur de modification", "Une erreur est survenue lors de la modification du riqsue.");
            }
        }
        else
        {
            QMessageBox::warning(this, "Données manquantes", "Veuillez entrer le type ou la discription.");
        }
}

void MainWindow::on_pushButton_supprimer_clicked()
{
    int idDel = ui->tableView->model()->data(ui->tableView->model()->index(ui->tableView->currentIndex().row(), 0)).toInt();
        Reclamation reclamation;
        bool test = reclamation.supprimer(idDel);
        if (test)
        {
            QMessageBox::information(this, "Suppression réussie", "Le reclamation a été supprimé avec succès.");
            reclamation.notification_suppReclamation();
        }
        else
        {
            QMessageBox::critical(this, "Erreur de suppression", "Une erreur est survenue lors de la suppression du reclamation.");
        }
        ui->tableView->setModel(reclamation.afficher());
}






void MainWindow::on_pushButton_triid_clicked()
{
    Reclamation reclamation;
    ui->tableView->setModel(reclamation.tri_id());

}

void MainWindow::on_pushButton_tritype_clicked()
{
    Reclamation reclamation;
    ui->tableView->setModel(reclamation.tri_titre());

}



void MainWindow::on_pushButton_trip_clicked()
{
    Reclamation reclamation;
    ui->tableView->setModel(reclamation.tri_status());
}


void MainWindow::on_pushButton_stat_clicked()
{
    QSqlQueryModel *model = new QSqlQueryModel();
    model->setQuery("SELECT type FROM reclamation WHERE titre='acceptable'");
    float countAcceptable = model->rowCount();
    model->setQuery("SELECT type FROM reclamation WHERE titre='moyen'");
    float countMoyen = model->rowCount();
    model->setQuery("SELECT type FROM reclamation WHERE titre='eleve'");
    float countEleve = model->rowCount();

    QPieSeries *series = new QPieSeries();
    series->append("acceptable", countAcceptable);
    series->append("moyen", countMoyen);
    series->append("eleve", countEleve);


    for (int i = 0; i < series->slices().size(); ++i)
    {
        QPieSlice *slice = series->slices().at(i);
        slice->setLabelVisible();
        slice->setLabel(QString("%1 - %2%").arg(slice->label()).arg(100 * slice->percentage(), 3, 'f', 1));
        slice->setPen(QPen(Qt::black));

        // You can customize the label color or other properties here if needed
    }

    QChart *chart = new QChart();
    chart->addSeries(series);
    chart->setTitle(" statistique");

    QChartView *chartView = new QChartView(chart);
    chartView->setRenderHint(QPainter::Antialiasing);
    chartView->resize(1000, 500);

    chartView->show();
}

void MainWindow::on_pushButton_2_clicked()
{

        Reclamation reclamation;
        QPdfWriter pdf("Reclamation.pdf");
        QPainter painter(&pdf);
        int i = 4000;
        painter.setPen(Qt::blue);
        painter.setFont(QFont("Arial", 30));
        painter.drawText(3300, 1200, "Liste Des Reclamation");
        painter.setPen(Qt::black);
        painter.setFont(QFont("Arial", 50));
        painter.drawRect(1500, 200, 7300, 2600);
        painter.drawRect(0, 3000, 9600, 500);
        painter.setFont(QFont("Arial", 9));
        painter.drawText(1000, 3300, "ID");
        painter.drawText(2000, 3300, "TITRE");
        painter.drawText(3000, 3300, "DESCRIPTION");
        painter.drawText(5000, 3300, "STATUS");


        QSqlQuery query;
        query.prepare("SELECT * FROM reclamation");
        query.exec();

        while (query.next())
        {
            painter.drawText(1000, i, query.value("id").toString());
            painter.drawText(2000, i, query.value("titre").toString());
            painter.drawText(3000, i, query.value("description").toString());
            painter.drawText(5000, i, query.value("status").toString());

            i = i + 500;
        }


        reclamation.notification_pdf();
        int reponse = QMessageBox::question(this, "Générer PDF", "PDF enregistré. Voulez-vous l'afficher ?", QMessageBox::Yes | QMessageBox::No);
        if (reponse == QMessageBox::Yes)
        {
            QDesktopServices::openUrl(QUrl::fromLocalFile("Reclamation.pdf"));
        }

        painter.end();

}



void MainWindow::on_lineEdit_rech_id_textChanged()
{
    Reclamation reclamation;
        if (ui->lineEdit_rech_id->text() != "")
        {
            QString a = ui->lineEdit_rech_id->text();
            ui->tableView->setModel(reclamation.displayClause("WHERE (id LIKE '%" + a + "%') "));
        }
        else
        {
            ui->tableView->setModel(reclamation.afficher());
        }
}

void MainWindow::on_lineEdit_rech_type_textChanged()
{
    Reclamation reclamation;
        if (ui->lineEdit_rech_type->text() != "")
        {
            QString a = ui->lineEdit_rech_type->text();
            ui->tableView->setModel(reclamation.displayClause("WHERE (titre LIKE '%" + a + "%') "));
        }
        else
        {
            ui->tableView->setModel(reclamation.afficher());
        }
}

void MainWindow::on_lineEdit_rech_porc_textChanged()
{
    Reclamation reclamation;
        if (ui->lineEdit_rech_porc->text() != "")
        {
            QString a = ui->lineEdit_rech_porc->text();
            ui->tableView->setModel(reclamation.displayClause("WHERE (status LIKE '%" + a + "%') "));
        }
        else
        {
            ui->tableView->setModel(reclamation.afficher());
        }

}
