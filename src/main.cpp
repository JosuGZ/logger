#include "mainwindow.h"

#include "eventfilter.h"
#include <QApplication>

void registerSessionNotification(WId winId);

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);
    MainWindow w;
    registerSessionNotification(w.winId());
    EventFilter *eventFilter = new EventFilter(w);
    a.installNativeEventFilter(eventFilter);
    w.show();

    return a.exec();
}

void registerSessionNotification(WId winId) {
    // https://docs.microsoft.com/es-es/windows/desktop/api/wtsapi32/nf-wtsapi32-wtsregistersessionnotification
    WTSRegisterSessionNotification(
        HWND(winId), NOTIFY_FOR_ALL_SESSIONS // NOTIFY_FOR_THIS_SESSION
    );
}
