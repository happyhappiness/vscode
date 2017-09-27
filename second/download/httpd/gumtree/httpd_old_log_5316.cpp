ap_log_error(APLOG_MARK, APLOG_WARNING, apr_get_netos_error(), 
                     ap_server_conf,
                     "winnt_accept: unrecognized AcceptFilter '%s', "
                     "only 'data', 'connect' or 'none' are valid. "
                     "Using 'none' instead", accf_name);