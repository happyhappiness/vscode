	/* fatal error, bail out */
	return result;
    }

    if ((fd = ap_popenf(r->pool, r->filename, O_RDONLY, 0)) < 0) {
	/* We can't open it, but we were able to stat it. */
	ap_log_error(APLOG_MARK, APLOG_ERR, r->server,
		    MODNAME ": can't read `%s'", r->filename);
	/* let some other handler decide what the problem is */
	return DECLINED;
    }

    /*
     * try looking at the first HOWMANY bytes
     */
    if ((nbytes = read(fd, (char *) buf, sizeof(buf) - 1)) == -1) {
	ap_log_error(APLOG_MARK, APLOG_ERR, r->server,
		    MODNAME ": read failed: %s", r->filename);
	return HTTP_INTERNAL_SERVER_ERROR;
    }

    if (nbytes == 0)
	magic_rsl_puts(r, MIME_TEXT_UNKNOWN);
