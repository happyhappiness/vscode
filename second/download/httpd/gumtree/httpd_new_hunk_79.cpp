    memset (&lcl_data, '\0', sizeof lcl_data);

    /* BS2000 requires the user name to be in upper case for authentication */
    ap_snprintf(lcl_data.username, sizeof lcl_data.username,
		"%s", user_name);
    for (cp = lcl_data.username; *cp; ++cp) {
	*cp = ap_toupper(*cp);
    }

    if (bs2000_authfile == NULL) {
	ap_log_error(APLOG_MARK, APLOG_ALERT|APLOG_NOERRNO, server,
		     "Use the 'BS2000AuthFile <passwdfile>' directive to specify "
		     "an authorization file for User %s",
