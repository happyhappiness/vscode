static CURLcode smtp_perform_auth(struct connectdata *conn,
                                  const char *mech,
                                  const char *initresp, size_t len,
                                  smtpstate state1, smtpstate state2)
{
  CURLcode result = CURLE_OK;
  struct smtp_conn *smtpc = &conn->proto.smtpc;

  if(initresp && 8 + strlen(mech) + len <= 512) { /* AUTH <mech> ...<crlf> */
    /* Send the AUTH command with the initial response */
    result = Curl_pp_sendf(&smtpc->pp, "AUTH %s %s", mech, initresp);

    if(!result)
      state(conn, state2);
  }
  else {
    /* Send the AUTH command */
    result = Curl_pp_sendf(&smtpc->pp, "AUTH %s", mech);

    if(!result)
      state(conn, state1);
  }

  return result;
}