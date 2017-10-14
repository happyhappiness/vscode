ap_log_rerror(APLOG_MARK, APLOG_ERR, rv, r,
                      "lb_heartbeat: Unable to read heartbeats at '%s'",
                      ctx->path);