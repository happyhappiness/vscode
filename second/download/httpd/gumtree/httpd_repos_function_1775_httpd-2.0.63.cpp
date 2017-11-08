int os_init_job_environment(server_rec *server, const char *user_name, int one_process)
{
    _rini_struct            inittask; 
    char                    username[USER_LEN+1];
    int                     save_errno;
    bs2_ForkType            type = os_forktype();

    /* We can be sure that no change to uid==0 is possible because of
     * the checks in http_core.c:set_user()
     */

    /* The _rini() function works only after a prior _rfork().
     * In the case of one_process, it would fail.
     */
    if (one_process) {

	type = forktype = bs2_noFORK;

	ap_log_error(APLOG_MARK, APLOG_ERR, 0, server,
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
	ap_log_error(APLOG_MARK, APLOG_ALERT, 0, server,
		     "No BS2000Account configured - cannot switch to User %s",
		     user_name);
	exit(APEXIT_CHILDFATAL);
    }

    apr_cpystrn(username, user_name, sizeof username);

    /* Make user name all upper case */
    ap_str_toupper(username);

    /* Pad to length 8 */
    ap_pad(username, sizeof username, ' ');

    inittask.username       = username;
    inittask.account        = bs2000_account;
    inittask.processor_name = "        ";

    /* Switch to the new logon user (setuid() and setgid() are done later) */
    /* Only the super user can switch identities. */
    if (_rini(&inittask) != 0) {

	ap_log_error(APLOG_MARK, APLOG_ALERT, errno, server,
		     "_rini: BS2000 auth failed for user \"%s\" acct \"%s\"",
		     inittask.username, inittask.account);

	exit(APEXIT_CHILDFATAL);
    }

    return 0;
}