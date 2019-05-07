#include "states.hpp"

States::States(QObject* parent)
    : QObject(parent)
    , actualData(nullptr)
{
}

States::~States()
{
    if (actualData) {
        array.removeAll(actualData);
        delete actualData;
        actualData = nullptr;
    }

    qDeleteAll(array);
    array.clear();
}

void States::undo()
{
    if (actualData) {
        array.removeAll(actualData);
        delete actualData;
        actualData = nullptr;
    }
    if (hasStates()) {
        actualData = array.takeFirst();
    }
    emit notifyObservers();
}

bool States::hasStates() const
{
    return !array.empty();
}

Estate* States::getActualData() const
{
    return actualData;
}

void States::add(Estate* state)
{
    if (!state)
        return;
    if (actualData) {
        array.push_front(actualData);
    }
    array.push_front(state);
    actualData = array.first();
    emit notifyObservers();
}