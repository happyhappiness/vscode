static LRESULT WINAPI RegisterWindows9xService(BOOL set_service)
{
    static HINSTANCE hkernel;
    static DWORD (WINAPI *register_service_process)(DWORD, DWORD) = NULL;
    BOOL rv;

    if (set_service == is_service)
        return 1;

#ifdef DBG
    DbgPrintf("R %s proc %8.8x as a service\r\n",
              set_service ? "installing" : "removing",
              GetCurrentProcessId());
#endif

    if (!register_service_process)
    {
        /* Obtain a handle to the kernel library */
        hkernel = LoadLibrary("KERNEL32.DLL");
        if (!hkernel)
            return 0;

        /* Find the RegisterServiceProcess function */
        register_service_process = (DWORD (WINAPI *)(DWORD, DWORD))
                         GetProcAddress(hkernel, "RegisterServiceProcess");
        if (register_service_process == NULL) {
            FreeLibrary(hkernel);
            return 0;
        }
    }

    /* Register this process as a service */
    rv = register_service_process(0, set_service != FALSE);
    if (rv)
        is_service = set_service;

    if (!is_service)
    {
        /* Unload the kernel library */
        FreeLibrary(hkernel);
        register_service_process = NULL;
    }
    return rv;
}