ap_log_perror(APLOG_MARK, APLOG_ERR, 0, p,
                      "Maximum new request methods %d reached while "
                      "registering method %s.",
                      METHOD_NUMBER_LAST, methname);