#endif
        *printing = 1;
        *conditional_status = 1;
        return 0;
    }
    else {
        ap_log_error(APLOG_MARK, APLOG_NOERRNO|APLOG_ERR, r->server,
                    "endif directive does not take tags in %s",
		    r->filename);
        ap_rputs(error, r);
        return -1;
    }
}
