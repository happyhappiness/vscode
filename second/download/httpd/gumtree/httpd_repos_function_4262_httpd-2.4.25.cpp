static APR_INLINE SC_HANDLE OpenSCManager(const void *lpMachine,
                                          const void *lpDatabase,
                                          DWORD dwAccess)
{
    if (!pfn_OpenSCManager) {
#if APR_HAS_UNICODE_FS
        IF_WIN_OS_IS_UNICODE
            pfn_OpenSCManager = (fpt_OpenSCManager)OpenSCManagerW;
#endif
#if APR_HAS_ANSI_FS
        ELSE_WIN_OS_IS_ANSI
            pfn_OpenSCManager = (fpt_OpenSCManager)OpenSCManagerA;
#endif
    }
    return (*(pfn_OpenSCManager))(lpMachine, lpDatabase, dwAccess); 
}