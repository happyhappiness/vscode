static int dav_method_copymove(request_rec *r, int is_move)
{
    dav_resource *resource;
    dav_resource *resnew;
    dav_auto_version_info src_av_info = { 0 };
    dav_auto_version_info dst_av_info = { 0 };
    const char *body;
    const char *dest;
    dav_error *err;
    dav_error *err2;
    dav_error *err3;
    dav_response *multi_response;
    dav_lookup_result lookup;
    int is_dir;
    int overwrite;
    int depth;
    int result;
    dav_lockdb *lockdb;
    int replace_dest;
    int resnew_state;

    /* Ask repository module to resolve the resource */
    err = dav_get_resource(r, !is_move /* label_allowed */,
                           0 /* use_checked_in */, &resource);
    if (err != NULL)
        return dav_handle_err(r, err, NULL);

    if (!resource->exists) {
        /* Apache will supply a default error for this. */
        return HTTP_NOT_FOUND;
    }

    /* If not a file or collection resource, COPY/MOVE not allowed */
    /* ### allow COPY/MOVE of DeltaV resource types */
    if (resource->type != DAV_RESOURCE_TYPE_REGULAR) {
        body = apr_psprintf(r->pool,
                            "Cannot COPY/MOVE resource %s.",
                            ap_escape_html(r->pool, r->uri));
        return dav_error_response(r, HTTP_METHOD_NOT_ALLOWED, body);
    }

    /* get the destination URI */
    dest = apr_table_get(r->headers_in, "Destination");
    if (dest == NULL) {
        /* Look in headers provided by Netscape's Roaming Profiles */
        const char *nscp_host = apr_table_get(r->headers_in, "Host");
        const char *nscp_path = apr_table_get(r->headers_in, "New-uri");

        if (nscp_host != NULL && nscp_path != NULL)
            dest = apr_psprintf(r->pool, "http://%s%s", nscp_host, nscp_path);
    }
    if (dest == NULL) {
        /* This supplies additional information for the default message. */
        ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r,
                      "The request is missing a Destination header.");
        return HTTP_BAD_REQUEST;
    }

    lookup = dav_lookup_uri(dest, r, 1 /* must_be_absolute */);
    if (lookup.rnew == NULL) {
        if (lookup.err.status == HTTP_BAD_REQUEST) {
            /* This supplies additional information for the default message. */
            ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r,
                          "%s", lookup.err.desc);
            return HTTP_BAD_REQUEST;
        }

        /* ### this assumes that dav_lookup_uri() only generates a status
         * ### that Apache can provide a status line for!! */

        return dav_error_response(r, lookup.err.status, lookup.err.desc);
    }
    if (lookup.rnew->status != HTTP_OK) {
        const char *auth = apr_table_get(lookup.rnew->err_headers_out,
                                        "WWW-Authenticate");
        if (lookup.rnew->status == HTTP_UNAUTHORIZED && auth != NULL) {
            /* propagate the WWW-Authorization header up from the
             * subreq so the client sees it. */
            apr_table_set(r->err_headers_out, "WWW-Authenticate",
                          apr_pstrdup(r->pool, auth));
        }

        /* ### how best to report this... */
        return dav_error_response(r, lookup.rnew->status,
                                  "Destination URI had an error.");
    }

    if (dav_get_provider(lookup.rnew) == NULL) {
        return dav_error_response(r, HTTP_METHOD_NOT_ALLOWED,
                                  "DAV not enabled for Destination URI.");
    }

    /* Resolve destination resource */
    err = dav_get_resource(lookup.rnew, 0 /* label_allowed */,
                           0 /* use_checked_in */, &resnew);
    if (err != NULL)
        return dav_handle_err(r, err, NULL);

    /* are the two resources handled by the same repository? */
    if (resource->hooks != resnew->hooks) {
        /* ### this message exposes some backend config, but screw it... */
        return dav_error_response(r, HTTP_BAD_GATEWAY,
                                  "Destination URI is handled by a "
                                  "different repository than the source URI. "
                                  "MOVE or COPY between repositories is "
                                  "not possible.");
    }

    /* get and parse the overwrite header value */
    if ((overwrite = dav_get_overwrite(r)) < 0) {
        /* dav_get_overwrite() supplies additional information for the
         * default message. */
        return HTTP_BAD_REQUEST;
    }

    /* quick failure test: if dest exists and overwrite is false. */
    if (resnew->exists && !overwrite) {
        /* Supply some text for the error response body. */
        return dav_error_response(r, HTTP_PRECONDITION_FAILED,
                                  "Destination is not empty and "
                                  "Overwrite is not \"T\"");
    }

    /* are the source and destination the same? */
    if ((*resource->hooks->is_same_resource)(resource, resnew)) {
        /* Supply some text for the error response body. */
        return dav_error_response(r, HTTP_FORBIDDEN,
                                  "Source and Destination URIs are the same.");

    }

    is_dir = resource->collection;

    /* get and parse the Depth header value. "0" and "infinity" are legal. */
    if ((depth = dav_get_depth(r, DAV_INFINITY)) < 0) {
        /* dav_get_depth() supplies additional information for the
         * default message. */
        return HTTP_BAD_REQUEST;
    }
    if (depth == 1) {
        /* This supplies additional information for the default message. */
        ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r,
                      "Depth must be \"0\" or \"infinity\" for COPY or MOVE.");
        return HTTP_BAD_REQUEST;
    }
    if (is_move && is_dir && depth != DAV_INFINITY) {
        /* This supplies additional information for the default message. */
        ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r,
                      "Depth must be \"infinity\" when moving a collection.");
        return HTTP_BAD_REQUEST;
    }

    /*
     * Check If-Headers and existing locks for each resource in the source
     * if we are performing a MOVE. We will return a 424 response with a
     * DAV:multistatus body. The multistatus responses will contain the
     * information about any resource that fails the validation.
     *
     * We check the parent resource, too, since this is a MOVE. Moving the
     * resource effectively removes it from the parent collection, so we
     * must ensure that we have met the appropriate conditions.
     *
     * If a problem occurs with the Request-URI itself, then a plain error
     * (rather than a multistatus) will be returned.
     */
    if (is_move
        && (err = dav_validate_request(r, resource, depth, NULL,
                                       &multi_response,
                                       DAV_VALIDATE_PARENT
                                       | DAV_VALIDATE_USE_424,
                                       NULL)) != NULL) {
        err = dav_push_error(r->pool, err->status, 0,
                             apr_psprintf(r->pool,
                                          "Could not MOVE %s due to a failed "
                                          "precondition on the source "
                                          "(e.g. locks).",
                                          ap_escape_html(r->pool, r->uri)),
                             err);
        return dav_handle_err(r, err, multi_response);
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
    if ((err = dav_validate_request(lookup.rnew, resnew, DAV_INFINITY, NULL,
                                    &multi_response,
                                    DAV_VALIDATE_PARENT
                                    | DAV_VALIDATE_USE_424, NULL)) != NULL) {
        err = dav_push_error(r->pool, err->status, 0,
                             apr_psprintf(r->pool,
                                          "Could not MOVE/COPY %s due to a "
                                          "failed precondition on the "
                                          "destination (e.g. locks).",
                                          ap_escape_html(r->pool, r->uri)),
                             err);
        return dav_handle_err(r, err, multi_response);
    }

    if (is_dir
        && depth == DAV_INFINITY
        && (*resource->hooks->is_parent_resource)(resource, resnew)) {
        /* Supply some text for the error response body. */
        return dav_error_response(r, HTTP_FORBIDDEN,
                                  "Source collection contains the "
                                  "Destination.");

    }
    if (is_dir
        && (*resnew->hooks->is_parent_resource)(resnew, resource)) {
        /* The destination must exist (since it contains the source), and
         * a condition above implies Overwrite==T. Obviously, we cannot
         * delete the Destination before the MOVE/COPY, as that would
         * delete the Source.
         */

        /* Supply some text for the error response body. */
        return dav_error_response(r, HTTP_FORBIDDEN,
                                  "Destination collection contains the Source "
                                  "and Overwrite has been specified.");
    }

    /* ### for now, we don't need anything in the body */
    if ((result = ap_discard_request_body(r)) != OK) {
        return result;
    }

    if ((err = dav_open_lockdb(r, 0, &lockdb)) != NULL) {
        /* ### add a higher-level description? */
        return dav_handle_err(r, err, NULL);
    }

    /* remove any locks from the old resources */
    /*
     * ### this is Yet Another Traversal. if we do a rename(), then we
     * ### really don't have to do this in some cases since the inode
     * ### values will remain constant across the move. but we can't
     * ### know that fact from outside the provider :-(
     *
     * ### note that we now have a problem atomicity in the move/copy
     * ### since a failure after this would have removed locks (technically,
     * ### this is okay to do, but really...)
     */
    if (is_move && lockdb != NULL) {
        /* ### this is wrong! it blasts direct locks on parent resources */
        /* ### pass lockdb! */
        (void)dav_unlock(r, resource, NULL);
    }

    /* if this is a move, then the source parent collection will be modified */
    if (is_move) {
        if ((err = dav_auto_checkout(r, resource, 1 /* parent_only */,
                                     &src_av_info)) != NULL) {
            if (lockdb != NULL)
                (*lockdb->hooks->close_lockdb)(lockdb);

            /* ### add a higher-level description? */
            return dav_handle_err(r, err, NULL);
        }
    }

    /*
     * Remember the initial state of the destination, so the lock system
     * can be notified as to how it changed.
     */
    resnew_state = dav_get_resource_state(lookup.rnew, resnew);

    /* In a MOVE operation, the destination is replaced by the source.
     * In a COPY operation, if the destination exists, is under version
     * control, and is the same resource type as the source,
     * then it should not be replaced, but modified to be a copy of
     * the source.
     */
    if (!resnew->exists)
        replace_dest = 0;
    else if (is_move || !resource->versioned)
        replace_dest = 1;
    else if (resource->type != resnew->type)
        replace_dest = 1;
    else if ((resource->collection == 0) != (resnew->collection == 0))
        replace_dest = 1;
    else
        replace_dest = 0;

    /* If the destination must be created or replaced,
     * make sure the parent collection is writable
     */
    if (!resnew->exists || replace_dest) {
        if ((err = dav_auto_checkout(r, resnew, 1 /*parent_only*/,
                                     &dst_av_info)) != NULL) {
            /* could not make destination writable:
             * if move, restore state of source parent
             */
            if (is_move) {
                (void)dav_auto_checkin(r, NULL, 1 /* undo */,
                                       0 /*unlock*/, &src_av_info);
            }

            if (lockdb != NULL)
                (*lockdb->hooks->close_lockdb)(lockdb);

            /* ### add a higher-level description? */
            return dav_handle_err(r, err, NULL);
        }
    }

    /* If source and destination parents are the same, then
     * use the same resource object, so status updates to one are reflected
     * in the other, when doing auto-versioning. Otherwise,
     * we may try to checkin the parent twice.
     */
    if (src_av_info.parent_resource != NULL
        && dst_av_info.parent_resource != NULL
        && (*src_av_info.parent_resource->hooks->is_same_resource)
            (src_av_info.parent_resource, dst_av_info.parent_resource)) {

        dst_av_info.parent_resource = src_av_info.parent_resource;
    }

    /* If destination is being replaced, remove it first
     * (we know Ovewrite must be TRUE). Then try to copy/move the resource.
     */
    if (replace_dest)
        err = (*resnew->hooks->remove_resource)(resnew, &multi_response);

    if (err == NULL) {
        if (is_move)
            err = (*resource->hooks->move_resource)(resource, resnew,
                                                    &multi_response);
        else
            err = (*resource->hooks->copy_resource)(resource, resnew, depth,
                                                    &multi_response);
    }

    /* perform any auto-versioning cleanup */
    err2 = dav_auto_checkin(r, NULL, err != NULL /* undo if error */,
                            0 /*unlock*/, &dst_av_info);

    if (is_move) {
        err3 = dav_auto_checkin(r, NULL, err != NULL /* undo if error */,
                                0 /*unlock*/, &src_av_info);
    }
    else
        err3 = NULL;

    /* check for error from remove/copy/move operations */
    if (err != NULL) {
        if (lockdb != NULL)
            (*lockdb->hooks->close_lockdb)(lockdb);

        err = dav_push_error(r->pool, err->status, 0,
                             apr_psprintf(r->pool,
                                          "Could not MOVE/COPY %s.",
                                          ap_escape_html(r->pool, r->uri)),
                             err);
        return dav_handle_err(r, err, multi_response);
    }

    /* check for errors from auto-versioning */
    if (err2 != NULL) {
        /* just log a warning */
        err = dav_push_error(r->pool, err2->status, 0,
                             "The MOVE/COPY was successful, but there was a "
                             "problem automatically checking in the "
                             "source parent collection.",
                             err2);
        dav_log_err(r, err, APLOG_WARNING);
    }
    if (err3 != NULL) {
        /* just log a warning */
        err = dav_push_error(r->pool, err3->status, 0,
                             "The MOVE/COPY was successful, but there was a "
                             "problem automatically checking in the "
                             "destination or its parent collection.",
                             err3);
        dav_log_err(r, err, APLOG_WARNING);
    }

    /* propagate any indirect locks at the target */
    if (lockdb != NULL) {

        /* notify lock system that we have created/replaced a resource */
        err = dav_notify_created(r, lockdb, resnew, resnew_state, depth);

        (*lockdb->hooks->close_lockdb)(lockdb);

        if (err != NULL) {
            /* The move/copy was successful, but the locking failed. */
            err = dav_push_error(r->pool, err->status, 0,
                                 "The MOVE/COPY was successful, but there "
                                 "was a problem updating the lock "
                                 "information.",
                                 err);
            return dav_handle_err(r, err, NULL);
        }
    }

    /* return an appropriate response (HTTP_CREATED or HTTP_NO_CONTENT) */
    return dav_created(r, lookup.rnew->uri, "Destination",
                       resnew_state == DAV_RESOURCE_EXISTS);
}