static int dav_method_label(request_rec *r)
{
    dav_resource *resource;
    const dav_hooks_vsn *vsn_hooks = DAV_GET_HOOKS_VSN(r);
    apr_xml_doc *doc;
    apr_xml_elem *child;
    int depth;
    int result;
    apr_size_t tsize;
    dav_error *err;
    dav_label_walker_ctx ctx = { { 0 } };
    dav_response *multi_status;

    /* If no versioning provider, or the provider doesn't support
     * labels, decline the request */
    if (vsn_hooks == NULL || vsn_hooks->add_label == NULL)
        return DECLINED;

    /* Ask repository module to resolve the resource */
    err = dav_get_resource(r, 1 /* label_allowed */, 0 /* use_checked_in */,
                           &resource);
    if (err != NULL)
        return dav_handle_err(r, err, NULL);
    if (!resource->exists) {
        /* Apache will supply a default error for this. */
        return HTTP_NOT_FOUND;
    }

    if ((depth = dav_get_depth(r, 0)) < 0) {
        /* dav_get_depth() supplies additional information for the
         * default message. */
        return HTTP_BAD_REQUEST;
    }

    /* parse the request body */
    if ((result = ap_xml_parse_input(r, &doc)) != OK) {
        return result;
    }

    if (doc == NULL || !dav_validate_root(doc, "label")) {
        /* This supplies additional information for the default message. */
        ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r,
                      "The request body does not contain "
                      "a \"label\" element.");
        return HTTP_BAD_REQUEST;
    }

    /* check for add, set, or remove element */
    if ((child = dav_find_child(doc->root, "add")) != NULL) {
        ctx.label_op = DAV_LABEL_ADD;
    }
    else if ((child = dav_find_child(doc->root, "set")) != NULL) {
        ctx.label_op = DAV_LABEL_SET;
    }
    else if ((child = dav_find_child(doc->root, "remove")) != NULL) {
        ctx.label_op = DAV_LABEL_REMOVE;
    }
    else {
        ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r,
                      "The \"label\" element does not contain "
                      "an \"add\", \"set\", or \"remove\" element.");
        return HTTP_BAD_REQUEST;
    }

    /* get the label string */
    if ((child = dav_find_child(child, "label-name")) == NULL) {
        ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r,
                      "The label command element does not contain "
                      "a \"label-name\" element.");
        return HTTP_BAD_REQUEST;
    }

    apr_xml_to_text(r->pool, child, APR_XML_X2T_INNER, NULL, NULL,
                    &ctx.label, &tsize);
    if (tsize == 0) {
        ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r,
                      "A \"label-name\" element does not contain "
                      "a label name.");
        return HTTP_BAD_REQUEST;
    }

    /* do the label operation walk */
    ctx.w.walk_type = DAV_WALKTYPE_NORMAL;
    ctx.w.func = dav_label_walker;
    ctx.w.walk_ctx = &ctx;
    ctx.w.pool = r->pool;
    ctx.w.root = resource;
    ctx.vsn_hooks = vsn_hooks;

    err = (*resource->hooks->walk)(&ctx.w, depth, &multi_status);

    if (err != NULL) {
        /* some sort of error occurred which terminated the walk */
        err = dav_push_error(r->pool, err->status, 0,
                             "The LABEL operation was terminated prematurely.",
                             err);
        return dav_handle_err(r, err, multi_status);
    }

    if (multi_status != NULL) {
        /* One or more resources had errors. If depth was zero, convert
         * response to simple error, else make sure there is an
         * overall error to pass to dav_handle_err()
         */
        if (depth == 0) {
            err = dav_new_error(r->pool, multi_status->status, 0, 0,
                                multi_status->desc);
            multi_status = NULL;
        }
        else {
            err = dav_new_error(r->pool, HTTP_MULTI_STATUS, 0, 0,
                                "Errors occurred during the LABEL operation.");
        }

        return dav_handle_err(r, err, multi_status);
    }

    /* set the Cache-Control header, per the spec */
    apr_table_setn(r->headers_out, "Cache-Control", "no-cache");

    /* no body */
    ap_set_content_length(r, 0);

    return DONE;
}