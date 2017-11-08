static CURLcode smtp_perform_authentication(struct connectdata *conn)
{
  CURLcode result = CURLE_OK;
  const char *mech = NULL;
  char *initresp = NULL;
  size_t len = 0;
  smtpstate state1 = SMTP_STOP;
  smtpstate state2 = SMTP_STOP;

  /* Check we have a username and password to authenticate with and end the
     connect phase if we don't */
  if(!conn->bits.user_passwd) {
    state(conn, SMTP_STOP);

    return result;
  }

  /* Calculate the SASL login details */
  result = smtp_calc_sasl_details(conn, &mech, &initresp, &len, &state1,
                                  &state2);

  if(!result) {
    if(mech) {
      /* Perform SASL based authentication */
      result = smtp_perform_auth(conn, mech, initresp, len, state1, state2);

      Curl_safefree(initresp);
    }
    else {
      /* Other mechanisms not supported */
      infof(conn->data, "No known authentication mechanisms supported!\n");
      result = CURLE_LOGIN_DENIED;
    }
  }

  return result;
}