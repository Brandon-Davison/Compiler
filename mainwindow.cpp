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
    QPalette palette;

    // base window color
    palette.setColor(QPalette::Window, QColor(53,53,53));

    // label text color
    palette.setColor(QPalette::WindowText, Qt::white);

    // base widget color
    palette.setColor(QPalette::Base, QColor(25,25,25));

    // text color in windows
    palette.setColor(QPalette::Text, Qt::white);

    // chart text background
    palette.setColor(QPalette::Button, QColor(53,53,53));

    // menu and chart text
    palette.setColor(QPalette::ButtonText, Qt::white);

    // set window theme
    qApp->setPalette(palette);
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

void MainWindow::on_actionRun_triggered()
{

}

void MainWindow::on_actionNewProject_triggered()
{

}


void MainWindow::on_actionOpen_triggered()
{
    QFileDialog dialog(this);
    dialog.setFileMode(QFileDialog::AnyFile);
    dialog.setNameFilter(tr("Files (*.txt)"));
    dialog.setViewMode(QFileDialog::Detail);

    QStringList fileNames;
    if (dialog.exec())
    {
        fileNames = dialog.selectedFiles();
    }

    if (!fileNames.empty())
    {
        QFile inputFile(fileNames.at(0));
        QString text;
        if (inputFile.open(QIODevice::ReadOnly))
        {
            QTextStream in(&inputFile);

            while (!in.atEnd())
            {
                text += in.readLine() + '\n';
            }
            inputFile.close();
        }
        codeEditor->document()->setPlainText(text);
        fileTextPath = fileNames.at(0);
    }
}
