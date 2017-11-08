static CURLcode smtp_state_auth_login_resp(struct connectdata *conn,
                                           int smtpcode,
                                           smtpstate instate)
{
  CURLcode result = CURLE_OK;
  struct SessionHandle *data = conn->data;
  size_t len = 0;
  char *authuser = NULL;

  (void)instate; /* no use for this yet */

  if(smtpcode != 334) {
    failf(data, "Access denied: %d", smtpcode);
    result = CURLE_LOGIN_DENIED;
  }
  else {
    /* Create the user message */
    result = Curl_sasl_create_login_message(conn->data, conn->user,
                                            &authuser, &len);
    if(!result && authuser) {
      /* Send the user */
      result = Curl_pp_sendf(&conn->proto.smtpc.pp, "%s", authuser);

      if(!result)
        state(conn, SMTP_AUTH_LOGIN_PASSWD);
    }
  }

  Curl_safefree(authuser);

  return result;
}