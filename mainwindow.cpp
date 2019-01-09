#include "mainwindow.h"
#include "ui_mainwindow.h"

//desnecessário comentar as duas proximas funções
int MainWindow::getStatusLed() const
{
    return statusLed;
}

void MainWindow::setStatusLed(int value)
{
    statusLed = value;
}

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(&serial, SIGNAL(readyRead()), this, SLOT(dados()));//conecta a serial do mesmo modo que o"salvar" e o "carregar do projetinho
    //na sequencia (endereço do objeto QSerialPort, sinal emitido(no caso, ler tudo que tá escrito na porta serial), janela (no caso, a própria mainWindow), função a ser chamada (no caso, dados))
}

MainWindow::~MainWindow()
{
    serial.close(); //
    delete ui;//n sei a utilidade, quando cria o programa já aparece, mas vou pesquisar sobre
}

void MainWindow::on_pushButton_clicked() // quando o botão "click" for clicado, n mudei os nomes dos botões por prguiça, pf não desistam de mim
{
    QString pacote; // criando uma string chamada pacote para enviar as informações na serial (enviar o pacote, entederam?KKKKKK)
    if (getStatusLed()==0){ // se o led estiver apagado
        pacote = "{"+ledaceso+"}"; // escrevendo no pacote "{LED1}"
        setStatusLed(1); //setando led como aceso
        serial.write(pacote.toUtf8()); //esccrevendo na porta serial uma string (pacote) em bits
    }else{ //se não
        pacote = "{"+ledapagado+"}"; // escrevendo no pacote "{LED0}"
        setStatusLed(0); // setando led como apagado
        serial.write(pacote.toUtf8());//esccrevendo na porta serial uma string (pacote) em bits
    }
    qDebug()<<"escrevendo:"<<pacote; // só pra testar se escreve mesmo
}

void MainWindow::dados() // essa função é para atualizar o status do led
{
    QString dados = serial.readAll();// criação de uma string para guardar os dados lidos na serial
    qDebug() << dados; // mostra a string, só pra saber mesmo
    if(dados.startsWith("{") && dados.endsWith("}")){//testa se a string começa com '{' e se termina com'}'
        if(dados.contains(ledaceso)){// a função contains tenta encontrar string dentro de outra, e retorna um booleano. Basicamente estamos testando se "LED1" está dentro dos dados
            setStatusLed(1); // seta o led como aceso
        }else if(dados.contains(ledapagado)){//se não se na string dados conter "LED0"
            setStatusLed(0);//setando o led como apagado
        }
    }
}

void MainWindow::on_pushButton_2_clicked() // esse botão é para conectar a porta USB (no exemplo foi utilizado a COM5, pq eu quis)
{
    serial.setPortName("COM5");//seta a porta COM5 (que eu utilizei no meu notebook) para comunicação, no projeto será necessário pedir ao usuário o nome da porta que ele utilizará.
    serial.setBaudRate(QSerialPort::Baud115200);//configura o numero de bits por segundos, é necessário que seja igual ao do arduino
    if(serial.open(QIODevice::ReadWrite)){ // essa função retorna um booleano referente a porta USB, se o Qt conseguir se comunicar com a porta, vai aparecer um "ok!" só pra saber se funcionou.
        qDebug()<<"ok!";
    }
}
