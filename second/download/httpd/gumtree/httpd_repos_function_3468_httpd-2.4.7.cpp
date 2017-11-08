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

    if ((ChangeServiceConfig2) &&
        (schSCManager = OpenSCManager(NULL, NULL, SC_MANAGER_CONNECT)))
    {
        SC_HANDLE schService = OpenService(schSCManager, mpm_service_name,
                                           SERVICE_CHANGE_CONFIG);
        if (schService) {
            /* Cast is necessary, ChangeServiceConfig2 handles multiple
             * object types, some volatile, some not.
             */
            /* ###: utf-ize */
            ChangeServiceConfig2(schService,
                                 1 /* SERVICE_CONFIG_DESCRIPTION */,
                                 (LPVOID) &full_description);
            CloseServiceHandle(schService);
        }
        CloseServiceHandle(schSCManager);
    }
}