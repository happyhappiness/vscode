    buff[35] = ' ';

    ap_proxy_sec2hex(c->len, buff + 36);

    buff[44] = '\n';

    buff[45] = '\0';



/* if file not modified */

    if (r->status == 304) {

	if (c->ims != BAD_DATE && lmod != BAD_DATE && lmod <= c->ims) {

/* set any changed headers somehow */

/* update dates and version, but not content-length */

	    if (lmod != c->lmod || expc != c->expire || date != c->date) {

		off_t curpos = lseek(c->fp->fd, 0, SEEK_SET);

		if (curpos == -1)

		    ap_log_error(APLOG_MARK, APLOG_ERR, r->server,

				 "proxy: error seeking on cache file %s",

				 c->filename);

		else if (write(c->fp->fd, buff, 35) == -1)

		    ap_log_error(APLOG_MARK, APLOG_ERR, r->server,

				 "proxy: error updating cache file %s",

				 c->filename);

	    }

	    ap_pclosef(r->pool, c->fp->fd);

	    Explain0("Remote document not modified, use local copy");

	    /* CHECKME: Is this right? Shouldn't we check IMS again here? */

