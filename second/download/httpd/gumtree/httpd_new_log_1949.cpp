ap_log_error(APLOG_MARK, APLOG_DEBUG, apr_get_netos_error(), 
                             ap_server_conf,
                             "winnt_accept: Failed to grab a connection ctx."
                             "  Temporary resource constraint? Retrying.");