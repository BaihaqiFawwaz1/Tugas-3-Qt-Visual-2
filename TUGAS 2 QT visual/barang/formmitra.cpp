#include "formmitra.h"
#include "ui_formmitra.h"
#include "QMessageBox"

FormMitra::FormMitra(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::FormMitra)
{
    ui->setupUi(this);

    loadtableMitra();
}

FormMitra::~FormMitra()
{
    delete ui;
}

void FormMitra::loadtableMitra()
{
    tableModel = new QSqlQueryModel(this);
    tableModel->setQuery("SELECT*FROM mitra ORDER BY kd_mitra ASC");
    tableModel->setHeaderData(0,Qt::Horizontal,QObject::tr("kd_mitra"));
    tableModel->setHeaderData(1,Qt::Horizontal,QObject::tr("nama_mitra"));
    tableModel->setHeaderData(2,Qt::Horizontal,QObject::tr("alamat"));
    tableModel->setHeaderData(3,Qt::Horizontal,QObject::tr("telp"));

    ui->tableMitra->setModel(tableModel);
    ui->tableMitra->setColumnWidth(0,150);
    ui->tableMitra->setColumnWidth(0,150);
    ui->tableMitra->setColumnWidth(0,200);
    ui->tableMitra->setColumnWidth(0,150);
    ui->tableMitra->show();
}

void FormMitra::on_pushButton_clicked()
{
    if(ui->kodeMitraLineEdit->text().isEmpty()){
    QMessageBox::information(this, "warning", "Kd Mitra Belum Di Isi");
    ui->kodeMitraLineEdit->setFocus();

    }else if(ui->namaMitraLineEdit->text().isEmpty()){
    QMessageBox::information(this, "warning", "Nama Mitra Belum Di Isi");
    ui->namaMitraLineEdit->setFocus();

    }else if(ui->alamatLineEdit->text().isEmpty()){
    QMessageBox::information(this, "warning", "Alamat Belum Di Isi");
    ui->alamatLineEdit->setFocus();

    }else if(ui->telpLineEdit->text().isEmpty()){
    QMessageBox::information(this, "warning", "Telp Belum Di Isi");
    ui->telpLineEdit->setFocus();
    }else {

        QSqlQuery duplikat;
        duplikat.prepare("SELECT * FROM mitra WHERE kd_mitra = '"+ui->kodeMitraLineEdit->text()+"'");
        duplikat.exec();
        if(duplikat.next()){
            QMessageBox::information(this, "warning", "kd_mitra sudah terdaftar");
            ui->namaMitraLineEdit->setText(duplikat.value(1).toString());
            ui->alamatLineEdit->setText(duplikat.value(2).toString());
            ui->telpLineEdit->setText(duplikat.value(3).toString());
        }else{

            QSqlQuery sql (koneksi);
            sql.prepare("INSERT INTO mitra (kd_mitra, nama_mitra, alamat, telp)"
                        "VALUE (:kd_mitra, :nama_mitra, :alamat, :telp)");
            sql.bindValue(":kd_mitra",ui->kodeMitraLineEdit->text());
            sql.bindValue(":nama_mitra",ui->namaMitraLineEdit->text());
            sql.bindValue(":alamat",ui->alamatLineEdit->text());
            sql.bindValue(":telp",ui->telpLineEdit->text());

            if (sql.exec()){
                qDebug()<<"Data Berhasil Di Simpan";
            }else{
                qDebug()<<sql.lastError().text();
            }
        }
    }
}


void FormMitra::on_pushButton_2_clicked()
{
    QSqlQuery sql (koneksi);
    sql.prepare("UPDATE mitra SET nama_mitra=:nama_mitra, alamat=:alamat, telp=:telp WHERE kd_mitra=:kd_mitra");
    sql.bindValue(":kd_mitra",ui->kodeMitraLineEdit->text());
    sql.bindValue(":nama_mitra",ui->namaMitraLineEdit->text());
    sql.bindValue(":alamat",ui->alamatLineEdit->text());
    sql.bindValue(":telp",ui->telpLineEdit->text());

    if (sql.exec()){
        qDebug()<<"Data Berhasil Di Edit";
    }else{
        qDebug()<<sql.lastError().text();
    }
}


void FormMitra::on_pushButton_4_clicked()
{
    QSqlQuery sql(koneksi);
    QSqlRecord cari;
    sql.prepare("SELECT * FROM mitra WHERE kd_mitra=:kd_mitra");
    sql.bindValue(":kd_mitra",ui->kodeMitraLineEdit->text());

    if (sql.exec()){
        QSqlRecord cari = sql.record();
        // ui->namaLineEdit->setText(cari.value());
        qDebug()<<cari.value(0).toString();
    }else{
        qDebug()<<sql.lastError().text();
    }
}


void FormMitra::on_pushButton_3_clicked()
{
    QSqlQuery sql(koneksi);
    sql.prepare("DELETE FROM mitra WHERE kd_mitra=:kd_mitra");
    sql.bindValue(":kd_mitra",ui->kodeMitraLineEdit->text());

    if (sql.exec()){
        qDebug()<<"Data Berhasil Di Hapus";
    }else{
        qDebug()<<sql.lastError().text();
    }
}


void FormMitra::on_tableMitra_activated(const QModelIndex &index)
{
    int baris = ui->tableMitra->currentIndex().row();
    // QMessageBox::information(this, "warning", QString::number(baris));
    ui->kodeMitraLineEdit->setText(ui->tableMitra->model()->index(baris,0).data().toString());
    ui->namaMitraLineEdit->setText(ui->tableMitra->model()->index(baris,1).data().toString());
    ui->alamatLineEdit->setText(ui->tableMitra->model()->index(baris,2).data().toString());
    ui->telpLineEdit->setText(ui->tableMitra->model()->index(baris,3).data().toString());
}

