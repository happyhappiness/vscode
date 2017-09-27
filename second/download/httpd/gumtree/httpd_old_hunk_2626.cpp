    /* ### dav_lookup_uri only allows absolute URIs; is that OK? */
    if (!is_label) {
        lookup = dav_lookup_uri(target, r, 0 /* must_be_absolute */);
        if (lookup.rnew == NULL) {
            if (lookup.err.status == HTTP_BAD_REQUEST) {
                /* This supplies additional information for the default message. */
                ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r,
                              "%s", lookup.err.desc);
                return HTTP_BAD_REQUEST;
            }

            /* ### this assumes that dav_lookup_uri() only generates a status
             * ### that Apache can provide a status line for!! */
