static CURLcode imap_state_servergreet_resp(struct connectdata *conn,
                                            int imapcode,
                                            imapstate instate)
{
  CURLcode result = CURLE_OK;
  struct SessionHandle *data = conn->data;

  (void)instate; /* no use for this yet */

  if(imapcode != 'O') {
    failf(data, "Got unexpected imap-server response");
    result = CURLE_FTP_WEIRD_SERVER_REPLY; /* TODO: fix this code */
  }
  else
    result = imap_perform_capability(conn);

  return result;
}