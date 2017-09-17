     * waiting for free_proc_chain to cleanup in the middle of an
     * SSI request -djg
     */
    if (!ap_bspawn_child(r->main ? r->main->pool : r->pool, cgi_child,
			 (void *) &cld, kill_after_timeout,
			 &script_out, &script_in, &script_err)) {
	ap_log_error(APLOG_MARK, APLOG_ERR, r->server,
		    "couldn't spawn child process: %s", r->filename);
	return SERVER_ERROR;
    }

    /* Transfer any put/post args, CERN style...
     * Note that if a buggy script fails to read everything we throw
     * at it, or a buggy client sends too much, we get a SIGPIPE, so
     * we have to ignore SIGPIPE while doing this.  CERN does the same
-- apache_1.3.1/src/modules/standard/mod_digest.c	1998-07-09 01:47:14.000000000 +0800
