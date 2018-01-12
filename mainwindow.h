#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "codeeditor.h"

#include <QMainWindow>
#include <QStyleFactory>

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

private slots:
    void on_actionRun_triggered();

    void on_actionNewProject_triggered();

    void on_actionRedo_triggered();

    void on_actionUndo_triggered();

    void on_actionOpen_triggered();

private:
    Ui::MainWindow *ui;

    CodeEditor *codeEditor;

    void setTheme();

    void addWidgets();
    void addCodeEditorWidget();
    void addOutputWidgets();

};

#endif // MAINWINDOW_H
