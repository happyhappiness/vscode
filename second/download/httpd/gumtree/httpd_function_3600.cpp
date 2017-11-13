static int dav_method_propfind(request_rec *r)
{
    dav_resource *resource;
    int depth;
    dav_error *err;
    int result;
    apr_xml_doc *doc;
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

    if (doc == NULL || dav_find_child(doc->root, "allprop") != NULL) {
        /* note: no request body implies allprop */
        ctx.propfind_type = DAV_PROPFIND_IS_ALLPROP;
    }
    else if (dav_find_child(doc->root, "propname") != NULL) {
        ctx.propfind_type = DAV_PROPFIND_IS_PROPNAME;
    }
    else if (dav_find_child(doc->root, "prop") != NULL) {
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
    ctx.bb = apr_brigade_create(r->pool, r->connection->bucket_alloc);
    apr_pool_create(&ctx.scratchpool, r->pool);

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

    /* send <multistatus> tag, with all doc->namespaces attached.  */

    /* NOTE: we *cannot* leave out the doc's namespaces from the
       initial <multistatus> tag.  if a 404 was generated for an HREF,
       then we need to spit out the doc's namespaces for use by the
       404. Note that <response> elements will override these ns0,
       ns1, etc, but NOT within the <response> scope for the
       badprops. */
    dav_begin_multistatus(ctx.bb, r, HTTP_MULTI_STATUS,
                          doc ? doc->namespaces : NULL);

    /* Have the provider walk the resource. */
    err = (*resource->hooks->walk)(&ctx.w, depth, &multi_status);

    if (ctx.w.lockdb != NULL) {
        (*ctx.w.lockdb->hooks->close_lockdb)(ctx.w.lockdb);
    }

    if (err != NULL) {
        /* If an error occurred during the resource walk, there's
           basically nothing we can do but abort the connection and
           log an error.  This is one of the limitations of HTTP; it
           needs to "know" the entire status of the response before
           generating it, which is just impossible in these streamy
           response situations. */
        err = dav_push_error(r->pool, err->status, 0,
                             "Provider encountered an error while streaming"
                             " a multistatus PROPFIND response.", err);
        dav_log_err(r, err, APLOG_ERR);
        r->connection->aborted = 1;
        return DONE;
    }

    dav_finish_multistatus(r, ctx.bb);

    /* the response has been sent. */
    return DONE;
}