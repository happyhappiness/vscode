ap_log_rerror(APLOG_MARK, APLOG_NOERRNO|APLOG_ERR, r,
          "Request content-length of %s is larger than the configured "
          "limit of %lu", lenp, max_body);