#ifndef VIEW_H
#define VIEW_H

#include <QGraphicsView>

class View : public QGraphicsView
{
public:
    View(QGraphicsScene * scene = nullptr, QWidget * widget = nullptr);



    // QWidget interface
protected:
    virtual void wheelEvent(QWheelEvent *event) override;


};

#endif // VIEW_H
