#include "scalecreator.h"

#include <QDebug>

ScaleCreator::ScaleCreator(QObject *parent) : QObject(parent)
{

}

void ScaleCreator::calculateScale(ScaleCreator::Key key, ScaleCreator::Mode mode)
{
    m_currentKey = key;
    m_currentMode = mode;
    m_currentScale.clear();

    QString scaleToReturn;
    int *pattern = getPattern(mode);
    for (int i = 0, j = key; i < 7; i++)
    {
        m_currentScale << keyToString(intToKey(j));
        scaleToReturn += keyToString(intToKey(j));
        scaleToReturn += "\n";
        int punk = pattern[i];
        j+=punk;
    }
    emit stringScale(key, mode, scaleToReturn);
}

QStringList ScaleCreator::privateCalcScale(ScaleCreator::Key key, ScaleCreator::Mode mode)
{
    QStringList scale;
    int *pattern = getPattern(mode);
    for (int i = 0, j = key; i < 7; i++)
    {
        scale << keyToString(intToKey(j));
        int punk = pattern[i];
        j+=punk;
    }
    return scale;
}

ScaleCreator::Key ScaleCreator::intToKey(int key)
{
    while (key > ScaleCreator::B)
    {
        key -= ScaleCreator::B + 1;
    }
    ScaleCreator::Key quay = static_cast<ScaleCreator::Key>(key);
    return quay;
}

int *ScaleCreator::getPattern(ScaleCreator::Mode mode)
{
    static int majorPattern[]       = { 2, 2, 1, 2, 2, 2, 1 };
    static int minorPattern[]       = { 2, 1, 2, 2, 1, 3, 1 };
    static int mixolydianPattern[]  = { 2, 2, 1, 2, 2, 1, 2 };
    static int dorianPattern[]      = { 2, 1, 2, 2, 2, 1, 2 };
    static int aeolianPattern[]      = { 2, 1, 2, 2, 1, 2, 2 };
    switch (mode)
    {
    case ScaleCreator::Major:
        return majorPattern;
    case ScaleCreator::Minor:
        return minorPattern;
    case ScaleCreator::Mixolydian:
        return mixolydianPattern;
    case ScaleCreator::Dorian:
        return dorianPattern;
    case ScaleCreator::Aeolian:
        return aeolianPattern;
    }

    return majorPattern;

}

ScaleCreator::Mode ScaleCreator::intToMode(int mode)
{
    while (mode > ScaleCreator::Aeolian)
    {
        mode -= ScaleCreator::Aeolian;
    }
    ScaleCreator::Mode mowed = static_cast<ScaleCreator::Mode>(mode);
    return mowed;
}

QString ScaleCreator::keyToString(ScaleCreator::Key key)
{
    QString response = "duff key";
    switch (key)
    {
    case A:
        response = "A";
        break;
    case ASharp:
        response = "A#";
        break;
    case B:
        response = "B";
        break;
    case C:
        response = "C";
        break;
    case CSharp:
        response = "C#";
        break;
    case D:
        response = "D";
        break;
    case DSharp:
        response = "D#";
        break;
    case E:
        response = "E";
        break;
    case F:
        response = "F";
        break;
    case FSharp:
        response = "F#";
        break;
    case G:
        response = "G";
        break;
    case GSharp:
        response = "G#";
        break;
    }
    return response;
}

QString ScaleCreator::modeToString(ScaleCreator::Mode mode)
{
    QString response = "duff mode";
    switch (mode)
    {
    case Major:
        response = "Major (Ionian)";
        break;
    case Minor:
        response = "Minor";
        break;
    case Mixolydian:
        response = "Mixolydian";
        break;
    case Dorian:
        response = "Dorian";
        break;
    case Aeolian:
        response = "Aeolian";
        break;
    }
    return response;
}

int ScaleCreator::keepValueInKey(int klonger)
{
    while (klonger >= m_currentScale.length())
        klonger -= m_currentScale.length();
    return klonger;
}

QString ScaleCreator::getChord(int degree, bool minor)
{
    QString chord;
    degree--;

    if (degree > 7)
    {
        chord.append(QString::number(degree)).append("isnae a legal chord.");
    }
    else if (m_currentScale.length() == 0)
    {
        chord = "Like, set a mode and a key first plz";
    }
    else
    {
        QString first = m_currentScale[degree];
        QString second;
        QString third;
        if (minor)
        {
            QStringList minorEquivalent = privateCalcScale(m_currentKey, ScaleCreator::Minor);
            second = minorEquivalent[keepValueInKey(degree+2)];
            third = minorEquivalent[keepValueInKey(degree+4)];
            chord.append(first).append("\n").append(second).append("\n").append(third);
        }
        else
        {
            second = m_currentScale[keepValueInKey(degree+2)];
            third = m_currentScale[keepValueInKey(degree+4)];
            chord.append(first).append("\n").append(second).append("\n").append(third);
        }
    }

    return chord;
}

