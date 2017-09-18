        return;
    }

    /*
     * create the various trace messages
     */
    if (sc->log_level >= SSL_LOG_TRACE) {
        if (where & SSL_CB_HANDSHAKE_START) {
            ssl_log(s, SSL_LOG_TRACE,
                    "%s: Handshake: start", SSL_LIBRARY_NAME);
        }
        else if (where & SSL_CB_HANDSHAKE_DONE) {
            ssl_log(s, SSL_LOG_TRACE,
                    "%s: Handshake: done", SSL_LIBRARY_NAME);
        }
        else if (where & SSL_CB_LOOP) {
            ssl_log(s, SSL_LOG_TRACE, "%s: Loop: %s",
                    SSL_LIBRARY_NAME, SSL_state_string_long(ssl));
        }
        else if (where & SSL_CB_READ) {
            ssl_log(s, SSL_LOG_TRACE, "%s: Read: %s",
                    SSL_LIBRARY_NAME, SSL_state_string_long(ssl));
        }
        else if (where & SSL_CB_WRITE) {
            ssl_log(s, SSL_LOG_TRACE, "%s: Write: %s",
                    SSL_LIBRARY_NAME, SSL_state_string_long(ssl));
        }
        else if (where & SSL_CB_ALERT) {
            char *str = (where & SSL_CB_READ) ? "read" : "write";
            ssl_log(s, SSL_LOG_TRACE, "%s: Alert: %s:%s:%s\n",
                    SSL_LIBRARY_NAME, str,
                    SSL_alert_type_string_long(rc),
                    SSL_alert_desc_string_long(rc));
        }
        else if (where & SSL_CB_EXIT) {
            if (rc == 0) {
                ssl_log(s, SSL_LOG_TRACE, "%s: Exit: failed in %s",
                        SSL_LIBRARY_NAME, SSL_state_string_long(ssl));
            }
            else if (rc < 0) {
                ssl_log(s, SSL_LOG_TRACE, "%s: Exit: error in %s",
                        SSL_LIBRARY_NAME, SSL_state_string_long(ssl));
            }
        }
    }

    /*
     * Because SSL renegotations can happen at any time (not only after
     * SSL_accept()), the best way to log the current connection details is
     * right after a finished handshake.
     */
    if (where & SSL_CB_HANDSHAKE_DONE) {
        ssl_log(s, SSL_LOG_INFO,
                "Connection: Client IP: %s, Protocol: %s, "
                "Cipher: %s (%s/%s bits)",
                ssl_var_lookup(NULL, s, c, NULL, "REMOTE_ADDR"),
                ssl_var_lookup(NULL, s, c, NULL, "SSL_PROTOCOL"),
                ssl_var_lookup(NULL, s, c, NULL, "SSL_CIPHER"),
                ssl_var_lookup(NULL, s, c, NULL, "SSL_CIPHER_USEKEYSIZE"),
                ssl_var_lookup(NULL, s, c, NULL, "SSL_CIPHER_ALGKEYSIZE"));
    }
}

