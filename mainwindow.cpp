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

    QTableWidget *memoryDump = static_cast<QTableWidget*>(ui->verticalLayout_2->itemAt(3)->widget());

    /* Insert Columns */
    for (int i = 0; i < 10; ++i)
    {
        memoryDump->insertColumn(i);
    }

    /* Insert rows */
    for (int i = 0; i < 100; ++i)
    {
        // Create rows
        memoryDump->insertRow(i);

        // Change row numbers to 0, 10, 20, 30, etc.
        memoryDump->setVerticalHeaderItem(i, new QTableWidgetItem(QString::number(i * 10)));
    }

    /* Add memory cell values */
    for (int i = 0; i < 100; ++i)
    {
        for (int j = 0; j < 10; ++j)
        {
            memoryDump->setItem(i, j, new QTableWidgetItem(QString::number(0)));
        }
    }

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
