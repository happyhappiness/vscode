static void check_for_d_option_error(const char *msg)
{
	static char rsync263_opts[] = "BCDHIKLPRSTWabceghlnopqrtuvxz";
	char *colon;
	int saw_d = 0;

	if (*msg != 'r'
	 || strncmp(msg, REMOTE_OPTION_ERROR, sizeof REMOTE_OPTION_ERROR - 1) != 0)
		return;

	msg += sizeof REMOTE_OPTION_ERROR - 1;
	if (*msg == '-' || (colon = strchr(msg, ':')) == NULL
	 || strncmp(colon, REMOTE_OPTION_ERROR2, sizeof REMOTE_OPTION_ERROR2 - 1) != 0)
		return;

	for ( ; *msg != ':'; msg++) {
		if (*msg == 'd')
			saw_d = 1;
		else if (*msg == 'e')
			break;
		else if (strchr(rsync263_opts, *msg) == NULL)
			return;
	}

	if (saw_d) {
		rprintf(FWARNING,
		    "*** Try using \"--old-d\" if remote rsync is <= 2.6.3 ***\n");
	}
}