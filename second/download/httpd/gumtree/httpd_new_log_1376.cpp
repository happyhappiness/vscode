ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, NULL,
                 "cache: Key for entity %s?%s is %s", r->parsed_uri.path,
                 r->parsed_uri.query, *key);