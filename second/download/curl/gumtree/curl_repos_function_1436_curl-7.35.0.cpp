static CURLcode pop3_perform_auth(struct connectdata *conn,
                                  const char *mech,
                                  const char *initresp, size_t len,
                                  pop3state state1, pop3state state2)
{
  CURLcode result = CURLE_OK;
  struct pop3_conn *pop3c = &conn->proto.pop3c;

  if(initresp && 8 + strlen(mech) + len <= 255) { /* AUTH <mech> ...<crlf> */
    /* Send the AUTH command with the initial response */
    result = Curl_pp_sendf(&pop3c->pp, "AUTH %s %s", mech, initresp);

    if(!result)
      state(conn, state2);
  }
  else {
    /* Send the AUTH command */
    result = Curl_pp_sendf(&pop3c->pp, "AUTH %s", mech);

    if(!result)
      state(conn, state1);
  }

  return result;
}