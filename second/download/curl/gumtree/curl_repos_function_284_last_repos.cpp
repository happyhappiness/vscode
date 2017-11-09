static int ssl_app_verify_callback(X509_STORE_CTX *ctx, void *arg)
{
  sslctxparm * p = (sslctxparm *) arg;
  int ok;

  if(p->verbose > 2)
    BIO_printf(p->errorbio, "entering ssl_app_verify_callback\n");

  ok = X509_verify_cert(ctx);
  if(ok && ctx->cert) {
    unsigned char *accessinfo;
    if(p->verbose > 1)
      X509_print_ex(p->errorbio, ctx->cert, 0, 0);

    accessinfo = my_get_ext(ctx->cert, p->accesstype, NID_sinfo_access);
    if(accessinfo) {
      if(p->verbose)
        BIO_printf(p->errorbio, "Setting URL from SIA to: %s\n", accessinfo);

      curl_easy_setopt(p->curl, CURLOPT_URL, accessinfo);
    }
    else if(accessinfo = my_get_ext(ctx->cert, p->accesstype,
                                    NID_info_access)) {
      if(p->verbose)
        BIO_printf(p->errorbio, "Setting URL from AIA to: %s\n", accessinfo);

      curl_easy_setopt(p->curl, CURLOPT_URL, accessinfo);
    }
  }
  if(p->verbose > 2)
    BIO_printf(p->errorbio, "leaving ssl_app_verify_callback with %d\n", ok);

  return ok;
}