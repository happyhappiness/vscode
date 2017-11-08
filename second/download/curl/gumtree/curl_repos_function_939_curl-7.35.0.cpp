static CURLcode imap_perform_capability(struct connectdata *conn)
{
  CURLcode result = CURLE_OK;
  struct imap_conn *imapc = &conn->proto.imapc;

  imapc->authmechs = 0;         /* No known authentication mechanisms yet */
  imapc->authused = 0;          /* Clear the authentication mechanism used */
  imapc->tls_supported = FALSE; /* Clear the TLS capability */

  /* Send the CAPABILITY command */
  result = imap_sendf(conn, "CAPABILITY");

  if(!result)
    state(conn, IMAP_CAPABILITY);

  return result;
}