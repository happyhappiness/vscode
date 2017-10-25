static CURLcode sslctxfun(CURL * curl, void * sslctx, void * parm)
{
  sslctxparm * p = (sslctxparm *) parm;

  SSL_CTX * ctx = (SSL_CTX *) sslctx ;
  fprintf(stderr,"sslctxfun start curl=%p ctx=%p parm=%p\n",
          (void *)curl,(void *)ctx,(void *)p);

  SSL_CTX_set_quiet_shutdown(ctx,1);
  SSL_CTX_set_cipher_list(ctx,"RC4-MD5");
  SSL_CTX_set_mode(ctx, SSL_MODE_AUTO_RETRY);

/* one might assume that the cert validaton would not fail when setting this,
   but it still does, see the error handling in the call back */

  SSL_CTX_set_verify_depth(ctx,0);
  SSL_CTX_set_verify(ctx,SSL_VERIFY_NONE,NULL);

#if OPENSSL_VERSION_NUMBER<0x00907000L
/* in newer openssl versions we can set a parameter for the call back. */
  fprintf(stderr,"This version %s of openssl does not support a parm,"
          " setting global one\n", OPENSSL_VERSION_TEXT);
  /* this is only done to support 0.9.6 version */
  globalparm = parm;

/* in 0.9.6 the parm is not taken */
#endif
  SSL_CTX_set_cert_verify_callback(ctx, ssl_app_verify_callback, parm);
  fprintf(stderr,"sslctxfun end\n");

  return CURLE_OK ;
}