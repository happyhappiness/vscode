    if ( hp->bufsiz <= 0) {
        debugs(33, 5, "Incomplete request, waiting for end of request line");
        return NULL;
    } else if ( (size_t)hp->bufsiz >= Config.maxRequestHeaderSize && headersEnd(hp->buf, Config.maxRequestHeaderSize) == 0) {
        debugs(33, 5, "parseHttpRequest: Too large request");
        hp->request_parse_status = Http::scHeaderTooLarge;
        return csd->abortRequestParsing("error:request-too-large");
    }

    /* Attempt to parse the first line; this'll define the method, url, version and header begin */
    r = HttpParserParseReqLine(hp);

    if (r == 0) {
        debugs(33, 5, "Incomplete request, waiting for end of request line");
        return NULL;
    }

    if (r == -1) {
        return csd->abortRequestParsing("error:invalid-request");
    }

    /* Request line is valid here .. */
    *http_ver = Http::ProtocolVersion(hp->req.v_maj, hp->req.v_min);

    /* This call scans the entire request, not just the headers */
