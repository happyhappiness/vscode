static CURLcode pop3_perform_quit(struct connectdata *conn)
{
  CURLcode result = CURLE_OK;

  /* Send the QUIT command */
  result = Curl_pp_sendf(&conn->proto.pop3c.pp, "%s", "QUIT");

  if(!result)
    state(conn, POP3_QUIT);

  return result;
}