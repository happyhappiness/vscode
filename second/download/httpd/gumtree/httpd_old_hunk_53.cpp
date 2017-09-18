        /* dav_get_depth() supplies additional information for the
         * default message. */
        return HTTP_BAD_REQUEST;
    }
    if (depth == 1) {
        /* This supplies additional information for the default message. */
        ap_log_rerror(APLOG_MARK, APLOG_ERR | APLOG_NOERRNO, 0, r,
                      "Depth must be \"0\" or \"infinity\" for COPY or MOVE.");
        return HTTP_BAD_REQUEST;
    }
    if (is_move && is_dir && depth != DAV_INFINITY) {
        /* This supplies additional information for the default message. */
        ap_log_rerror(APLOG_MARK, APLOG_ERR | APLOG_NOERRNO, 0, r,
                      "Depth must be \"infinity\" when moving a collection.");
        return HTTP_BAD_REQUEST;
    }

    /*
     * Check If-Headers and existing locks for each resource in the source
