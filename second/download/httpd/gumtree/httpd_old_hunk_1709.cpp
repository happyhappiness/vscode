	if (cfd != -1) {

	    ap_note_cleanups_for_fd(r->pool, cfd);

	    cachefp = ap_bcreate(r->pool, B_RD | B_WR);

	    ap_bpushfd(cachefp, cfd, cfd);

	}

	else if (errno != ENOENT)

	    ap_log_error(APLOG_MARK, APLOG_ERR, r->server,

			 "proxy: error opening cache file %s",

			 c->filename);

#ifdef EXPLAIN

	else

	    Explain1("File %s not found", c->filename);

#endif

    }



    if (cachefp != NULL) {

	i = rdcache(r->pool, cachefp, c);

	if (i == -1)

	    ap_log_error(APLOG_MARK, APLOG_ERR, r->server,

			 "proxy: error reading cache file %s", 

			 c->filename);

	else if (i == 0)

	    ap_log_error(APLOG_MARK, APLOG_ERR|APLOG_NOERRNO, r->server,

			 "proxy: bad (short?) cache file: %s", c->filename);

	if (i != 1) {

	    ap_pclosef(r->pool, cachefp->fd);

	    cachefp = NULL;

	}

    }

/* fixed?  in this case, we want to get the headers from the remote server

   it will be handled later if we don't do this (I hope ;-)

    if (cachefp == NULL)

	c->hdrs = ap_make_array(r->pool, 2, sizeof(struct hdr_entry));

*/

    /* FIXME: Shouldn't we check the URL somewhere? */

    now = time(NULL);

/* Ok, have we got some un-expired data? */

    if (cachefp != NULL && c->expire != BAD_DATE && now < c->expire) {

	Explain0("Unexpired data available");

/* check IMS */

	if (c->lmod != BAD_DATE && c->ims != BAD_DATE && c->ims >= c->lmod) {

/* has the cached file changed since this request? */

	    if (c->date == BAD_DATE || c->date > c->ims) {

/* No, but these header values may have changed, so we send them with the

 * 304 response

 */

		/* CHECKME: surely this was wrong? (Ben)

		   p = table_get(r->headers_in, "Expires");

		 */

		struct hdr_entry *q;



		q = ap_proxy_get_header(c->hdrs, "Expires");

		if (q != NULL && q->value != NULL)

		    ap_table_set(r->headers_out, "Expires", q->value);

	    }

	    ap_pclosef(r->pool, cachefp->fd);

	    Explain0("Use local copy, cached file hasn't changed");

	    return HTTP_NOT_MODIFIED;

	}



