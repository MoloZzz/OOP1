#include "mainwindow.h"
#include "ui_mainwindow.h"



MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->timeEdit->setTime(QTime::currentTime());

    timer = new QTimer(this);

    connect(timer, SIGNAL(timeout()) ,this ,SLOT(TimerSlot()) );

    timer->start(1000);
}

MainWindow::~MainWindow()
{
    delete ui;
}

std::vector<timeT> mainList;



void MainWindow::TimerSlot()
{

date = QDate::currentDate();

time = QTime::currentTime();

time.setHMS(time.hour(),time.minute(),time.second(),0);

if(!mainList.empty()){

if(date == mainList.begin()->date && time == mainList.begin()->time){

    QMessageBox::about(this,"bzzz","bzzz");



    ui->listWidget->clear();

}

}

}




void sortV(std::vector<timeT> &V){

    if(V.size() <= 1){
        return void();
    }

    int x = 0;
    timeT tmp;
    for (int i = V.size() - 1; i >= x; i--)
    {
        for (int j = V.size() - 1; j >= x; j--)    {
            if ((V[j].date < V[j-1].date) || (V[j].date <= V[j-1].date || V[j].time < V[j-1].time))    {
                tmp = V[j];
                V[j] = V[j-1];
                V[j-1] = tmp;
            }

        }
     x++;
    }


}


//add budilik
void MainWindow::on_pushButton_clicked()
{

QDate Date = ui->calendarWidget->selectedDate();

QTime Time = ui->timeEdit->time();

Time.setHMS(Time.hour(),Time.minute(),0,0);

QString Info = ui->textEdit->toPlainText();

QString Type = "budilnik";


if(( Date == QDate::currentDate() && Time > QTime::currentTime() ) || ( Date > QDate::currentDate()) ){

    for(const timeT &child: mainList){

        if(child.date == Date && child.time == Time){

            QMessageBox::warning(this,"Помилка","Будильник з таким часом вже є");

            return void();

        }


    }

    timeT newNode(Time,Date,Info,Type);

    mainList.push_back(newNode);
   // sortV(mainList);


    QMessageBox::about(this,"Додано успішно",Date.toString("dd.MM.yyyy") + " " + Time.toString("hh:mm") + " " + Info + " " + "Будильник");

    ui->timeEdit->setTime(QTime::currentTime());
    ui->textEdit->setText("");


    QString outString = Date.toString("dd.MM.yyyy") + " " + Time.toString("hh:mm") + " " + " " + "Будильник " + Info;

    ui->listWidget->addItem(outString);

}else{

    ui->timeEdit->setTime(QTime::currentTime());

    ui->textEdit->setText("");

    QMessageBox::warning(this,"Помилка вводу","Некоректні дані,перевірте ввід");
}




}


//add timer
void MainWindow::on_pushButton_2_clicked()
{
    int h = ui->lineEdit->text().toInt();

    int m = ui->lineEdit_2->text().toInt();

    int s = ui->lineEdit_3->text().toInt();



    if(( h <= 0 && m <= 0 && s <= 0 ) || h >= 24 || m >= 60 || s >= 60){

        QMessageBox::warning(this,"Помилка","Некоректні дані!");

        return void();
    }


    QDate resD = QDate::currentDate();

    QTime resT = QTime::currentTime();

    int resSecond = resT.second();
    int resMinute = resT.minute();
    int resHour =  resT.hour();

    while(h != 0 || m != 0 || s != 0){

        if(resSecond + s >= 60){
            resSecond = resSecond + s - 60;
            resMinute = resMinute + 1;
            s = 0;
        }else{
            resSecond = resSecond + s;
            s = 0;
        }

        if(resMinute + m >= 60){
            resMinute = resMinute + m - 60;
            resHour = resHour + 1;
            m = 0;
        }else{
            resMinute = resMinute + m;
            m = 0;
        }

        if(resHour + h >= 24){
            resHour = resHour + h - 24;
            h = 0;
            resD = resD.addDays(1);
        }else{
            resHour = resHour + h;
            h = 0;
        }

        const QString fileway = ui->lineEdit_4->text();


     mainList.push_back(timeT(QTime(resHour,resMinute,resSecond),resD,fileway,"timer"));

     sortV(mainList);

      QString outString;
     if(fileway != "" || fileway != nullptr){

         QMessageBox::about(this,"Додано успішно",resD.toString("dd.MM.yyyy") + " " + QTime(resHour,resMinute,resSecond).toString("hh:mm") + " "
                            + "Таймер \nЯкщо шлях вірний,то по закінченню часу відкриється файл: " + fileway);

         outString = resD.toString("dd.MM.yyyy") + " " + QTime(resHour,resMinute,resSecond).toString("hh:mm") + " "
                 + "Таймер, відкриває файл: " + fileway;
     }else{
         QMessageBox::about(this,"Додано успішно",resD.toString("dd.MM.yyyy") + " " + QTime(resHour,resMinute,resSecond).toString("hh:mm") + " " + "Таймер");
         outString = resD.toString("dd.MM.yyyy") + " " + QTime(resHour,resMinute,resSecond).toString("hh:mm") + " " + "Таймер";

     }

    ui->lineEdit_4->setText("");
    ui->lineEdit->setText("0");
    ui->lineEdit_2->setText("0");
    ui->lineEdit_3->setText("0");


    ui->listWidget->addItem(outString);

    }
}

