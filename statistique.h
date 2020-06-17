#ifndef STATISTIQUE_H
#define STATISTIQUE_H


#include <QtCharts/QChartView>
#include <QtCharts/QBarSeries>

class statistique
{
public:
    statistique();
    void Loaddata();
private :

  QtCharts::QChartView* chartview;
  QtCharts::QBarSeries *barseries;


};

#endif // STATISTIQUE_H
