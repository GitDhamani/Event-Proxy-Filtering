#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QListView>
#include <QLabel>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QStringListModel>
#include <QLineEdit>
#include <QSortFilterProxyModel>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    setWindowTitle("Colour Viewer");
    resize(300,300);
    statusBar()->hide();
    menuBar()->hide();

    QListView* view = new QListView(this);
    view->setMinimumSize(150,300);

    QLabel* label = new QLabel(this);
    label->setAutoFillBackground(true);
    label->setMinimumSize(100,100);
    label->setSizePolicy(QSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding));

    QLabel* matchlabel = new QLabel(this);
    matchlabel->setText("Match String: ");
    QLineEdit* lineEdit = new QLineEdit(this);
    lineEdit->setFont(QFont("Arial", 12));

    //Set Main Window Layout to Vertical, owner is the Central Widget
    QWidget* widget = new QWidget(this);
    setCentralWidget(widget);
    QVBoxLayout* vlayout = new QVBoxLayout(widget);

    //Create a Horizontal Container and add the List View and Colour Label to it
    QHBoxLayout* layout = new QHBoxLayout;
    layout->addWidget(view);
    layout->addWidget(label);

    //Create a Horizontal Container and add the match Label and Line Edit to it
    QHBoxLayout* lowerlayout = new QHBoxLayout;
    lowerlayout->addWidget(matchlabel);
    lowerlayout->addWidget(lineEdit);

    //Add Both horizontal containers to the Vertical Layout of the Window
    vlayout->addLayout(layout);
    vlayout->addLayout(lowerlayout);

    //Create a StringListModel and load it with the Colour Names
    QStringList colors = QColor::colorNames();
    QStringListModel* colormodel = new QStringListModel(colors, this);
    view->setFont(QFont("Arial", 12));

    //Create A Proxy Model and set its source as the Original Colour Model
    QSortFilterProxyModel* proxymodel = new QSortFilterProxyModel(this);
    proxymodel->setSourceModel(colormodel);
    view->setModel(proxymodel);  //Set the View to show the Proxy Model

    //Each time text is typed, we set the filter on the Proxy Model to that text
    connect(lineEdit, &QLineEdit::textChanged, [=](QString txt){
        proxymodel->setFilterRegExp(txt);
    });

    //Each click is now referencing the Proxy Model, so grab the data and change the colour label
    connect(view, &QListView::clicked, [=](QModelIndex index){
        QPalette pal = label->palette();
        pal.setColor(QPalette::Window, QColor(proxymodel->data(index, Qt::DisplayRole).toString()));
        label->setPalette(pal);
    });

}

MainWindow::~MainWindow()
{
    delete ui;
}

