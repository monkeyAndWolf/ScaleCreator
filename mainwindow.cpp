#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "scalecreator.h"

#include <QDebug>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    m_scaleCreator = new ScaleCreator();

    this->setWindowTitle("Scaler Application");

    QStringList keys;
    QStringList modes;
    // These two string lists MUST map to the ScaleCreator values
    keys << m_scaleCreator->keyToString(m_scaleCreator->intToKey(0));
    keys << m_scaleCreator->keyToString(m_scaleCreator->intToKey(1));
    keys << m_scaleCreator->keyToString(m_scaleCreator->intToKey(2));
    keys << m_scaleCreator->keyToString(m_scaleCreator->intToKey(3));
    keys << m_scaleCreator->keyToString(m_scaleCreator->intToKey(4));
    keys << m_scaleCreator->keyToString(m_scaleCreator->intToKey(5));
    keys << m_scaleCreator->keyToString(m_scaleCreator->intToKey(6));
    keys << m_scaleCreator->keyToString(m_scaleCreator->intToKey(7));
    keys << m_scaleCreator->keyToString(m_scaleCreator->intToKey(8));
    keys << m_scaleCreator->keyToString(m_scaleCreator->intToKey(9));
    keys << m_scaleCreator->keyToString(m_scaleCreator->intToKey(10));
    keys << m_scaleCreator->keyToString(m_scaleCreator->intToKey(11));
    modes << "Major (Ionian)" << "Minor" << "Mixolydian" << "Dorian" << "Aeolian";

    ui->Key->addItems(keys);
    ui->Mode->addItems(modes);

    connect(ui->Key, SIGNAL(currentIndexChanged(int)), this, SLOT(recalculateScales()));
    connect(ui->Mode, SIGNAL(currentIndexChanged(int)), this, SLOT(recalculateScales()));

    connect(this, &MainWindow::newScaleSettings, m_scaleCreator, &ScaleCreator::calculateScale);
    connect(m_scaleCreator, &ScaleCreator::stringScale, this, &MainWindow::textRecalulated);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::recalculateScales()
{
    int keykey = ui->Key->currentIndex();
    ScaleCreator::Key key = m_scaleCreator->intToKey(keykey);
    int modekey = ui->Mode->currentIndex();
    ScaleCreator::Mode mode = m_scaleCreator->intToMode(modekey);
    emit newScaleSettings(key, mode);
}

void MainWindow::textRecalulated(ScaleCreator::Key key, ScaleCreator::Mode mode, QString text)
{
    ui->textScale->setText(text);
}
