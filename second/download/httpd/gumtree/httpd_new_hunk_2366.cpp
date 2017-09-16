    i = ap_proxy_cache_update(c, resp_hdrs, !backasswards, nocache);

    if (i != DECLINED) {

	ap_bclose(f);

	return i;

    }



    ap_hard_timeout("proxy receive", r);



/* write status line */

    if (!r->assbackwards)

	ap_rvputs(r, "HTTP/1.0 ", r->status_line, CRLF, NULL);

    if (c != NULL && c->fp != NULL &&

	ap_bvputs(c->fp, "HTTP/1.0 ", r->status_line, CRLF, NULL) == -1)

	c = ap_proxy_cache_error(c);



/* send headers */

    tdo.req = r;

    tdo.cache = c;

    ap_table_do(ap_proxy_send_hdr_line, &tdo, resp_hdrs, NULL);



    if (!r->assbackwards)

	ap_rputs(CRLF, r);

    if (c != NULL && c->fp != NULL && ap_bputs(CRLF, c->fp) == -1)

	c = ap_proxy_cache_error(c);



    ap_bsetopt(r->connection->client, BO_BYTECT, &zero);

    r->sent_bodyct = 1;

/* Is it an HTTP/0.9 respose? If so, send the extra data */

    if (backasswards) {

	ap_bwrite(r->connection->client, buffer, len);

	if (c != NULL && c->fp != NULL && ap_bwrite(c->fp, buffer, len) != len)

	    c = ap_proxy_cache_error(c);

    }

    ap_kill_timeout(r);



#ifdef CHARSET_EBCDIC

    /* What we read/write after the header should not be modified

     * (i.e., the cache copy is ASCII, not EBCDIC, even for text/html)

