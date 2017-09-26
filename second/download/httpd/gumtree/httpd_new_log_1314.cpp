ap_log_rerror(APLOG_MARK, APLOG_WARNING, 0, r,
                              "incomplete redirection target of '%s' for "
                              "URI '%s' modified to '%s'",
                              orig_target, r->uri, ret);