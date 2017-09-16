     * If the requests aren't pipelined, then the client is still waiting

     * for the final buffer flush from us, and we will block in the implicit

     * read().  B_SAFEREAD ensures that the BUFF layer flushes if it will

     * have to block during a read.

     */

    ap_bsetflag(conn->client, B_SAFEREAD, 1);

    while ((len = getline(l, sizeof(l), conn->client, 0)) <= 0) {

        if ((len < 0) || ap_bgetflag(conn->client, B_EOF)) {

            ap_bsetflag(conn->client, B_SAFEREAD, 0);

            return 0;

        }

    }

    /* we've probably got something to do, ignore graceful restart requests */

#ifdef SIGUSR1

    signal(SIGUSR1, SIG_IGN);

#endif



    ap_bsetflag(conn->client, B_SAFEREAD, 0);



    r->request_time = time(NULL);

    r->the_request = ap_pstrdup(r->pool, l);

    r->method = ap_getword_white(r->pool, &ll);

    uri = ap_getword_white(r->pool, &ll);



