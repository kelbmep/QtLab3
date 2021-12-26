#include "mainwindow.h"
#include "ui_mainwindow.h"


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

void MainWindow::on_show_clicked()
{
    ui->gsWidget->convexHull();
}

void MainWindow::on_generate_clicked()
{
    ui->gsWidget->generatePoints(ui->pNumber->value() * 1000);
}
