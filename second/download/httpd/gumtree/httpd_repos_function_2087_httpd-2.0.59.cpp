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