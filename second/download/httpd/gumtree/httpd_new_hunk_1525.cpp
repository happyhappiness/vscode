	}
	if ((timefd = creat(filename, 0666)) == -1) {
	    if (errno != EEXIST)
		ap_log_error(APLOG_MARK, APLOG_ERR, r->server,
			     "proxy: creat(%s)", filename);
	    else
		lastcheck = garbage_now;	/* someone else got in there */
	    ap_unblock_alarms();
	    return;
	}
	close(timefd);
    }
    else {
