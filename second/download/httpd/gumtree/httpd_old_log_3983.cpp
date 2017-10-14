ap_log_rerror(APLOG_MARK, APLOG_DEBUG, 0, r,
                      "request details scope:%u, cache:%u, filename:%s, function:%s",
                      d->spec->scope,
                      d->spec->code_cache_style,
                      d->spec->file,
                      d->function_name);