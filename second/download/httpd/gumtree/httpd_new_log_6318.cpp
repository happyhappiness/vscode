ap_log_cerror(APLOG_MARK, APLOG_DEBUG, 0, ctx->owner, APLOGNO(10023)
                      "giving up after %d reconnects, %d requests todo",
                      reconnects, h2_proxy_fifo_count(ctx->requests));