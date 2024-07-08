#include "formpesanan.h"
#include "ui_formpesanan.h"
#include "QMessageBox"

FormPesanan::FormPesanan(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::FormPesanan)
{
    ui->setupUi(this);

    loadtablePesanan();
}

FormPesanan::~FormPesanan()
{
    delete ui;
}

void FormPesanan::loadtablePesanan()
{
    tableModel = new QSqlQueryModel(this);
    tableModel->setQuery("SELECT*FROM pesanan ORDER BY kd_pesan ASC");
    tableModel->setHeaderData(0,Qt::Horizontal,QObject::tr("kd_pesan"));
    tableModel->setHeaderData(1,Qt::Horizontal,QObject::tr("kd_mitra"));
    tableModel->setHeaderData(2,Qt::Horizontal,QObject::tr("tgl_pesan"));
    tableModel->setHeaderData(3,Qt::Horizontal,QObject::tr("kd_barang"));
    tableModel->setHeaderData(3,Qt::Horizontal,QObject::tr("nama_barang"));
    tableModel->setHeaderData(3,Qt::Horizontal,QObject::tr("kuantiti"));
    tableModel->setHeaderData(3,Qt::Horizontal,QObject::tr("harga"));

    ui->tablePesanan->setModel(tableModel);
    ui->tablePesanan->setColumnWidth(0,150);
    ui->tablePesanan->setColumnWidth(0,150);
    ui->tablePesanan->setColumnWidth(0,150);
    ui->tablePesanan->setColumnWidth(0,150);
    ui->tablePesanan->setColumnWidth(0,150);
    ui->tablePesanan->setColumnWidth(0,150);
    ui->tablePesanan->setColumnWidth(0,150);
    ui->tablePesanan->show();
}

void FormPesanan::on_pushButton_clicked()
{
    if(ui->kodePesanLineEdit->text().isEmpty()){
        QMessageBox::information(this, "warning", "Kd Pesan Belum Di Isi");
        ui->kodePesanLineEdit->setFocus();

    }else if(ui->kodeMitraLineEdit->text().isEmpty()){
        QMessageBox::information(this, "warning", "Kode Mitra Belum Di Isi");
        ui->kodeMitraLineEdit->setFocus();

    }else if(ui->tanggalPesanDateEdit->date().toString("YYYY-MM-DD").isEmpty()){
        QMessageBox::information(this, "warning", "Tanggal Pesan Belum Di Isi");
        ui->tanggalPesanDateEdit->setFocus();

    }else if(ui->kodeBarangLineEdit->text().isEmpty()){
        QMessageBox::information(this, "warning", "Kode Barang Belum Di Isi");
        ui->kodeBarangLineEdit->setFocus();

    }else if(ui->namaBarangLineEdit->text().isEmpty()){
        QMessageBox::information(this, "warning", "Nama Barang Belum Di Isi");
        ui->namaBarangLineEdit->setFocus();

    }else if(ui->kuantitiLineEdit->text().isEmpty()){
        QMessageBox::information(this, "warning", "Kuantiti Belum Di Isi");
        ui->kuantitiLineEdit->setFocus();

    }else if(ui->hargaLineEdit->text().isEmpty()){
        QMessageBox::information(this, "warning", "Harga Belum Di Isi");
        ui->hargaLineEdit->setFocus();
    }else{

        QSqlQuery duplikat;
        duplikat.prepare("SELECT * FROM pesanan WHERE kd_pesan = '"+ui->kodePesanLineEdit->text()+"'");
        duplikat.exec();
        if(duplikat.next()){
            QMessageBox::information(this, "warning", "kd_pesan sudah terdaftar");
            ui->kodePesanLineEdit->setText(duplikat.value(1).toString());
            ui->kodeMitraLineEdit->setText(duplikat.value(2).toString());
            ui->tanggalPesanDateEdit->setDate(duplikat.value(3).toDate());
            ui->kodeBarangLineEdit->setText(duplikat.value(4).toString());
            ui->namaBarangLineEdit->setText(duplikat.value(5).toString());
            ui->kuantitiLineEdit->setText(duplikat.value(6).toString());
            ui->hargaLineEdit->setText(duplikat.value(7).toString());
        }else{

            QSqlQuery sql (koneksi);
            sql.prepare("INSERT INTO pesanan (kd_pesan, kd_mitra, tgl_pesan, kd_barang, nama_barang, kuantiti, harga)"
                "VALUE (:kd_pesan, :kd_mitra, :tgl_pesan, :kd_barang, :nama_barang, :kuantiti, :harga)");
            sql.bindValue(":kd_pesan",ui->kodePesanLineEdit->text());
            sql.bindValue(":kd_mitra",ui->kodeMitraLineEdit->text());
            sql.bindValue(":tgl_pesan",ui->tanggalPesanDateEdit->date().toString("YYYY-MM-DD"));
            sql.bindValue(":kd_barang",ui->kodeBarangLineEdit->text());
            sql.bindValue(":nama_barang",ui->namaBarangLineEdit->text());
            sql.bindValue(":kuantiti",ui->kuantitiLineEdit->text());
            sql.bindValue(":harga",ui->hargaLineEdit->text());

            if (sql.exec()){
                qDebug()<<"Data Berhasil Di Simpan";
            }else{
                qDebug()<<sql.lastError().text();
            }
        }
    }
}


void FormPesanan::on_pushButton_3_clicked()
{
    QSqlQuery sql (koneksi);
    sql.prepare("UPDATE pesanan SET kd_mitra=:kd_mitra, tgl_pesan=:tgl_pesan, kd_barang=:kd_barang, "
                "nama_barang=:nama_barang, kuantiti=:kuantiti, harga=:harga WHERE kd_pesan=:kd_pesan");
    sql.bindValue(":kd_pesan",ui->kodePesanLineEdit->text());
    sql.bindValue(":kd_mitra",ui->kodeMitraLineEdit->text());
    sql.bindValue(":tgl_pesan",ui->tanggalPesanDateEdit->date().toString("YYYY-MM-DD"));
    sql.bindValue(":kd_barang",ui->kodeBarangLineEdit->text());
    sql.bindValue(":nama_barang",ui->namaBarangLineEdit->text());
    sql.bindValue(":kuantiti",ui->kuantitiLineEdit->text());
    sql.bindValue(":harga",ui->hargaLineEdit->text());

    if (sql.exec()){
        qDebug()<<"Data Berhasil Di Edit";
    }else{
        qDebug()<<sql.lastError().text();
    }
}


void FormPesanan::on_pushButton_4_clicked()
{
    QSqlQuery sql(koneksi);
    QSqlRecord cari;
    sql.prepare("SELECT * FROM pesanan WHERE kd_pesan=:kd_pesan");
    sql.bindValue(":kd_pesan",ui->kodePesanLineEdit->text());

    if (sql.exec()){
        QSqlRecord cari = sql.record();
        // ui->namaLineEdit->setText(cari.value());
        qDebug()<<cari.value(0).toString();
    }else{
        qDebug()<<sql.lastError().text();
    }
}


void FormPesanan::on_pushButton_2_clicked()
{
    QSqlQuery sql(koneksi);
    sql.prepare("DELETE FROM pesanan WHERE kd_pesan=:kd_pesan");
    sql.bindValue(":kd_pesan",ui->kodePesanLineEdit->text());

    if (sql.exec()){
        qDebug()<<"Data Berhasil Di Hapus";
    }else{
        qDebug()<<sql.lastError().text();
    }
}


void FormPesanan::on_tablePesanan_activated(const QModelIndex &index)
{
    int baris = ui->tablePesanan->currentIndex().row();
    // QMessageBox::information(this, "warning", QString::number(baris));
    ui->kodePesanLineEdit->setText(ui->tablePesanan->model()->index(baris,0).data().toString());
    ui->kodeMitraLineEdit->setText(ui->tablePesanan->model()->index(baris,1).data().toString());
    ui->tanggalPesanDateEdit->setDate(ui->tablePesanan->model()->index(baris,2).data().toDate());
    ui->kodeBarangLineEdit->setText(ui->tablePesanan->model()->index(baris,3).data().toString());
    ui->namaBarangLineEdit->setText(ui->tablePesanan->model()->index(baris,4).data().toString());
    ui->kuantitiLineEdit->setText(ui->tablePesanan->model()->index(baris,5).data().toString());
    ui->hargaLineEdit->setText(ui->tablePesanan->model()->index(baris,6).data().toString());
}

