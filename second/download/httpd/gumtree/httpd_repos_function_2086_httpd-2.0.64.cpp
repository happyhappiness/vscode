static void set_service_description(void)
{
    const char *full_description;
    SC_HANDLE schSCManager;
    BOOL ret = 0;

    /* Nothing to do if we are a console
     */
    if (!mpm_service_name)
        return;

    /* Time to fix up the description, upon each successful restart
     */
    full_description = ap_get_server_version();

    if ((osver.dwPlatformId == VER_PLATFORM_WIN32_NT) 
          && (osver.dwMajorVersion > 4) 
          && (ChangeServiceConfig2)
          && (schSCManager = OpenSCManager(NULL, NULL, SC_MANAGER_CONNECT)))
    {    
        SC_HANDLE schService = OpenService(schSCManager, mpm_service_name,
                                           SERVICE_CHANGE_CONFIG);
        if (schService) {
            /* Cast is necessary, ChangeServiceConfig2 handles multiple
             * object types, some volatile, some not.
             */
            /* ###: utf-ize */
            if (ChangeServiceConfig2(schService,
                                     1 /* SERVICE_CONFIG_DESCRIPTION */,
                                     (LPVOID) &full_description)) {
                full_description = NULL;
            }
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