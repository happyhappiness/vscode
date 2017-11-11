FARPROC apr_load_dll_func(apr_dlltoken_e fnLib, char* fnName, int ordinal)
{
    if (!lateDllHandle[fnLib]) { 
        lateDllHandle[fnLib] = LoadLibrary(lateDllName[fnLib]);
        if (!lateDllHandle[fnLib])
            return NULL;
    }
    if (ordinal)
        return GetProcAddress(lateDllHandle[fnLib], (char *) ordinal);
    else
        return GetProcAddress(lateDllHandle[fnLib], fnName);
}