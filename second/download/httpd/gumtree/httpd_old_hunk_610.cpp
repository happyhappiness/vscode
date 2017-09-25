            && (service_to_start_success != APR_SUCCESS)) {
        ap_log_error(APLOG_MARK,APLOG_CRIT, service_to_start_success, NULL, 
                     "%s: Unable to start the service manager.",
                     service_name);
        exit(APEXIT_INIT);
    }

    /* Win9x: disable AcceptEx */
    if (osver.dwPlatformId == VER_PLATFORM_WIN32_WINDOWS) {
        use_acceptex = 0;
    }

