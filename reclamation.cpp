#include "reclamation.h"
#include <QSystemTrayIcon>

Reclamation::Reclamation()
{

}

Reclamation::Reclamation(int a, QString t,QString p, QString d)
{
    id = a;
    titre = t;
    description = p;
    status = p;
}
void Reclamation::setTitre(const QString &t)
{
    titre = t;
}

void Reclamation::setDescription(QString p)
{
    description = p;
}
void Reclamation::setStatus(const QString &d)
{
    status = d;
}



QSqlQueryModel *Reclamation::afficher()
{
    QSqlQueryModel *model = new QSqlQueryModel();
    model->setQuery("SELECT * FROM reclamation");
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("id"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("titre"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("description"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("status"));

    return model;
}

bool Reclamation::ajouter()
{
    QSqlQuery query;
    QString res = QString::number(id);

    query.prepare("INSERT INTO reclamation (id, titre, description, status) "
                  "VALUES (:id, :titre, :description, :status)");
    query.bindValue(":id", id);
    query.bindValue(":titre", titre);
    query.bindValue(":description", description);
    query.bindValue(":status", status);


    return query.exec();
}

bool Reclamation::supprimer(int id)
{
    QSqlQuery query;
    QString res = QString::number(id);
    query.prepare("DELETE FROM reclamation WHERE id = :id");
    query.bindValue(":id", res);

    return query.exec();
}

bool Reclamation::modifier(int idE)
{
    QSqlQuery query;
    QString res = QString::number(idE);

    query.prepare("UPDATE RECLAMATION SET TITRE = :titre, DESCRIPTION = :description, STATUS = :status WHERE ID= :idE");
    query.bindValue(":idE", id);
    query.bindValue(":titre", titre);
    query.bindValue(":description",description);
    query.bindValue(":status",status);



    return query.exec();
}

QSqlQueryModel *Reclamation::displayClause(QString cls)
{
    QSqlQueryModel *model = new QSqlQueryModel();
    model->setQuery("SELECT * FROM reclamation " + cls);

    model->setHeaderData(0, Qt::Horizontal, QObject::tr("id"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("titre"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("description"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("status"));

    return model;
}


QSqlQueryModel * Reclamation::tri_id()
{
    QSqlQueryModel * model = new QSqlQueryModel();
    model->setQuery("SELECT * FROM reclamation ORDER BY id ASC");

    model->setHeaderData(0, Qt::Horizontal, QObject::tr("id"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("titre"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("description"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("status"));

    return model;
}


QSqlQueryModel * Reclamation::tri_titre()
{
    QSqlQueryModel * model = new QSqlQueryModel();
    model->setQuery("SELECT * FROM reclamation ORDER BY titre DESC");

    model->setHeaderData(0, Qt::Horizontal, QObject::tr("id"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("titre"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("description"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("status"));

    return model;
}



QSqlQueryModel * Reclamation::tri_status()
{
    QSqlQueryModel * model = new QSqlQueryModel();
    model->setQuery("SELECT * FROM reclamation ORDER BY status ASC");

    model->setHeaderData(0, Qt::Horizontal, QObject::tr("id"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("titre"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("description"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("status"));

    return model;
}
void Reclamation::notification_ajoutReclamation()
{

    QSystemTrayIcon *notifyIcon = new QSystemTrayIcon;
    notifyIcon->show();
    notifyIcon->showMessage("Gestion des reclamation ","Nouveau Reclamation ajouté ",QSystemTrayIcon::Information,15000);
}


void Reclamation::notification_suppReclamation()
{

    QSystemTrayIcon *notifyIcon = new QSystemTrayIcon;
    notifyIcon->show();
    notifyIcon->showMessage("Gestion des reclamation ","reclamation supprime ",QSystemTrayIcon::Information,15000);
}

void Reclamation::notification_modifReclamation()
{

    QSystemTrayIcon *notifyIcon = new QSystemTrayIcon;
    notifyIcon->show();
    notifyIcon->showMessage("Gestion des reclamation ","Reclamation modifie ",QSystemTrayIcon::Information,15000);
}


void Reclamation::notification_pdf()
{

    QSystemTrayIcon *notifyIcon = new QSystemTrayIcon;
    notifyIcon->show();
    notifyIcon->showMessage("Gestion des reclamation  ","pdf generee ",QSystemTrayIcon::Information,15000);
}
