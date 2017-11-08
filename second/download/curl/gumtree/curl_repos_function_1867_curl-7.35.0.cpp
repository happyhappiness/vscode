static CURLcode smtp_state_auth_login_password_resp(struct connectdata *conn,
                                                    int smtpcode,
                                                    smtpstate instate)
{
  CURLcode result = CURLE_OK;
  struct SessionHandle *data = conn->data;
  size_t len = 0;
  char *authpasswd = NULL;

  (void)instate; /* no use for this yet */

  if(smtpcode != 334) {
    failf(data, "Access denied: %d", smtpcode);
    result = CURLE_LOGIN_DENIED;
  }
  else {
    /* Create the password message */
    result = Curl_sasl_create_login_message(conn->data, conn->passwd,
                                            &authpasswd, &len);
    if(!result && authpasswd) {
      /* Send the password */
      result = Curl_pp_sendf(&conn->proto.smtpc.pp, "%s", authpasswd);

      if(!result)
        state(conn, SMTP_AUTH_FINAL);
    }
  }

  Curl_safefree(authpasswd);

  return result;
}