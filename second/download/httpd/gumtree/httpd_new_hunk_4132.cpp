            apr_socket_close(sd);
        }
    }

    if (sa == NULL) {
        ap_log_cerror(APLOG_MARK, APLOG_ERR, rv, c, APLOGNO(01974)
                      "could not connect to %s '%s'",
                      proxy_uri ? "proxy" : "OCSP responder",
                      next_hop_uri->hostinfo);
        return NULL;
    }

    /* send the request and get a response */
    ap_log_cerror(APLOG_MARK, APLOG_DEBUG, 0, c, APLOGNO(01975)
                 "sending request to OCSP responder");
