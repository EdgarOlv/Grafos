#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <deque>
#include <QVector>
#include <QPixmap>

QVector <int> avisitar2;

using namespace std;


int visitados[11],pai[11],custov[11];
int i,j,y,v,custo, vertices, arestas,temp,temp2, opcao=1;
int matriz[11][11];
QList<int> avisitar;
QString fileName, line;


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QPixmap pix("C:/Users/edgar/Desktop/IA/grafo.png");

    int x1 = ui->label_5->width ();
    int y1 = ui->label_5->height ();
    ui->label_5->setPixmap(pix.scaled (x1,y1,Qt::KeepAspectRatio));

    //ui->label_5->setPixmap(pix);
}

void MainWindow::on_pushButton_2_clicked()  // Buscar arquivo
{
    ui->lineEdit->clear();
        ui->lineEdit_2->clear();
        ui->label_7->clear();
        ui->listWidget->clear();


    QFile file(QFileDialog::getOpenFileName(this, tr("Open File"), "C:/Users/edgar/Desktop/IA", tr("Arquivo de Texto (*.txt)")));
    file.open(QIODevice::ReadOnly | QIODevice::Text);
    QTextStream s(&file);

    ui->label_8->setText(file.fileName());

    int x=0, y=0, z=0;

    s >> vertices >> arestas;

    for(i=0; i<arestas; i++)    // atribuir nos e custos
       {
          s >> x >> y >> z;
          matriz[x][y] = z;
       }
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pushButton_clicked()
{

    for(i=0; i<vertices; i++){
        for(j=0; j<arestas; j++)
            visitados[i] = 0;
            pai[i] = 0;
            custov[i] =0;
    }
    custo =0;

    switch(opcao)
    {
        case 1:


            while(avisitar.empty()!=1){
                 avisitar.pop_front();
            }

            ui->listWidget->clear();
            i= ui->lineEdit->text().toInt();
            j= ui->lineEdit_2->text().toInt();

            if(i>10 or j>10){
                QMessageBox msgB1;
                msgB1.setText("Um dos nós não existe");
                msgB1.exec();
            }
            else{
                v=0;
                avisitar.push_front(i);
                while(avisitar.empty()!=1){
                    i = avisitar.front();
                    avisitar.pop_front();
                    visitados[i]= 1;
                        if(i==j){
                            v=1;
                            for(int k =1; k<11; k++){
                                visitados[k]=0;
                            }
                        break;
                        }
                        for(int k=1;k<11; k++ ){
                            if(matriz[i][k] != 0 and visitados[k]==0 ){
                               avisitar.push_back(k);
                               visitados[k]= 1;
                               pai[k]=i;
                            }
                        }
                }
                if(v==1){
                    int y = 0;
                    y = j;
                    QString caminho = QString::number(y);
                    ui->listWidget->addItem("Caminho: " );
                    ui->listWidget->addItem(caminho);
                    custo = 0;
                    while(pai[y]!=0){
                       QString caminho = QString::number(pai[y]);
                       ui->listWidget->insertItem(1,caminho);
                       custo= matriz[pai[y]][y]+ custo;
                       y=pai[y];
                    }
                    ui->label_7->setNum(custo);

                }else{
                QMessageBox msgB;
                msgB.setText("Os nos nao estao conectados");
                msgB.exec();
                    for(int k =0; k<11; k++){
                    visitados[k]=0;
                    }
                }
            }

        break;

        case 2:

            avisitar2.clear();
            for(int i=1; i<vertices+1; i++)
                pai[i]=0;
                custov[i]=0;
                ui->listWidget->clear();
                i= ui->lineEdit->text().toInt();
                j= ui->lineEdit_2->text().toInt();

                v=0;
                avisitar2.push_back(i);
                custov[i]=0;

                while(avisitar2.empty()!=1 ){
                    i = avisitar2.at(0);
                    avisitar2.erase(avisitar2.begin()+0);
                    visitados[i]= 1;

                    for(int k=0;k<=vertices; k++ ){
                        if(matriz[i][k] != 0 and visitados[k]==0 ){
                            if(custov[j]==0 or custov[j]>matriz[i][k] + custov[i]){
                            custov[k] = matriz[i][k] + custov[i];
                            avisitar2.push_back(k);
                            pai[k]=i;
                            }
                        }
                    }

                    for(int z=0;z<avisitar2.size();z++){
                        temp=custov[avisitar2.at(z)];
                        temp2= avisitar2.at(z);
                        for(int w=z+1;w<avisitar2.size();w++){
                            if(custov[avisitar2.at(w)]< custov[avisitar2.at(z)]){
                                avisitar2.insert(avisitar2.begin()+z,avisitar2.at(w));
                                avisitar2.insert(avisitar2.begin()+w,temp2);
                                avisitar2.erase(avisitar2.begin()+(z+1));
                                avisitar2.erase(avisitar2.begin()+(w+1));
                                }
                            }
                    }

                if(i==j){
                    v=1;
                    for(int k =0; k<vertices; k++){
                        visitados[k]=0;
                    }
                    break;
                }

                 }
                if(v==1 ){
                    int y =j;

                    QString caminho = QString::number(y);
                    ui->listWidget->addItem("Caminho: " );
                    ui->listWidget->addItem(caminho);


                    std::cout << y << " ";

                    while(pai[y]!=0){
                        QString caminho = QString::number(pai[y]);
                        ui->listWidget->insertItem(1,caminho);
                        custo= matriz[pai[y]][y]+ custo;
                        y=pai[y];
                    }
                    ui->label_7->setNum(custov[j]);


                }else{
                    QMessageBox msgB;
                    msgB.setText("Os nos nao estao conectados");
                    msgB.exec();
                    for(int k =0; k<vertices; k++){
                    visitados[k]=0;
                }
                }
                for(i=0; i<vertices; i++){
                    for(j=0; j<arestas; j++)
                        visitados[i] = 0;
                        pai[i] = 0;
                        custov[i] =0;
                }
                custo =0;
        break;
     }
}

void MainWindow::on_radioButton_clicked()
{
    opcao = 1;
}

void MainWindow::on_radioButton_2_clicked()
{
    opcao = 2;
}
