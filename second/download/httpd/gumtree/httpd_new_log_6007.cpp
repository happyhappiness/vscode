ap_log_rerror(APLOG_MARK, APLOG_TRACE2, 0, ctx->r, 
                      "reverse_map[%s] %s --> %s", ctx->p_server_uri, buffer, mapped);