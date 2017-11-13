ap_log_rerror(APLOG_MARK, APLOG_DEBUG, 0, r,
                          "proxy: Unhandled bucket type of type %s in"
                          " ap_proxy_buckets_lifetime_transform", e->type->name);