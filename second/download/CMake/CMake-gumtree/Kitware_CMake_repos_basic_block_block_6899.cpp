f(SSL_OptionSet(connssl->handle, SSL_ENABLE_NPN, conn->bits.tls_enable_npn
                   ? PR_TRUE : PR_FALSE) != SECSuccess)
    goto error;