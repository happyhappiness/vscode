        ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r,
                      "Depth must be \"infinity\" when moving a collection.");
        return HTTP_BAD_REQUEST;
    }

    /*
     * Check If-Headers and existing locks for each resource in the source.
     * We will return a 424 response with a DAV:multistatus body.
     * The multistatus responses will contain the information about any
     * resource that fails the validation.
     *
     * We check the parent resource, too, if this is a MOVE. Moving the
     * resource effectively removes it from the parent collection, so we
     * must ensure that we have met the appropriate conditions.
     *
     * If a problem occurs with the Request-URI itself, then a plain error
     * (rather than a multistatus) will be returned.
     */
    if ((err = dav_validate_request(r, resource, depth, NULL,
                                    &multi_response,
                                    (is_move ? DAV_VALIDATE_PARENT
                                             : DAV_VALIDATE_RESOURCE
                                               | DAV_VALIDATE_NO_MODIFY)
                                    | DAV_VALIDATE_USE_424,
                                    NULL)) != NULL) {
        err = dav_push_error(r->pool, err->status, 0,
                             apr_psprintf(r->pool,
                                          "Could not %s %s due to a failed "
                                          "precondition on the source "
                                          "(e.g. locks).",
                                          is_move ? "MOVE" : "COPY",
                                          ap_escape_html(r->pool, r->uri)),
                             err);
        return dav_handle_err(r, err, multi_response);
    }

    /*
