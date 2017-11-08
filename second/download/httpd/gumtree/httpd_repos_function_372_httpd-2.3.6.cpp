static int dav_method_report(request_rec *r)
{
    dav_resource *resource;
    const dav_hooks_vsn *vsn_hooks = DAV_GET_HOOKS_VSN(r);
    int result;
    int label_allowed;
    apr_xml_doc *doc;
    dav_error *err;

    /* If no versioning provider, decline the request */
    if (vsn_hooks == NULL)
        return DECLINED;

    if ((result = ap_xml_parse_input(r, &doc)) != OK)
        return result;
    if (doc == NULL) {
        /* This supplies additional information for the default msg. */
        ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r,
                      "The request body must specify a report.");
        return HTTP_BAD_REQUEST;
    }

    /* Ask repository module to resolve the resource.
     * First determine whether a Target-Selector header is allowed
     * for this report.
     */
    label_allowed = (*vsn_hooks->report_label_header_allowed)(doc);
    err = dav_get_resource(r, label_allowed, 0 /* use_checked_in */,
                           &resource);
    if (err != NULL)
        return dav_handle_err(r, err, NULL);

    if (!resource->exists) {
        /* Apache will supply a default error for this. */
        return HTTP_NOT_FOUND;
    }

    /* set up defaults for the report response */
    r->status = HTTP_OK;
    ap_set_content_type(r, DAV_XML_CONTENT_TYPE);

    /* run report hook */
    if ((err = (*vsn_hooks->deliver_report)(r, resource, doc,
                                            r->output_filters)) != NULL) {
        if (! r->sent_bodyct)
          /* No data has been sent to client yet;  throw normal error. */
          return dav_handle_err(r, err, NULL);

        /* If an error occurred during the report delivery, there's
           basically nothing we can do but abort the connection and
           log an error.  This is one of the limitations of HTTP; it
           needs to "know" the entire status of the response before
           generating it, which is just impossible in these streamy
           response situations. */
        err = dav_push_error(r->pool, err->status, 0,
                             "Provider encountered an error while streaming"
                             " a REPORT response.", err);
        dav_log_err(r, err, APLOG_ERR);
        r->connection->aborted = 1;
        return DONE;
    }

    return DONE;
}