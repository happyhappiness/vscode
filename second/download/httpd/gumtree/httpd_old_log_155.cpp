ap_log_rerror(APLOG_MARK, APLOG_DEBUG|APLOG_NOERRNO, 0, r,
                          "xlate input filter not added implicitly because %s",
                          !reqinfo->input_ctx ?
                          "no input configuration available" :
                          "another module added the filter");