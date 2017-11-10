static int dav_method_update(request_rec *r)
{
    dav_resource *resource;
    dav_resource *version = NULL;
    const dav_hooks_vsn *vsn_hooks = DAV_GET_HOOKS_VSN(r);
    apr_xml_doc *doc;
    apr_xml_elem *child;
    int is_label = 0;
    int depth;
    int result;
    apr_size_t tsize;
    const char *target;
    dav_response *multi_response;
    dav_error *err;
    dav_lookup_result lookup;

    /* If no versioning provider, or UPDATE not supported,
     * decline the request */
    if (vsn_hooks == NULL || vsn_hooks->update == NULL)
        return DECLINED;

    if ((depth = dav_get_depth(r, 0)) < 0) {
        /* dav_get_depth() supplies additional information for the
         * default message. */
        return HTTP_BAD_REQUEST;
    }

    /* parse the request body */
    if ((result = ap_xml_parse_input(r, &doc)) != OK) {
        return result;
    }

    if (doc == NULL || !dav_validate_root(doc, "update")) {
        /* This supplies additional information for the default message. */
        ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r, APLOGNO(00604)
                      "The request body does not contain "
                      "an \"update\" element.");
        return HTTP_BAD_REQUEST;
    }

    /* check for label-name or version element, but not both */
    if ((child = dav_find_child(doc->root, "label-name")) != NULL)
        is_label = 1;
    else if ((child = dav_find_child(doc->root, "version")) != NULL) {
        /* get the href element */
        if ((child = dav_find_child(child, "href")) == NULL) {
            ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r, APLOGNO(00605)
                          "The version element does not contain "
                          "an \"href\" element.");
            return HTTP_BAD_REQUEST;
        }
    }
    else {
        ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r, APLOGNO(00606)
                      "The \"update\" element does not contain "
                      "a \"label-name\" or \"version\" element.");
        return HTTP_BAD_REQUEST;
    }

    /* a depth greater than zero is only allowed for a label */
    if (!is_label && depth != 0) {
        ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r, APLOGNO(00607)
                      "Depth must be zero for UPDATE with a version");
        return HTTP_BAD_REQUEST;
    }

    /* get the target value (a label or a version URI) */
    apr_xml_to_text(r->pool, child, APR_XML_X2T_INNER, NULL, NULL,
                    &target, &tsize);
    if (tsize == 0) {
        ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r, APLOGNO(00608)
                      "A \"label-name\" or \"href\" element does not contain "
                      "any content.");
        return HTTP_BAD_REQUEST;
    }

    /* Ask repository module to resolve the resource */
    err = dav_get_resource(r, 0 /* label_allowed */, 0 /* use_checked_in */,
                           &resource);
    if (err != NULL)
        return dav_handle_err(r, err, NULL);

    if (!resource->exists) {
        /* Apache will supply a default error for this. */
        return HTTP_NOT_FOUND;
    }

    /* ### need a general mechanism for reporting precondition violations
     * ### (should be returning XML document for 403/409 responses)
     */
    if (resource->type != DAV_RESOURCE_TYPE_REGULAR
        || !resource->versioned || resource->working) {
        return dav_error_response(r, HTTP_CONFLICT,
                                  "<DAV:must-be-checked-in-version-controlled-resource>");
    }

    /* if target is a version, resolve the version resource */
    /* ### dav_lookup_uri only allows absolute URIs; is that OK? */
    if (!is_label) {
        lookup = dav_lookup_uri(target, r, 0 /* must_be_absolute */);
        if (lookup.rnew == NULL) {
            if (lookup.err.status == HTTP_BAD_REQUEST) {
                /* This supplies additional information for the default message. */
                ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r, APLOGNO(00609)
                              "%s", lookup.err.desc);
                return HTTP_BAD_REQUEST;
            }

            /* ### this