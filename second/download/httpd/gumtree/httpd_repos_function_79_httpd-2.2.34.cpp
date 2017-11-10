static void ssl_print_info(struct connection *c)
{
    X509_STACK_TYPE *sk;
    X509 *cert;
    int count;

    BIO_printf(bio_err, "\n");
    sk = SSL_get_peer_cert_chain(c->ssl);
    if ((count = SK_NUM(sk)) > 0) {
        int i;
        for (i=1; i<count; i++) {
            cert = (X509 *)SK_VALUE(sk, i);
            ssl_print_cert_info(bio_out, cert);
            X509_free(cert);
    }
    }
    cert = SSL_get_peer_certificate(c->ssl);
    if (cert == NULL) {
        BIO_printf(bio_out, "Anon DH\n");
    } else {
        BIO_printf(bio_out, "Peer certificate\n");
        ssl_print_cert_info(bio_out, cert);
        X509_free(cert);
    }
    ssl_print_connection_info(bio_err,c->ssl);
    SSL_SESSION_print(bio_err, SSL_get_session(c->ssl));
    }