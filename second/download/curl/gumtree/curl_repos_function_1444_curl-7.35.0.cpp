static CURLcode pop3_state_auth_login_resp(struct connectdata *conn,
                                           int pop3code,
                                           pop3state instate)
{
  CURLcode result = CURLE_OK;
  struct SessionHandle *data = conn->data;
  size_t len = 0;
  char *authuser = NULL;

  (void)instate; /* no use for this yet */

  if(pop3code != '+') {
    failf(data, "Access denied: %d", pop3code);
    result = CURLE_LOGIN_DENIED;
  }
  else {
    /* Create the user message */
    result = Curl_sasl_create_login_message(data, conn->user,
                                            &authuser, &len);
    if(!result && authuser) {
      /* Send the user */
      result = Curl_pp_sendf(&conn->proto.pop3c.pp, "%s", authuser);

      if(!result)
        state(conn, POP3_AUTH_LOGIN_PASSWD);
    }
  }

  Curl_safefree(authuser);

  return result;
}