static CURLcode smtp_state_auth_cram_resp(struct connectdata *conn,
                                          int smtpcode,
                                          smtpstate instate)
{
  CURLcode result = CURLE_OK;
  struct SessionHandle *data = conn->data;
  char *chlg = NULL;
  char *chlg64 = NULL;
  char *rplyb64 = NULL;
  size_t len = 0;

  (void)instate; /* no use for this yet */

  if(smtpcode != 334) {
    failf(data, "Access denied: %d", smtpcode);
    return CURLE_LOGIN_DENIED;
  }

  /* Get the challenge message */
  smtp_get_message(data->state.buffer, &chlg64);

  /* Decode the challenge message */
  result = Curl_sasl_decode_cram_md5_message(chlg64, &chlg, &len);
  if(result) {
    /* Send the cancellation */
    result = Curl_pp_sendf(&conn->proto.smtpc.pp, "%s", "*");

    if(!result)
      state(conn, SMTP_AUTH_CANCEL);
  }
  else {
    /* Create the response message */
    result = Curl_sasl_create_cram_md5_message(data, chlg, conn->user,
                                               conn->passwd, &rplyb64, &len);
    if(!result && rplyb64) {
      /* Send the response */
      result = Curl_pp_sendf(&conn->proto.smtpc.pp, "%s", rplyb64);

      if(!result)
        state(conn, SMTP_AUTH_FINAL);
    }
  }

  Curl_safefree(chlg);
  Curl_safefree(rplyb64);

  return result;
}