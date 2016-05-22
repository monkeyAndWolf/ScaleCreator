#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class MainWindow;
}

#include "scalecreator.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

public slots:
    void recalculateScales();

    void textRecalulated(ScaleCreator::Key key, ScaleCreator::Mode mode, QString text);
//    void svgRecalculated(QString filepath);
signals:
    void newScaleSettings(ScaleCreator::Key key, ScaleCreator::Mode mode);
private:
    Ui::MainWindow *ui;

    ScaleCreator *m_scaleCreator;
};

#endif // MAINWINDOW_H
