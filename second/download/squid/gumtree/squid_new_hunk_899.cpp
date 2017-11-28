void
WIN32_RemoveService()
{
    SC_HANDLE schService;
    SC_HANDLE schSCManager;

    if (service_name.isEmpty())
        service_name = SBuf(APP_SHORTNAME);

    const char *service =  service_name.c_str();
    strcat(REGKEY, service);

    keys[4] = const_cast<char*>(service);

    schSCManager = OpenSCManager(NULL,	/* machine (NULL == local)    */
                                 NULL,          /* database (NULL == default) */
                                 SC_MANAGER_ALL_ACCESS	/* access required            */
                                );

    if (!schSCManager)
        fprintf(stderr, "OpenSCManager failed\n");
    else {
        schService = OpenService(schSCManager, service, SERVICE_ALL_ACCESS);

        if (schService == NULL)
            fprintf(stderr, "OpenService failed\n");

        /* Could not open the service */
        else {
