#include "formbarang.h"
#include "ui_formbarang.h"
#include "QMessageBox"

FormBarang::FormBarang(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::FormBarang)
{
    ui->setupUi(this);

    QSqlDatabase koneksi = QSqlDatabase::addDatabase("QODBC");
    koneksi.setDatabaseName("dsn_sistemkesehatan");
    koneksi.setUserName("root");
    koneksi.setPassword("");

    if(!koneksi.open()){
        qDebug()<<koneksi.lastError().text();
    }else{
        qDebug()<<"Database Terkoneksi";

    }

    loadtableBarang();
}

FormBarang::~FormBarang()
{
    delete ui;
}

void FormBarang::loadtableBarang()
{
    tableModel = new QSqlQueryModel(this);
    tableModel->setQuery("SELECT*FROM barang ORDER BY kd_barang ASC");
    tableModel->setHeaderData(0,Qt::Horizontal,QObject::tr("kd_barang"));
    tableModel->setHeaderData(1,Qt::Horizontal,QObject::tr("kd_mitra"));
    tableModel->setHeaderData(2,Qt::Horizontal,QObject::tr("nama_barang"));
    tableModel->setHeaderData(3,Qt::Horizontal,QObject::tr("harga"));
    tableModel->setHeaderData(4,Qt::Horizontal,QObject::tr("stok"));

    ui->tableBarang->setModel(tableModel);
    ui->tableBarang->setColumnWidth(0,150);
    ui->tableBarang->setColumnWidth(0,150);
    ui->tableBarang->setColumnWidth(0,200);
    ui->tableBarang->setColumnWidth(0,150);
    ui->tableBarang->setColumnWidth(0,150);
    ui->tableBarang->show();
}
void FormBarang::on_pushButton_2_clicked()
{
    if(ui->kodeBarangLineEdit->text().isEmpty()){
        QMessageBox::information(this, "warning", "Kd Barang Belum Di Isi");
        ui->kodeBarangLineEdit->setFocus();

    }else if(ui->kodeMitraLineEdit->text().isEmpty()){
        QMessageBox::information(this, "warning", "Kd Mitra Belum Di Isi");
        ui->kodeMitraLineEdit->setFocus();

    }else if(ui->namaBarangLineEdit->text().isEmpty()){
        QMessageBox::information(this, "warning", "Nama Barang Belum Di Isi");
        ui->namaBarangLineEdit->setFocus();

    }else if(ui->hargaLineEdit->text().isEmpty()){
        QMessageBox::information(this, "warning", "Harga Belum Di Isi");
        ui->hargaLineEdit->setFocus();

    }else if(ui->stokLineEdit->text().isEmpty()){
        QMessageBox::information(this, "warning", "Stok Belum Di Isi");
        ui->stokLineEdit->setFocus();
    }else {

        QSqlQuery duplikat;
        duplikat.prepare("SELECT * FROM barang WHERE kd_barang = '"+ui->kodeBarangLineEdit->text()+"'");
        duplikat.exec();
        if(duplikat.next()){
            QMessageBox::information(this, "warning", "kd_barang sudah terdaftar");
            ui->kodeMitraLineEdit->setText(duplikat.value(1).toString());
            ui->namaBarangLineEdit->setText(duplikat.value(2).toString());
            ui->hargaLineEdit->setText(duplikat.value(3).toString());
            ui->stokLineEdit->setText(duplikat.value(4).toString());
        }else{

            QSqlQuery sql (koneksi);
            sql.prepare("INSERT INTO barang (kd_barang, kd_mitra, nama_barang, harga, stok)"
                        "VALUE (:kd_barang, :kd_mitra, :nama_barang, :harga, :stok)");
            sql.bindValue(":kd_barang",ui->kodeBarangLineEdit->text());
            sql.bindValue(":kd_mitra",ui->kodeMitraLineEdit->text());
            sql.bindValue(":nama_barang",ui->namaBarangLineEdit->text());
            sql.bindValue(":harga",ui->hargaLineEdit->text());
            sql.bindValue(":stok",ui->stokLineEdit->text());

            if (sql.exec()){
                qDebug()<<"Data Berhasil Di Simpan";
            }else{
                qDebug()<<sql.lastError().text();
            }
        }
    }
}


void FormBarang::on_pushButton_clicked()
{
    QSqlQuery sql (koneksi);
    sql.prepare("UPDATE barang SET kd_mitra=:kd_mitra, nama_barang=:nama_barang, "
                "harga=:harga, stok=:stok WHERE kd_barang=:kd_barang");
    sql.bindValue(":kd_barang",ui->kodeBarangLineEdit->text());
    sql.bindValue(":kd_mitra",ui->kodeMitraLineEdit->text());
    sql.bindValue(":nama_barang",ui->namaBarangLineEdit->text());
    sql.bindValue(":harga",ui->hargaLineEdit->text());
    sql.bindValue(":stok",ui->stokLineEdit->text());

    if (sql.exec()){
        qDebug()<<"Data Berhasil Di Edit";
    }else{
        qDebug()<<sql.lastError().text();
    }
}


void FormBarang::on_pushButton_4_clicked()
{
    QSqlQuery sql(koneksi);
    QSqlRecord cari;
    sql.prepare("SELECT * FROM barang WHERE kd_barang=:kd_barang");
    sql.bindValue(":kd_barang",ui->kodeBarangLineEdit->text());

    if (sql.exec()){
        QSqlRecord cari = sql.record();
        // ui->namaLineEdit->setText(cari.value());
        qDebug()<<cari.value(0).toString();
    }else{
        qDebug()<<sql.lastError().text();
    }
}


void FormBarang::on_pushButton_3_clicked()
{
    QSqlQuery sql(koneksi);
    sql.prepare("DELETE FROM barang WHERE kd_barang=:kd_barang");
    sql.bindValue(":kd_barang",ui->kodeBarangLineEdit->text());

    if (sql.exec()){
        qDebug()<<"Data Berhasil Di Hapus";
    }else{
        qDebug()<<sql.lastError().text();
    }
}


void FormBarang::on_tableBarang_activated(const QModelIndex &index)
{
    int baris = ui->tableBarang->currentIndex().row();
    // QMessageBox::information(this, "warning", QString::number(baris));
    ui->kodeBarangLineEdit->setText(ui->tableBarang->model()->index(baris,0).data().toString());
    ui->kodeMitraLineEdit->setText(ui->tableBarang->model()->index(baris,1).data().toString());
    ui->namaBarangLineEdit->setText(ui->tableBarang->model()->index(baris,1).data().toString());
    ui->hargaLineEdit->setText(ui->tableBarang->model()->index(baris,1).data().toString());
    ui->stokLineEdit->setText(ui->tableBarang->model()->index(baris,1).data().toString());

}

