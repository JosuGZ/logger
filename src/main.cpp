#include "mainwindow.h"


#ifdef __windows__
#include "eventfilter.h"
#endif
#include <QApplication>

#ifdef __windows__
void registerSessionNotification(WId winId);
#endif

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);
    MainWindow w;
#ifdef __windows__
    registerSessionNotification(w.winId());
    EventFilter *eventFilter = new EventFilter(w);
    a.installNativeEventFilter(eventFilter);
#endif
    w.show();

    return a.exec();
}

#ifdef __windows__
void registerSessionNotification(WId winId) {
    // https://docs.microsoft.com/es-es/windows/desktop/api/wtsapi32/nf-wtsapi32-wtsregistersessionnotification
    WTSRegisterSessionNotification(
        HWND(winId), NOTIFY_FOR_ALL_SESSIONS // NOTIFY_FOR_THIS_SESSION
    );
}
#endif
