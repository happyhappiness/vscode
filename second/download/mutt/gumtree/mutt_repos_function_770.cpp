int mutt_sasl_start (void)
{
  static unsigned char sasl_init = 0;

  static sasl_callback_t callbacks[2];
  int rc;

  if (sasl_init)
    return SASL_OK;

  /* set up default logging callback */
  callbacks[0].id = SASL_CB_LOG;
  callbacks[0].proc = (int (*)(void))mutt_sasl_cb_log;
  callbacks[0].context = NULL;

  callbacks[1].id = SASL_CB_LIST_END;
  callbacks[1].proc = NULL;
  callbacks[1].context = NULL;

  rc = sasl_client_init (callbacks);

  if (rc != SASL_OK)
  {
    dprint (1, (debugfile, "mutt_sasl_start: libsasl initialisation failed.\n"));
    return SASL_FAIL;
  }

  sasl_init = 1;

  return SASL_OK;
}