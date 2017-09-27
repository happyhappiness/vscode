                              server_rec *s, int where, int rc)
{
    /*
     * create the various trace messages
     */
    if (where & SSL_CB_HANDSHAKE_START) {
        ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, s,
                     "%s: Handshake: start", SSL_LIBRARY_NAME);
    }
    else if (where & SSL_CB_HANDSHAKE_DONE) {
        ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, s,
                     "%s: Handshake: done", SSL_LIBRARY_NAME);
    }
    else if (where & SSL_CB_LOOP) {
        ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, s,
                     "%s: Loop: %s",
                     SSL_LIBRARY_NAME, SSL_state_string_long(ssl));
    }
    else if (where & SSL_CB_READ) {
        ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, s,
                     "%s: Read: %s",
                     SSL_LIBRARY_NAME, SSL_state_string_long(ssl));
    }
    else if (where & SSL_CB_WRITE) {
        ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, s,
                     "%s: Write: %s",
                     SSL_LIBRARY_NAME, SSL_state_string_long(ssl));
    }
    else if (where & SSL_CB_ALERT) {
        char *str = (where & SSL_CB_READ) ? "read" : "write";
        ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, s,
                     "%s: Alert: %s:%s:%s",
                     SSL_LIBRARY_NAME, str,
                     SSL_alert_type_string_long(rc),
                     SSL_alert_desc_string_long(rc));
    }
    else if (where & SSL_CB_EXIT) {
        if (rc == 0) {
            ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, s,
                         "%s: Exit: failed in %s",
                         SSL_LIBRARY_NAME, SSL_state_string_long(ssl));
        }
        else if (rc < 0) {
            ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, s,
                         "%s: Exit: error in %s",
                         SSL_LIBRARY_NAME, SSL_state_string_long(ssl));
        }
    }

    /*
     * Because SSL renegotations can happen at any time (not only after
     * SSL_accept()), the best way to log the current connection details is
     * right after a finished handshake.
     */
    if (where & SSL_CB_HANDSHAKE_DONE) {
        ap_log_error(APLOG_MARK, APLOG_INFO, 0, s,
                     "Connection: Client IP: %s, Protocol: %s, "
                     "Cipher: %s (%s/%s bits)",
                     ssl_var_lookup(NULL, s, c, NULL, "REMOTE_ADDR"),
                     ssl_var_lookup(NULL, s, c, NULL, "SSL_PROTOCOL"),
                     ssl_var_lookup(NULL, s, c, NULL, "SSL_CIPHER"),
                     ssl_var_lookup(NULL, s, c, NULL, "SSL_CIPHER_USEKEYSIZE"),
                     ssl_var_lookup(NULL, s, c, NULL, "SSL_CIPHER_ALGKEYSIZE"));
    }
}

/*
 * This callback function is executed while OpenSSL processes the SSL
 * handshake and does SSL record layer stuff.  It's used to trap
