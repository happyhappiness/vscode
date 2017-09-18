     * In the case of one_process, it would fail.
     */
    if (one_process) {

	type = forktype = bs2_noFORK;

	ap_log_error(APLOG_MARK, APLOG_ERR|APLOG_NOERRNO, 0, server,
		     "The debug mode of Apache should only "
		     "be started by an unprivileged user!");
	return 0;
    }

    /* If no _rini() is required, then return quickly. */
    if (type != bs2_RFORK_RINI && type != bs2_FORK_RINI)
	return 0;

    /* An Account is required for _rini() */
    if (bs2000_account == NULL)
    {
	ap_log_error(APLOG_MARK, APLOG_ALERT|APLOG_NOERRNO, 0, server,
		     "No BS2000Account configured - cannot switch to User %s",
		     user_name);
	exit(APEXIT_CHILDFATAL);
    }

    apr_cpystrn(username, user_name, sizeof username);
