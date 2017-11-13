ap_log_cerror(APLOG_MARK, APLOG_DEBUG, 0, c,
                          "%s: type: %s, length: %" APR_SIZE_T_FMT,
                          fname, b->type->name ? b->type->name : "(unknown)",
                          b->length);