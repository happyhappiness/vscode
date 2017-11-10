static int dav_error_response_tag(request_rec *r,
                                  dav_error *err)
{
    r->status = err->status;

    /* ### I really don't think this is needed; gotta test */
    r->status_line = ap_get_status_line(err->status);

    ap_set_content_type(r, DAV_XML_CONTENT_TYPE);

    ap_rputs(DAV_XML_HEADER DEBUG_CR
             "<D:error xmlns:D=\"DAV:\"", r);

    if (err->desc != NULL) {
        /* ### should move this namespace somewhere (with the others!) */
        ap_rputs(" xmlns:m=\"http://apache.org/dav/xmlns\"", r);
    }

    if (err->namespace != NULL) {
        ap_rprintf(r,
                   " xmlns:C=\"%s\">" DEBUG_CR
                   "<C:%s/>" DEBUG_CR,
                   err->namespace, err->tagname);
    }
    else {
        ap_rprintf(r,
                   ">" DEBUG_CR
                   "<D:%s/>" DEBUG_CR, err->tagname);
    }

    /* here's our mod_dav specific tag: */
    if (err->desc != NULL) {
        ap_rprintf(r,
                   "<m:human-readable errcode=\"%d\">" DEBUG_CR
                   "%s" DEBUG_CR
                   "</m:human-readable>" DEBUG_CR,
                   err->error_id,
                   apr_xml_quote_string(r->pool, err->desc, 0));
    }

    ap_rputs("</D:error>" DEBUG_CR, r);

    /* the response has been sent. */
    /*
     * ### Use of DONE obviates logging..!
     */
    return DONE;
}