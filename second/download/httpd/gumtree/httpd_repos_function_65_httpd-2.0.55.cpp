void ssl_start_connect(struct connection * c)
{
    BIO *bio;
    X509 *x509cert;
#ifdef RSAREF
    STACK *sk;
#else
    STACK_OF(X509) *sk;
#endif
    int i, count, hdone = 0;
    char ssl_hostname[80];
    
    /* XXX - Verify if it's okay - TBD */
    if (requests < concurrency)
        requests = concurrency;

    if (!(started < requests))
        return;

    c->read = 0;
    c->bread = 0;
    c->keepalive = 0;
    c->cbx = 0;
    c->gotheader = 0;
    c->rwrite = 0;
    if (c->ctx)
        apr_pool_destroy(c->ctx);
    apr_pool_create(&c->ctx, cntxt);

    if ((c->ssl=SSL_new(ctx)) == NULL)
    {
        BIO_printf(bio_err,"SSL_new failed\n");
        exit(1);
    }

    ssl_rand_seed();

    c->start = apr_time_now();
    memset(ssl_hostname, 0, 80);
    sprintf(ssl_hostname, "%s:%d", hostname, port);

    if ((bio = BIO_new_connect(ssl_hostname)) == NULL)
    {
        BIO_printf(bio_err,"BIO_new_connect failed\n");
        exit(1);
    }
    SSL_set_bio(c->ssl,bio,bio);
    SSL_set_connect_state(c->ssl);

    if (verbosity >= 4)
    {
        BIO_set_callback(bio,ssl_print_cb);
        BIO_set_callback_arg(bio,(void*)bio_err);
    }

    while (!hdone)
    {
        i = SSL_do_handshake(c->ssl);

        switch (SSL_get_error(c->ssl,i))
        {
            case SSL_ERROR_NONE:
                hdone=1;
                break;
            case SSL_ERROR_SSL:
            case SSL_ERROR_SYSCALL:
                BIO_printf(bio_err,"SSL connection failed\n");
                err_conn++;
                c->state = STATE_UNCONNECTED;
                if (bad++ > 10) {
                    SSL_free (c->ssl);
                    BIO_printf(bio_err,"\nTest aborted after 10 failures\n\n");
                    exit (1);
                }
                break;
            case SSL_ERROR_WANT_READ:
            case SSL_ERROR_WANT_WRITE:
            case SSL_ERROR_WANT_CONNECT:
                BIO_printf(bio_err, "Waiting .. sleep(1)\n");
                apr_sleep(apr_time_from_sec(1));
                c->state = STATE_CONNECTED;
                c->rwrite = 0;
                break;
            case SSL_ERROR_ZERO_RETURN:
                BIO_printf(bio_err,"socket closed\n");
                break;
        }
    }
    
    if (verbosity >= 2)
    {
        BIO_printf(bio_err, "\n");
        sk = SSL_get_peer_cert_chain(c->ssl);
#ifdef RSAREF
        if ((count = sk_num(sk)) > 0)
#else
        if ((count = sk_X509_num(sk)) > 0)
#endif
        {
            for (i=1; i<count; i++)
            {
#ifdef RSAREF
                x509cert = (X509 *)sk_value(sk,i);
#else
                x509cert = (X509 *)sk_X509_value(sk,i);
#endif
                ssl_print_cert_info(bio_out,x509cert);
                X509_free(x509cert);
            }
        }

        x509cert = SSL_get_peer_certificate(c->ssl);
        if (x509cert == NULL)
            BIO_printf(bio_out, "Anon DH\n");
        else
        {
            BIO_printf(bio_out, "Peer certificate\n");
            ssl_print_cert_info(bio_out,x509cert);
            X509_free(x509cert);
        }

        ssl_print_connection_info(bio_err,c->ssl);
        SSL_SESSION_print(bio_err,SSL_get_session(c->ssl));
    }

    /* connected first time */
    started++;
    write_request(c);
}