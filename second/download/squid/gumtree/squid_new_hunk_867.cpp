                      version_string);

    storeAppendPrintf(sentry, "Build Info: " SQUID_BUILD_INFO "\n");

#if _SQUID_WINDOWS_
    if (WIN32_run_mode == _WIN_SQUID_RUN_MODE_SERVICE) {
        storeAppendPrintf(sentry,"\nRunning as " SQUIDSBUFPH " Windows System Service on %s\n",
                          SQUIDSBUFPRINT(service_name), WIN32_OS_string);
        storeAppendPrintf(sentry,"Service command line is: %s\n", WIN32_Service_Command_Line);
    } else
        storeAppendPrintf(sentry,"Running on %s\n",WIN32_OS_string);
#else
    storeAppendPrintf(sentry,"Service Name: " SQUIDSBUFPH "\n", SQUIDSBUFPRINT(service_name));
#endif

    storeAppendPrintf(sentry, "Start Time:\t%s\n",
                      mkrfc1123(stats.squid_start.tv_sec));

    storeAppendPrintf(sentry, "Current Time:\t%s\n",
                      mkrfc1123(stats.current_time.tv_sec));

    storeAppendPrintf(sentry, "Connection information for %s:\n",APP_SHORTNAME);

    if (Config.onoff.client_db)
        storeAppendPrintf(sentry, "\tNumber of clients accessing cache:\t%.0f\n", stats.client_http_clients);
    else
        sentry->append("\tNumber of clients accessing cache:\t(client_db off)\n", 52);

    storeAppendPrintf(sentry, "\tNumber of HTTP requests received:\t%.0f\n",
                      stats.client_http_requests);

    storeAppendPrintf(sentry, "\tNumber of ICP messages received:\t%.0f\n",
                      stats.icp_pkts_recv);
