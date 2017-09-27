            rc = ap_proxygetline(tmp_bb, buffer, sizeof(buffer), rp, 0, &len);
        }
        if (len <= 0) {
            ap_log_rerror(APLOG_MARK, APLOG_ERR, rc, r,
                          "proxy: error reading status line from remote "
                          "server %s", backend->hostname);
            /*
             * If we are a reverse proxy request shutdown the connection
             * WITHOUT ANY response to trigger a retry by the client
             * if allowed (as for idempotent requests).
             * BUT currently we should not do this if the request is the
             * first request on a keepalive connection as browsers like
             * seamonkey only display an empty page in this case and do
             * not do a retry.
             */
            if (r->proxyreq == PROXYREQ_REVERSE && c->keepalives) {
                apr_bucket *eos;

                ap_log_rerror(APLOG_MARK, APLOG_DEBUG, 0, r,
                              "proxy: Closing connection to client because"
                              " reading from backend server %s failed. Number"
                              " of keepalives %i", backend->hostname, 
