#include "widget.h"
#include "ui_widget.h"

#include <QSettings>
#include <QDir>
#include <QFileDialog>
#include <QDebug>

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);

    on_pushButton_clicked();
}

Widget::~Widget()
{
    delete ui;
}

void Widget::TypeI(QImage & image)
{

    for (int i = 0 ; i < ui->spinBox_2->value() ; i++)
        image.setPixel(0,i,(rand()>RAND_MAX/2)?0:1);

    int rule = rand() & 0xFF ;

    for (int j = 1 ; j < ui->spinBox->value() ; j++)
        for (int i = 0 ; i < ui->spinBox_2->value() ; i++)
            image.setPixel(j,i,applyRule(image.pixelIndex(j-1,(i+ui->spinBox_2->value()-1)%(ui->spinBox_2->value())),
                                         image.pixelIndex(j-1,i),
                                         image.pixelIndex(j-1,(i+1)%(ui->spinBox_2->value())),
                                         rule));

}

void Widget::TypeII(QImage & image)
{

    for (int i = 0 ; i < ui->spinBox_2->value() ; i++)
        image.setPixel(0,i,(rand()>RAND_MAX/2)?0:1);

    int rule1 = rand() & 0xFF ;
    int rule2 = rand() & 0xFF ;
    int proba = rand() ;

    for (int j = 1 ; j < ui->spinBox->value() ; j++)
        for (int i = 0 ; i < ui->spinBox_2->value() ; i++)
            image.setPixel(j,i,(rand()>proba)?
                               applyRule(image.pixelIndex(j-1,(i+ui->spinBox_2->value()-1)%(ui->spinBox_2->value())),
                                         image.pixelIndex(j-1,i),
                                         image.pixelIndex(j-1,(i+1)%(ui->spinBox_2->value())),
                                         rule1)
                             :
                               applyRule(image.pixelIndex(j-1,(i+ui->spinBox_2->value()-1)%(ui->spinBox_2->value())),
                                         image.pixelIndex(j-1,i),
                                         image.pixelIndex(j-1,(i+1)%(ui->spinBox_2->value())),
                                         rule2)
                               );

}


void Widget::TypeIII(QImage & image)
{
    image.fill(0);
    for (int i = 0 ; i < ui->spinBox_2->value() ; i++)
        image.setPixel(0,i,(rand()>RAND_MAX/2)?0:1);

    bool something_changed;
    do{
        something_changed = false ;
        for (int i = 0 ; i < image.height() ; i++)
            for (int j = 0 ; j < image.width() ; j++)
                if (!image.pixelIndex(j,i) )
                {
                    int count = 0 ;
                    count += image.pixelIndex(j,(i+1)%image.height()) ;
                    count += image.pixelIndex(j,(i+image.height()-1)%image.height()) ;
                    count += image.pixelIndex((j+1)%image.width(),i) ;
                    count += image.pixelIndex((j+image.width()-1)%image.width(),i) ;
                    count += image.pixelIndex((j+image.width()-1)%image.width(),(i+1)%image.height()) ;
                    count += image.pixelIndex((j+image.width()-1)%image.width(),(i+image.height()-1)%image.height()) ;
                    count += image.pixelIndex((j+1)%image.width(),(i+1)%image.height()) ;
                    count += image.pixelIndex((j+1)%image.width(),(i+image.height()-1)%image.height()) ;

                    if ((count)&&(count <=1))
                    {
                        something_changed = true ;
                        if ((rand()<RAND_MAX>>2))
                            image.setPixel(j,i,1);
                    }
                }
    }while(something_changed);
}
void Widget::TypeIV(QImage & image)
{
    image.fill(0);
    for (int i = 0 ; i < ui->spinBox_2->value() ; i++)
        image.setPixel(0,i,(rand()>RAND_MAX/2)?0:1);

    bool something_changed;
    do{
        something_changed = false ;
        for (int i = 0 ; i < image.height() ; i++)
            for (int j = 0 ; j < image.width() ; j++)
                if (!image.pixelIndex(j,i) )
                {
                    int count = 0 ;
                    count += image.pixelIndex(j,(i+1)%image.height()) ;
                    count += image.pixelIndex(j,(i+image.height()-1)%image.height()) ;
                    count += image.pixelIndex((j+1)%image.width(),i) ;
                    count += image.pixelIndex((j+image.width()-1)%image.width(),i) ;
                    count += image.pixelIndex((j+image.width()-1)%image.width(),(i+1)%image.height()) ;
                    count += image.pixelIndex((j+image.width()-1)%image.width(),(i+image.height()-1)%image.height()) ;
                    count += image.pixelIndex((j+1)%image.width(),(i+1)%image.height()) ;
                    count += image.pixelIndex((j+1)%image.width(),(i+image.height()-1)%image.height()) ;

                    if ((count)&&(count <=3))
                    {
                        something_changed = true ;
                        if ((rand()<RAND_MAX>>2))
                            image.setPixel(j,i,1);
                    }
                }
    }while(something_changed);
}

int Widget::count8Neighbours(QImage & image,int j,int i)
{

    int count = 0 ;
    count += image.pixelIndex(j,(i+1)%image.height()) ;
    count += image.pixelIndex(j,(i+image.height()-1)%image.height()) ;
    count += image.pixelIndex((j+1)%image.width(),i) ;
    count += image.pixelIndex((j+image.width()-1)%image.width(),i) ;
    count += image.pixelIndex((j+image.width()-1)%image.width(),(i+1)%image.height()) ;
    count += image.pixelIndex((j+image.width()-1)%image.width(),(i+image.height()-1)%image.height()) ;
    count += image.pixelIndex((j+1)%image.width(),(i+1)%image.height()) ;
    count += image.pixelIndex((j+1)%image.width(),(i+image.height()-1)%image.height()) ;

    return count ;
}

void Widget::TypeVI(QImage & image)
{
    image.fill(0) ;

    image.setPixel(image.width()>>1,image.height()>>1,1);
//    for (int i = 0 ; i < ui->spinBox_2->value() ; i++)
//        image.setPixel(0,i,(rand()>RAND_MAX/2)?0:1);

    bool something_changed;
    do{
        something_changed = false ;
        for (int i = 0 ; i < image.height() ; i++)
            for (int j = 0 ; j < image.width() ; j++)
                if (!image.pixelIndex(j,i) )
                {
                    int count = 0 ;
                    count += image.pixelIndex(j,(i+1)%image.height()) ;
                    count += image.pixelIndex(j,(i+image.height()-1)%image.height()) ;
                    count += image.pixelIndex((j+1)%image.width(),i) ;
                    count += image.pixelIndex((j+image.width()-1)%image.width(),i) ;

                    if (count ==1)
                    {
                        if (image.pixelIndex(j,(i+1)%image.height()))
                        {
                            if((!image.pixelIndex((j+image.width()-1)%image.width(),(i+image.height()-1)%image.height())) &&
                                    (!image.pixelIndex((j+1)%image.width(),(i+image.height()-1)%image.height())))
                            {
                                if (rand()<RAND_MAX>>2)
                                    image.setPixel(j,i,1);
                                something_changed = true ;
                            }
                        }
                        else
                            if (image.pixelIndex(j,(i+image.height()-1)%image.height()))
                            {
                                if((!image.pixelIndex((j+image.width()-1)%image.width(),(i+1)%image.height())) &&
                                        (!image.pixelIndex((j+1)%image.width(),(i+1)%image.height())))
                                {
                                    if (rand()<RAND_MAX>>2)
                                        image.setPixel(j,i,1);
                                    something_changed = true ;
                                }
                            }
                            else
                                if (image.pixelIndex((j+image.width()-1)%image.width(),i))
                                {
                                    if ((!image.pixelIndex((j+1)%image.width(),(i+1)%image.height())) &&
                                            (!image.pixelIndex((j+1)%image.width(),(i+image.height()-1)%image.height())))
                                    {
                                        if (rand()<RAND_MAX>>2)
                                            image.setPixel(j,i,1);
                                        something_changed = true ;
                                    }
                                }
                                else
                                    //if (image.pixelIndex((j+1)%image.width(),i))
                                {
                                    if ((!image.pixelIndex((j+image.width()-1)%image.width(),(i+1)%image.height())) &&
                                            (!image.pixelIndex((j+image.width()-1)%image.width(),(i+image.height()-1)%image.height())))
                                    {
                                        if (rand()<RAND_MAX>>2)
                                            image.setPixel(j,i,1);
                                        something_changed = true ;
                                    }
                                }
                    }
                }

    }while(something_changed);
}

void Widget::TypeV(QImage & image)
{

    image.fill(1) ;

    for (int i = 0 ; i < ui->spinBox_2->value() ; i++)
        image.setPixel(0,i,(rand()>RAND_MAX/2)?0:1);

    bool something_changed;
    do{
        something_changed = false ;
        for (int i = 0 ; i < image.height() ; i++)
            for (int j = 0 ; j < image.width() ; j++)
                if (image.pixelIndex(j,i) )
                {
                    int count = 0 ;
                    count += image.pixelIndex(j,(i+1)%image.height()) ;
                    count += image.pixelIndex(j,(i+image.height()-1)%image.height()) ;
                    count += image.pixelIndex((j+1)%image.width(),i) ;
                    count += image.pixelIndex((j+image.width()-1)%image.width(),i) ;

                    if (count ==3)
                    {
                        count += image.pixelIndex((j+image.width()-1)%image.width(),(i+1)%image.height()) ;
                        count += image.pixelIndex((j+image.width()-1)%image.width(),(i+image.height()-1)%image.height()) ;
                        count += image.pixelIndex((j+1)%image.width(),(i+1)%image.height()) ;
                        count += image.pixelIndex((j+1)%image.width(),(i+image.height()-1)%image.height()) ;

                        if (count >=5)
                        {

                            if ((rand()<RAND_MAX>>2))
                            {
                                image.setPixel(j,i,0);
                                something_changed = true ;
                            }

                        }
                    }
                }

    }while(something_changed);
}

bool Widget::connectionTest(QImage & image , QPoint &p1, QPoint &p2,QVector<int> & minPoint)
{
    int idx1 = p1.y() * image.width() + p1.x() ;
    int idx2 = p2.y() * image.width() + p2.x() ;

    if (minPoint[idx1]!=minPoint[idx2])
    {
        if (image.pixelIndex(p1)==image.pixelIndex(p2))
        {
            if (idx1<idx2)
            {
                minPoint[idx2]=minPoint[idx1];
                return true ;
            }
        }
    }

    return false ;
}

void Widget::compute4ConnectedComponents(QImage & image,int&black,int&white)
{


    QVector<int> fifo_in ;

    for (int i = 0 ; i < image.height() ;i++)
        for (int j = 0 ; j < image.width() ; j++)
            fifo_in << j+i*image.width() ;

    QVector<int> minPoint(fifo_in) ;

    while (fifo_in.count())
    {
        QVector<int> fifo_out ;

        for (int i = 0 ; i < fifo_in.count() ; i++)
        {
            QPoint p(fifo_in[i]%image.width(),fifo_in[i]/image.width()) ;

            QPoint p2((p.x()+1)%image.width(),p.y());
            QPoint p3((p.x()+image.width()-1)%image.width(),p.y());
            QPoint p4(p.x(),(p.y()+1)%image.height());
            QPoint p5(p.x(),(p.y()+image.height()-1)%image.height());

            if (connectionTest(image,p,p2,minPoint))
                fifo_out << p2.x()+p2.y()*image.width() ;
            if (connectionTest(image,p,p3,minPoint))
                fifo_out << p3.x()+p3.y()*image.width() ;
            if (connectionTest(image,p,p4,minPoint))
                fifo_out << p4.x()+p4.y()*image.width() ;
            if (connectionTest(image,p,p5,minPoint))
                fifo_out << p5.x()+p5.y()*image.width() ;
        }


        fifo_in = fifo_out ;

    }

    QSet<int> blacks,whites;

    for (int i = 0 ; i < minPoint.count() ; i++)
    {
        if (image.pixelIndex(i%image.width(),i/image.width()))
            whites << minPoint[i] ;
        else
            blacks << minPoint[i] ;

    }

    black = blacks.count() ;
    white = whites.count() ;
}

void Widget::compute8ConnectedComponents(QImage & image,int&black,int&white)
{


    QVector<int> fifo_in ;

    for (int i = 0 ; i < image.height() ;i++)
        for (int j = 0 ; j < image.width() ; j++)
            fifo_in << j+i*image.width() ;

    QVector<int> minPoint(fifo_in) ;

    while (fifo_in.count())
    {
        QVector<int> fifo_out ;

        for (int i = 0 ; i < fifo_in.count() ; i++)
        {
            QPoint p(fifo_in[i]%image.width(),fifo_in[i]/image.width()) ;

            QPoint p2((p.x()+1)%image.width(),p.y());
            QPoint p3((p.x()+image.width()-1)%image.width(),p.y());
            QPoint p4(p.x(),(p.y()+1)%image.height());
            QPoint p5(p.x(),(p.y()+image.height()-1)%image.height());

            if (connectionTest(image,p,p2,minPoint))
                fifo_out << p2.x()+p2.y()*image.width() ;
            if (connectionTest(image,p,p3,minPoint))
                fifo_out << p3.x()+p3.y()*image.width() ;
            if (connectionTest(image,p,p4,minPoint))
                fifo_out << p4.x()+p4.y()*image.width() ;
            if (connectionTest(image,p,p5,minPoint))
                fifo_out << p5.x()+p5.y()*image.width() ;

            QPoint p6((p.x()+1)%image.width(),(p.y()+1)%image.height());
            QPoint p7((p.x()+image.width()-1)%image.width(),(p.y()+1)%image.height());
            QPoint p8((p.x()+1)%image.width(),(p.y()+image.height()-1)%image.height());
            QPoint p9((p.x()+image.width()-1)%image.width(),(p.y()+image.height()-1)%image.height());

            if (connectionTest(image,p,p6,minPoint))
                fifo_out << p6.x()+p6.y()*image.width() ;
            if (connectionTest(image,p,p7,minPoint))
                fifo_out << p7.x()+p7.y()*image.width() ;
            if (connectionTest(image,p,p8,minPoint))
                fifo_out << p8.x()+p8.y()*image.width() ;
            if (connectionTest(image,p,p9,minPoint))
                fifo_out << p9.x()+p9.y()*image.width() ;
        }


        fifo_in = fifo_out ;

    }

    QSet<int> blacks,whites;

    for (int i = 0 ; i < minPoint.count() ; i++)
    {
        if (image.pixelIndex(i%image.width(),i/image.width()))
            whites << minPoint[i] ;
        else
            blacks << minPoint[i] ;

    }

    black = blacks.count() ;
    white = whites.count() ;
}

void Widget::on_pushButton_clicked()
{
    //Recalculer
    ui->label_4->setText(tr("%1").arg(ui->spinBox->value()*ui->spinBox_2->value()));


    QImage image(ui->spinBox->value(),ui->spinBox_2->value(),QImage::Format_Indexed8);
    QVector<QRgb> palette ;
    palette << qRgb(0,0,0) ;
    palette << qRgb(255,255,255) ;
    image.setColorTable(palette);



    switch (ui->comboBox->currentIndex()) {
    case 0:
        TypeI(image);
        break;
    case 1:
        TypeII(image);
        break;
    case 2:
        TypeIII(image);
        break;
    case 3:
        TypeIV(image);
        break;
    case 4:
        TypeV(image);
        break;
    case 5:
        TypeVI(image);
        break;
    default:
        break;
    }

    int black4,white4,black8,white8;
    compute4ConnectedComponents(image,black4,white4);
    compute8ConnectedComponents(image,black8,white8);
    ui->label_7->setText(tr("4-Composantes Connexes : %1/%2\n8-Composantes Connexes : %3/%4")
                         .arg(white4).arg(black4).arg(white8).arg(black8));

    ui->label_5->setPixmap(QPixmap::fromImage(image.scaledToHeight(ui->spinBox_2->value()*2)));

    repaint() ;
}

unsigned char Widget::applyRule(unsigned char a,unsigned char  b,unsigned char  c,unsigned char  seed)
{
    int n = ((a==0)?4:0)+((b==0)?2:0)+((c==0)?1:0) ;
    int r = (0x1 & (seed>>n)) ;
    return r;
}

void Widget::on_pushButton_2_clicked()
{
    QSettings settings ;

    QString last_path = settings.value("last_path",QDir::currentPath()).toString() ;

    QString new_path = QFileDialog::getSaveFileName(this,tr("Choisissez un nom pour l'image"),last_path);

    if (new_path!=QString())
    {
        settings.setValue("last_path",new_path);

        ui->label_5->pixmap()->save(new_path);
    }
}

void Widget::on_comboBox_currentIndexChanged(int index)
{
    on_pushButton_clicked();
}
