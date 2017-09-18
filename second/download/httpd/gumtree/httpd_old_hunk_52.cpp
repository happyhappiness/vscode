
        if (nscp_host != NULL && nscp_path != NULL)
            dest = apr_psprintf(r->pool, "http://%s%s", nscp_host, nscp_path);
    }
    if (dest == NULL) {
        /* This supplies additional information for the default message. */
        ap_log_rerror(APLOG_MARK, APLOG_ERR | APLOG_NOERRNO, 0, r,
                      "The request is missing a Destination header.");
        return HTTP_BAD_REQUEST;
    }

    lookup = dav_lookup_uri(dest, r, 1 /* must_be_absolute */);
    if (lookup.rnew == NULL) {
        if (lookup.err.status == HTTP_BAD_REQUEST) {
            /* This supplies additional information for the default message. */
            ap_log_rerror(APLOG_MARK, APLOG_ERR | APLOG_NOERRNO, 0, r,
                          lookup.err.desc);
            return HTTP_BAD_REQUEST;
        }

        /* ### this assumes that dav_lookup_uri() only generates a status
         * ### that Apache can provide a status line for!! */
