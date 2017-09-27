ap_log_error(APLOG_MARK, APLOG_ALERT, errno, NULL,
                         "getpwuid: couldn't determine user name from uid %ld, "
                         "you probably need to modify the User directive",
                         (long)uid);