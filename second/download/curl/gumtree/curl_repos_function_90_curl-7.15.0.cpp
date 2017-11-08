static int ssl_app_verify_callback(X509_STORE_CTX *ctx, void *arg)
{
  sslctxparm * p = (sslctxparm *) arg;
  int ok, err;

  fprintf(stderr,"ssl_app_verify_callback sslctxparm=%p ctx=%p\n",
          (void *)p, (void*)ctx);

#if OPENSSL_VERSION_NUMBER<0x00907000L
/* not necessary in openssl 0.9.7 or later */

  fprintf(stderr,"This version %s of openssl does not support a parm (%p)"
          ", getting a global static %p \n",
          OPENSSL_VERSION_TEXT, (void *)p, (void *)globalparm);

  p = globalparm;
#endif

/* The following error should not occur. We test this to avoid segfault. */
  if (!p || !ctx) {
    fprintf(stderr,"Internal error in ssl_app_verify_callback "
            "sslctxparm=%p ctx=%p\n",(void *)p,(void*)ctx);
    return 0;
  }

  ok= X509_verify_cert(ctx);
  err=X509_STORE_CTX_get_error(ctx);

/* The following seems to be a problem in 0.9.7/8 openssl versions */

#if 1
  if (err == X509_V_ERR_DEPTH_ZERO_SELF_SIGNED_CERT ||
      err == X509_V_ERR_UNABLE_TO_GET_ISSUER_CERT_LOCALLY) {
    fprintf(stderr,"X509_verify_cert: repairing self signed\n") ;
    X509_STORE_CTX_set_error(ctx,X509_V_OK);
    ok = 1;
  }
#endif

  if (ok && ctx->cert) {
    unsigned char * accessinfoURL ;

    accessinfoURL = my_get_ext(ctx->cert,p->accesstype ,NID_info_access);
    if (accessinfoURL) {

      if (strcmp((char *)p->accessinfoURL, (char *)accessinfoURL)) {
        fprintf(stderr, "Setting URL <%s>, was <%s>\n",
                (char *)accessinfoURL, (char *)p->accessinfoURL);
        OPENSSL_free(p->accessinfoURL);
        p->accessinfoURL = accessinfoURL;

        /* We need to be able to deal with a custom port number, but the
           URL in the cert uses a static one. We thus need to create a new
           URL that uses the currently requested port number which may not
           be the one this URL uses! */
        sprintf(newurl, "https://127.0.0.1:%d/509", portnum);
        fprintf(stderr, "But *really* Setting URL <%s>\n", newurl);

        curl_easy_setopt(p->curl, CURLOPT_URL, newurl);
      }
      else
        OPENSSL_free(accessinfoURL);
    }
  }
  return(ok);
}