static unsigned int
GetOSVersion()
{
    OSVERSIONINFOEX osvi;
    BOOL bOsVersionInfoEx;

    safe_free(WIN32_OS_string);
    memset(&osvi, '\0', sizeof(OSVERSIONINFOEX));
    /* Try calling GetVersionEx using the OSVERSIONINFOEX structure.
     * If that fails, try using the OSVERSIONINFO structure.
     */

    osvi.dwOSVersionInfoSize = sizeof(OSVERSIONINFOEX);

    if (!(bOsVersionInfoEx = GetVersionEx((OSVERSIONINFO *) & osvi))) {
        osvi.dwOSVersionInfoSize = sizeof(OSVERSIONINFO);
        if (!GetVersionEx((OSVERSIONINFO *) & osvi))
            goto GetVerError;
    }
    switch (osvi.dwPlatformId) {
    case VER_PLATFORM_WIN32_NT:
        if (osvi.dwMajorVersion <= 4) {
            WIN32_OS_string = xstrdup("Windows NT");
            return _WIN_OS_WINNT;
        }
        if ((osvi.dwMajorVersion == 5) && (osvi.dwMinorVersion == 0)) {
            WIN32_OS_string = xstrdup("Windows 2000");
            return _WIN_OS_WIN2K;
        }
        if ((osvi.dwMajorVersion == 5) && (osvi.dwMinorVersion == 1)) {
            WIN32_OS_string = xstrdup("Windows XP");
            return _WIN_OS_WINXP;
        }
        if ((osvi.dwMajorVersion == 5) && (osvi.dwMinorVersion == 2)) {
            WIN32_OS_string = xstrdup("Windows Server 2003");
            return _WIN_OS_WINNET;
        }
        if ((osvi.dwMajorVersion == 6) && (osvi.dwMinorVersion == 0)) {
            if (osvi.wProductType == VER_NT_WORKSTATION)
                WIN32_OS_string = xstrdup("Windows Vista");
            else
                WIN32_OS_string = xstrdup("Windows Server 2008");
            return _WIN_OS_WINLON;
        }
        if ((osvi.dwMajorVersion == 6) && (osvi.dwMinorVersion == 1)) {
            if (osvi.wProductType == VER_NT_WORKSTATION)
                WIN32_OS_string = xstrdup("Windows 7");
            else
                WIN32_OS_string = xstrdup("Windows Server 2008 R2");
            return _WIN_OS_WIN7;
        }
        if (((osvi.dwMajorVersion > 6)) || ((osvi.dwMajorVersion == 6) && (osvi.dwMinorVersion > 1))) {
            if (osvi.wProductType == VER_NT_WORKSTATION)
                WIN32_OS_string = xstrdup("Unknown Windows version, assuming Windows 7 capabilities");
            else
                WIN32_OS_string = xstrdup("Unknown Windows version, assuming Windows Server 2008 R2 capabilities");
            return _WIN_OS_WIN7;
        }
        break;
    case VER_PLATFORM_WIN32_WINDOWS:
        if ((osvi.dwMajorVersion == 4) && (osvi.dwMinorVersion == 0)) {
            WIN32_OS_string = xstrdup("Windows 95");
            return _WIN_OS_WIN95;
        }
        if ((osvi.dwMajorVersion == 4) && (osvi.dwMinorVersion == 10)) {
            WIN32_OS_string = xstrdup("Windows 98");
            return _WIN_OS_WIN98;
        }
        if ((osvi.dwMajorVersion == 4) && (osvi.dwMinorVersion == 90)) {
            WIN32_OS_string = xstrdup("Windows Me");
            return _WIN_OS_WINME;
        }
        break;
    case VER_PLATFORM_WIN32s:
        WIN32_OS_string = xstrdup("Windows 3.1 with WIN32S");
        return _WIN_OS_WIN32S;
        break;
    default:
        break;
    }
GetVerError:
    WIN32_OS_string = xstrdup("Unknown Windows system");
    return _WIN_OS_UNKNOWN;
}