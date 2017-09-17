	     * how libraries and such are going to fail.  If we can't
	     * do this F_DUPFD there's a good chance that apache has too
	     * few descriptors available to it.  Note we don't warn on
	     * the high line, because if it fails we'll eventually try
	     * the low line...
	     */
	    ap_log_error(APLOG_MARK, APLOG_ERR, NULL,
		        "unable to open a file descriptor above %u, "
			"you may need to increase the number of descriptors",
			LOW_SLACK_LINE);
	    low_warned = 1;
	}
	return fd;
