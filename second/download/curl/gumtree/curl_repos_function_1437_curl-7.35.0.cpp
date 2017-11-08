static CURLcode pop3_perform_authentication(struct connectdata *conn)
{
  CURLcode result = CURLE_OK;
  struct pop3_conn *pop3c = &conn->proto.pop3c;
  const char *mech = NULL;
  char *initresp = NULL;
  size_t len = 0;
  pop3state state1 = POP3_STOP;
  pop3state state2 = POP3_STOP;

  /* Check we have a username and password to authenticate with and end the
     connect phase if we don't */
  if(!conn->bits.user_passwd) {
    state(conn, POP3_STOP);

    return result;
  }

  /* Calculate the SASL login details */
  if(pop3c->authtypes & POP3_TYPE_SASL)
    result = pop3_calc_sasl_details(conn, &mech, &initresp, &len, &state1,
                                    &state2);

  if(!result) {
    if(mech && (pop3c->preftype & POP3_TYPE_SASL)) {
      /* Perform SASL based authentication */
      result = pop3_perform_auth(conn, mech, initresp, len, state1, state2);

      Curl_safefree(initresp);
    }
#ifndef CURL_DISABLE_CRYPTO_AUTH
    else if((pop3c->authtypes & POP3_TYPE_APOP) &&
            (pop3c->preftype & POP3_TYPE_APOP))
      /* Perform APOP authentication */
      result = pop3_perform_apop(conn);
#endif
    else if((pop3c->authtypes & POP3_TYPE_CLEARTEXT) &&
            (pop3c->preftype & POP3_TYPE_CLEARTEXT))
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