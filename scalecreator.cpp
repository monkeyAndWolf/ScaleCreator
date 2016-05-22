#include "scalecreator.h"

#include <QDebug>

ScaleCreator::ScaleCreator(QObject *parent) : QObject(parent)
{

}

void ScaleCreator::calculateScale(ScaleCreator::Key key, ScaleCreator::Mode mode)
{
    qDebug() << key << keyToString(key);
    int *pattern = getPattern(mode);
    QString notes;
    for (int i = 0, j = key; i < 7; i++)
    {
        notes += keyToString(intToKey(j));
        notes += "\n";
        int punk = pattern[i];
        j+=punk;
        qDebug() << j << punk << key << keyToString(intToKey(j));
    }
    emit stringScale(key, mode, notes);
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

