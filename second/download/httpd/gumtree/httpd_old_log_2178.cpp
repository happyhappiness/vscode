ap_log_error(APLOG_MARK, APLOG_ALERT, errno, NULL,
                         "getpwuid: couldn't determine user name from uid %u, "
                         "you probably need to modify the User directive",
                         (unsigned)uid);