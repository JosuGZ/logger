#include "eventfilter.h"

#ifdef __windows__

EventFilter::EventFilter(MainWindow &mainWindow): mMainWindow(mainWindow) {};

// https://docs.microsoft.com/en-us/windows/desktop/api/winuser/ns-winuser-tagmsg
// https://docs.microsoft.com/en-us/windows/desktop/api/winuser/nf-winuser-getmessage
// https://docs.microsoft.com/en-us/windows/desktop/power/wm-power
// https://docs.microsoft.com/en-us/windows/desktop/power/wm-powerbroadcast
// https://docs.microsoft.com/en-us/windows/desktop/power/wm-powerbroadcast-messages
bool EventFilter::nativeEventFilter(const QByteArray &eventType, void *message, long *result) {
    if (eventType == "windows_generic_MSG" /*"windows_dispatcher_MSG"*/) {
        MSG * windowsMSG = static_cast<MSG *>(message);

        switch (windowsMSG->message) {
            // https://stackoverflow.com/questions/5198210/windows-message-for-user-locking-screen
            // Bloqueo de pantalla (Requiere registro) -> https://docs.microsoft.com/es-es/windows/desktop/api/wtsapi32/nf-wtsapi32-wtsregistersessionnotification
            // https://docs.microsoft.com/es-es/windows/desktop/TermServ/wm-wtssession-change
            case WM_WTSSESSION_CHANGE: {
                QString type;
                switch (windowsMSG->wParam) {
                    case WTS_CONSOLE_CONNECT:
                        type = "WTS_CONSOLE_CONNECT";
                        break;
                    case WTS_CONSOLE_DISCONNECT:
                        type = "WTS_CONSOLE_DISCONNECT";
                        break;
                    case WTS_REMOTE_CONNECT:
                        type = "WTS_REMOTE_CONNECT";
                        break;
                    case WTS_REMOTE_DISCONNECT:
                        type = "WTS_REMOTE_DISCONNECT";
                        break;
                    case WTS_SESSION_LOGON:
                        type = "WTS_SESSION_LOGON";
                        break;
                    case WTS_SESSION_LOGOFF:
                        type = "WTS_SESSION_LOGOFF";
                        break;
                    case WTS_SESSION_LOCK:
                        mMainWindow.log(QString("Session locked"));
                        type = "WTS_SESSION_LOCK";
                        break;
                    case WTS_SESSION_UNLOCK:
                        mMainWindow.log(QString("Session unlocked"));
                        type = "WTS_SESSION_UNLOCK";
                        break;
                    case WTS_SESSION_REMOTE_CONTROL:
                        type = "WTS_SESSION_REMOTE_CONTROL";
                        break;
                    case WTS_SESSION_CREATE:
                        type = "WTS_SESSION_CREATE";
                        break;
                    case WTS_SESSION_TERMINATE:
                        type = "WTS_SESSION_TERMINATE";
                        break;
                    default:
                        type = "UNKOWN";
                        break;
                }
                qDebug() << QString("WM_WTSSESSION_CHANGE: %1 (Session Identifier: %2)").arg(type).arg(windowsMSG->lParam);
            } break;
            case WM_POWERBROADCAST:
            // https://forum.qt.io/topic/69485/do-an-operation-when-computer-goes-to-sleep/3
            qDebug() << "WM_POWERBROADCAST" << windowsMSG->message;
            switch (windowsMSG->wParam) {
              case PBT_APMPOWERSTATUSCHANGE:
            /*{
                mMainWindow.log(QString("WM_POWERBROADCAST: PBT_APMPOWERSTATUSCHANGE  received LPARAM: %1").arg(windowsMSG->lParam));
                // https://docs.microsoft.com/en-us/windows/desktop/power/pbt-apmpowerstatuschange
                // https://docs.microsoft.com/es-es/windows/desktop/api/winbase/ns-winbase-_system_power_status
                struct _SYSTEM_POWER_STATUS lpSystemPowerStatus;
                BOOL result = GetSystemPowerStatus(&lpSystemPowerStatus); // TODO
                mMainWindow.log(QString("ACLineStatus: %1").arg(lpSystemPowerStatus.ACLineStatus));
                mMainWindow.log(QString("BatteryFlag: %1").arg(lpSystemPowerStatus.BatteryFlag));
                mMainWindow.log(QString("BatteryLifePercent: %1").arg(lpSystemPowerStatus.BatteryLifePercent));
                //mMainWindow.log(QString("SystemStatusFlag: %1").arg(lpSystemPowerStatus.SystemStatusFlag));
                mMainWindow.log(QString("BatteryLifeTime: %1").arg(lpSystemPowerStatus.BatteryLifeTime));
                mMainWindow.log(QString("BatteryFullLifeTime: %1").arg(lpSystemPowerStatus.BatteryFullLifeTime));
}*/
                break;
              case PBT_APMRESUMEAUTOMATIC:
                //mMainWindow.log(QString("WM_POWERBROADCAST: PBT_APMRESUMEAUTOMATIC  received LPARAM: %1").arg(windowsMSG->lParam));
                break;
              case PBT_APMRESUMESUSPEND:
                mMainWindow.log(QString("System resumed"));
                //mMainWindow.log(QString("WM_POWERBROADCAST: PBT_APMRESUMESUSPEND  received LPARAM: %1").arg(windowsMSG->lParam));
                break;
              case PBT_APMSUSPEND:
                mMainWindow.log(QString("System suspended"));
                //mMainWindow.log(QString("WM_POWERBROADCAST: PBT_APMSUSPEND  received LPARAM: %1").arg(windowsMSG->lParam));
                break;
              default:
                //mMainWindow.log(QString("WM_POWERBROADCAST: WPARAM: %1 LPARAM: %2").arg(windowsMSG->wParam).arg(windowsMSG->lParam));
                break;
            }
            break;
        default:
            break;
        }
    }
    return false;
}

#endif // __windows__
