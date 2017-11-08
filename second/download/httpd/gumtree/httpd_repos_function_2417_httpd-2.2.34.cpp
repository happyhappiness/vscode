static void set_service_description(void)
{
    const char *full_description;
    SC_HANDLE schSCManager;

    /* Nothing to do if we are a console
     */
    if (!mpm_service_name)
        return;

    /* Time to fix up the description, upon each successful restart
     */
    full_description = ap_get_server_description();

    if ((osver.dwPlatformId == VER_PLATFORM_WIN32_NT)
          && (osver.dwMajorVersion > 4)
          && (ChangeServiceConfig2)
          && (schSCManager = OpenSCManager(NULL, NULL, SC_MANAGER_CONNECT)))
    {
        SC_HANDLE schService;

#if APR_HAS_UNICODE_FS
        IF_WIN_OS_IS_UNICODE
        {
            schService = OpenServiceW(schSCManager, mpm_service_name_w,
                                      SERVICE_CHANGE_CONFIG);
        }
#endif /* APR_HAS_UNICODE_FS */
#if APR_HAS_ANSI_FS
        ELSE_WIN_OS_IS_ANSI
        {
            schService = OpenService(schSCManager, mpm_service_name,
                                     SERVICE_CHANGE_CONFIG);
        }
#endif
        if (schService) {
            /* Cast is necessary, ChangeServiceConfig2 handles multiple
             * object types, some volatile, some not.
             */
#if APR_HAS_UNICODE_FS
            IF_WIN_OS_IS_UNICODE
            {
                apr_size_t slen = strlen(full_description) + 1;
                apr_size_t wslen = slen;
                apr_wchar_t *full_description_w = apr_palloc(pconf, wslen * sizeof(apr_wchar_t));
                apr_status_t rv = apr_conv_utf8_to_ucs2(full_description, &slen,
                                                        full_description_w, &wslen);
                if ((rv != APR_SUCCESS) || slen
                        || ChangeServiceConfig2W(schService,
                                                 1 /* SERVICE_CONFIG_DESCRIPTION */,
                                                 (LPVOID) &full_description_w))
                    full_description = NULL;
            }
#endif /* APR_HAS_UNICODE_FS */
#if APR_HAS_ANSI_FS
            ELSE_WIN_OS_IS_ANSI
            {
                if (ChangeServiceConfig2(schService,
                                         1 /* SERVICE_CONFIG_DESCRIPTION */,
                                         (LPVOID) &full_description))
                    full_description = NULL;
            }
#endif
            CloseServiceHandle(schService);
        }
        CloseServiceHandle(schSCManager);
    }

    if (full_description)
    {
        char szPath[MAX_PATH];
        ap_regkey_t *svckey;
        apr_status_t rv;

        /* Find the Service key that Monitor Applications iterate */
        apr_snprintf(szPath, sizeof(szPath),
                     "SYSTEM\\CurrentControlSet\\Services\\%s",
                     mpm_service_name);
        rv = ap_regkey_open(&svckey, AP_REGKEY_LOCAL_MACHINE, szPath,
                            APR_READ | APR_WRITE, pconf);
        if (rv != APR_SUCCESS) {
            return;
        }
        /* Attempt to set the Description value for our service */
        ap_regkey_value_set(svckey, "Description", full_description, 0, pconf);
        ap_regkey_close(svckey);
    }
}