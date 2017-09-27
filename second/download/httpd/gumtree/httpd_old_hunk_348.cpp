    char pwin[MAX_STRING_LEN];
    char pwv[MAX_STRING_LEN];
    unsigned int i;
    apr_size_t len = sizeof(pwin);

    if (apr_password_get("New password: ", pwin, &len) != APR_SUCCESS) {
	fprintf(stderr, "password too long");
	exit(5);
    }
    len = sizeof(pwin);
    apr_password_get("Re-type new password: ", pwv, &len);
    if (strcmp(pwin, pwv) != 0) {
	fprintf(stderr, "They don't match, sorry.\n");
	if (tfp) {
	    apr_file_close(tfp);
	}
	exit(1);
    }
    pw = pwin;
    apr_file_printf(f, "%s:%s:", user, realm);

    /* Do MD5 stuff */
    sprintf(string, "%s:%s:%s", user, realm, pw);
