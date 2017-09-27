        return DECLINED;

    if ((result = ap_xml_parse_input(r, &doc)) != OK)
        return result;
    if (doc == NULL) {
        /* This supplies additional information for the default msg. */
        ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r, APLOGNO(00614)
                      "The request body must specify a report.");
        return HTTP_BAD_REQUEST;
    }

    /* Ask repository module to resolve the resource.
     * First determine whether a Target-Selector header is allowed
