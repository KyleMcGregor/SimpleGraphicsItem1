
#include "scene.h"

#include <QPropertyAnimation>

Scene::Scene(QObject *parent) : QGraphicsScene(parent),
    _salesChart(new SalesChart),
    _mousepos(new QGraphicsSimpleTextItem)
{




    setupSalesChart();



    addItem(_salesChart);

    _mousepos->setX(0);



}

void Scene::setupSalesChart()
{



}



void Scene::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{

    QGraphicsScene::mouseMoveEvent(event);

    _mousepos->setText(QString("%0 %1")
                       .arg(event->scenePos().x())
                       .arg(event->scenePos().y()));
}
