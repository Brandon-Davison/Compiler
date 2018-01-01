#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QStyleFactory>

#include "codeeditor.h"
#include "highlighter.h"

class QTextEdit;

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(CodeEditor* codeEditor, QWidget *parent = 0);

    ~MainWindow();

private:
    Ui::MainWindow *ui;
    CodeEditor* codeEditor;

    QTextEdit *edi;
    Highlighter *highlighter;
};

#endif // MAINWINDOW_H
