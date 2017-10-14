ap_log_error(APLOG_MARK, APLOG_WARNING, 0, ap_server_conf, APLOGNO(00331)
                     "winnt_accept: unrecognized AcceptFilter '%s', "
                     "only 'data', 'connect' or 'none' are valid. "
                     "Using 'none' instead", accf_name);