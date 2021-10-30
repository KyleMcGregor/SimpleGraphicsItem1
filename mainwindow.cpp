#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent),
      _scene(new Scene(this)),
      _view(new View(_scene, this)),
    _items(new QListWidget),
    _dwid(new QDockWidget("Items")),
    _dwidl(new QVBoxLayout),
    _currentFocusItem(new QLabel),
    _statusBar(new QStatusBar),
    _sceneInfoDock(new QDockWidget),
    _sceneInfoLayout(new QVBoxLayout),
    _sceneInfoList(new QListWidget),
    _sceneInfoModel(new SceneInfoListModel),
    _sceneTree(new QTreeView)
{

    setCentralWidget(_view);
    setStatusBar(_statusBar);
    _statusBar->addWidget(_currentFocusItem);

    _dwid->setObjectName("ItemsDock");
    _dwidl->setObjectName("ItemsDockLayout");
//    addDockWidget(Qt::RightDockWidgetArea, _dwid);

    _dwidl->addWidget(_items);
    setupList();
    auto *btn = new QPushButton("Test");
    _dwidl->addWidget(btn);
    QWidget * prox = new QWidget;
    prox->setLayout(_dwidl);
    _dwid->setWidget(prox);
    connect(_scene, &QGraphicsScene::focusItemChanged, this, &MainWindow::sceneItemChanged);

//    setupSceneInfoDock();

}

MainWindow::~MainWindow()
{
}

void MainWindow::setupList()
{

//    for(const auto iter : _scene->items()){
//        _items->addItem(QString("%1").arg(iter->x()));
//    }

}

void MainWindow::setupSceneInfoDock()
{

    _sceneTree->setModel(_sceneInfoModel);

    auto *proxy = new QWidget;
    proxy->setLayout(_sceneInfoLayout);
    _sceneInfoDock->setWidget(proxy);
    _sceneInfoLayout->addWidget(_sceneTree);
    addDockWidget(Qt::LeftDockWidgetArea, _sceneInfoDock);

    // still working out the algo too add treeitem.
    // Simple trees aint so simple.
    QStringList lines;
    lines << "Heelo";

    QFile file(":/descriptions.txt");
    file.open(QIODevice::ReadOnly);

//    TreeModel model(file.readAll());
//    file.close();

    lines << QString(file.readAll()).split("\n");

    _sceneInfoModel->setupModelData(lines, _sceneInfoModel->root());


}

void MainWindow::sceneItemChanged(QGraphicsItem *newFocusItem,
                                  QGraphicsItem *oldFocusItem,
                                  Qt::FocusReason reason)
{
    _items->addItem(QString("%1").arg( (newFocusItem->data(1).toString())));
    _currentFocusItem->setText(QString("%1").arg( (newFocusItem->data(1).toString())));

}




SceneInfoListModel::SceneInfoListModel(const QString &data, QObject *parent) :
    QAbstractItemModel(parent)
{
    QList<QVariant> rootData;
    rootData << "Title" << "Summary";
    _rootItem = new TreeItem(rootData);


}

QModelIndex SceneInfoListModel::index(int row, int column, const QModelIndex &parent) const
{
    if(!hasIndex(row, column, parent))
        return QModelIndex();

    TreeItem *parentItem;
    if(!parent.isValid())
        parentItem = _rootItem;
    else
        parentItem = static_cast<TreeItem*>(parent.internalPointer());

    TreeItem *childItem = parentItem->child(row);
    if(childItem)
        return createIndex(row, column, childItem);
    else
        return QModelIndex();

}

QModelIndex SceneInfoListModel::parent(const QModelIndex &child) const
{
    if(child.isValid())
        return QModelIndex();

    TreeItem *childItem = static_cast<TreeItem*>(child.internalPointer());
    TreeItem *parentItem = childItem->parentItem();

    if(parentItem == _rootItem){
        return QModelIndex();
    }

    return createIndex(parentItem->row(), 0, parentItem);
}

int SceneInfoListModel::rowCount(const QModelIndex &parent) const
{
    TreeItem *parentItem;
    if(parent.column() > 0 )
        return 0;
    if(!parent.isValid()){
        parentItem = _rootItem;
    } else {
        parentItem = static_cast<TreeItem*  >(parent.internalPointer()  );

    }

    return parentItem->childCount();

}

int SceneInfoListModel::columnCount(const QModelIndex &parent) const
{
    if(parent.isValid())
        return static_cast<TreeItem*>(parent.internalPointer())->columnCount();

    else
        return _rootItem->columnCount();
}

QVariant SceneInfoListModel::data(const QModelIndex &index, int role) const
{

    if(!index.isValid()){
        return QVariant();
    }

    if(role != Qt::DisplayRole){
        return QVariant();
    }

    TreeItem *item = static_cast<TreeItem*>(index.internalPointer());

    return item->data(index.column());
}


Qt::ItemFlags SceneInfoListModel::flags(const QModelIndex &index) const
{
    if(!index.isValid())
        return 0;

    return QAbstractItemModel::flags(index);
}


TreeItem::TreeItem(const QList<QVariant> &data, TreeItem *parent)
{
    m_parentItem = parent;
    m_itemData = data;
}

TreeItem::~TreeItem()
{
    qDeleteAll(m_childItems);
}

void TreeItem::appendChild(TreeItem *item)
{
    m_childItems.append(item);
}

TreeItem *TreeItem::child(int row)
{
    return m_childItems.value(row);
}

int TreeItem::childCount() const
{
    return m_childItems.count();
}

int TreeItem::columnCount() const
{
    return m_itemData.count();
}

QVariant TreeItem::data(int column) const
{
    return m_itemData.value(column);
}

TreeItem *TreeItem::parentItem()
{
    return m_parentItem;
}

int TreeItem::row() const
{
    if (m_parentItem)
        return m_parentItem->m_childItems.indexOf(const_cast<TreeItem*>(this));

    return 0;
}


void SceneInfoListModel::setupModelData(const QStringList &lines, TreeItem *parent)
{

    //TODO Describe this method in terms.

    // Create a list of Parents
    QList<TreeItem*> parents;
    QList<int> indentations;
    parents << parent;
    indentations << 0;

    int number = 0;

    // loop over the string list (lines)

    while (number < lines.count()) {
        int position = 0;
        while (position < lines[number].length()) {
            if (lines[number].at(position) != ' ')
                break;
            position++;
        }

        QString lineData = lines[number].mid(position).trimmed();

        if (!lineData.isEmpty()) {
            // Read the column data from the rest of the line.
            QStringList columnStrings = lineData.split("\t", QString::SkipEmptyParts);
            QList<QVariant> columnData;
            for (int column = 0; column < columnStrings.count(); ++column)
                columnData << columnStrings[column];

            if (position > indentations.last()) {
                // The last child of the current parent is now the new parent
                // unless the current parent has no children.

                if (parents.last()->childCount() > 0) {
                    parents << parents.last()->child(parents.last()->childCount()-1);
                    indentations << position;
                }
            } else {
                while (position < indentations.last() && parents.count() > 0) {
                    parents.pop_back();
                    indentations.pop_back();
                }
            }

            // Append a new item to the current parent's list of children.
            parents.last()->appendChild(new TreeItem(columnData, parents.last()));
        }

        ++number;
    }
}

TreeItem *SceneInfoListModel::root()
{
    return _rootItem;
}
