int
untrustedToStoreCtx_cb(X509_STORE_CTX *ctx,void *data)
{
    debugs(83, 4,  "Try to use pre-downloaded intermediate certificates\n");

    SSL *ssl = static_cast<SSL *>(X509_STORE_CTX_get_ex_data(ctx, SSL_get_ex_data_X509_STORE_CTX_idx()));
    STACK_OF(X509) *sslUntrustedStack = static_cast <STACK_OF(X509) *>(SSL_get_ex_data(ssl, ssl_ex_index_ssl_untrusted_chain));

    // OpenSSL already maintains ctx->untrusted but we cannot modify
    // internal OpenSSL list directly. We have to give OpenSSL our own
    // list, but it must include certificates on the OpenSSL ctx->untrusted
#if HAVE_LIBCRYPTO_X509_STORE_CTX_GET0_UNTRUSTED
    STACK_OF(X509) *oldUntrusted = X509_STORE_CTX_get0_untrusted(ctx);
#else
    STACK_OF(X509) *oldUntrusted = ctx->untrusted;
#endif
    STACK_OF(X509) *sk = sk_X509_dup(oldUntrusted); // oldUntrusted is always not NULL

    for (int i = 0; i < sk_X509_num(sslUntrustedStack); ++i) {
        X509 *cert = sk_X509_value(sslUntrustedStack, i);
        sk_X509_push(sk, cert);
    }

    // If the local untrusted certificates internal database is used
    // run completeIssuers to add missing certificates if possible.
    if (SquidUntrustedCerts.size() > 0)
        completeIssuers(ctx, sk);

    X509_STORE_CTX_set_chain(ctx, sk); // No locking/unlocking, just sets ctx->untrusted
    int ret = X509_verify_cert(ctx);
#if HAVE_LIBCRYPTO_X509_STORE_CTX_SET0_UNTRUSTED
    X509_STORE_CTX_set0_untrusted(ctx, oldUntrusted);
#else
    X509_STORE_CTX_set_chain(ctx, oldUntrusted); // Set back the old untrusted list
#endif
    sk_X509_free(sk); // Release sk list
    return ret;
}