static DWORD WINAPI
WIN32_IpAddrChangeMonitor(LPVOID lpParam)
{
    DWORD Result;
    HMODULE IPHLPAPIHandle;
    PFNotifyAddrChange NotifyAddrChange;

    if ((IPHLPAPIHandle = GetModuleHandle("IPHLPAPI")) == NULL)
        IPHLPAPIHandle = LoadLibrary("IPHLPAPI");
    NotifyAddrChange = (PFNotifyAddrChange) GetProcAddress(IPHLPAPIHandle, NOTIFYADDRCHANGE);

    while (1) {
        Result = NotifyAddrChange(NULL, NULL);
        if (Result != NO_ERROR) {
            debugs(1, 1, "NotifyAddrChange error " << Result);
            return 1;
        }
        debugs(1, 1, "Notification of IP address change received, requesting Squid reconfiguration ...");
        reconfigure(SIGHUP);
    }
    return 0;
}