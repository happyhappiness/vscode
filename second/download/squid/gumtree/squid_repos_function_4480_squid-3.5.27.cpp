int
untrustedToStoreCtx_cb(X509_STORE_CTX *ctx,void *data)
{
    debugs(83, 4,  "Try to use pre-downloaded intermediate certificates\n");

    // OpenSSL already maintains ctx->untrusted but we cannot modify
    // internal OpenSSL list directly. We have to give OpenSSL our own
    // list, but it must include certificates on the OpenSSL ctx->untrusted
    STACK_OF(X509) *oldUntrusted = ctx->untrusted;
    STACK_OF(X509) *sk = sk_X509_dup(oldUntrusted); // oldUntrusted is always not NULL
    completeIssuers(ctx, sk);
    X509_STORE_CTX_set_chain(ctx, sk); // No locking/unlocking, just sets ctx->untrusted
    int ret = X509_verify_cert(ctx);
    X509_STORE_CTX_set_chain(ctx, oldUntrusted); // Set back the old untrusted list
    sk_X509_free(sk); // Release sk list
    return ret;
}