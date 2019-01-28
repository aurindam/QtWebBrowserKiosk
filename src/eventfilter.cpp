#include "eventfilter.h"

#include <QDebug>
#include <QEvent>
#include <QMetaObject>

EventFilter::EventFilter(QObject *timer, QObject *parent) : QObject(parent), m_timer(timer)
{
}

bool EventFilter::eventFilter(QObject *obj, QEvent *ev)
{
    if(ev->type() == QEvent::MouseMove ||
            ev->type() == QEvent::TouchEnd) {
        QVariant returnedValue;
        QVariant msg = "Hello from C++";
        QMetaObject::invokeMethod(m_timer, "restartTimer",
                Q_RETURN_ARG(QVariant, returnedValue));
    }


  return QObject::eventFilter(obj, ev);
}
