#include "mainwindow.h"
#include "codeeditor.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    CodeEditor *editor = new CodeEditor();

    MainWindow w(editor);
    w.setWindowTitle("Compiler");
    w.show();

    return a.exec();
}
