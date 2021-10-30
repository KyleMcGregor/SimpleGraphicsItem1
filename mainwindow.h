#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "scene.h"
#include "view.h"

#include <QGraphicsView>
#include <QMainWindow>
#include <QListWidget>

class TreeItem;
class SceneInfoListModel;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    void setupList();

private:
    Scene *_scene;
    View *_view;
    QListWidget *_items;
    QDockWidget *_dwid;
    QVBoxLayout *_dwidl;
    QLabel *_currentFocusItem;
    QStatusBar *_statusBar;
    QDockWidget *_sceneInfoDock;
    QVBoxLayout *_sceneInfoLayout;
    QListWidget *_sceneInfoList;
    SceneInfoListModel *_sceneInfoModel;
    QTreeView *_sceneTree;




private:
    void setupSceneInfoDock();

private slots:
    void sceneItemChanged(QGraphicsItem *newFocusItem,
                          QGraphicsItem *oldFocusItem,
                          Qt::FocusReason reason);



};


class SceneInfoListModel : public QAbstractItemModel
{
    Q_OBJECT
public:
    SceneInfoListModel(const QString &data = QString("Node"), QObject *parent = nullptr);
    virtual ~SceneInfoListModel() {}

    // QAbstractItemModel interface
public:
    virtual QModelIndex index(int row, int column, const QModelIndex &parent) const override;
    virtual QModelIndex parent(const QModelIndex &child) const override;
    virtual int rowCount(const QModelIndex &parent) const override;
    virtual int columnCount(const QModelIndex &parent) const override;
    virtual QVariant data(const QModelIndex &index, int role) const override;
    virtual Qt::ItemFlags flags(const QModelIndex &index) const override;
    void setupModelData(const QStringList &lines, TreeItem *parent);
    TreeItem *root();

private:
    TreeItem *_rootItem;
};

class TreeItem
{
public:
    explicit TreeItem(const QList<QVariant> &data, TreeItem *parentItem = 0);
    ~TreeItem();

    void appendChild(TreeItem *child);

    TreeItem *child(int row);
    int childCount() const;
    int columnCount() const;
    QVariant data(int column) const;
    int row() const;
    TreeItem *parentItem();

private:
    QList<TreeItem*> m_childItems;
    QList<QVariant> m_itemData;
    TreeItem *m_parentItem;
};

#endif // MAINWINDOW_H
