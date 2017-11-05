ap_log_rerror(APLOG_MARK, APLOG_TRACE1, status, r,
                          "status_handler(%s): ap_pass_brigade failed", 
                          task->id);