    SERVICE_TABLE_ENTRY dispatchTable[] =
    {
        { "", service_nt_main_fn },
        { NULL, NULL }
    };

    if (!StartServiceCtrlDispatcher(dispatchTable))
    {
        /* This is a genuine failure of the SCM. */
        rv = apr_get_os_error();
        ap_log_error(APLOG_MARK, APLOG_ERR | APLOG_STARTUP, rv, NULL,
                     "Error starting service control dispatcher");
