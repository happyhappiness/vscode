		       0,	     /* reserved */
		       REG_MULTI_SZ, /* type */
		       buf,	     /* value data */
		       (DWORD) bufsize); /* for size of "value" */

    if (rv == ERROR_SUCCESS) {
	ap_log_error(APLOG_MARK,APLOG_INFO|APLOG_NOERRNO,rv,NULL,
	    "Registry stored HKLM\\" REGKEY "\\%s", key);
    }

    /* Make sure we close the key even if there was an error storing
     * the data
     */
