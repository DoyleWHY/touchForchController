#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QTime>
#include <QTimer>

static CGlobal uiGlobal;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    touch(new touchUSBNode()),
    graphnode(new GlGragh()),
    ui(new Ui::MainWindow)
{
    cout << "Step1:Initialize UI interface...";
    ui->setupUi(this);
    cout << "   OK!" << endl;

    cout << "Step2:Initialize touch interface...";
    touch->initUSBTouch();

    cout << "Step3 : Initialize opengl graph\n";
    graphnode->resize(700,700);
    graphnode->show();
    cout << "*********************************" << endl;

    QTimer *timer = new QTimer(this);
    timer->start(100);
    connect(timer,SIGNAL(timeout()),this,SLOT(realTimeUpdate()));

    ui->lineEdit_16->setText(QString::number(0));
    ui->lineEdit_17->setText(QString::number(0));
    ui->lineEdit_18->setText(QString::number(0));
    ui->lineEdit_19->setText(QString::number(0));
    ui->lineEdit_20->setText(QString::number(0));
    ui->lineEdit_21->setText(QString::number(0));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::realTimeUpdate()
{
    static QString strCPOSA1, strCPOSB1, strCPOSC1;
    static QString strCPOSA2, strCPOSB2, strCPOSC2, strCPOSD2, strCPOSE2, strCPOSF2;
    static QString strCPOSA3, strCPOSB3, strCPOSC3;
    static QString strCPOSA4, strCPOSB4, strCPOSC4;

    touch->realTimeTouch();
    graphnode->drawonline();

    strCPOSA1.sprintf("%.4f",uiGlobal.touchState.position[0]);
    ui->lineEdit->setText(strCPOSA1);
//    cout << uiGlobal.testValue << endl;
    strCPOSB1.sprintf("%.4f",uiGlobal.touchState.position[1]);
    ui->lineEdit_2->setText(strCPOSB1);
    strCPOSC1.sprintf("%.4f",uiGlobal.touchState.position[2]);
    ui->lineEdit_3->setText(strCPOSC1);

    strCPOSA2.sprintf("%ld",uiGlobal.touchState.encoder_values[0]);
    ui->lineEdit_4->setText(strCPOSA2);
    strCPOSB2.sprintf("%ld",uiGlobal.touchState.encoder_values[1]);
    ui->lineEdit_5->setText(strCPOSB2);
    strCPOSC2.sprintf("%ld",uiGlobal.touchState.encoder_values[2]);
    ui->lineEdit_6->setText(strCPOSC2);
    strCPOSD2.sprintf("%ld",uiGlobal.touchState.encoder_values[3]);
    ui->lineEdit_7->setText(strCPOSD2);
    strCPOSE2.sprintf("%ld",uiGlobal.touchState.encoder_values[4]);
    ui->lineEdit_8->setText(strCPOSE2);
    strCPOSF2.sprintf("%ld",uiGlobal.touchState.encoder_values[5]);
    ui->lineEdit_9->setText(strCPOSF2);

    strCPOSA3.sprintf("%.4f",uiGlobal.touchState.jointTorqueValues[0]);
    ui->lineEdit_10->setText(strCPOSA3);
    strCPOSB3.sprintf("%.4f",uiGlobal.touchState.jointTorqueValues[1]);
    ui->lineEdit_11->setText(strCPOSB3);
    strCPOSC3.sprintf("%.4f",uiGlobal.touchState.jointTorqueValues[2]);
    ui->lineEdit_12->setText(strCPOSC3);

    strCPOSA4.sprintf("%.4f",uiGlobal.touchState.forceValues[0]);
    ui->lineEdit_13->setText(strCPOSA4);
    strCPOSB4.sprintf("%.4f",uiGlobal.touchState.forceValues[1]);
    ui->lineEdit_14->setText(strCPOSB4);
    strCPOSC4.sprintf("%.4f",uiGlobal.touchState.forceValues[2]);
    ui->lineEdit_15->setText(strCPOSC4);

}

void MainWindow::on_pushButton_clicked()
{
    uiGlobal.setTouchState.jointTorqueValues[0] = ui->lineEdit_16->text().toDouble();
    uiGlobal.setTouchState.jointTorqueValues[1] = ui->lineEdit_17->text().toDouble();
    uiGlobal.setTouchState.jointTorqueValues[2] = ui->lineEdit_18->text().toDouble();
    cout << uiGlobal.setTouchState.jointTorqueValues[0] << uiGlobal.setTouchState.jointTorqueValues[1] << uiGlobal.setTouchState.jointTorqueValues[2] << endl;
    forceTorqueMode = 2;
    touch->setTorque();
}

void MainWindow::on_pushButton_2_clicked()
{
    uiGlobal.setTouchState.forceValues[0] = ui->lineEdit_19->text().toDouble();
    uiGlobal.setTouchState.forceValues[1] = ui->lineEdit_20->text().toDouble();
    uiGlobal.setTouchState.forceValues[2] = ui->lineEdit_21->text().toDouble();
    cout << uiGlobal.setTouchState.forceValues[0] << uiGlobal.setTouchState.forceValues[1] << uiGlobal.setTouchState.forceValues[2] << endl;
    forceTorqueMode = 1;
    touch->setForce();
}

void MainWindow::on_pushButton_3_clicked()
{
    uiGlobal.setTouchState.jointTorqueValues[0] = 0;
    uiGlobal.setTouchState.jointTorqueValues[1] = 0;
    uiGlobal.setTouchState.jointTorqueValues[2] = 0;
    uiGlobal.setTouchState.forceValues[0] = 0;
    uiGlobal.setTouchState.forceValues[1] = 0;
    uiGlobal.setTouchState.forceValues[2] = 0;

    ui->lineEdit_16->setText(QString::number(0));
    ui->lineEdit_17->setText(QString::number(0));
    ui->lineEdit_18->setText(QString::number(0));
    ui->lineEdit_19->setText(QString::number(0));
    ui->lineEdit_20->setText(QString::number(0));
    ui->lineEdit_21->setText(QString::number(0));
}

void MainWindow::on_pushButton_4_clicked()
{
    ui->lineEdit_16->setEnabled(true);
    ui->lineEdit_17->setEnabled(true);
    ui->lineEdit_18->setEnabled(true);
    ui->pushButton_4->setDisabled(true);
    ui->pushButton_6->setDisabled(true);
    ui->pushButton->setEnabled(true);
    cout << "( joint torque )key the specific parameters..." << endl;
}

void MainWindow::on_pushButton_6_clicked()
{
    ui->lineEdit_19->setEnabled(true);
    ui->lineEdit_20->setEnabled(true);
    ui->lineEdit_21->setEnabled(true);
    ui->pushButton_6->setDisabled(true);
    ui->pushButton_4->setDisabled(true);
    ui->pushButton_2->setEnabled(true);
    cout << "( effector force )key the specificparameters..." << endl;
}

void MainWindow::on_pushButton_5_clicked()
{
    ui->lineEdit_16->setDisabled(true);
    ui->lineEdit_17->setDisabled(true);
    ui->lineEdit_18->setDisabled(true);
    ui->lineEdit_19->setDisabled(true);
    ui->lineEdit_20->setDisabled(true);
    ui->lineEdit_21->setDisabled(true);

    ui->pushButton->setDisabled(true);
    ui->pushButton_2->setDisabled(true);
    ui->pushButton_4->setEnabled(true);
    ui->pushButton_6->setEnabled(true);
    touch->disableForceFeedback(forceTorqueMode);
}

