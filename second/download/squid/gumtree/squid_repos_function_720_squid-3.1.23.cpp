VOID WINAPI
WIN32_svcHandler(DWORD Opcode)
{
    DWORD status;

    switch (Opcode) {

    case _WIN_SQUID_SERVICE_CONTROL_STOP:

    case _WIN_SQUID_SERVICE_CONTROL_SHUTDOWN:
        /* Do whatever it takes to stop here. */
        svcStatus.dwWin32ExitCode = 0;
        svcStatus.dwCurrentState = SERVICE_STOP_PENDING;
        svcStatus.dwCheckPoint = 0;
        svcStatus.dwWaitHint = 10000;
        shut_down(SIGTERM);

        if (!SetServiceStatus(svcHandle, &svcStatus)) {
            status = GetLastError();
            debugs(1, 1, "SetServiceStatus error " << status);
        }

        debugs(1, 1, "Leaving Squid service");
        return;

    case _WIN_SQUID_SERVICE_CONTROL_INTERROGATE:
        /* Fall through to send current status. */

        if (!SetServiceStatus(svcHandle, &svcStatus)) {
            status = GetLastError();
            debugs(1, 1, "SetServiceStatus error " << status);
        }

        break;

    case _WIN_SQUID_SERVICE_CONTROL_ROTATE:
        rotate_logs(SIGUSR1);
        break;

    case _WIN_SQUID_SERVICE_CONTROL_RECONFIGURE:
        reconfigure(SIGHUP);
        break;

    case _WIN_SQUID_SERVICE_CONTROL_DEBUG:
        sigusr2_handle(SIGUSR2);
        break;

    case _WIN_SQUID_SERVICE_CONTROL_INTERRUPT:
        /* Do whatever it takes to stop here. */
        svcStatus.dwWin32ExitCode = 0;
        svcStatus.dwCurrentState = SERVICE_STOP_PENDING;
        svcStatus.dwCheckPoint = 0;
        svcStatus.dwWaitHint = 10000;
        shut_down(SIGINT);

        if (!SetServiceStatus(svcHandle, &svcStatus)) {
            status = GetLastError();
            debugs(1, 1, "SetServiceStatus error " << status);
        }

        debugs(1, 1, "Leaving Squid service");
        break;

    default:
        debugs(1, 1, "Unrecognized opcode " << Opcode);
    }

    return;
}