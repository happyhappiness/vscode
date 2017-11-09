static int ssl_set_verify_partial (SSL_CTX *ctx)
{
  int rv = 0;
#ifdef HAVE_SSL_PARTIAL_CHAIN
  X509_VERIFY_PARAM *param;

  if (option (OPTSSLVERIFYPARTIAL))
  {
    param = X509_VERIFY_PARAM_new();
    if (param)
    {
      X509_VERIFY_PARAM_set_flags(param, X509_V_FLAG_PARTIAL_CHAIN);
      if (0 == SSL_CTX_set1_param(ctx, param))
      {
        dprint (2, (debugfile, "ssl_set_verify_partial: SSL_CTX_set1_param() failed."));
        rv = -1;
      }
      X509_VERIFY_PARAM_free(param);
    }
    else
    {
      dprint (2, (debugfile, "ssl_set_verify_partial: X509_VERIFY_PARAM_new() failed."));
      rv = -1;
    }
  }
#endif
  return rv;
}