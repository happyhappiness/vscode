ap_log_cerror(APLOG_MARK, APLOG_TRACE1, status, ctx->owner, 
                              "set SNI to %s for (%s)", 
                              ctx->p_conn->ssl_hostname, 
                              ctx->p_conn->hostname);