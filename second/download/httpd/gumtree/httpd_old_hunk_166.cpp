    i = ap_proxy_cache_update(c, resp_hdrs, !backasswards, nocache);
    if (i != DECLINED) {
	ap_bclose(f);
	return i;
    }

    cache = c->fp;

    ap_hard_timeout("proxy receive", r);

/* write status line */
    if (!r->assbackwards)
	ap_rvputs(r, "HTTP/1.0 ", r->status_line, CRLF, NULL);
    if (cache != NULL)
	if (ap_bvputs(cache, "HTTP/1.0 ", r->status_line, CRLF, NULL) == -1)
	    cache = ap_proxy_cache_error(c);

/* send headers */
    for (i = 0; i < resp_hdrs->nelts; i++) {
	if (hdr[i].field == NULL || hdr[i].value == NULL ||
	    hdr[i].value[0] == '\0')
	    continue;
	if (!r->assbackwards) {
	    ap_rvputs(r, hdr[i].field, ": ", hdr[i].value, CRLF, NULL);
	    ap_table_set(r->headers_out, hdr[i].field, hdr[i].value);
	}
	if (cache != NULL)
	    if (ap_bvputs(cache, hdr[i].field, ": ", hdr[i].value, CRLF,
		       NULL) == -1)
		cache = ap_proxy_cache_error(c);
    }

    if (!r->assbackwards)
	ap_rputs(CRLF, r);
    if (cache != NULL)
	if (ap_bputs(CRLF, cache) == -1)
	    cache = ap_proxy_cache_error(c);

    ap_bsetopt(r->connection->client, BO_BYTECT, &zero);
    r->sent_bodyct = 1;
/* Is it an HTTP/0.9 respose? If so, send the extra data */
    if (backasswards) {
	ap_bwrite(r->connection->client, buffer, len);
	if (cache != NULL)
	    if (ap_bwrite(f, buffer, len) != len)
		cache = ap_proxy_cache_error(c);
    }
    ap_kill_timeout(r);

#ifdef CHARSET_EBCDIC
    /* What we read/write after the header should not be modified
     * (i.e., the cache copy is ASCII, not EBCDIC, even for text/html)
