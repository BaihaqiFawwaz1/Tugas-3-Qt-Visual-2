#ifndef FORMSLIPPEMBAYARAN_H
#define FORMSLIPPEMBAYARAN_H

#include <QWidget>
#include <QtSql>
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
#include <QDebug>
#include <QSqlRecord>
#include <QSqlQueryModel>

namespace Ui {
class FormSlippembayaran;
}

class FormSlippembayaran : public QWidget
{
    Q_OBJECT

public:
    explicit FormSlippembayaran(QWidget *parent = nullptr);
    void loadtableSlipPembayaran();
    ~FormSlippembayaran();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_4_clicked();

    void on_pushButton_3_clicked();

    void on_tableSlipPembayaran_activated(const QModelIndex &index);

private:
    Ui::FormSlippembayaran *ui;
    QSqlDatabase koneksi;
    QSqlQuery sql;
    QSqlRecord cari;
    QSqlQueryModel  * tableModel;
};

#endif // FORMSLIPPEMBAYARAN_H
