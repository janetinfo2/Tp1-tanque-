#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>
#include <QTimer>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    timer.start(1000);

    connect(&timer, SIGNAL (timeout()),  this, SLOT (tanklevel()));
    connect(ui->tankbutton, SIGNAL (clicked()),  this, SLOT (setCapacity()));
}

MainWindow::~MainWindow()
{
    delete ui;
}


 int MainWindow::Qin()
{
    bool ok;

    // qstring es una clase de Qt para manejar cadenas de caracteres
    //aux1 almacena el texto contenido en qin para luego convertirlo en entero
    QString aux1 = ui->lineEdit_2->text();
     qDebug() << aux1;
    //utilizo la funcion toInt de qstring para convertir a entero y lo almaceno en Qin
    //&ok es un puntero a una variable booleana que se usa para ver si se convirtió bien
    int Qin = aux1.toInt(&ok);
    if (ok==true && Qin > 0)
        return Qin;
    else
    {
        qDebug() << "Qin es inválido";
        return -1;
    }
}
 int MainWindow::Qout()
{
    bool ok;
    QString aux2 = ui->QOUT->text();
    int Qout = aux2.toInt(&ok);
    if (ok==true && Qout > 0)
        return Qout;
    else
    {
        qDebug() << "Qout es inválido";
        return -1;
    }
}
int MainWindow::capacitytank()
{
    bool ok;
    QString aux3 = ui->CAPACITY->text();
    int CAP = aux3.toInt(&ok);
    if (ok==true && CAP > 0)
        return CAP;
    else
    {
        qDebug() << "la capacidad no es valida";
        return -1;
    }
}

int MainWindow::llenar()
{
    int qin = Qin();
    if (qin <= 0)
    {
        qDebug() << "Error: El caudal de entrada es inválido.";
        return -1;
    }
    int kin = ui->KIN->value();
    int llenar = (qin * kin)/100;

    return llenar;
}

int MainWindow::vaciar()
{
    int qout = Qout();
    if (qout <= 0)
    {
        qDebug() << "Error: El caudal de salida es inválido.";
        return -1;
    }
    int kout = ui->KOUT->value();
    int vaciar = (qout * kout)/100;

    return vaciar;
}

void MainWindow::tanklevel()
{
    int llenado = llenar();
    int vaciado = vaciar();
    int capacity = capacitytank();
    if (llenado == -1 || vaciado == -1)
    {
        qDebug() << "Error en el llenado o vaciado";
        return ;
    }
    int level = ui->progressBar->value();
    //qmin devuelve el valor min y q max el valor max, entonces si el nivel calculado es mayor de capacity
    //igualemente muestra capacity pq seria el valor menor. qmax limita el nivel minimo a cero.
    //si el nivel calculado es menor que cero, igual devuelve cero
    int newlevel = qMax(0, qMin(level + llenado - vaciado, capacity));
     qDebug() << newlevel;
    ui->progressBar->setValue(newlevel);
}
void MainWindow::setCapacity()
{
    int cap = capacitytank();
    if (cap > 0)
    {
        ui->progressBar->setMaximum(cap); // También actualizar la barra de progreso
        qDebug() << "la capacidad es de " << cap << " litros.";
    } else {
        qDebug() << "Capacidad inválida.";
    }
}



