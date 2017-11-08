static CURLcode imap_perform_authenticate(struct connectdata *conn,
                                          const char *mech,
                                          const char *initresp,
                                          imapstate state1, imapstate state2)
{
  CURLcode result = CURLE_OK;

  if(initresp) {
    /* Send the AUTHENTICATE command with the initial response */
    result = imap_sendf(conn, "AUTHENTICATE %s %s", mech, initresp);

    if(!result)
      state(conn, state2);
  }
  else {
    /* Send the AUTHENTICATE command */
    result = imap_sendf(conn, "AUTHENTICATE %s", mech);

    if(!result)
      state(conn, state1);
  }

  return result;
}