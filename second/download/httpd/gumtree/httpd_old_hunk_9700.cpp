
    ap_hard_timeout("proxy receive", r);
/* send response */
/* write status line */
    if (!r->assbackwards)
	ap_rvputs(r, "HTTP/1.0 ", r->status_line, CRLF, NULL);
    if (cache != NULL)
	if (ap_bvputs(cache, "HTTP/1.0 ", r->status_line, CRLF,
		   NULL) == -1)
	    cache = ap_proxy_cache_error(c);

/* send headers */
    len = resp_hdrs->nelts;
    hdr = (struct hdr_entry *) resp_hdrs->elts;
    for (i = 0; i < len; i++) {
	if (hdr[i].field == NULL || hdr[i].value == NULL ||
	    hdr[i].value[0] == '\0')
	    continue;
	if (!r->assbackwards)
	    ap_rvputs(r, hdr[i].field, ": ", hdr[i].value, CRLF, NULL);
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
/* send body */
    if (!r->header_only) {
	if (parms[0] != 'd') {
/* we need to set this for ap_proxy_send_fb()... */
	    c->cache_completion = 0;
	    ap_proxy_send_fb(data, r, cache, c);
	} else
	    send_dir(data, r, cache, c, url);

	if (rc == 125 || rc == 150)
	    rc = ftp_getrc(f);
	if (rc != 226 && rc != 250)
	    ap_proxy_cache_error(c);
    }
    else {
/* abort the transfer */
	ap_bputs("ABOR" CRLF, f);
	ap_bflush(f);
	if (!pasvmode)
	    ap_bclose(data);
	Explain0("FTP: ABOR");
/* responses: 225, 226, 421, 500, 501, 502 */
	i = ftp_getrc(f);
	Explain1("FTP: returned status %d", i);
    }

    ap_kill_timeout(r);
    ap_proxy_cache_tidy(c);

/* finish */
    ap_bputs("QUIT" CRLF, f);
    ap_bflush(f);
    Explain0("FTP: QUIT");
/* responses: 221, 500 */

    if (pasvmode)
	ap_bclose(data);
    ap_bclose(f);

    ap_rflush(r);	/* flush before garbage collection */
-- apache_1.3.1/src/modules/proxy/proxy_http.c	1998-07-10 03:45:56.000000000 +0800
