#ifndef EVENTFILTER_H
#define EVENTFILTER_H

#include "mainwindow.h"

#include <QAbstractNativeEventFilter>
#include <QDebug>
#include <windows.h>
#include <wtsapi32.h>

// https://doc.qt.io/qt-5/qabstractnativeeventfilter.html
class EventFilter : public QAbstractNativeEventFilter {

public:
    explicit EventFilter(MainWindow &mainWindow);
    bool nativeEventFilter(const QByteArray &eventType, void *message, long *result) override;

private:
    MainWindow &mMainWindow;
};

// Native event: https://stackoverflow.com/questions/14048565/get-hwnd-on-windows-with-qt5-from-wid

#endif // EVENTFILTER_H
