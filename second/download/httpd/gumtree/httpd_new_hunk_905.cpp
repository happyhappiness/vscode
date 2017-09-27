        }

        launch_cmd = apr_psprintf(ptemp, "\"%s\" -k runservice", exe_path);

        if (reconfig) {
            /* ###: utf-ize */
            schService = OpenService(schSCManager, mpm_service_name,
                                     SERVICE_CHANGE_CONFIG);
            if (!schService) {
                ap_log_error(APLOG_MARK, APLOG_ERR|APLOG_ERR,
                             apr_get_os_error(), NULL,
                             "OpenService failed");
            }
            /* ###: utf-ize */
            else if (!ChangeServiceConfig(schService,
                                          SERVICE_WIN32_OWN_PROCESS,
                                          SERVICE_AUTO_START,
                                          SERVICE_ERROR_NORMAL,
                                          launch_cmd, NULL, NULL,
                                          "Tcpip\0Afd\0", NULL, NULL,
                                          mpm_display_name)) {
                ap_log_error(APLOG_MARK, APLOG_ERR|APLOG_ERR,
                             apr_get_os_error(), NULL,
                             "ChangeServiceConfig failed");
	        /* !schService aborts configuration below */
	        CloseServiceHandle(schService);
	        schService = NULL;
	    }
        }
        else {
            /* RPCSS is the Remote Procedure Call (RPC) Locator required
             * for DCOM communication pipes.  I am far from convinced we
             * should add this to the default service dependencies, but
             * be warned that future apache modules or ISAPI dll's may
             * depend on it.
             */
            /* ###: utf-ize */
            schService = CreateService(schSCManager,         // SCManager database
                                   mpm_service_name,     // name of service
                                   mpm_display_name,     // name to display
