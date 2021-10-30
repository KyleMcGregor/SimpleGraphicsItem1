#include "view.h"
#include <QWheelEvent>
#include <QDebug>

#include <qmath.h>

View::View(QGraphicsScene *scene, QWidget *widget):
    QGraphicsView(scene, widget)
{
    setMouseTracking(true);
//    ensureVisible(QRectF{QPointF{0, 0},QPointF{500, 500}}, 0, 0);
//    setFixedSize(500, 500);
}


void View::wheelEvent(QWheelEvent *event)
{
    if (event->modifiers() & Qt::ControlModifier) {
        // zoom
//        const ViewportAnchor anchor = transformationAnchor();
//        setTransformationAnchor(QGraphicsView::AnchorUnderMouse);
        int angle = event->angleDelta().y();
        qreal factor;
        if (angle > 0) {
            factor = 1.1;
        } else {
            factor = 0.9;
        }
        scale(factor, factor);
//        setTransformationAnchor(anchor);
        centerOn(event->posF());
    } else {
        QGraphicsView::wheelEvent(event);
    }

}
