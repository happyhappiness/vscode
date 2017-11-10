apr_status_t apr_get_oslevel(apr_oslevel_e *level)
{
    if (apr_os_level == APR_WIN_UNK) 
    {
        static OSVERSIONINFO oslev;
        oslev.dwOSVersionInfoSize = sizeof(OSVERSIONINFO);
        GetVersionEx(&oslev);

        if (oslev.dwPlatformId == VER_PLATFORM_WIN32_NT) 
        {
            static unsigned int servpack = 0;
            TCHAR *pservpack;
            if ((pservpack = oslev.szCSDVersion)) {
                while (*pservpack && !apr_isdigit(*pservpack)) {
                    pservpack++;
                }
                if (*pservpack)
#ifdef _UNICODE
                    servpack = _wtoi(pservpack);
#else
                    servpack = atoi(pservpack);
#endif
            }

            if (oslev.dwMajorVersion < 3) {
                apr_os_level = APR_WIN_UNSUP;
            }
            else if (oslev.dwMajorVersion == 3) {
                if (oslev.dwMajorVersion < 50) {
                    apr_os_level = APR_WIN_UNSUP;
                }
                else if (oslev.dwMajorVersion == 50) {
                    apr_os_level = APR_WIN_NT_3_5;
                }
                else {
                    apr_os_level = APR_WIN_NT_3_51;
                }
            }
            else if (oslev.dwMajorVersion == 4) {
                if (servpack < 2)
                    apr_os_level = APR_WIN_NT_4;
                else if (servpack <= 2)
                    apr_os_level = APR_WIN_NT_4_SP2;
                else if (servpack <= 3)
                    apr_os_level = APR_WIN_NT_4_SP3;
                else if (servpack <= 4)
                    apr_os_level = APR_WIN_NT_4_SP4;
                else if (servpack <= 5)
                    apr_os_level = APR_WIN_NT_4_SP5;
                else 
                    apr_os_level = APR_WIN_NT_4_SP6;
            }
            else if (oslev.dwMajorVersion == 5) {
                if (oslev.dwMinorVersion == 0) {
                    if (servpack == 0)
                        apr_os_level = APR_WIN_2000;
                    else if (servpack == 1)
                        apr_os_level = APR_WIN_2000_SP1;
                    else
                        apr_os_level = APR_WIN_2000_SP2;
                }
                else if (oslev.dwMinorVersion == 2) {
                    apr_os_level = APR_WIN_2003;
                }
                else {
                    if (servpack < 1)
                        apr_os_level = APR_WIN_XP;
                    else if (servpack == 1)
                        apr_os_level = APR_WIN_XP_SP1;
                    else
                        apr_os_level = APR_WIN_XP_SP2;
                }
            }
            else if (oslev.dwMajorVersion == 6) {
                if (oslev.dwMinorVersion == 0)
                    apr_os_level = APR_WIN_VISTA;
                else
                    apr_os_level = APR_WIN_7;
            }
            else {
                apr_os_level = APR_WIN_XP;
            }
        }
#ifndef WINNT
        else if (oslev.dwPlatformId == VER_PLATFORM_WIN32_WINDOWS) {
            TCHAR *prevision;
            if (prevision = oslev.szCSDVersion) {
                while (*prevision && !apr_isupper(*prevision)) {
                     prevision++;
                }
            }
            else prevision = _T("");

            if (oslev.dwMinorVersion < 10) {
                if (*prevision < _T('C'))
                    apr_os_level = APR_WIN_95;
                else
                    apr_os_level = APR_WIN_95_OSR2;
            }
            else if (oslev.dwMinorVersion < 90) {
                if (*prevision < _T('A'))
                    apr_os_level = APR_WIN_98;
                else
                    apr_os_level = APR_WIN_98_SE;
            }
            else {
                apr_os_level = APR_WIN_ME;
            }
        }
#endif
#ifdef _WIN32_WCE
        else if (oslev.dwPlatformId == VER_PLATFORM_WIN32_CE) 
        {
            if (oslev.dwMajorVersion < 3) {
                apr_os_level = APR_WIN_UNSUP;
            }
            else {
                apr_os_level = APR_WIN_CE_3;
            }
        }
#endif
        else {
            apr_os_level = APR_WIN_UNSUP;
        }
    }

    *level = apr_os_level;

    if (apr_os_level < APR_WIN_UNSUP) {
        return APR_EGENERAL;
    }

    return APR_SUCCESS;
}