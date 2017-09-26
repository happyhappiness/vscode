        if (!schSCManager) {
            rv = apr_get_os_error();
            ap_log_error(APLOG_MARK, APLOG_ERR | APLOG_STARTUP, rv, NULL,
                         "Failed to open the WinNT service manager.");
            return (rv);
        }

        /* ###: utf-ize */
        schService = OpenService(schSCManager, mpm_service_name, DELETE);

        if (!schService) {
           rv = apr_get_os_error();
           ap_log_error(APLOG_MARK, APLOG_ERR | APLOG_STARTUP, rv, NULL,
			"%s: OpenService failed", mpm_display_name);
           return (rv);
        }

        /* assure the service is stopped before continuing
         *
         * This may be out of order... we might not be able to be
         * granted all access if the service is running anyway.
         *
         * And do we want to make it *this easy* for them
