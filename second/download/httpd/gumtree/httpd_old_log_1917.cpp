ap_log_rerror(APLOG_MARK, APLOG_CRIT, 0, r,
                                          "Regular expression replacement "
                                          "failed for '%s', value too long?",
                                          elts[j].key);