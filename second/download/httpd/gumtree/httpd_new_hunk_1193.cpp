            return HTTP_FORBIDDEN;
        }

        SSL_set_client_CA_list(ssl, ca_list);
        renegotiate = TRUE;

        ap_log_rerror(APLOG_MARK, APLOG_DEBUG, 0, r,
                      "Changed client verification locations will force "
                      "renegotiation");
    }
#endif /* HAVE_SSL_SET_CERT_STORE */

    /* If a renegotiation is now required for this location, and the
     * request includes a message body (and the client has not
     * requested a "100 Continue" response), then the client will be
