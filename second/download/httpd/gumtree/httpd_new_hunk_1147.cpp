

    ap_hard_timeout("proxy receive", r);

/* send response */

/* write status line */

    if (!r->assbackwards)

	ap_rvputs(r, "HTTP/1.0 ", r->status_line, CRLF, NULL);

    if (c != NULL && c->fp != NULL

	&& ap_bvputs(c->fp, "HTTP/1.0 ", r->status_line, CRLF, NULL) == -1)

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

/* send body */

    if (!r->header_only) {

	if (parms[0] != 'd') {

/* we need to set this for ap_proxy_send_fb()... */

	    if (c != NULL)

		c->cache_completion = 0;

	    ap_proxy_send_fb(data, r, c);

	} else

	    send_dir(data, r, c, cwd);



	if (rc == 125 || rc == 150)

	    rc = ftp_getrc(f);



	/* XXX: we checked for 125||150||226||250 above. This is redundant. */

	if (rc != 226 && rc != 250)

	    c = ap_proxy_cache_error(c);

    }

    else {

/* abort the transfer */

	ap_bputs("ABOR" CRLF, f);

	ap_bflush(f);

	if (!pasvmode)

	    ap_bclose(data);

	Explain0("FTP: ABOR");

/* responses: 225, 226, 421, 500, 501, 502 */

    /* 225 Data connection open; no transfer in progress. */

    /* 226 Closing data connection. */

    /* 421 Service not available, closing control connection. */

    /* 500 Syntax error, command unrecognized. */

    /* 501 Syntax error in parameters or arguments. */

    /* 502 Command not implemented. */

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

    /* 221 Service closing control connection. */

    /* 500 Syntax error, command unrecognized. */

    i = ftp_getrc(f);

    Explain1("FTP: QUIT: status %d", i);



    if (pasvmode)

	ap_bclose(data);

    ap_bclose(f);



    ap_rflush(r);	/* flush before garbage collection */

++ apache_1.3.2/src/modules/proxy/proxy_http.c	1998-09-01 03:51:59.000000000 +0800

