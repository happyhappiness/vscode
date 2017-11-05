ap_log_rerror(APLOG_MARK, APLOG_TRACE1, 0, r, 
                      "%s, early announcing %d resources for push",
                      tag, conf->push_list->nelts);