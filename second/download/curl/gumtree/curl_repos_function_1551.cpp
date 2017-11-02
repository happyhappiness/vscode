static CURLcode pop3_perform_authentication(struct connectdata *conn)
{
  CURLcode result = CURLE_OK;
  struct pop3_conn *pop3c = &conn->proto.pop3c;
  saslprogress progress = SASL_IDLE;

  /* Check we have enough data to authenticate with and end the
     connect phase if we don't */
  if(!Curl_sasl_can_authenticate(&pop3c->sasl, conn)) {
    state(conn, POP3_STOP);
    return result;
  }

  if(pop3c->authtypes & pop3c->preftype & POP3_TYPE_SASL) {
    /* Calculate the SASL login details */
    result = Curl_sasl_start(&pop3c->sasl, conn, FALSE, &progress);

    if(!result)
      if(progress == SASL_INPROGRESS)
        state(conn, POP3_AUTH);
  }

  if(!result && progress == SASL_IDLE) {
#ifndef CURL_DISABLE_CRYPTO_AUTH
    if(pop3c->authtypes & pop3c->preftype & POP3_TYPE_APOP)
      /* Perform APOP authentication */
      result = pop3_perform_apop(conn);
    else
#endif
    if(pop3c->authtypes & pop3c->preftype & POP3_TYPE_CLEARTEXT)
      /* Perform clear text authentication */
      result = pop3_perform_user(conn);
    else {
      /* Other mechanisms not supported */
      infof(conn->data, "No known authentication mechanisms supported!\n");
      result = CURLE_LOGIN_DENIED;
    }
  }

  return result;
}