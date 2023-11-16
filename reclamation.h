#ifndef RISQUE_H
#define RISQUE_H

#include <QString>
#include <QDate>
#include <QSqlQuery>
#include <QSqlQueryModel>

class Reclamation
{
public:
    Reclamation();
    Reclamation(int a, QString t,QString p, QString d);

    QSqlQueryModel *afficher();
    bool ajouter();
    bool supprimer(int id);
    bool modifier(int idE);

    int getId() const;
    QString getTitre() const;


    QString getDescription() const;

    QString getStatus() const;

    void setId(int a);

    void setTitre(const QString &t);


    void setDescription(QString p);

    void setStatus(const QString &d);




     QSqlQueryModel *displayClause(QString cls);
     QSqlQueryModel *tri_id();
     QSqlQueryModel *tri_titre();
     QSqlQueryModel *tri_status();


     void notification_ajoutReclamation();
     void notification_suppReclamation();
     void notification_modifReclamation();
     void notification_pdf();




private:
     int id;
     QString titre;
     QString description;
     QString status;
};

#endif // RISQUE_H
