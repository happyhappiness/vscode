static CURLcode sslctxfun(CURL * curl, void * sslctx, void * parm) {

  sslctxparm * p = (sslctxparm *) parm;
  SSL_CTX * ctx = (SSL_CTX *) sslctx ;

  if (!SSL_CTX_use_certificate(ctx,p->usercert)) {
    BIO_printf(p->errorbio, "SSL_CTX_use_certificate problem\n"); goto err;
  }
  if (!SSL_CTX_use_PrivateKey(ctx,p->pkey)) {
    BIO_printf(p->errorbio, "SSL_CTX_use_PrivateKey\n"); goto err;
  }

  if (!SSL_CTX_check_private_key(ctx)) {
    BIO_printf(p->errorbio, "SSL_CTX_check_private_key\n"); goto err;
  }

  SSL_CTX_set_quiet_shutdown(ctx,1);
  SSL_CTX_set_cipher_list(ctx,"RC4-MD5");
  SSL_CTX_set_mode(ctx, SSL_MODE_AUTO_RETRY);

  X509_STORE_add_cert(ctx->cert_store,sk_X509_value(p->ca,
                                                    sk_X509_num(p->ca)-1));

  SSL_CTX_set_verify_depth(ctx,2);

  SSL_CTX_set_verify(ctx,SSL_VERIFY_PEER,NULL);

  SSL_CTX_set_cert_verify_callback(ctx, ssl_app_verify_callback, parm);


  return CURLE_OK ;
  err:
  ERR_print_errors(p->errorbio);
  return CURLE_SSL_CERTPROBLEM;

}