ap_log_rerror(APLOG_MARK, APLOG_DEBUG, 0, r,
                          "xlate output filter not added implicitly because %s",
                          !reqinfo->output_ctx ? 
                          "no output configuration available" :
                          "another module added the filter");