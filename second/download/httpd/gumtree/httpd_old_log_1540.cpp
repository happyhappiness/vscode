r(APLOG_MARK, APLOG_DEBUG, 0, r,
                          "Performing full renegotiation: complete handshake "
                          "protocol (%s support secure renegotiation)",
#if defined(SSL_get_secure_renegotiation_support)
                          SSL_get_secure_renegotiation_support(ssl) ? 
                          "client does" : "client does not"
#else
                          "server does not"
#endif
                );