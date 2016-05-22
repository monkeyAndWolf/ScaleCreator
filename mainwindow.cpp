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


    recalculateScales();
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
    QString output = "Notes in the key of ";
    output.append(m_scaleCreator->keyToString(key)).append(" ").append(m_scaleCreator->modeToString(mode)).append(":").append("\n\n").append(text);
    ui->textScale->setText(output);

    QString chord1 = "1st:\n\n";
    chord1.append(m_scaleCreator->getChord(1));
    ui->chord1->setText(chord1);

    QString chord2 = "4th:\n\n";
    chord2.append(m_scaleCreator->getChord(4));
    ui->chord2->setText(chord2);

    QString chord3 = "5th:\n\n";
    chord3.append(m_scaleCreator->getChord(5));
    ui->chord3->setText(chord3);

    QString minot6 = "Minor 6th:\n\n";
    minot6.append(m_scaleCreator->getChord(6, true));
    ui->minor6->setText(minot6);
}
