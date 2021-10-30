#include "bouncingbutton.h"

#include <QKeyEvent>
#include <QPainter>
#include <QStyleOptionGraphicsItem>

#include <QDebug>

BouncingButton::BouncingButton(QGraphicsItem *parent, QObject *parentObject):
    QObject(parentObject),
    QGraphicsItem(parent),
    m_brect(QPointF{0, 0}, QPointF{50, 50}),
    m_rating(0)
{
    setFlag(ItemIsFocusable, true);
    setFlag(ItemIsMovable, true);


    m_explodeBox = new QPropertyAnimation(this);
    m_explodeBox->setTargetObject(this);
    m_explodeBox->setPropertyName("rating");
    m_explodeBox->setStartValue(0);
    m_explodeBox->setKeyValueAt(0.5, 5);
    m_explodeBox->setEndValue(0);
    m_explodeBox->setDuration(1000);
    m_explodeBox->setEasingCurve(QEasingCurve::OutInCirc);

    setData(1, QString("BouncingButton"));
    QStyleOptionGraphicsItem opt;


}

QRectF BouncingButton::boundingRect() const
{
    return m_brect.marginsAdded(QMarginsF(5, 5, 5, 5));
}

void BouncingButton::paint(QPainter *painter,
                         const QStyleOptionGraphicsItem *option,
                         QWidget *widget)
{
    auto lod = option->levelOfDetailFromTransform(painter->worldTransform());
    painter->drawRect(m_brect.marginsAdded(QMarginsF(rating(), rating(), rating(), rating())));
    painter->setBrush(QColor(10, 10, 10));
    if(lod > 3){
        painter->drawText(QPoint{0, 0}, "test");
    }

    if(hasFocus()){
        painter->drawEllipse(m_brect.marginsRemoved({rating(), rating(), rating(), rating()}));
        QPen pen;
        pen.setColor(Qt::red);
        pen.setStyle(Qt::DashLine);
        pen.setWidthF(1.2);
        painter->setPen(pen);
        painter->setBrush(QBrush());
        painter->drawRect(m_brect.marginsAdded(QMarginsF(5, 5, 5, 5)));
    }


}


void BouncingButton::keyPressEvent(QKeyEvent *event)
{
    QGraphicsItem::keyPressEvent(event);
    if(event->text() == "e"){
        if(QAbstractAnimation::Stopped == m_explodeBox->state()){
            m_explodeBox->start();
        } else {
            m_explodeBox->setCurrentTime(10);
        }
        event->accept();
        return;
    }

}

qreal BouncingButton::rating() const
{
    return m_rating;
}

void BouncingButton::setRating(qreal newRating)
{
    if (qFuzzyCompare(m_rating, newRating))
        return;
    m_rating = newRating;
    update();
    emit ratingChanged();
}
