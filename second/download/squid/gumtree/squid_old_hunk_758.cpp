    hp->hdr_start = hp->req.end + 1;

    /* Enforce max_request_size */
    if (req_sz >= Config.maxRequestHeaderSize) {
        debugs(33, 5, "parseHttpRequest: Too large request");
        hp->request_parse_status = Http::scHeaderTooLarge;
        return parseHttpRequestAbort(csd, "error:request-too-large");
    }

    /* Set method_p */
    *method_p = HttpRequestMethod(&hp->buf[hp->req.m_start], &hp->buf[hp->req.m_end]+1);

    /* deny CONNECT via accelerated ports */
    if (*method_p == Http::METHOD_CONNECT && csd->port && csd->port->flags.accelSurrogate) {
        debugs(33, DBG_IMPORTANT, "WARNING: CONNECT method received on " << csd->port->protocol << " Accelerator port " << csd->port->s.port() );
        /* XXX need a way to say "this many character length string" */
        debugs(33, DBG_IMPORTANT, "WARNING: for request: " << hp->buf);
        hp->request_parse_status = Http::scMethodNotAllowed;
        return parseHttpRequestAbort(csd, "error:method-not-allowed");
    }

    if (*method_p == Http::METHOD_NONE) {
        /* XXX need a way to say "this many character length string" */
        debugs(33, DBG_IMPORTANT, "clientParseRequestMethod: Unsupported method in request '" << hp->buf << "'");
        hp->request_parse_status = Http::scMethodNotAllowed;
        return parseHttpRequestAbort(csd, "error:unsupported-request-method");
    }

    /*
     * Process headers after request line
     * TODO: Use httpRequestParse here.
     */
