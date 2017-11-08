static CURLcode imap_state_auth_login_resp(struct connectdata *conn,
                                           int imapcode,
                                           imapstate instate)
{
  CURLcode result = CURLE_OK;
  struct SessionHandle *data = conn->data;
  size_t len = 0;
  char *authuser = NULL;

  (void)instate; /* no use for this yet */

  if(imapcode != '+') {
    failf(data, "Access denied: %d", imapcode);
    result = CURLE_LOGIN_DENIED;
  }
  else {
    /* Create the user message */
    result = Curl_sasl_create_login_message(data, conn->user,
                                            &authuser, &len);
    if(!result && authuser) {
      /* Send the user */
      result = Curl_pp_sendf(&conn->proto.imapc.pp, "%s", authuser);

      if(!result)
        state(conn, IMAP_AUTHENTICATE_LOGIN_PASSWD);
    }
  }

  Curl_safefree(authuser);

  return result;
}