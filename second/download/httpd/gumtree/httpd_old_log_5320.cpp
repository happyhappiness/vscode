ap_log_error(APLOG_MARK, APLOG_ERR | APLOG_STARTUP, rv, NULL,
                     "Failed to open the WinNT service manager, perhaps "
                     "you forgot to log in as Adminstrator?");