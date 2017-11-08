static CURLcode pop3_perform_user(struct connectdata *conn)
{
  CURLcode result = CURLE_OK;

  /* Check we have a username and password to authenticate with and end the
     connect phase if we don't */
  if(!conn->bits.user_passwd) {
    state(conn, POP3_STOP);

    return result;
  }

  /* Send the USER command */
  result = Curl_pp_sendf(&conn->proto.pop3c.pp, "USER %s",
                         conn->user ? conn->user : "");
  if(!result)
    state(conn, POP3_USER);

  return result;
}