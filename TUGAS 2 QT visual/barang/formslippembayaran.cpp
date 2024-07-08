#include "formslippembayaran.h"
#include "ui_formslippembayaran.h"
#include "QMessageBox"

FormSlippembayaran::FormSlippembayaran(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::FormSlippembayaran)
{
    ui->setupUi(this);

    loadtableSlipPembayaran();
}

FormSlippembayaran::~FormSlippembayaran()
{
    delete ui;
}

void FormSlippembayaran::loadtableSlipPembayaran()
{
    tableModel = new QSqlQueryModel(this);
    tableModel->setQuery("SELECT*FROM slippembayaran ORDER BY kd_pembayaran ASC");
    tableModel->setHeaderData(0,Qt::Horizontal,QObject::tr("kd_pembayaran"));
    tableModel->setHeaderData(1,Qt::Horizontal,QObject::tr("kd_mitra"));
    tableModel->setHeaderData(2,Qt::Horizontal,QObject::tr("kd_barang"));
    tableModel->setHeaderData(3,Qt::Horizontal,QObject::tr("harga"));
    tableModel->setHeaderData(3,Qt::Horizontal,QObject::tr("kuantiti"));
    tableModel->setHeaderData(3,Qt::Horizontal,QObject::tr("ttl_harga"));

    ui->tableSlipPembayaran->setModel(tableModel);
    ui->tableSlipPembayaran->setColumnWidth(0,150);
    ui->tableSlipPembayaran->setColumnWidth(0,150);
    ui->tableSlipPembayaran->setColumnWidth(0,150);
    ui->tableSlipPembayaran->setColumnWidth(0,150);
    ui->tableSlipPembayaran->setColumnWidth(0,150);
    ui->tableSlipPembayaran->setColumnWidth(0,150);
    ui->tableSlipPembayaran->show();
}

void FormSlippembayaran::on_pushButton_clicked()
{
    if(ui->kodePembayaranLineEdit->text().isEmpty()){
        QMessageBox::information(this, "warning", "Kd Pembayaran Belum Di Isi");
        ui->kodePembayaranLineEdit->setFocus();

    }else if(ui->kodeMitraLineEdit->text().isEmpty()){
        QMessageBox::information(this, "warning", "Kode Mitra Belum Di Isi");
        ui->kodeMitraLineEdit->setFocus();

    }else if(ui->kodeBarangLineEdit->text().isEmpty()){
        QMessageBox::information(this, "warning", "Kode Barang Belum Di Isi");
        ui->kodeBarangLineEdit->setFocus();

    }else if(ui->hargaLineEdit->text().isEmpty()){
        QMessageBox::information(this, "warning", "Harga Belum Di Isi");
        ui->hargaLineEdit->setFocus();

    }else if(ui->kuantitiLineEdit->text().isEmpty()){
        QMessageBox::information(this, "warning", "Kuantiti Belum Di Isi");
        ui->kuantitiLineEdit->setFocus();

    }else if(ui->totalHargaLineEdit->text().isEmpty()){
        QMessageBox::information(this, "warning", "Total Harga Belum Di Isi");
        ui->totalHargaLineEdit->setFocus();
    }else{

        QSqlQuery duplikat;
        duplikat.prepare("SELECT * FROM slippembayaran WHERE kd_pembayaran = '"+ui->kodePembayaranLineEdit->text()+"'");
        duplikat.exec();
        if(duplikat.next()){
            QMessageBox::information(this, "warning", "kd_pembayaran sudah terdaftar");
            ui->kodePembayaranLineEdit->setText(duplikat.value(1).toString());
            ui->kodeMitraLineEdit->setText(duplikat.value(2).toString());
            ui->kodeBarangLineEdit->setText(duplikat.value(3).toString());
            ui->hargaLineEdit->setText(duplikat.value(4).toString());
            ui->kuantitiLineEdit->setText(duplikat.value(5).toString());
            ui->totalHargaLineEdit->setText(duplikat.value(6).toString());
        }else {

            QSqlQuery sql (koneksi);
            sql.prepare("INSERT INTO slippembayaran (kd_pembayaran, kd_mitra, kd_barang, harga, kuantiti, ttl_harga)"
                        "VALUE (:kd_pembayaran, :kd_mitra, :kd_barang, :harga, :kuantiti, :ttl_harga)");
            sql.bindValue(":kd_pembayaran",ui->kodePembayaranLineEdit->text());
            sql.bindValue(":kd_mitra",ui->kodeMitraLineEdit->text());
            sql.bindValue(":kd_barang",ui->kodeBarangLineEdit->text());
            sql.bindValue(":harga",ui->hargaLineEdit->text());
            sql.bindValue(":kuantiti",ui->kuantitiLineEdit->text());
            sql.bindValue(":ttl_harga",ui->totalHargaLineEdit->text());

            if (sql.exec()){
                qDebug()<<"Data Berhasil Di Simpan";
            }else{
                qDebug()<<sql.lastError().text();
            }
        }
    }
}


void FormSlippembayaran::on_pushButton_2_clicked()
{
    QSqlQuery sql (koneksi);
    sql.prepare("UPDATE slippembayaran SET kd_mitra=:kd_mitra, kd_barang=:kd_barang, "
                "harga=:harga, kuantiti=:kuantiti, ttl_harga=:ttl_harga WHERE kd_pembayaran=:kd_pembayaran)");
    sql.bindValue(":kd_pembayaran",ui->kodePembayaranLineEdit->text());
    sql.bindValue(":kd_mitra",ui->kodeMitraLineEdit->text());
    sql.bindValue(":kd_barang",ui->kodeBarangLineEdit->text());
    sql.bindValue(":harga",ui->hargaLineEdit->text());
    sql.bindValue(":kuantiti",ui->kuantitiLineEdit->text());
    sql.bindValue(":ttl_harga",ui->totalHargaLineEdit->text());

    if (sql.exec()){
        qDebug()<<"Data Berhasil Di Edit";
    }else{
        qDebug()<<sql.lastError().text();
    }
}


void FormSlippembayaran::on_pushButton_4_clicked()
{
    QSqlQuery sql(koneksi);
    QSqlRecord cari;
    sql.prepare("SELECT * FROM slippembayaran WHERE kd_pembayaran=:kd_pembayaran");
    sql.bindValue(":kd_pembayaran",ui->kodePembayaranLineEdit->text());

    if (sql.exec()){
        QSqlRecord cari = sql.record();
        // ui->namaLineEdit->setText(cari.value());
        qDebug()<<cari.value(0).toString();
    }else{
        qDebug()<<sql.lastError().text();
    }
}


void FormSlippembayaran::on_pushButton_3_clicked()
{
    QSqlQuery sql(koneksi);
    sql.prepare("DELETE FROM slippembayaran WHERE kd_pembayaran=:kd_pembayaran");
    sql.bindValue(":kd_pembayaran",ui->kodePembayaranLineEdit->text());

    if (sql.exec()){
        qDebug()<<"Data Berhasil Di Hapus";
    }else{
        qDebug()<<sql.lastError().text();
    }
}


void FormSlippembayaran::on_tableSlipPembayaran_activated(const QModelIndex &index)
{
    int baris = ui->tableSlipPembayaran->currentIndex().row();
    // QMessageBox::information(this, "warning", QString::number(baris));
    ui->kodePembayaranLineEdit->setText(ui->tableSlipPembayaran->model()->index(baris,0).data().toString());
    ui->kodeMitraLineEdit->setText(ui->tableSlipPembayaran->model()->index(baris,1).data().toString());
    ui->kodeBarangLineEdit->setText(ui->tableSlipPembayaran->model()->index(baris,2).data().toString());
    ui->hargaLineEdit->setText(ui->tableSlipPembayaran->model()->index(baris,3).data().toString());
    ui->kuantitiLineEdit->setText(ui->tableSlipPembayaran->model()->index(baris,4).data().toString());
    ui->totalHargaLineEdit->setText(ui->tableSlipPembayaran->model()->index(baris,4).data().toString());
}

