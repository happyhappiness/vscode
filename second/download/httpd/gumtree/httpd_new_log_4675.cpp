ap_log_error(APLOG_MARK, APLOG_WARNING, apr_get_os_error(),
                                 ap_server_conf, APLOGNO(00329)
                                 "mpm_get_completion_context: "
                                 "CreateEvent failed.");