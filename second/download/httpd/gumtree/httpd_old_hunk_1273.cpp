                     ssl_var_lookup(NULL, s, c, NULL, "SSL_CIPHER"),
                     ssl_var_lookup(NULL, s, c, NULL, "SSL_CIPHER_USEKEYSIZE"),
                     ssl_var_lookup(NULL, s, c, NULL, "SSL_CIPHER_ALGKEYSIZE"));
    }
}

#ifndef OPENSSL_NO_TLSEXT
/*
 * This callback function is executed when OpenSSL encounters an extended
 * client hello with a server name indication extension ("SNI", cf. RFC 4366).
 */
int ssl_callback_ServerNameIndication(SSL *ssl, int *al, modssl_ctx_t *mctx)
