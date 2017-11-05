static int dav_method_bind(request_rec *r)
{
    dav_resource *resource;
    dav_resource *binding;
    dav_auto_version_info av_info;
    const dav_hooks_binding *binding_hooks = DAV_GET_HOOKS_BINDING(r);
    const char *dest;
    dav_error *err;
    dav_error *err2;
    dav_response *multi_response = NULL;
    dav_lookup_result lookup;
    int overwrite;

    /* If no bindings provider, decline the request */
    if (binding_hooks == NULL)
        return DECLINED;

    /* Ask repository module to resolve the resource */
    err = dav_get_resource(r, 0 /* label_allowed */, 0 /* use_checked_in */,
                           &resource);
    if (err != NULL)
        return dav_handle_err(r, err, NULL);

    if (!resource->exists) {
        /* Apache will supply a default error for this. */
        return HTTP_NOT_FOUND;
    }

    /* get the destination URI */
    dest = apr_table_get(r->headers_in, "Destination");
    if (dest == NULL) {
        /* This supplies additional information for the default message. */
        ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r,
                      "The request is missing a Destination header.");
        return HTTP_BAD_REQUEST;
    }

    lookup = dav_lookup_uri(dest, r, 0 /* must_be_absolute */);
    if (lookup.rnew == NULL) {
        if (lookup.err.status == HTTP_BAD_REQUEST) {
            /* This supplies additional information for the default message. */
            ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r,
                          "%s", lookup.err.desc);
            return HTTP_BAD_REQUEST;
        }
        else if (lookup.err.status == HTTP_BAD_GATEWAY) {
            /* ### Bindings protocol draft 02 says to return 507
             * ### (Cross Server Binding Forbidden); Apache already defines 507
             * ### as HTTP_INSUFFICIENT_STORAGE. So, for now, we'll return
             * ### HTTP_FORBIDDEN
             */
             return dav_error_response(r, HTTP_FORBIDDEN,
                                       "Cross server bindings are not "
                                       "allowed by this server.");
        }

        /* ### this assumes that dav_lookup_uri() only generates a status
         * ### that Apache can provide a status line for!! */

        return dav_error_response(r, lookup.err.status, lookup.err.desc);
    }
    if (lookup.rnew->status != HTTP_OK) {
        /* ### how best to report this... */
        return dav_error_response(r, lookup.rnew->status,
                                  "Destination URI had an error.");
    }

    /* resolve binding resource */
    err = dav_get_resource(lookup.rnew, 0 /* label_allowed */,
                           0 /* use_checked_in */, &binding);
    if (err != NULL)
        return dav_handle_err(r, err, NULL);

    /* are the two resources handled by the same repository? */
    if (resource->hooks != binding->hooks) {
        /* ### this message exposes some backend config, but screw it... */
        return dav_error_response(r, HTTP_BAD_GATEWAY,
                                  "Destination URI is handled by a "
                                  "different repository than the source URI. "
                                  "BIND between repositories is not possible.");
    }

    /* get and parse the overwrite header value */
    if ((overwrite = dav_get_overwrite(r)) < 0) {
        /* dav_get_overwrite() supplies additional information for the
         * default message. */
        return HTTP_BAD_REQUEST;
    }

    /* quick failure test: if dest exists and overwrite is false. */
    if (binding->exists && !overwrite) {
        return dav_error_response(r, HTTP_PRECONDITION_FAILED,
                                  "Destination is not empty and "
                                  "Overwrite is not \"T\"");
    }

    /* are the source and destination the same? */
    if ((*resource->hooks->is_same_resource)(resource, binding)) {
        return dav_error_response(r, HTTP_FORBIDDEN,
                                  "Source and Destination URIs are the same.");
    }

    /*
     * Check If-Headers and existing locks for destination. Note that we
     * use depth==infinity since the target (hierarchy) will be deleted
     * before the move/copy is completed.
     *
     * Note that we are overwriting the target, which implies a DELETE, so
     * we are subject to the error/response rules as a DELETE. Namely, we
     * will return a 424 error if any of the validations fail.
     * (see dav_method_delete() for more information)
     */
    if ((err = dav_validate_request(lookup.rnew, binding, DAV_INFINITY, NULL,
                                    &multi_response,
                                    DAV_VALIDATE_PARENT
                                    | DAV_VALIDATE_USE_424, NULL)) != NULL) {
        err = dav_push_error(r->pool, err->status, 0,
                             apr_psprintf(r->pool,
                                          "Could not BIND %s due to a "
                                          "failed precondition on the "
                                          "destination (e.g. locks).",
                                          ap_escape_html(r->pool, r->uri)),
                             err);
        return dav_handle_err(r, err, multi_response);
    }

    /* guard against creating circular bindings */
    if (resource->collection
        && (*resource->hooks->is_parent_resource)(resource, binding)) {
        return dav_error_response(r, HTTP_FORBIDDEN,
                                  "Source collection contains the Destination.");
    }
    if (resource->collection
        && (*resource->hooks->is_parent_resource)(binding, resource)) {
        /* The destination must exist (since it contains the source), and
         * a condition above implies Overwrite==T. Obviously, we cannot
         * delete the Destination before the BIND, as that would
         * delete the Source.
         */

        return dav_error_response(r, HTTP_FORBIDDEN,
                                  "Destination collection contains the Source and "
                                  "Overwrite has been specified.");
    }

    /* prepare the destination collection for modification */
    if ((err = dav_auto_checkout(r, binding, 1 /* parent_only */,
                                 &av_info)) != NULL) {
        /* could not make destination writable */
        return dav_handle_err(r, err, NULL);
    }

    /* If target exists, remove it first (we know Ovewrite must be TRUE).
     * Then try to bind to the resource.
     */
    if (binding->exists)
        err = (*resource->hooks->remove_resource)(binding, &multi_response);

    if (err == NULL) {
        err = (*binding_hooks->bind_resource)(resource, binding);
    }

    /* restore parent collection states */
    err2 = dav_auto_checkin(r, NULL,
                            err != NULL /* undo if error */,
                            0 /* unlock */, &av_info);

    /* check for error from remove/bind operations */
    if (err != NULL) {
        err = dav_push_error(r->pool, err->status, 0,
                             apr_psprintf(r->pool,
                                          "Could not BIND %s.",
                                          ap_escape_html(r->pool, r->uri)),
                             err);
        return dav_handle_err(r, err, multi_response);
    }

    /* check for errors from reverting writability */
    if (err2 != NULL) {
        /* just log a warning */
        err = dav_push_error(r->pool, err2->status, 0,
                             "The BIND was successful, but there was a "
                             "problem automatically checking in the "
                             "source parent collection.",
                             err2);
        dav_log_err(r, err, APLOG_WARNING);
    }

    /* return an appropriate response (HTTP_CREATED) */
    /* ### spec doesn't say what happens when destination was replaced */
    return dav_created(r, lookup.rnew->uri, "Binding", 0);
}