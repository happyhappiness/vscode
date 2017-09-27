ap_log_error(APLOG_MARK,APLOG_NOTICE, APR_SUCCESS, ap_server_conf,
                             "Parent: Forcing termination of child process %pp",
                             event_handles[CHILD_HANDLE]);