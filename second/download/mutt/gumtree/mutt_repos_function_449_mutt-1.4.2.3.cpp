int mutt_sasl_start (void)
{
  static unsigned char sasl_init = 0;

  sasl_callback_t* callback, callbacks[2];
  int rc;

  if (sasl_init)
    return SASL_OK;

  /* set up default logging callback */
  callback = callbacks;

  callback->id = SASL_CB_LOG;
  callback->proc = mutt_sasl_cb_log;
  callback->context = NULL;
  callback++;

  callback->id = SASL_CB_LIST_END;
  callback->proc = NULL;
  callback->context = NULL;

  rc = sasl_client_init (callbacks);

  if (rc != SASL_OK)
  {
    dprint (1, (debugfile, "mutt_sasl_start: libsasl initialisation failed.\n"));
    return SASL_FAIL;
  }

  sasl_init = 1;

  return SASL_OK;
}