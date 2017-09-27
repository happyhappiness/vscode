    return APR_SUCCESS;
}


/* signal_service_transition is a simple thunk to signal the service
 * and monitor its successful transition.  If the signal passed is 0,
 * then the caller is assumed to already have performed some service
 * operation to be monitored (such as StartService), and no actual
 * ControlService signal is sent.
 */

static int signal_service_transition(SC_HANDLE schService, DWORD signal, DWORD pending, DWORD complete)
{
    if (signal && !ControlService(schService, signal, &globdat.ssStatus))
        return FALSE;

    do {
        Sleep(1000);
        if (!QueryServiceStatus(schService, &globdat.ssStatus))
            return FALSE;
    } while (globdat.ssStatus.dwCurrentState == pending);

    return (globdat.ssStatus.dwCurrentState == complete);
}


apr_status_t mpm_service_start(apr_pool_t *ptemp, int argc,
                               const char * const * argv)
{
    apr_status_t rv;

    fprintf(stderr,"Starting the %s service\n", mpm_display_name);

    if (osver.dwPlatformId == VER_PLATFORM_WIN32_NT)
    {
        char **start_argv;
        SC_HANDLE   schService;
