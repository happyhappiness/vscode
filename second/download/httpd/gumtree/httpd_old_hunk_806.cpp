    }

    /*
     * Support for SSLRequireSSL directive
     */
    if (dc->bSSLRequired && !ssl) {
        ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r, 
                      "access to %s failed, reason: %s",
                      r->filename, "SSL connection required");

        /* remember forbidden access for strict require option */
        apr_table_setn(r->notes, "ssl-access-forbidden", "1");

        return HTTP_FORBIDDEN;
    }

    /*
     * Check to see whether SSL is in use; if it's not, then no
     * further access control checks are relevant.  (the test for
     * sc->enabled is probably strictly unnecessary)
     */
    if (!sc->enabled || !ssl) {
        return DECLINED;
    }

    /*
     * Support for per-directory reconfigured SSL connection parameters.
     *
     * This is implemented by forcing an SSL renegotiation with the
     * reconfigured parameter suite. But Apache's internal API processing
     * makes our life very hard here, because when internal sub-requests occur
