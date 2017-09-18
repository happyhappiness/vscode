ap_log_error(APLOG_MARK, APLOG_ERR | APLOG_NOERRNO, 0, NULL,
                         "A subtree cannot specify a different DAV provider "
                         "than its parent.");