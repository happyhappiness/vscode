sasl_callback_t* mutt_sasl_get_callbacks (ACCOUNT* account)
{
  sasl_callback_t* callback;

  callback = mutt_sasl_callbacks;

  callback->id = SASL_CB_USER;
  callback->proc = (int (*)(void))mutt_sasl_cb_authname;
  callback->context = account;
  callback++;

  callback->id = SASL_CB_AUTHNAME;
  callback->proc = (int (*)(void))mutt_sasl_cb_authname;
  callback->context = account;
  callback++;

  callback->id = SASL_CB_PASS;
  callback->proc = (int (*)(void))mutt_sasl_cb_pass;
  callback->context = account;
  callback++;

  callback->id = SASL_CB_GETREALM;
  callback->proc = NULL;
  callback->context = NULL;
  callback++;

  callback->id = SASL_CB_LIST_END;
  callback->proc = NULL;
  callback->context = NULL;

  return mutt_sasl_callbacks;
}