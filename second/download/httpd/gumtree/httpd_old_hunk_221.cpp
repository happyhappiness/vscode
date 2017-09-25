	setuid(unixd_config.user_id) == -1)) {
	ap_log_error(APLOG_MARK, APLOG_ALERT, errno, NULL,
		    "setuid: unable to change to uid: %ld",
                    (long) unixd_config.user_id);
	return -1;
    }
#endif
    return 0;
}


AP_DECLARE(const char *) unixd_set_user(cmd_parms *cmd, void *dummy, 
