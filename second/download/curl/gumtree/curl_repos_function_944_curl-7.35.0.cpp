static CURLcode imap_perform_authentication(struct connectdata *conn)
{
  CURLcode result = CURLE_OK;
  struct imap_conn *imapc = &conn->proto.imapc;
  const char *mech = NULL;
  char *initresp = NULL;
  size_t len = 0;
  imapstate state1 = IMAP_STOP;
  imapstate state2 = IMAP_STOP;

  /* Check we have a username and password to authenticate with and end the
     connect phase if we don't */
  if(!conn->bits.user_passwd) {
    state(conn, IMAP_STOP);

    return result;
  }

  /* Calculate the SASL login details */
  result = imap_calc_sasl_details(conn, &mech, &initresp, &len, &state1,
                                  &state2);

  if(!result) {
    if(mech && (imapc->preftype & IMAP_TYPE_SASL)) {
      /* Perform SASL based authentication */
      result = imap_perform_authenticate(conn, mech, initresp, state1, state2);

      Curl_safefree(initresp);
    }
    else if((!imapc->login_disabled) &&
            (imapc->preftype & IMAP_TYPE_CLEARTEXT))
      /* Perform clear text authentication */
      result = imap_perform_login(conn);
    else {
      /* Other mechanisms not supported */
      infof(conn->data, "No known authentication mechanisms supported!\n");
      result = CURLE_LOGIN_DENIED;
    }
  }

  return result;
}