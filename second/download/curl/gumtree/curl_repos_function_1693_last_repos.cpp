static CURLcode pop3_state_starttls_resp(struct connectdata *conn,
                                         int pop3code,
                                         pop3state instate)
{
  CURLcode result = CURLE_OK;
  struct Curl_easy *data = conn->data;

  (void)instate; /* no use for this yet */

  if(pop3code != '+') {
    if(data->set.use_ssl != CURLUSESSL_TRY) {
      failf(data, "STARTTLS denied");
      result = CURLE_USE_SSL_FAILED;
    }
    else
      result = pop3_perform_authentication(conn);
  }
  else
    result = pop3_perform_upgrade_tls(conn);

  return result;
}