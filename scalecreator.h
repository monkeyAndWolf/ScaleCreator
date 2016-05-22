#ifndef SCALECREATOR_H
#define SCALECREATOR_H

#include <QObject>

class ScaleCreator : public QObject
{
    Q_OBJECT
public:
    explicit ScaleCreator(QObject *parent = 0);

    enum Key {
        C = 0,
        CSharp = 1,
        D = 2,
        DSharp = 3,
        E = 4,
        F = 5,
        FSharp = 6,
        G = 7,
        GSharp = 8,
        A = 9,
        ASharp = 10,
        B = 11
    };
    Q_ENUM(Key)

    enum Mode {
        Major = 0, // aka Ionian
        Minor = 1,
        Mixolydian = 2,
        Dorian = 3,
        Aeolian = 4
    };
    Q_ENUM(Mode)

    ScaleCreator::Key intToKey(int key);
    ScaleCreator::Mode intToMode(int Mode);

    QString keyToString(ScaleCreator::Key key);
    QString modeToString(ScaleCreator::Mode mode);

    Q_INVOKABLE QString getChord(int degree, bool minor = false);

    int* getPattern(ScaleCreator::Mode mode);
signals:
    void stringScale(ScaleCreator::Key key, ScaleCreator::Mode mode, QString text);

public slots:
    void calculateScale(Key key, Mode mode);

private:
    QStringList         m_currentScale;
    ScaleCreator::Key   m_currentKey;
    ScaleCreator::Mode  m_currentMode;

    int keepValueInKey(int klonger);
    QStringList privateCalcScale(ScaleCreator::Key key, ScaleCreator::Mode mode);

};

#endif // SCALECREATOR_H
