		       0,	/* reserved */
		       REG_SZ,	/* type */
		       value,	/* value data */
		       (DWORD) strlen(value) + 1); /* for size of "value" */

    if (rv == ERROR_SUCCESS) {
	ap_log_error(APLOG_MARK,APLOG_INFO,rv,NULL,
	    "Registry stored HKLM\\" REGKEY "\\%s value %s", key, value);
    }

    /* Make sure we close the key even if there was an error storing
     * the data
     */
