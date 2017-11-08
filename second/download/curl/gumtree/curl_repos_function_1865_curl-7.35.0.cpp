static CURLcode smtp_state_auth_plain_resp(struct connectdata *conn,
                                           int smtpcode,
                                           smtpstate instate)
{
  CURLcode result = CURLE_OK;
  struct SessionHandle *data = conn->data;
  size_t len = 0;
  char *plainauth = NULL;

  (void)instate; /* no use for this yet */

  if(smtpcode != 334) {
    failf(data, "Access denied: %d", smtpcode);
    result = CURLE_LOGIN_DENIED;
  }
  else {
    /* Create the authorisation message */
    result = Curl_sasl_create_plain_message(conn->data, conn->user,
                                            conn->passwd, &plainauth, &len);
    if(!result && plainauth) {
      /* Send the message */
      result = Curl_pp_sendf(&conn->proto.smtpc.pp, "%s", plainauth);

      if(!result)
        state(conn, SMTP_AUTH_FINAL);
    }
  }

  Curl_safefree(plainauth);

  return result;
}