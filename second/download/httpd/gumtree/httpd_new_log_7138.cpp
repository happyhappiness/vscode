ap_log_cerror(APLOG_MARK, APLOG_TRACE3, status, ctx->owner, 
                          "h2_proxy_engine(%s): pulled request (%s) %s", 
                          ctx->engine_id, 
                          before_leave? "before leave" : "regular", 
                          r->the_request);