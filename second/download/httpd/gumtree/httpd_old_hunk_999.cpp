     * If the requests aren't pipelined, then the client is still waiting

     * for the final buffer flush from us, and we will block in the implicit

     * read().  B_SAFEREAD ensures that the BUFF layer flushes if it will

     * have to block during a read.

     */

    ap_bsetflag(conn->client, B_SAFEREAD, 1);

    while ((len = getline(l, HUGE_STRING_LEN, conn->client, 0)) <= 0) {

        if ((len < 0) || ap_bgetflag(conn->client, B_EOF)) {

            ap_bsetflag(conn->client, B_SAFEREAD, 0);

            return 0;

        }

    }

    /* we've probably got something to do, ignore graceful restart requests */

#ifdef SIGUSR1

    signal(SIGUSR1, SIG_IGN);

#endif                          /* SIGUSR1 */

    ap_bsetflag(conn->client, B_SAFEREAD, 0);

    if (len == (HUGE_STRING_LEN - 1)) {

        ap_log_error(APLOG_MARK, APLOG_NOERRNO|APLOG_ERR, r->server,

                    "request failed for %s, reason: URI too long",

            ap_get_remote_host(r->connection, r->per_dir_config, REMOTE_NAME));

	/* hack to deal with the HTTP_REQUEST_TIME_OUT setting up above: */

	if (r->status == HTTP_REQUEST_TIME_OUT) {

	    r->status = HTTP_OK;

	}

	r->request_time = time(NULL);

	ap_die (HTTP_REQUEST_URI_TOO_LARGE, r);

        return 0;

    }



    r->request_time = time(NULL);

    r->the_request = ap_pstrdup(r->pool, l);

    r->method = ap_getword_white(r->pool, &ll);

    uri = ap_getword_white(r->pool, &ll);



