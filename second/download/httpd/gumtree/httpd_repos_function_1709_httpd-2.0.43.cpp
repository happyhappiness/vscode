pid_t os_fork(const char *user)
{
    pid_t pid;
    char  username[USER_LEN+1];

    switch (os_forktype()) {
      case bs2_FORK:
      case bs2_FORK_RINI:
	pid = fork();
	break;

      case bs2_RFORK_RINI:
	pid = _rfork();
	break;

      case bs2_UFORK:
	apr_cpystrn(username, user, sizeof username);

	/* Make user name all upper case - for some versions of ufork() */
	ap_str_toupper(username);

	pid = ufork(username);
	if (pid == -1 && errno == EPERM) {
	    ap_log_error(APLOG_MARK, APLOG_EMERG, errno,
			 NULL, "ufork: Possible mis-configuration "
			 "for user %s - Aborting.", user);
	    exit(1);
	}
	break;

      default:
	pid = 0;
	break;
    }

    return pid;
}