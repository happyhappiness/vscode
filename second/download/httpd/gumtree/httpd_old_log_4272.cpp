ap_log_error(APLOG_MARK, APLOG_ERR, 0, r->server,
               "ajp_handle_cping_cpong: awaited CPONG, received %d ",
               result);