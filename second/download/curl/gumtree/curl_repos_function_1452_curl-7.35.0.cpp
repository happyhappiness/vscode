static CURLcode pop3_state_auth_cancel_resp(struct connectdata *conn,
                                            int pop3code,
                                            pop3state instate)
{
  CURLcode result = CURLE_OK;
  struct SessionHandle *data = conn->data;
  struct pop3_conn *pop3c = &conn->proto.pop3c;
  const char *mech = NULL;
  char *initresp = NULL;
  size_t len = 0;
  pop3state state1 = POP3_STOP;
  pop3state state2 = POP3_STOP;

  (void)pop3code;
  (void)instate; /* no use for this yet */

  /* Remove the offending mechanism from the supported list */
  pop3c->authmechs ^= pop3c->authused;

  /* Calculate alternative SASL login details */
  result = pop3_calc_sasl_details(conn, &mech, &initresp, &len, &state1,
                                  &state2);

  if(!result) {
    /* Do we have any mechanisms left or can we fallback to another
       authentication type? */
    if(mech) {
      /* Retry SASL based authentication */
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
      failf(data, "Authentication cancelled");

      result = CURLE_LOGIN_DENIED;
    }
  }

  return result;
}