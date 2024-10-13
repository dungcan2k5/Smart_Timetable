#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void onToolButtonConfigClicked();
    
private:
    Ui::MainWindow *ui;
    bool CONFIG_WINDOW_OPEN = false;
};
#endif // MAINWINDOW_H
