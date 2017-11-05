static void test(void)
{
    apr_time_t now;
    apr_int16_t rv;
    long i;
    apr_status_t status;
    int snprintf_res = 0;
#ifdef NOT_ASCII
    apr_size_t inbytes_left, outbytes_left;
#endif

    if (isproxy) {
        connecthost = apr_pstrdup(cntxt, proxyhost);
        connectport = proxyport;
    }
    else {
        connecthost = apr_pstrdup(cntxt, hostname);
        connectport = port;
    }

    if (!use_html) {
        printf("Benchmarking %s ", hostname);
    if (isproxy)
        printf("[through %s:%d] ", proxyhost, proxyport);
    printf("(be patient)%s",
           (heartbeatres ? "\n" : "..."));
    fflush(stdout);
    }

    now = apr_time_now();

    con = calloc(concurrency, sizeof(struct connection));

    stats = calloc(requests, sizeof(struct data));

    if ((status = apr_pollset_create(&readbits, concurrency, cntxt, 0)) != APR_SUCCESS) {
        apr_err("apr_pollset_create failed", status);
    }

    /* setup request */
    if (posting <= 0) {
        snprintf_res = apr_snprintf(request, sizeof(_request),
            "%s %s HTTP/1.0\r\n"
            "User-Agent: ApacheBench/%s\r\n"
            "%s" "%s" "%s"
            "Host: %s%s\r\n"
            "Accept: */*\r\n"
            "%s" "\r\n",
            (posting == 0) ? "GET" : "HEAD",
            (isproxy) ? fullurl : path,
            AP_AB_BASEREVISION,
            keepalive ? "Connection: Keep-Alive\r\n" : "",
            cookie, auth, host_field, colonhost, hdrs);
    }
    else {
        snprintf_res = apr_snprintf(request,  sizeof(_request),
            "POST %s HTTP/1.0\r\n"
            "User-Agent: ApacheBench/%s\r\n"
            "%s" "%s" "%s"
            "Host: %s%s\r\n"
            "Accept: */*\r\n"
            "Content-length: %" APR_SIZE_T_FMT "\r\n"
            "Content-type: %s\r\n"
            "%s"
            "\r\n",
            (isproxy) ? fullurl : path,
            AP_AB_BASEREVISION,
            keepalive ? "Connection: Keep-Alive\r\n" : "",
            cookie, auth,
            host_field, colonhost, postlen,
            (content_type[0]) ? content_type : "text/plain", hdrs);
    }
    if (snprintf_res >= sizeof(_request)) {
        err("Request too long\n");
    }

    if (verbosity >= 2)
        printf("INFO: POST header == \n---\n%s\n---\n", request);

    reqlen = strlen(request);

    /*
     * Combine headers and (optional) post file into one contineous buffer
     */
    if (posting == 1) {
        char *buff = malloc(postlen + reqlen + 1);
        if (!buff) {
            fprintf(stderr, "error creating request buffer: out of memory\n");
            return;
        }
        strcpy(buff, request);
        memcpy(buff + reqlen, postdata, postlen);
        request = buff;
    }

#ifdef NOT_ASCII
    inbytes_left = outbytes_left = reqlen;
    status = apr_xlate_conv_buffer(to_ascii, request, &inbytes_left,
                   request, &outbytes_left);
    if (status || inbytes_left || outbytes_left) {
        fprintf(stderr, "only simple translation is supported (%d/%u/%u)\n",
           status, inbytes_left, outbytes_left);
        exit(1);
    }
#endif              /* NOT_ASCII */

    /* This only needs to be done once */
    if ((rv = apr_sockaddr_info_get(&destsa, connecthost, APR_UNSPEC, connectport, 0, cntxt))
       != APR_SUCCESS) {
        char buf[120];
        apr_snprintf(buf, sizeof(buf),
                 "apr_sockaddr_info_get() for %s", connecthost);
        apr_err(buf, rv);
    }

    /* ok - lets start */
    start = apr_time_now();

    /* initialise lots of requests */
    for (i = 0; i < concurrency; i++) {
        con[i].socknum = i;
        start_connect(&con[i]);
    }

    while (done < requests) {
        apr_int32_t n;
        apr_int32_t timed;
            const apr_pollfd_t *pollresults;

        /* check for time limit expiry */
        now = apr_time_now();
        timed = (apr_int32_t)apr_time_sec(now - start);
        if (tlimit && timed >= tlimit) {
            requests = done;    /* so stats are correct */
            break;      /* no need to do another round */
        }

        n = concurrency;
        status = apr_pollset_poll(readbits, aprtimeout, &n, &pollresults);
        if (status != APR_SUCCESS)
            apr_err("apr_poll", status);

        if (!n) {
            err("\nServer timed out\n\n");
        }

        for (i = 0; i < n; i++) {
            const apr_pollfd_t *next_fd = &(pollresults[i]);
            struct connection *c;

                c = next_fd->client_data;

            /*
             * If the connection isn't connected how can we check it?
             */
            if (c->state == STATE_UNCONNECTED)
                continue;

            rv = next_fd->rtnevents;

#ifdef USE_SSL
            if (c->state == STATE_CONNECTED && c->ssl && SSL_in_init(c->ssl)) {
                ssl_proceed_handshake(c);
                continue;
            }
#endif

            /*
             * Notes: APR_POLLHUP is set after FIN is received on some
             * systems, so treat that like APR_POLLIN so that we try to read
             * again.
             *
             * Some systems return APR_POLLERR with APR_POLLHUP.  We need to
             * call read_connection() for APR_POLLHUP, so check for
             * APR_POLLHUP first so that a closed connection isn't treated
             * like an I/O error.  If it is, we never figure out that the
             * connection is done and we loop here endlessly calling
             * apr_poll().
             */
            if ((rv & APR_POLLIN) || (rv & APR_POLLPRI) || (rv & APR_POLLHUP))
                read_connection(c);
            if ((rv & APR_POLLERR) || (rv & APR_POLLNVAL)) {
                bad++;
                err_except++;
                start_connect(c);
                continue;
            }
            if (rv & APR_POLLOUT) {
                if (c->state == STATE_CONNECTING) {
                    apr_pollfd_t remove_pollfd;
                    rv = apr_socket_connect(c->aprsock, destsa);
                    remove_pollfd.desc_type = APR_POLL_SOCKET;
                    remove_pollfd.desc.s = c->aprsock;
                    apr_pollset_remove(readbits, &remove_pollfd);
                    if (rv != APR_SUCCESS) {
                        apr_socket_close(c->aprsock);
                        err_conn++;
                        if (bad++ > 10) {
                            fprintf(stderr,
                                    "\nTest aborted after 10 failures\n\n");
                            apr_err("apr_socket_connect()", rv);
                        }
                        c->state = STATE_UNCONNECTED;
                        start_connect(c);
                        continue;
                    }
                    else {
                        c->state = STATE_CONNECTED;
                        started++;
#ifdef USE_SSL
                        if (c->ssl)
                            ssl_proceed_handshake(c);
                        else
#endif
                        write_request(c);
                    }
                }
                else {
                    write_request(c);
                }
            }

            /*
             * When using a select based poll every time we check the bits
             * are reset. In 1.3's ab we copied the FD_SET's each time
             * through, but here we're going to check the state and if the
             * connection is in STATE_READ or STATE_CONNECTING we'll add the
             * socket back in as APR_POLLIN.
             */
                if (c->state == STATE_READ) {
                    apr_pollfd_t new_pollfd;
                    new_pollfd.desc_type = APR_POLL_SOCKET;
                    new_pollfd.reqevents = APR_POLLIN;
                    new_pollfd.desc.s = c->aprsock;
                    new_pollfd.client_data = c;
                    apr_pollset_add(readbits, &new_pollfd);
                }
        }
    }

    if (heartbeatres)
        fprintf(stderr, "Finished %ld requests\n", done);
    else
        printf("..done\n");

    if (use_html)
        output_html_results();
    else
        output_results();
}