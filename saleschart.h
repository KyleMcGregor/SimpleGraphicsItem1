#ifndef SALESCHART_H
#define SALESCHART_H

#include <QtCharts>
#include <QObject>
#include <QWidget>

QT_CHARTS_USE_NAMESPACE

class SalesChart : public QChart
{
    Q_OBJECT
    Q_PROPERTY(float rotation READ rotation WRITE setRotation NOTIFY rotationChanged)
    Q_PROPERTY(QColor selectionColor READ selectionColor WRITE setSelectionColor NOTIFY selectionColorChanged)

public:
    SalesChart(QGraphicsItem *parentItem = nullptr);


    // QGraphicsItem interface
public:
    virtual QRectF boundingRect() const override;

private:
    QRectF _bounds;
    QPropertyAnimation * _rotationAnimation;
    QColor _selectionAnimationColor;
    QPropertyAnimation *_selectionAnimation;


    // QGraphicsLayoutItem interface
    float m_rotation;

    QColor m_selectionColor;

protected:
    virtual QSizeF sizeHint(Qt::SizeHint which, const QSizeF &constraint) const override;

    // QGraphicsItem interface
public:
    virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;

    float rotation() const;
    void setRotation(float newRotation);



    const QColor &selectionColor() const;
    void setSelectionColor(const QColor &newSelectionColor);

signals:
    void rotationChanged();

    void selectionColorChanged();

protected:
    virtual void mousePressEvent(QGraphicsSceneMouseEvent *event) override;

    // QGraphicsItem interface
protected:
    virtual void focusInEvent(QFocusEvent *event) override;
    virtual void focusOutEvent(QFocusEvent *event) override;
};

#endif // SALESCHART_H
