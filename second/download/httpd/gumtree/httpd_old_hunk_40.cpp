
    /* ### I really don't think this is needed; gotta test */
    r->status_line = ap_get_status_line(err->status);

    ap_set_content_type(r, DAV_XML_CONTENT_TYPE);

    /* since we're returning DONE, ensure the request body is consumed. */
    (void) ap_discard_request_body(r);

    ap_rputs(DAV_XML_HEADER DEBUG_CR
             "<D:error xmlns:D=\"DAV:\"", r);

    if (err->desc != NULL) {
        /* ### should move this namespace somewhere (with the others!) */
        ap_rputs(" xmlns:m=\"http://apache.org/dav/xmlns\"", r);
