ap_log_error(APLOG_MARK, APLOG_ALERT, 0,
                         ap_server_conf,
                         "A resource shortage or other unrecoverable failure "
                         "was encountered before any child process initialized "
                         "successfully... httpd is exiting!");