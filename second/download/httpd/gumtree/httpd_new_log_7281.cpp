ap_log_rerror(
                APLOG_MARK, APLOG_INFO, 0, r, APLOGNO() "cache: %s responded with an uncacheable 304, retrying the request. Reason: %s", r->unparsed_uri, reason);