static void ssl_proceed_handshake(struct connection *c)
{
    int do_next = 1;

    while (do_next) {
        int ret, ecode;

        ret = SSL_do_handshake(c->ssl);
        ecode = SSL_get_error(c->ssl, ret);

        switch (ecode) {
        case SSL_ERROR_NONE:
            if (verbosity >= 2)
                ssl_print_info(c);
            if (ssl_info == NULL) {
                AB_SSL_CIPHER_CONST SSL_CIPHER *ci;
                X509 *cert;
                int sk_bits, pk_bits, swork;

                ci = SSL_get_current_cipher(c->ssl);
                sk_bits = SSL_CIPHER_get_bits(ci, &swork);
                cert = SSL_get_peer_certificate(c->ssl);
                if (cert)
                    pk_bits = EVP_PKEY_bits(X509_get_pubkey(cert));
                else
                    pk_bits = 0;  /* Anon DH */

                ssl_info = malloc(128);
                apr_snprintf(ssl_info, 128, "%s,%s,%d,%d",
                             SSL_CIPHER_get_version(ci),
                             SSL_CIPHER_get_name(ci),
                             pk_bits, sk_bits);
            }
            write_request(c);
            do_next = 0;
            break;
        case SSL_ERROR_WANT_READ:
            set_polled_events(c, APR_POLLIN);
            do_next = 0;
            break;
        case SSL_ERROR_WANT_WRITE:
            /* Try again */
            do_next = 1;
            break;
        case SSL_ERROR_WANT_CONNECT:
        case SSL_ERROR_SSL:
        case SSL_ERROR_SYSCALL:
            /* Unexpected result */
            BIO_printf(bio_err, "SSL handshake failed (%d).\n", ecode);
            ERR_print_errors(bio_err);
            close_connection(c);
            do_next = 0;
            break;
        }
    }
}