#include "mainwindow.h"
#include "codeeditor.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    CodeEditor editor;
    editor.show();

    MainWindow w(&editor);
    w.show();

    return a.exec();
}
