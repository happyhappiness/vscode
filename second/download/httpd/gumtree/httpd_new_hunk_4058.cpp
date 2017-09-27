            break;
        }
        p++;
    }
    
    if (found) {
        h2_ctx *ctx = h2_ctx_get(c, 1);
        
        ap_log_cerror(APLOG_MARK, APLOG_TRACE1, 0, c,
                      "switching protocol to '%s'", protocol);
        h2_ctx_protocol_set(ctx, protocol);
        h2_ctx_server_set(ctx, s);
        
