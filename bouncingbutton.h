#ifndef BOUNCINGBUTTON_H
#define BOUNCINGBUTTON_H

#include <QGraphicsItem>
#include <QObject>
#include <QPropertyAnimation>

class BouncingButton : public QObject, public QGraphicsItem
{
    Q_OBJECT
    Q_PROPERTY(qreal rating READ rating WRITE setRating NOTIFY ratingChanged)
public:
    BouncingButton(QGraphicsItem *parent = nullptr, QObject * parentObject = nullptr);

    // QGraphicsItem interface
public:
    virtual QRectF boundingRect() const override;
    virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;


    qreal rating() const;
    void setRating(qreal newRating);

signals:
    void ratingChanged();

private:
    QRectF m_brect;


    // QGraphicsItem interface
    qreal m_rating;

    QPropertyAnimation * m_explodeBox;

protected:
    virtual void keyPressEvent(QKeyEvent *event) override;
};

#endif // BOUNCINGBUTTON_H
