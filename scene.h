#ifndef SCENE_H
#define SCENE_H

#include <QGraphicsScene>

#include "bouncingbutton.h"
#include "simplechart.h"
#include "saleschart.h"

class Scene : public QGraphicsScene
{
public:
    explicit Scene(QObject *parent = nullptr);

private:
    void setupSalesChart();

private:
    SalesChart *_salesChart;
    QGraphicsSimpleTextItem *_mousepos;



    // QGraphicsScene interface
protected:
    virtual void mouseMoveEvent(QGraphicsSceneMouseEvent *event) override;
};

#endif // SCENE_H
