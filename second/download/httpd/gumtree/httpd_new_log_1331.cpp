ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r,
                      "%s: Forcing worker (%s) into error state "
                      "due to timeout and 'failonstatus' parameter being set",
                       balancer->name, worker->name);