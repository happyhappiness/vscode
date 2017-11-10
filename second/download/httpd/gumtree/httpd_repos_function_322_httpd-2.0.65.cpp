static int dav_method_vsn_control(request_rec *r)
{
    dav_resource *resource;
    int resource_state;
    dav_auto_version_info av_info;
    const dav_hooks_locks *locks_hooks = DAV_GET_HOOKS_LOCKS(r);
    const dav_hooks_vsn *vsn_hooks = DAV_GET_HOOKS_VSN(r);
    dav_error *err;
    apr_xml_doc *doc;
    const char *target = NULL;
    int result;

    /* if no versioning provider, decline the request */
    if (vsn_hooks == NULL)
        return DECLINED;

    /* ask repository module to resolve the resource */
    err = dav_get_resource(r, 0 /* label_allowed */, 0 /* use_checked_in */,
                           &resource);
    if (err != NULL)
        return dav_handle_err(r, err, NULL);

    /* remember the pre-creation resource state */
    resource_state = dav_get_resource_state(r, resource);

    /* parse the request body (may be a version-control element) */
    if ((result = ap_xml_parse_input(r, &doc)) != OK) {
        return result;
    }
    /* note: doc == NULL if no request body */

    if (doc != NULL) {
        const apr_xml_elem *child;
        apr_size_t tsize;

        if (!dav_validate_root(doc, "version-control")) {
            ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r,
                          "The request body does not contain "
                          "a \"version-control\" element.");
            return HTTP_BAD_REQUEST;
        }

        /* get the version URI */
        if ((child = dav_find_child(doc->root, "version")) == NULL) {
            ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r,
                          "The \"version-control\" element does not contain "
                          "a \"version\" element.");
            return HTTP_BAD_REQUEST;
        }

        if ((child = dav_find_child(child, "href")) == NULL) {
            ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r,
                          "The \"version\" element does not contain "
                          "an \"href\" element.");
            return HTTP_BAD_REQUEST;
        }

        /* get version URI */
        apr_xml_to_text(r->pool, child, APR_XML_X2T_INNER, NULL, NULL,
                        &target, &tsize);
        if (tsize == 0) {
            ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r,
                          "An \"href\" element does not contain a URI.");
            return HTTP_BAD_REQUEST;
        }
    }

    /* Check request preconditions */

    /* ### need a general mechanism for reporting precondition violations
     * ### (should be returning XML document for 403/409 responses)
     */

    /* if not versioning existing resource, must specify version to select */
    if (!resource->exists && target == NULL) {
        err = dav_new_error(r->pool, HTTP_CONFLICT, 0,
                            "<DAV:initial-version-required/>");
        return dav_handle_err(r, err, NULL);
    }
    else if (resource->exists) {
        /* cannot add resource to existing version history */
        if (target != NULL) {
            err = dav_new_error(r->pool, HTTP_CONFLICT, 0,
                                "<DAV:cannot-add-to-existing-history/>");
            return dav_handle_err(r, err, NULL);
        }

        /* resource must be unversioned and versionable, or version selector */
        if (resource->type != DAV_RESOURCE_TYPE_REGULAR
            || (!resource->versioned && !(vsn_hooks->versionable)(resource))) {
            err = dav_new_error(r->pool, HTTP_CONFLICT, 0,
                                "<DAV:must-be-versionable/>");
            return dav_handle_err(r, err, NULL);
        }

        /* the DeltaV spec says if resource is a version selector,
         * then VERSION-CONTROL is a no-op
         */
        if (resource->versioned) {
            /* set the Cache-Control header, per the spec */
            apr_table_setn(r->headers_out, "Cache-Control", "no-cache");

            /* no body */
            ap_set_content_length(r, 0);

            return DONE;
        }
    }

    /* Check If-Headers and existing locks */
    /* Note: depth == 0. Implies no need for a multistatus response. */
    if ((err = 