static int dav_method_delete(request_rec *r)
{
    dav_resource *resource;
    dav_auto_version_info av_info;
    dav_error *err;
    dav_error *err2;
    dav_response *multi_response;
    int result;
    int depth;

    /* We don't use the request body right now, so torch it. */
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

    /* 2518 says that depth must be infinity only for collections.
     * For non-collections, depth is ignored, unless it is an illegal value (1).
     */
    depth = dav_get_depth(r, DAV_INFINITY);

    if (resource->collection && depth != DAV_INFINITY) {
        /* This supplies additional information for the default message. */
        ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r,
                      "Depth must be \"infinity\" for DELETE of a collection.");
        return HTTP_BAD_REQUEST;
    }

    if (!resource->collection && depth == 1) {
        /* This supplies additional information for the default message. */
        ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r,
                      "Depth of \"1\" is not allowed for DELETE.");
        return HTTP_BAD_REQUEST;
    }

    /*
    ** If any resources fail the lock/If: conditions, then we must fail
    ** the delete. Each of the failing resources will be listed within
    ** a DAV:multistatus body, wrapped into a 424 response.
    **
    ** Note that a failure on the resource itself does not generate a
    ** multistatus response -- only internal members/collections.
    */
    if ((err = dav_validate_request(r, resource, depth, NULL,
                                    &multi_response,
                                    DAV_VALIDATE_PARENT
                                    | DAV_VALIDATE_USE_424, NULL)) != NULL) {
        err = dav_push_error(r->pool, err->status, 0,
                             apr_psprintf(r->pool,
                                          "Could not DELETE %s due to a failed "
                                          "precondition (e.g. locks).",
                                          ap_escape_html(r->pool, r->uri)),
                             err);
        return dav_handle_err(r, err, multi_response);
    }

    /* ### RFC 2518 s. 8.10.5 says to remove _all_ locks, not just those
     *     locked by the token(s) in the if_header.
     */
    if ((result = dav_unlock(r, resource, NULL)) != OK) {
        return result;
    }

    /* if versioned resource, make sure parent is checked out */
    if ((err = dav_auto_checkout(r, resource, 1 /* parent_only */,
                                 &av_info)) != NULL) {
        /* ### add a higher-level description? */
        return dav_handle_err(r, err, NULL);
    }

    /* try to remove the resource */
    err = (*resource->hooks->remove_resource)(resource, &multi_response);

    /* restore writability of parent back to what it was */
    err2 = dav_auto_checkin(r, NULL, err != NULL /* undo if error */,
                            0 /*unlock*/, &av_info);

    /* check for errors now */
    if (err != NULL) {
        err = dav_push_error(r->pool, err->status, 0,
                             apr_psprintf(r->pool,
                                          "Could not DELETE %s.",
                                          ap_escape_html(r->pool, r->uri)),
                             err);
        return dav_handle_err(r, err, multi_response);
    }
    if (err2 != NULL) {
        /* just log a warning */
        err = dav_push_error(r->pool, err2->status, 0,
                             "The DELETE was successful, but there "
                             "was a problem automatically checking in "
                             "the parent collection.",
                             err2);
        dav_log_err(r, err, APLOG_WARNING);
    }

    /* ### HTTP_NO_CONTENT if no body, HTTP_OK if there is a body (some day) */

    /* Apache will supply a default error for this. */
    return HTTP_NO_CONTENT;
}