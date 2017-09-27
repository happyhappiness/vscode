    r->read_chunked = 0;
    r->remaining = 0;

    if (tenc) {
        if (strcasecmp(tenc, "chunked")) {
            /* Use this instead of Apache's default error string */
            ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r, APLOGNO(00589)
                          "Unknown Transfer-Encoding %s", tenc);
            return HTTP_NOT_IMPLEMENTED;
        }

        r->read_chunked = 1;
    }
