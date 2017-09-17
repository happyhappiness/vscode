
#ifdef RELAX_HEADER_RULE
	    if (lf)
		*lf = '\0';
#else
	    if (!lf) { /* Huh? Invalid data, I think */
		ap_log_rerror(APLOG_MARK, APLOG_ERR, r,
			    "ISA sent invalid headers: %s", r->filename);
		SetLastError(ERROR);	/* XXX: Find right error */
		return FALSE;
	    }

	    /* Get rid of \n and \r */
