#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(CodeEditor *codeEditor, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    Q_ASSERT(codeEditor != nullptr);

    ui->setupUi(this);
    setTheme();
    addWidgets();
}

void MainWindow::setTheme()
{
    // create window theme
    qApp->setStyle(QStyleFactory::create("Fusion"));
    QPalette darkPalette;

    // base window color
    darkPalette.setColor(QPalette::Window, QColor(53,53,53));

    // label text color
    darkPalette.setColor(QPalette::WindowText, Qt::white);

    // base widget color
    darkPalette.setColor(QPalette::Base, QColor(25,25,25));

    // text color in windows
    darkPalette.setColor(QPalette::Text, Qt::white);

    // chart text background
    darkPalette.setColor(QPalette::Button, QColor(53,53,53));

    // menu and chart text
    darkPalette.setColor(QPalette::ButtonText, Qt::white);

    // set window theme
    qApp->setPalette(darkPalette);
    qApp->setStyleSheet("QToolTip { color: #ffffff; background-color: #2a82da; border: 1px solid white; }");
}

void MainWindow::addWidgets()
{
    addCodeEditorWidget();
    addOutputWidgets();
}

void MainWindow::addCodeEditorWidget()
{
    // create CodeEditor
    codeEditor = new CodeEditor();
    highlighter = new Highlighter(codeEditor->document());

    // add code editor to window
    ui->verticalLayout->addWidget(codeEditor);
}

void MainWindow::addOutputWidgets()
{
    // create memory dump table
    QTableWidget *memoryDump = static_cast<QTableWidget*>(ui->verticalLayout_2->itemAt(3)->widget());

    // insert columns
    for (int i = 0; i < 10; ++i)
    {
        memoryDump->insertColumn(i);
    }

    // insert rows
    for (int i = 0; i < 100; ++i)
    {
        // Create rows
        memoryDump->insertRow(i);

        // Change row numbers to multiples of 10
        memoryDump->setVerticalHeaderItem(i, new QTableWidgetItem(QString::number(i * 10)));
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}
