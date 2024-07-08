#ifndef FORMRETUR_H
#define FORMRETUR_H

#include <QWidget>
#include <QtSql>
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
#include <QDebug>
#include <QSqlRecord>
#include <QSqlQueryModel>

namespace Ui {
class FormRetur;
}

class FormRetur : public QWidget
{
    Q_OBJECT

public:
    explicit FormRetur(QWidget *parent = nullptr);
    void loadtableRetur();
    ~FormRetur();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_4_clicked();

    void on_pushButton_3_clicked();

    void on_tableRetur_activated(const QModelIndex &index);

private:
    Ui::FormRetur *ui;
    QSqlDatabase koneksi;
    QSqlQuery sql;
    QSqlRecord cari;
    QSqlQueryModel  * tableModel;
};

#endif // FORMRETUR_H
