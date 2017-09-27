                      "Failed to connect to '%s'", url);
        return HTTP_INTERNAL_SERVER_ERROR;
    }

    {
        int status;
        const char *flush_method = *worker->s->flusher ? worker->s->flusher : "flush";

        proxy_fdpass_flush *flush = ap_lookup_provider(PROXY_FDPASS_FLUSHER,
                                                       flush_method, "0");

        if (!flush) {
            ap_log_rerror(APLOG_MARK, APLOG_ERR, rv, r, APLOGNO(01153)
