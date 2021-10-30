#include "saleschart.h"

SalesChart::SalesChart(QGraphicsItem * parentItem) :
    QChart(parentItem),
    _bounds(QPointF{0, 0}, QPointF{1950, 1150}),
    _rotationAnimation(new QPropertyAnimation(this, "rotation", this)),
    _selectionAnimationColor(QColor(255, 0, 0)),
  _selectionAnimation(new QPropertyAnimation(this, "selectionColor", this))
{

    QBarSet *set1 = new QBarSet("Sales", this);
    *set1 << 50 << 45 << 35 << 10;

    QBarSeries * quarterSales = new QBarSeries(this);
    quarterSales->append(set1);

    addSeries(quarterSales);
    setTitle("Sales");

    QBarCategoryAxis *salesAxis = new QBarCategoryAxis(this);

    addAxis(salesAxis, Qt::AlignLeft);
    quarterSales->attachAxis(salesAxis);

    legend()->setVisible(true);
    setData(1, "SalesChart");

    setAcceptHoverEvents(true);
    setAcceptedMouseButtons(Qt::AllButtons);


    setFlag(ItemIsFocusable, true);
    setFlag(ItemIsMovable, true);

    _rotationAnimation = new QPropertyAnimation(this, "rotation");
    _rotationAnimation->setDuration(1000);
    _rotationAnimation->setEndValue(360);
    _rotationAnimation->setStartValue(0);
    _rotationAnimation->setEasingCurve(QEasingCurve::InOutBounce);

}




QRectF SalesChart::boundingRect() const
{
    return _bounds;
}




QSizeF SalesChart::sizeHint(Qt::SizeHint which, const QSizeF &constraint) const
{
//    switch (which) {
//    case Qt::MinimumSize:
//        return QSizeF{250, 250};
//        break;
//    case Qt::PreferredSize:
//        return QSizeF{450, 300};
//        break;
//    case Qt::MaximumSize:
        return QSizeF{1920, 1080};
//        break;
//    default:
//        return QSizeF{1920, 1080};
//    }
}


void SalesChart::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    if(hasFocus()){
        painter->setBrush(Qt::NoBrush);
        auto pen = QPen(Qt::DashLine);
        pen.setColor(_selectionAnimationColor);
        painter->setPen(pen);
        painter->drawRect(_bounds.marginsRemoved(QMarginsF(10, 10, 10, 10)));
    }

    QChart::paint(painter, option, widget);
}

void SalesChart::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    QChart::mousePressEvent(event);
    setFocus(Qt::FocusReason::MouseFocusReason);
    update(_bounds);
}

float SalesChart::rotation() const
{
    return m_rotation;
}

void SalesChart::setRotation(float newRotation)
{
    if (qFuzzyCompare(m_rotation, newRotation))
        return;
    setGeometry(geometry().marginsAdded(QMarginsF(0, 0, newRotation, newRotation)));
    m_rotation = newRotation;
    emit rotationChanged();
}


void SalesChart::focusInEvent(QFocusEvent *event)
{
    QGraphicsItem::focusInEvent(event);
    update();
}

void SalesChart::focusOutEvent(QFocusEvent *event)
{
    QGraphicsItem::focusOutEvent(event);
    update();
}

const QColor &SalesChart::selectionColor() const
{
    return m_selectionColor;
}

void SalesChart::setSelectionColor(const QColor &newSelectionColor)
{
    if (m_selectionColor == newSelectionColor)
        return;
    m_selectionColor = newSelectionColor;
    _selectionAnimationColor = newSelectionColor;
    emit selectionColorChanged();
}
