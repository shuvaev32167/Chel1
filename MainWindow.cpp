#include "MainWindow.h"
#include "ui_MainWindow.h"

#include <cmath>
#include <omp.h>

double Settings::eps_min = 100000.0;
double Settings::iStep = 0.05;
double Settings::minX = -0.5;
double Settings::maxX = 0.5;
double Settings::allX = Settings::maxX - Settings::minX;
double Settings::h_min;
int Settings::n = 4;
int Settings::nn =Settings::n-1;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void forr(const double h, Weight *w, const Trigon* vec,int i, const double &step,
          const double &begin, const double &end, MainWindow *mw, const bool flag)
{
    if (i != Settings::n)
    {
        double  bufs = w[i].vOld - 0.25,
                bufe = w[i].vOld + 0.25;

        double b = flag ? begin : bufs < 0 ? 0 : bufs,
                e = flag ? end : bufe > 1 ? 1 : bufe;
        for (w[i] = b; w[i] <= e; w[i] += step)
        {
            forr(h, w, vec, i + 1, step, begin, end, mw, flag);
        }
        return;
    }

    double eps = 0;

    int bufs = Settings::minX * 1000;
    int bufe = Settings::maxX * 1000;
    int bufh = Settings::iStep * 1000;
    #pragma omp parallel for reduction (+:eps)
    for(int i = bufs; i<=bufe; i+=bufh)
    {
            double x = i / 1000.0;
            double rez[Settings::n];

            for (int i = 0; i < Settings::n; ++i)
            {
                rez[i] = vec[i].func(x);
            }

            double y = 0;

            for (int i = 0; i < Settings::n; ++i)
            {
                y += w[i].v*rez[i];
            }

            double z = cos(M_PI*x);
            eps += fabs(z-y);
    }    // цикл по переменной X

    QApplication::processEvents(0);

    if (eps < Settings::eps_min)
    {
        for (int i = 0; i < Settings::n; ++i)
        {
            w[i].vMin = w[i].v;
        }
        Settings::h_min = h;
        Settings::eps_min = eps;
        mw->ui->Memo3->append(QString::number(Settings::eps_min));
    }
}


void MainWindow::changeEvent(QEvent *e)
{
    QMainWindow::changeEvent(e);
    switch (e->type()) {
    case QEvent::LanguageChange:
        ui->retranslateUi(this);
        break;
    default:
        break;
    }
}

void MainWindow::on_pushButtonRabb_clicked()
{
    // 4 треугольника
    double x;

    Trigon vec[Settings::n];
    Weight weigth[Settings::n];

    double h;
    double abs1, abs_max;

    ui->Memo1->clear();
    ui->Memo2->clear();
    ui->Memo3->clear();
    ui->Memo4->clear();
    Settings::eps_min = 100000.0;
    //103410
    //115946
    //101994
    QTime time;
    time.start();
    for (h = 1;h<=2; h+=0.025)  // 1.0 1.2
    { // цикл по параметру h
        for (int i = 0; i < Settings::n; ++i)
        {
            vec[i].initialization(Settings::allX, Settings::minX, h, i, Settings::nn);
        }

        forr(h, weigth, vec, 0, 0.05, 0, 1, this, true);

    } // цикл по параметру h

    qDebug() << time.elapsed();

    ui->Memo4->append("eps_min="+QString::number(Settings::eps_min));

    for (int i = 0; i < Settings::n;)
    {
        ui->Memo4->append(QString("v%2_min=%1").arg(QString::number(weigth[i++].vMin)).arg(QString::number(i)));
    }

    ui->Memo4->append("h_min=" + QString::number(Settings::h_min));
    ui->Memo2->append("Результаты: практический и теоретический");

    abs_max = 0;
    for (int i = 0; i <Settings:: n; ++i)
    {
        vec[i].initialization(Settings::allX, Settings::minX, Settings::h_min, i, Settings::nn);
    }

    for(x=Settings::minX;x<=Settings::maxX;x+=Settings::iStep)
    {
        double rez[Settings::n];
#pragma omp parallel for
        for (int i = 0; i < Settings::n; ++i)
        {
            rez[i] = vec[i].func(x);
        }

        double y = 0;

        for (int i = 0; i < Settings::n; ++i)
        {
            y += weigth[i].vMin*rez[i];
        }

        double z = cos(M_PI*x);
        abs1 = fabs(y-z);
        if (abs1 > abs_max)
            abs_max = abs1;
        ui->Memo2->append(QString("П:%1\nT:%2\nX=%3").arg(QString::number(y),QString::number(z), QString::number(x)));
    }    // цикл по переменной X

    ui->Memo1->append(QString("Абсолютная погрешность,\n%1%").arg(QString::number(abs_max*100)));

    ui->Memo1->append("2-й этап");
    ui->Memo2->append("2-й этап");
    ui->Memo3->append("2-й этап");
    ui->Memo4->append("2-й этап");

    // 2-й этап
    for (int i = 0; i < Settings::n; ++i)
    {
        weigth[i].vOld = weigth[i].vMin;
    }

    Settings::eps_min = 100000.0;

    double hMax = Settings::h_min + 0.25;

    for (h = Settings::h_min - 0.25;h <= hMax; h+=0.025)  // 1.0 1.2
    { // цикл по параметру h
        for (int i = 0; i < Settings::n; ++i)
        {
            vec[i].initialization(Settings::allX, Settings::minX, h, i, Settings::nn);
        }

        forr(h, weigth, vec, 0, 0.025, 0, 1, this, false);

    } // цикл по параметру h

    ui->Memo4->append("eps_min="+QString::number(Settings::eps_min));

    for (int i = 0; i < Settings::n;)
    {
        ui->Memo4->append(QString("v%2_min=%1").arg(QString::number(weigth[i++].vMin), QString::number(i)));
    }

    ui->Memo4->append("h_min=" + QString::number(Settings::h_min));
    ui->Memo2->append("Результаты: практический и теоретический");

    abs_max = 0;

    for (int i = 0; i < Settings::n; ++i)
    {
        vec[i].initialization(Settings::allX, Settings::minX, Settings::h_min, i, Settings::nn);
    }

    for(x=Settings::minX;x<=Settings::maxX;x+=Settings::iStep)
    {
        double rez[Settings::n];

        #pragma omp parallel for
        for (int i = 0; i < Settings::n; ++i)
        {
            rez[i] = vec[i].func(x);
        }

        double y = 0;

        for (int i = 0; i < Settings::n; ++i)
        {
            y += weigth[i].vMin*rez[i];
        }

        double z = cos(M_PI*x);
        abs1 = fabs(y-z/1);
        if (abs1 > abs_max)
            abs_max = abs1;
        ui->Memo2->append(QString("П:%1\nT:%2\nX=%3").arg(QString::number(y),QString::number(z), QString::number(x)));
    }    // цикл по переменной X
    ui->Memo1->append(QString("Абсолютная погрешность,\n%1%").arg(QString::number(abs_max*100)));

    qDebug() << time.elapsed();
    QMessageBox::information(this, "", QString::number(time.elapsed()));
}
