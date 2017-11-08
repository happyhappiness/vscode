static int dav_method_uncheckout(request_rec *r)
{
    dav_resource *resource;
    const dav_hooks_vsn *vsn_hooks = DAV_GET_HOOKS_VSN(r);
    dav_error *err;
    int result;

    /* If no versioning provider, decline the request */
    if (vsn_hooks == NULL)
        return DECLINED;

    if ((result = ap_discard_request_body(r)) != OK) {
        return result;
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
                                  "Cannot uncheckout this type of resource.");
    }

    if (!resource->versioned) {
        return dav_error_response(r, HTTP_CONFLICT,
                                  "Cannot uncheckout unversioned resource.");
    }

    if (!resource->working) {
        return dav_error_response(r, HTTP_CONFLICT,
                                  "The resource is not checked out to the workspace.");
    }

    /* ### do lock checks, once behavior is defined */

    /* Do the uncheckout */
    if ((err = (*vsn_hooks->uncheckout)(resource)) != NULL) {
        err = dav_push_error(r->pool, HTTP_CONFLICT, 0,
                             apr_psprintf(r->pool,
                                          "Could not UNCHECKOUT resource %s.",
                                          ap_escape_html(r->pool, r->uri)),
                             err);
        return dav_handle_err(r, err, NULL);
    }

    /* no body */
    ap_set_content_length(r, 0);

    return DONE;
}