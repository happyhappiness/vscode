FARPROC apr_load_dll_func(apr_dlltoken_e fnLib, char* fnName, int ordinal)
{
    if (!lateDllHandle[fnLib]) { 
        lateDllHandle[fnLib] = LoadLibraryA(lateDllName[fnLib]);
        if (!lateDllHandle[fnLib])
            return NULL;
    }
#if defined(_WIN32_WCE)
    if (ordinal)
        return GetProcAddressA(lateDllHandle[fnLib], (const char *)
                                                     (apr_ssize_t)ordinal);
    else
        return GetProcAddressA(lateDllHandle[fnLib], fnName);
#else
    if (ordinal)
        return GetProcAddress(lateDllHandle[fnLib], (const char *)
                                                    (apr_ssize_t)ordinal);
    else
        return GetProcAddress(lateDllHandle[fnLib], fnName);
#endif
}