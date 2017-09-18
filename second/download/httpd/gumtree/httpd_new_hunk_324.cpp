            sslconn->verify_depth = n = sc->server->auth.verify_depth;
        }

        /* determine whether a renegotiation has to be forced */
        if (dc->nVerifyDepth < n) {
            renegotiate = TRUE;
            ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, r->server,
                         "Reduced client verification depth will force "
                         "renegotiation");
        }
    }

    /*
     * override of SSLVerifyClient
     *
