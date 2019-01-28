#ifndef EVENTFILTER_H
#define EVENTFILTER_H

#include <QObject>

class EventFilter : public QObject
{
    Q_OBJECT
public:
    explicit EventFilter(QObject* timer, QObject *parent = nullptr);

protected:
      bool eventFilter(QObject *obj, QEvent *ev);

private:
      QObject *m_timer;
};

#endif // EVENTFILTER_H
