static CURLcode smtp_perform_ehlo(struct connectdata *conn)
{
  CURLcode result = CURLE_OK;
  struct smtp_conn *smtpc = &conn->proto.smtpc;

  smtpc->authmechs = 0;         /* No known authentication mechanisms yet */
  smtpc->authused = 0;          /* Clear the authentication mechanism used
                                   for esmtp connections */
  smtpc->tls_supported = FALSE; /* Clear the TLS capability */

  /* Send the EHLO command */
  result = Curl_pp_sendf(&smtpc->pp, "EHLO %s", smtpc->domain);

  if(!result)
    state(conn, SMTP_EHLO);

  return result;
}