ap_log_rerror(APLOG_MARK, APLOG_DEBUG, errno, r, APLOGNO(01256)
                              "connect #%d to cgi daemon failed, sleeping before retry",
                              connect_tries);