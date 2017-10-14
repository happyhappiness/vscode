static int dav_method_checkin(request_rec *r)
{
    dav_resource *resource;
    dav_resource *new_version;
    const dav_hooks_vsn *vsn_hooks = DAV_GET_HOOKS_VSN(r);
    dav_error *err;
    int result;
    apr_xml_doc *doc;
    int keep_checked_out = 0;

    /* If no versioning provider, decline the request */
    if (vsn_hooks == NULL)
        return DECLINED;

    if ((result = ap_xml_parse_input(r, &doc)) != OK)
        return result;

    if (doc != NULL) {
        if (!dav_validate_root(doc, "checkin")) {
            /* This supplies additional information for the default msg. */
            ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r,
                          "The request body, if present, must be a "
                          "DAV:checkin element.");
            return HTTP_BAD_REQUEST;
        }

        keep_checked_out = dav_find_child(doc->root, "keep-checked-out") != NULL;
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

    /* Check the state of the resource: must be a file or collection,
     * must be versioned, and must be checked out.
     */
    if (resource->type != DAV_RESOURCE_TYPE_REGULAR) {
        return dav_error_response(r, HTTP_CONFLICT,
                                  "Cannot checkin this type of resource.");
    }

    if (!resource->versioned) {
        return dav_error_response(r, HTTP_CONFLICT,
                                  "Cannot checkin unversioned resource.");
    }

    if (!resource->working) {
        return dav_error_response(r, HTTP_CONFLICT,
                                  "The resource is not checked out.");
    }

    /* ### do lock checks, once behavior is defined */

    /* Do the checkin */
    if ((err = (*vsn_hooks->checkin)(resource, keep_checked_out, &new_version))
        != NULL) {
        err = dav_push_error(r->pool, HTTP_CONFLICT, 0,
                             apr_psprintf(r->pool,
                                          "Could not CHECKIN resource %s.",
                                          ap_escape_html(r->pool, r->uri)),
                             err);
        return dav_handle_err(r, err, NULL);
    }

    return dav_created(r, new_version->uri, "Version", 0);
}