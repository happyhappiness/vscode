static CURLcode pop3_state_auth_plain_resp(struct connectdata *conn,
                                           int pop3code,
                                           pop3state instate)
{
  CURLcode result = CURLE_OK;
  struct SessionHandle *data = conn->data;
  size_t len = 0;
  char *plainauth = NULL;

  (void)instate; /* no use for this yet */

  if(pop3code != '+') {
    failf(data, "Access denied. %c", pop3code);
    result = CURLE_LOGIN_DENIED;
  }
  else {
    /* Create the authorisation message */
    result = Curl_sasl_create_plain_message(data, conn->user, conn->passwd,
                                            &plainauth, &len);
    if(!result && plainauth) {
      /* Send the message */
      result = Curl_pp_sendf(&conn->proto.pop3c.pp, "%s", plainauth);

      if(!result)
        state(conn, POP3_AUTH_FINAL);
    }
  }

  Curl_safefree(plainauth);

  return result;
}