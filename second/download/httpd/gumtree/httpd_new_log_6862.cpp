ap_log_cerror(APLOG_MARK, APLOG_DEBUG, status, ctx->owner, APLOGNO(03353)
                          "setup new connection: is_ssl=%d %s %s %s", 
                          ctx->p_conn->is_ssl, ctx->p_conn->ssl_hostname, 
                          locurl, ctx->p_conn->hostname);