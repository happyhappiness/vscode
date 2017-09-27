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
        ap_log_cerror(APLOG_MARK, APLOG_DEBUG, 0, c,
                      "Connection: Client IP: %s, Protocol: %s, "
                      "Cipher: %s (%s/%s bits)",
                      ssl_var_lookup(NULL, s, c, NULL, "REMOTE_ADDR"),
                      ssl_var_lookup(NULL, s, c, NULL, "SSL_PROTOCOL"),
                      ssl_var_lookup(NULL, s, c, NULL, "SSL_CIPHER"),
                      ssl_var_lookup(NULL, s, c, NULL, "SSL_CIPHER_USEKEYSIZE"),
                      ssl_var_lookup(NULL, s, c, NULL, "SSL_CIPHER_ALGKEYSIZE"));
    }
}
