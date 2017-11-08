static DWORD WINAPI service_nt_dispatch_thread(LPVOID nada)
 {
#if APR_HAS_UNICODE_FS
    SERVICE_TABLE_ENTRYW dispatchTable_w[] =
    {
        { L"", service_nt_main_fn_w },
        { NULL, NULL }
    };
#endif /* APR_HAS_UNICODE_FS */
#if APR_HAS_ANSI_FS
    SERVICE_TABLE_ENTRYA dispatchTable[] =
    {
        { "", service_nt_main_fn },
        { NULL, NULL }
    };
#endif
    apr_status_t rv;
 
#if APR_HAS_UNICODE_FS
    IF_WIN_OS_IS_UNICODE
        rv = StartServiceCtrlDispatcherW(dispatchTable_w);
#endif
#if APR_HAS_ANSI_FS
    ELSE_WIN_OS_IS_ANSI
         rv = StartServiceCtrlDispatcherA(dispatchTable);
#endif
    if (rv) {
        rv = APR_SUCCESS;
    }
    else {
        /* This is a genuine failure of the SCM. */
        rv = apr_get_os_error();
        ap_log_error(APLOG_MARK, APLOG_ERR | APLOG_STARTUP, rv, NULL,
                     APLOGNO(00366) "Error starting Windows service control "
                     "dispatcher");
    }
    return (rv);
}