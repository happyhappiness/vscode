static CURLcode pop3_state_auth_ntlm_resp(struct connectdata *conn,
                                          int pop3code,
                                          pop3state instate)
{
  CURLcode result = CURLE_OK;
  struct SessionHandle *data = conn->data;
  size_t len = 0;
  char *type1msg = NULL;

  (void)instate; /* no use for this yet */

  if(pop3code != '+') {
    failf(data, "Access denied: %d", pop3code);
    result = CURLE_LOGIN_DENIED;
  }
  else {
    /* Create the type-1 message */
    result = Curl_sasl_create_ntlm_type1_message(conn->user, conn->passwd,
                                                 &conn->ntlm,
                                                 &type1msg, &len);
    if(!result && type1msg) {
      /* Send the message */
      result = Curl_pp_sendf(&conn->proto.pop3c.pp, "%s", type1msg);

      if(!result)
        state(conn, POP3_AUTH_NTLM_TYPE2MSG);
    }
  }

  Curl_safefree(type1msg);

  return result;
}