ap_log_error(APLOG_MARK, APLOG_WARNING, apr_get_netos_error(), 
                             ap_server_conf,
                             "winnt_accept: Failed to allocate an accept socket. "
                             "Temporary resource constraint? Try again.");