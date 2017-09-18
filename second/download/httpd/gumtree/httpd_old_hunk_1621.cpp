#endif
        *printing = !(*conditional_status);
        *conditional_status = 1;
        return 0;
    }
    else {
        ap_log_error(APLOG_MARK, APLOG_NOERRNO|APLOG_ERR, r->server,
                    "else directive does not take tags in %s",
		    r->filename);
        if (*printing) {
            ap_rputs(error, r);
        }
        return -1;
