static int dav_method_propfind(request_rec *r)
{
    dav_resource *resource;
    int depth;
    dav_error *err;
    int result;
    apr_xml_doc *doc;
    const apr_xml_elem *child;
    dav_walker_ctx ctx = { { 0 } };
    dav_response *multi_status;

    /* Ask repository module to resolve the resource */
    err = dav_get_resource(r, 1 /* label_allowed */, 0 /* use_checked_in */,
                           &resource);
    if (err != NULL)
        return dav_handle_err(r, err, NULL);

    if (dav_get_resource_state(r, resource) == DAV_RESOURCE_NULL) {
        /* Apache will supply a default error for this. */
        return HTTP_NOT_FOUND;
    }

    if ((depth = dav_get_depth(r, DAV_INFINITY)) < 0) {
        /* dav_get_depth() supplies additional information for the
         * default message. */
        return HTTP_BAD_REQUEST;
    }

    if (depth == DAV_INFINITY && resource->collection) {
        dav_dir_conf *conf;
        conf = (dav_dir_conf *)ap_get_module_config(r->per_dir_config,
                                                    &dav_module);
        /* default is to DISALLOW these requests */
        if (conf->allow_depthinfinity != DAV_ENABLED_ON) {
            return dav_error_response(r, HTTP_FORBIDDEN,
                                      apr_psprintf(r->pool,
                                                   "PROPFIND requests with a "
                                                   "Depth of \"infinity\" are "
                                                   "not allowed for %s.",
                                                   ap_escape_html(r->pool,
                                                                  r->uri)));
        }
    }

    if ((result = ap_xml_parse_input(r, &doc)) != OK) {
        return result;
    }
    /* note: doc == NULL if no request body */

    if (doc && !dav_validate_root(doc, "propfind")) {
        /* This supplies additional information for the default message. */
        ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r,
                      "The \"propfind\" element was not found.");
        return HTTP_BAD_REQUEST;
    }

    /* ### validate that only one of these three elements is present */

    if (doc == NULL
        || (child = dav_find_child(doc->root, "allprop")) != NULL) {
        /* note: no request body implies allprop */
        ctx.propfind_type = DAV_PROPFIND_IS_ALLPROP;
    }
    else if ((child = dav_find_child(doc->root, "propname")) != NULL) {
        ctx.propfind_type = DAV_PROPFIND_IS_PROPNAME;
    }
    else if ((child = dav_find_child(doc->root, "prop")) != NULL) {
        ctx.propfind_type = DAV_PROPFIND_IS_PROP;
    }
    else {
        /* "propfind" element must have one of the above three children */

        /* This supplies additional information for the default message. */
        ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r,
                      "The \"propfind\" element does not contain one of "
                      "the required child elements (the specific command).");
        return HTTP_BAD_REQUEST;
    }

    ctx.w.walk_type = DAV_WALKTYPE_NORMAL | DAV_WALKTYPE_AUTH;
    ctx.w.func = dav_propfind_walker;
    ctx.w.walk_ctx = &ctx;
    ctx.w.pool = r->pool;
    ctx.w.root = resource;

    ctx.doc = doc;
    ctx.r = r;

    /* ### should open read-only */
    if ((err = dav_open_lockdb(r, 0, &ctx.w.lockdb)) != NULL) {
        err = dav_push_error(r->pool, err->status, 0,
                             "The lock database could not be opened, "
                             "preventing access to the various lock "
                             "properties for the PROPFIND.",
                             err);
        return dav_handle_err(r, err, NULL);
    }
    if (ctx.w.lockdb != NULL) {
        /* if we have a lock database, then we can walk locknull resources */
        ctx.w.walk_type |= DAV_WALKTYPE_LOCKNULL;
    }

    err = (*resource->hooks->walk)(&ctx.w, depth, &multi_status);

    if (ctx.w.lockdb != NULL) {
        (*ctx.w.lockdb->hooks->close_lockdb)(ctx.w.lockdb);
    }

    if (err != NULL) {
        /* ### add a highe