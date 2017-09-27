    /* Perform initial SSL handshake. */
    SSL_set_accept_state(ssl);
    SSL_do_handshake(ssl);

    if (SSL_get_state(ssl) != SSL_ST_OK) {
        ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r, APLOGNO(02030)
                      "TLS upgrade handshake failed: not accepted by client!?");

        return APR_ECONNABORTED;
    }

    return APR_SUCCESS;
}
