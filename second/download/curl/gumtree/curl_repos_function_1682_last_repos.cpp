static CURLcode pop3_perform_starttls(struct connectdata *conn)
{
  CURLcode result = CURLE_OK;

  /* Send the STLS command */
  result = Curl_pp_sendf(&conn->proto.pop3c.pp, "%s", "STLS");

  if(!result)
    state(conn, POP3_STARTTLS);

  return result;
}