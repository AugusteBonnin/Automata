#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>

namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = 0);
    ~Widget();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_comboBox_currentIndexChanged(int index);

private:
    Ui::Widget *ui;

    unsigned char applyRule(unsigned char a, unsigned char b, unsigned char c, unsigned char seed);
    void TypeI(QImage &image);
    void TypeII(QImage &image);
    void TypeIII(QImage &image);
    void TypeIV(QImage &image);
    void TypeV(QImage &image);
    void compute4ConnectedComponents(QImage &image, int &black, int &white);
    bool connectionTest(QImage &image, QPoint &p1, QPoint &p2, QVector<int> &minPoint);
    void compute8ConnectedComponents(QImage &image, int &black, int &white);
    void TypeVI(QImage &image);
    int count8Neighbours(QImage &image, int j, int i);
};

#endif // WIDGET_H
