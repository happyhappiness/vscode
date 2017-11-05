ap_log_error(APLOG_MARK, APLOG_NOTICE, rv, r->server,
                    "Detected ErrorOnState (%d) for member (%s). Forcing worker into error state.", val, worker->name);