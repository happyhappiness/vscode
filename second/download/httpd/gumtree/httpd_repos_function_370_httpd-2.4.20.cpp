static int dav_method_proppatch(request_rec *r)
{
    dav_error *err;
    dav_resource *resource;
    int result;
    apr_xml_doc *doc;
    apr_xml_elem *child;
    dav_propdb *propdb;
    int failure = 0;
    dav_response resp = { 0 };
    apr_text *propstat_text;
    apr_array_header_t *ctx_list;
    dav_prop_ctx *ctx;
    dav_auto_version_info av_info;

    /* Ask repository module to resolve the resource */
    err = dav_get_resource(r, 0 /* label_allowed */, 0 /* use_checked_in */,
                           &resource);
    if (err != NULL)
        return dav_handle_err(r, err, NULL);
    if (!resource->exists) {
        /* Apache will supply a default error for this. */
        return HTTP_NOT_FOUND;
    }

    if ((result = ap_xml_parse_input(r, &doc)) != OK) {
        return result;
    }
    /* note: doc == NULL if no request body */

    if (doc == NULL || !dav_validate_root(doc, "propertyupdate")) {
        /* This supplies additional information for the default message. */
        ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r, APLOGNO(00587)
                      "The request body does not contain "
                      "a \"propertyupdate\" element.");
        return HTTP_BAD_REQUEST;
    }

    /* Check If-Headers and existing locks */
    /* Note: depth == 0. Implies no need for a multistatus response. */
    if ((err = dav_validate_request(r, resource, 0, NULL, NULL,
                                    DAV_VALIDATE_RESOURCE, NULL)) != NULL) {
        /* ### add a higher-level description? */
        return dav_handle_err(r, err, NULL);
    }

    /* make sure the resource can be modified (if versioning repository) */
    if ((err = dav_auto_checkout(r, resource,
                                 0 /* not parent_only */,
                                 &av_info)) != NULL) {
        /* ### add a higher-level description? */
        return dav_handle_err(r, err, NULL);
    }

    if ((err = dav_open_propdb(r, NULL, resource, 0, doc->namespaces,
                               &propdb)) != NULL) {
        /* undo any auto-checkout */
        dav_auto_checkin(r, resource, 1 /*undo*/, 0 /*unlock*/, &av_info);

        err = dav_push_error(r->pool, HTTP_INTERNAL_SERVER_ERROR, 0,
                             apr_psprintf(r->pool,
                                          "Could not open the property "
                                          "database for %s.",
                                          ap_escape_html(r->pool, r->uri)),
                             err);
        return dav_handle_err(r, err, NULL);
    }
    /* ### what to do about closing the propdb on server failure? */

    /* ### validate "live" properties */

    /* set up an array to hold property operation contexts */
    ctx_list = apr_array_make(r->pool, 10, sizeof(dav_prop_ctx));

    /* do a first pass to ensure that all "remove" properties exist */
    for (child = doc->root->first_child; child; child = child->next) {
        int is_remove;
        apr_xml_elem *prop_group;
        apr_xml_elem *one_prop;

        /* Ignore children that are not set/remove */
        if (child->ns != APR_XML_NS_DAV_ID
            || (!(is_remove = (strcmp(child->name, "remove") == 0))
                && strcmp(child->name, "set") != 0)) {
            continue;
        }

        /* make sure that a "prop" child exists for set/remove */
        if ((prop_group = dav_find_child(child, "prop")) == NULL) {
            dav_close_propdb(propdb);

            /* undo any auto-checkout */
            dav_auto_checkin(r, resource, 1 /*undo*/, 0 /*unlock*/, &av_info);

            /* This supplies additional information for the default message. */
            ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r, APLOGNO(00588)
                          "A \"prop\" element is missing inside "
                          "the propertyupdate command.");
            return HTTP_BAD_REQUEST;
        }

        for (one_prop = prop_group->first_child; one_prop;
             one_prop = one_prop->next) {

            ctx = (dav_prop_ctx *)apr_array_push(ctx_list);
            ctx->prop