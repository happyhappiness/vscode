static CURLcode pop3_state_auth_xoauth2_resp(struct connectdata *conn,
                                             int pop3code, pop3state instate)
{
  CURLcode result = CURLE_OK;
  struct SessionHandle *data = conn->data;
  size_t len = 0;
  char *xoauth = NULL;

  (void)instate; /* no use for this yet */

  if(pop3code != '+') {
    failf(data, "Access denied: %d", pop3code);
    result = CURLE_LOGIN_DENIED;
  }
  else {
    /* Create the authorisation message */
    result = Curl_sasl_create_xoauth2_message(conn->data, conn->user,
                                              conn->xoauth2_bearer,
                                              &xoauth, &len);
    if(!result && xoauth) {
      /* Send the message */
      result = Curl_pp_sendf(&conn->proto.pop3c.pp, "%s", xoauth);

      if(!result)
        state(conn, POP3_AUTH_FINAL);
    }
  }

  Curl_safefree(xoauth);

  return result;
}