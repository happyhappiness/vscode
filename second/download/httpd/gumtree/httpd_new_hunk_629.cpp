            /* This supplies additional information for the default message. */
            ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r,
                          "Invalid Content-Length %s", lenp);
            return HTTP_BAD_REQUEST;
        }

        r->remaining = apr_atoi64(lenp);
    }

    if (r->read_chunked || r->remaining > 0) {
        /* ### log something? */

        /* Apache will supply a default error for this. */
