#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <iostream>
#include <qfiledialog.h>
#include <QGraphicsScene>
#include <QColor>
#include<sstream>
#include <fstream>
using namespace std;

Neurona::Neurona(){}

Neurona::Neurona(int i,float v,int px,int py,int r,int b,int g){
    id=i;
    voltaje=v;
    posicion_x=px;
    posicion_y=py;
    red=r;
    blue=b;
    green=g;
}

string Neurona::print(){
    string s;
    ostringstream o;
    o <<"ID:"<<id<<endl
    <<"Voltaje:"<<voltaje<<endl
    <<"Posicion x:"<<posicion_x<<endl
    <<"Posicion y:"<<posicion_y<<endl
    <<"Rojo:"<<red<<endl
    <<"Azul:"<<blue<<endl
    <<"Verde:"<<green<<endl<<endl;
    s = o.str();
    return s;
}

void Neurona::salvar(fstream& out){
    out<<id<<endl;
    out<<voltaje<<endl;
    out<<posicion_x<<endl;
    out<<posicion_y<<endl;
    out<<red<<endl;
    out<<blue<<endl;
    out<<green<<endl;
}

void Neurona::cargar(fstream& in){
    in>>id;
    in>>voltaje;
    in>>posicion_x;
    in>>posicion_y;
    in>>red;
    in>>blue;
    in>>green;
}

administrar::administrar(){
    aux=0;
}

void administrar::agregar_inicio(Neurona n){
    vect.insert(vect.begin(), n);
    aux++;
}

void administrar::salvar(fstream& out){
    out<<aux<<endl;
    for(int i=0;i<aux;i++){
        vect[i].salvar(out);
    }
}

void administrar::cargar(fstream& in){
    in>>aux;
    for(int i=0;i<aux;i++){
        Neurona n;
        n.cargar(in);
        vect.insert(vect.end(), n);
    }
}

void administrar::agregar_final(Neurona n){
    vect.insert(vect.end(), n);
    aux++;
}

string administrar::mostrar(){
    string s;
    ostringstream o;
    for(int i=0;i<aux;i++){
        o<<vect[i].print();
    }
    s = o.str();
    return s;
}

bool administrar::validar_id(int id){
    bool maybe;
    for(int i=0;i<aux;i++){
        if(vect[i].id == id)
            maybe=true;
        else
            maybe=false;
    }
    return maybe;
}

Neurona* administrar::buscarn(int id){
    Neurona* N;
    for(int i=0;i<aux;i++){
        if(vect[i].id == id)
            N=&vect[i];
    }
    return N;
}

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_inicio_clicked()
{
    int id = ui->id->value();
    float volt = ui->volt->value();
    int posx = ui->posx->value();
    int posy = ui->posy->value();
    int red = ui->red->value();
    int blue = ui->blue->value();
    int green = ui->green->value();
    string r = "Id repetido, por favor ingrese otro";
    string s = "Neurona ingresada";
    if(admin.validar_id(id)){
        ui->pantallaid->setPlainText(QString::fromStdString (r));
    }
    else{
        Neurona n(id,volt,posx,posy,red,blue,green);
        admin.agregar_inicio(n);
        ui->pantallaid->setPlainText(QString::fromStdString (s));
    }
}


void MainWindow::on_final_2_clicked()
{
    int id = ui->id->value();
    float volt = ui->volt->value();
    int posx = ui->posx->value();
    int posy = ui->posy->value();
    int red = ui->red->value();
    int blue = ui->blue->value();
    int green = ui->green->value();
    string r = "Id repetido, por favor ingrese otro";
    string s = "Neurona ingresada";
    if(admin.validar_id(id)){
        ui->pantallaid->setPlainText(QString::fromStdString (r));
    }
    else{
        Neurona n(id,volt,posx,posy,red,blue,green);
        admin.agregar_final(n);
        ui->pantallaid->setPlainText(QString::fromStdString (s));
    }
}


void MainWindow::on_mostrar_clicked()
{
    string s = admin.mostrar();
    ui->pantalla->setPlainText(QString::fromStdString (s));
}


void MainWindow::on_actionAbrir_triggered()
{
    QString Filenameopen = QFileDialog::getOpenFileName(this,"Abrir archivo",".","archivo (*.txt)") ;
    string file=Filenameopen.toStdString();
    fstream entrada(file,ios_base::in);
    admin.cargar(entrada);
}


void MainWindow::on_actionGuardar_triggered()
{
    QString Filenamesave = QFileDialog::getSaveFileName(this,"Guardar archivo",".","archivo (*.txt)");
    string file=Filenamesave.toStdString();
    fstream salida(file,ios_base::out);
    admin.salvar(salida);
}


void MainWindow::on_mostrar_tabla_button_clicked()
{
    ui->tableWidget->setColumnCount(7);
    QStringList headers = {"ID","Voltaje","X","Y","RED","BLUE","GREEN"};
    ui->tableWidget->setHorizontalHeaderLabels(headers);
    ui->tableWidget->setRowCount(admin.aux);
    for(int i=0;i<admin.aux;i++){
        Neurona* n=&admin.vect[i];
        int id = n->id;
        QString sid = QString::number(id);
        float volt = n->voltaje;
        QString svolt = QString::number(volt);
        int posx = n->posicion_x;
        QString sposx = QString::number(posx);
        int posy = n->posicion_y;
        QString sposy = QString::number(posy);
        int red = n->red;
        QString sred = QString::number(red);
        int blue = n->blue;
        QString sblue = QString::number(blue);
        int green = n->green;
        QString sgreen = QString::number(green);
        ui->tableWidget->setColumnCount(7);
        QStringList headers = {"ID","Voltaje","X","Y","RED","BLUE","GREEN"};
        ui->tableWidget->setHorizontalHeaderLabels(headers);
        ui->tableWidget->setRowCount(admin.aux+1);
        QTableWidgetItem *nid = new QTableWidgetItem(sid);
        QTableWidgetItem *nvolt = new QTableWidgetItem(svolt);
        QTableWidgetItem *nposx = new QTableWidgetItem(sposx);
        QTableWidgetItem *nposy = new QTableWidgetItem(sposy);
        QTableWidgetItem *nred = new QTableWidgetItem(sred);
        QTableWidgetItem *nblue = new QTableWidgetItem(sblue);
        QTableWidgetItem *ngreen = new QTableWidgetItem(sgreen);
        ui->tableWidget->setItem(i+1,0,nid);
        ui->tableWidget->setItem(i+1,1,nvolt);
        ui->tableWidget->setItem(i+1,2,nposx);
        ui->tableWidget->setItem(i+1,3,nposy);
        ui->tableWidget->setItem(i+1,4,nred);
        ui->tableWidget->setItem(i+1,5,nblue);
        ui->tableWidget->setItem(i+1,6,ngreen);
    }
}


void MainWindow::on_buscar_tabla_button_clicked()
{
    int idd = ui->buscarid->value();
    Neurona* n=admin.buscarn(idd);
    int id = n->id;
    QString sid = QString::number(id);
    float volt = n->voltaje;
    QString svolt = QString::number(volt);
    int posx = n->posicion_x;
    QString sposx = QString::number(posx);
    int posy = n->posicion_y;
    QString sposy = QString::number(posy);
    int red = n->red;
    QString sred = QString::number(red);
    int blue = n->blue;
    QString sblue = QString::number(blue);
    int green = n->green;
    QString sgreen = QString::number(green);
    ui->tableWidget->setColumnCount(7);
    QStringList headers = {"ID","Voltaje","X","Y","RED","BLUE","GREEN"};
    ui->tableWidget->setHorizontalHeaderLabels(headers);
    ui->tableWidget->setRowCount(2);
    QTableWidgetItem *nid = new QTableWidgetItem(sid);
    QTableWidgetItem *nvolt = new QTableWidgetItem(svolt);
    QTableWidgetItem *nposx = new QTableWidgetItem(sposx);
    QTableWidgetItem *nposy = new QTableWidgetItem(sposy);
    QTableWidgetItem *nred = new QTableWidgetItem(sred);
    QTableWidgetItem *nblue = new QTableWidgetItem(sblue);
    QTableWidgetItem *ngreen = new QTableWidgetItem(sgreen);
    ui->tableWidget->setItem(1,0,nid);
    ui->tableWidget->setItem(1,1,nvolt);
    ui->tableWidget->setItem(1,2,nposx);
    ui->tableWidget->setItem(1,3,nposy);
    ui->tableWidget->setItem(1,4,nred);
    ui->tableWidget->setItem(1,5,nblue);
    ui->tableWidget->setItem(1,6,ngreen);
}


void MainWindow::on_dibujar_button_clicked()
{
    QPen pen;
    pen.setWidth(2);
    QColor color(20,200,50);
    pen.setColor(color);
    escena.addEllipse(100,100, 50,50,pen);
    ui->PantallaNeuronas->setScene(&escena);
}


void MainWindow::on_limpiar_button_clicked()
{
    escena.clear();
}

