ap_log_cerror(APLOG_MARK, APLOG_DEBUG, 0, c,
                      "Connection: Client IP: %s, Protocol: %s, "
                      "Cipher: %s (%s/%s bits)",
                      ssl_var_lookup(NULL, s, c, NULL, "REMOTE_ADDR"),
                      ssl_var_lookup(NULL, s, c, NULL, "SSL_PROTOCOL"),
                      ssl_var_lookup(NULL, s, c, NULL, "SSL_CIPHER"),
                      ssl_var_lookup(NULL, s, c, NULL, "SSL_CIPHER_USEKEYSIZE"),
                      ssl_var_lookup(NULL, s, c, NULL, "SSL_CIPHER_ALGKEYSIZE"));