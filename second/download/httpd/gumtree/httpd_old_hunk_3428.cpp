         * for DCOM communication pipes.  I am far from convinced we
         * should add this to the default service dependencies, but
         * be warned that future apache modules or ISAPI dll's may
         * depend on it.
         */
        /* ###: utf-ize */
        schService = CreateService(schSCManager,         // SCManager database
                                   mpm_service_name,     // name of service
                                   mpm_display_name,     // name to display
                                   SERVICE_ALL_ACCESS,   // access required
                                   SERVICE_WIN32_OWN_PROCESS,  // service type
                                   SERVICE_AUTO_START,   // start type
                                   SERVICE_ERROR_NORMAL, // error control type
                                   launch_cmd,           // service's binary
                                   NULL,                 // no load svc group
                                   NULL,                 // no tag identifier
                                   "Tcpip\0Afd\0",       // dependencies
                                   NULL,                 // use SYSTEM account
                                   NULL);                // no password

        if (!schService)
        {
            rv = apr_get_os_error();
            ap_log_error(APLOG_MARK, APLOG_ERR | APLOG_STARTUP, rv, NULL,
                         "Failed to create WinNT Service Profile");
            CloseServiceHandle(schSCManager);
            return (rv);
        }
    }

