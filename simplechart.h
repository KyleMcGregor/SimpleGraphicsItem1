#ifndef SIMPLECHART_H
#define SIMPLECHART_H

#include <QObject>
#include <QGraphicsItem>
#include <QObject>
#include <QtCharts>

QT_CHARTS_USE_NAMESPACE

class SimpleChart : public QObject, public QGraphicsItem
{
    Q_OBJECT
public:
    SimpleChart(QObject *parentObject = nullptr, QGraphicsItem * parentItem = nullptr);

private:
    QRectF _brect;
    QChart *_chart;
    QSize *_size;

    // QGraphicsItem interface
public:
    virtual QRectF boundingRect() const override;
    virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;

    // QGraphicsItem interface
protected:
    virtual void mousePressEvent(QGraphicsSceneMouseEvent *event) override;
};

#endif // SIMPLECHART_H
