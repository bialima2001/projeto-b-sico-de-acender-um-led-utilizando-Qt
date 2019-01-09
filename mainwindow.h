#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSerialPort> //inclui  duas bibliotecas a QSerialPort para comunicação serial e a QDebug para me ajudar a ver as variaveis
#include <QDebug>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
    //criação de duas string para enviar informação pelo serial, o conteudo é igual as do progama do arduino para facilitar a comunicação e o meu entendimento
    const QString ledaceso = "LED1"; // utilizei a palavra LED e 1 para aceso ou 0 para apagado
    const QString ledapagado = "LED0";
    int statusLed = 0; // variavel para guardar o status do led, 1 para aceso e zero para apagado
    QSerialPort serial; // objeto do tipo QSerialPort

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();


    int getStatusLed() const;
    void setStatusLed(int value);

private slots:
    void on_pushButton_clicked(); // botão click
    void dados(); // função que lê os dados da serial
    void on_pushButton_2_clicked(); // botão pra conectar a porta

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
