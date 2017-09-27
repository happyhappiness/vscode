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

