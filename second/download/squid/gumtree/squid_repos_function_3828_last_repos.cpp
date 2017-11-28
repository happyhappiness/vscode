static void
maybeSetupRsaCallback(Security::ContextPointer &ctx)
{
#if HAVE_LIBSSL_SSL_CTX_SET_TMP_RSA_CALLBACK
    debugs(83, 9, "Setting RSA key generation callback.");
    SSL_CTX_set_tmp_rsa_callback(ctx.get(), ssl_temp_rsa_cb);
#endif
}