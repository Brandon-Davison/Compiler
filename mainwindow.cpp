#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(CodeEditor *codeEditor, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    Q_ASSERT(codeEditor != nullptr);

    ui->setupUi(this);

   CodeEditor *a = new CodeEditor();

    highlighter = new Highlighter(a->document());

    QHBoxLayout* layout = new QHBoxLayout();
    layout->addWidget(a);

    QWidget* window = new QWidget;
    window->setLayout(layout);
    window->show();

    ui->verticalLayout->addWidget(window);

    //setCentralWidget(a);

    /* Dark window theme */
    qApp->setStyle(QStyleFactory::create("Fusion"));

    QPalette darkPalette;
    darkPalette.setColor(QPalette::Window, QColor(53,53,53));
    darkPalette.setColor(QPalette::WindowText, Qt::white);
    darkPalette.setColor(QPalette::Base, QColor(25,25,25));
    darkPalette.setColor(QPalette::AlternateBase, QColor(53,53,53));
    darkPalette.setColor(QPalette::ToolTipBase, Qt::white);
    darkPalette.setColor(QPalette::ToolTipText, Qt::white);
    darkPalette.setColor(QPalette::Text, Qt::white);
    darkPalette.setColor(QPalette::Button, QColor(53,53,53));
    darkPalette.setColor(QPalette::ButtonText, Qt::white);
    darkPalette.setColor(QPalette::BrightText, Qt::red);
    darkPalette.setColor(QPalette::Link, QColor(42, 130, 218));
    darkPalette.setColor(QPalette::Highlight, QColor(42, 130, 218));
    darkPalette.setColor(QPalette::HighlightedText, Qt::black);

    qApp->setPalette(darkPalette);
    qApp->setStyleSheet("QToolTip { color: #ffffff; background-color: #2a82da; border: 1px solid white; }");
}

MainWindow::~MainWindow()
{
    delete ui;
}
