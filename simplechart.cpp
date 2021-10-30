#include "simplechart.h"

#include <QGraphicsSceneMouseEvent>

SimpleChart::SimpleChart(QObject *parentObject, QGraphicsItem *parentItem) :
    QObject(parentObject),
    QGraphicsItem(parentItem),
    _brect(QRectF{QPointF{0, 0}, QPointF{450, 350}}),
    _chart(new QChart(this))
{

    setFlag(ItemIsFocusable, true);

    QBarSet *set1 = new QBarSet("Sales", _chart);
    *set1 << 50 << 45 << 35 << 10;

    QBarSeries * quarterSales = new QBarSeries(_chart);
    quarterSales->append(set1);

    _chart->addSeries(quarterSales);
    _chart->setTitle("Sales");

    QBarCategoryAxis *salesAxis = new QBarCategoryAxis(_chart);
//    salesAxis->append({"Q1", "Q2", "Q3", "Q4"});

    _chart->addAxis(salesAxis, Qt::AlignLeft);
    quarterSales->attachAxis(salesAxis);

    _chart->legend()->setVisible(true);

    _chart->setGeometry(_brect);

    setData(1, "Simple Chart");
//    set

}


QRectF SimpleChart::boundingRect() const
{
    return _brect;
}

void SimpleChart::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->setBrush(QBrush());

    QPen pen;
    pen.setColor(Qt::red);
    pen.setStyle(Qt::DashLine);

    painter->setPen(pen);
    painter->drawRect(QRectF{QPointF{10, 10}, QPointF{40, 40}});

    painter->drawRect(_brect);
}


void SimpleChart::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    QGraphicsItem::mousePressEvent(event);
}
