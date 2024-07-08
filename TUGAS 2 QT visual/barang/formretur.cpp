#include "formretur.h"
#include "ui_formretur.h"
#include "QMessageBox"

FormRetur::FormRetur(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::FormRetur)
{
    ui->setupUi(this);

    loadtableRetur();
}

FormRetur::~FormRetur()
{
    delete ui;
}

void FormRetur::loadtableRetur()
{
    tableModel = new QSqlQueryModel(this);
    tableModel->setQuery("SELECT*FROM retur ORDER BY no_retur ASC");
    tableModel->setHeaderData(0,Qt::Horizontal,QObject::tr("no_retur"));
    tableModel->setHeaderData(1,Qt::Horizontal,QObject::tr("kd_mitra"));
    tableModel->setHeaderData(2,Qt::Horizontal,QObject::tr("kd_barang"));
    tableModel->setHeaderData(3,Qt::Horizontal,QObject::tr("jmlh_retur"));
    tableModel->setHeaderData(3,Qt::Horizontal,QObject::tr("ttl_retur"));

    ui->tableRetur->setModel(tableModel);
    ui->tableRetur->setColumnWidth(0,150);
    ui->tableRetur->setColumnWidth(0,150);
    ui->tableRetur->setColumnWidth(0,150);
    ui->tableRetur->setColumnWidth(0,150);
    ui->tableRetur->setColumnWidth(0,150);
    ui->tableRetur->show();
}

void FormRetur::on_pushButton_clicked()
{
    if(ui->noReturLineEdit->text().isEmpty()){
        QMessageBox::information(this, "warning", "No Retur Belum Di Isi");
        ui->noReturLineEdit->setFocus();

    }else if(ui->kodeMitraLineEdit->text().isEmpty()){
        QMessageBox::information(this, "warning", "Kode Mitra Belum Di Isi");
        ui->kodeMitraLineEdit->setFocus();

    }else if(ui->kodeBarangLineEdit->text().isEmpty()){
        QMessageBox::information(this, "warning", "Kode Barang Belum Di Isi");
        ui->kodeBarangLineEdit->setFocus();

    }else if(ui->jumlahReturLineEdit->text().isEmpty()){
        QMessageBox::information(this, "warning", "Jumlah Retur Belum Di Isi");
        ui->jumlahReturLineEdit->setFocus();

    }else if(ui->totalReturLineEdit->text().isEmpty()){
        QMessageBox::information(this, "warning", "Total Retur Belum Di Isi");
        ui->totalReturLineEdit->setFocus();
    }else{

        QSqlQuery duplikat;
        duplikat.prepare("SELECT * FROM retur WHERE no_retur = '"+ui->noReturLineEdit->text()+"'");
        duplikat.exec();
        if(duplikat.next()){
            QMessageBox::information(this, "warning", "no_retur sudah terdaftar");
            ui->noReturLineEdit->setText(duplikat.value(1).toString());
            ui->kodeMitraLineEdit->setText(duplikat.value(2).toString());
            ui->kodeBarangLineEdit->setText(duplikat.value(3).toString());
            ui->jumlahReturLineEdit->setText(duplikat.value(4).toString());
            ui->totalReturLineEdit->setText(duplikat.value(5).toString());
        }else{

            QSqlQuery sql (koneksi);
            sql.prepare("INSERT INTO retur (no_retur, kd_mitra, kd_barang, jmlh_retur, ttl_retur)"
                        "VALUE (:no_retur, :kd_mitra, :kd_barang, :jmlh_retur, :ttl_retur)");
            sql.bindValue(":no_retur",ui->noReturLineEdit->text());
            sql.bindValue(":kd_mitra",ui->kodeMitraLineEdit->text());
            sql.bindValue(":kd_barang",ui->kodeBarangLineEdit->text());
            sql.bindValue(":jmlh_retur",ui->jumlahReturLineEdit->text());
            sql.bindValue(":ttl_retur",ui->totalReturLineEdit->text());

            if (sql.exec()){
                qDebug()<<"Data Berhasil Di Simpan";
            }else{
                qDebug()<<sql.lastError().text();
            }
        }
    }
}


void FormRetur::on_pushButton_2_clicked()
{
    QSqlQuery sql (koneksi);
    sql.prepare("UPDATE retur SET kd_mitra=:kd_mitra, kd_barang=:kd_barang, "
                "jmlh_retur=:jmlh_retur, ttl_retur=:ttl_retur WHERE no_retur=:no_retur)");
    sql.bindValue(":no_retur",ui->noReturLineEdit->text());
    sql.bindValue(":kd_mitra",ui->kodeMitraLineEdit->text());
    sql.bindValue(":kd_barang",ui->kodeBarangLineEdit->text());
    sql.bindValue(":jmlh_retur",ui->jumlahReturLineEdit->text());
    sql.bindValue(":ttl_retur",ui->totalReturLineEdit->text());

    if (sql.exec()){
        qDebug()<<"Data Berhasil Di Simpan";
    }else{
        qDebug()<<sql.lastError().text();
    }
}


void FormRetur::on_pushButton_4_clicked()
{
    QSqlQuery sql(koneksi);
    QSqlRecord cari;
    sql.prepare("SELECT * FROM retur WHERE no_retur=:no_retur");
    sql.bindValue(":no_retur",ui->noReturLineEdit->text());

    if (sql.exec()){
        QSqlRecord cari = sql.record();
        // ui->namaLineEdit->setText(cari.value());
        qDebug()<<cari.value(0).toString();
    }else{
        qDebug()<<sql.lastError().text();
    }
}


void FormRetur::on_pushButton_3_clicked()
{
    QSqlQuery sql(koneksi);
    sql.prepare("DELETE FROM retur WHERE no_retur=:no_retur");
    sql.bindValue(":no_retur",ui->noReturLineEdit->text());

    if (sql.exec()){
        qDebug()<<"Data Berhasil Di Hapus";
    }else{
        qDebug()<<sql.lastError().text();
    }
}


void FormRetur::on_tableRetur_activated(const QModelIndex &index)
{
    int baris = ui->tableRetur->currentIndex().row();
    // QMessageBox::information(this, "warning", QString::number(baris));
    ui->noReturLineEdit->setText(ui->tableRetur->model()->index(baris,0).data().toString());
    ui->kodeMitraLineEdit->setText(ui->tableRetur->model()->index(baris,1).data().toString());
    ui->kodeBarangLineEdit->setText(ui->tableRetur->model()->index(baris,2).data().toString());
    ui->jumlahReturLineEdit->setText(ui->tableRetur->model()->index(baris,3).data().toString());
    ui->totalReturLineEdit->setText(ui->tableRetur->model()->index(baris,4).data().toString());
}
