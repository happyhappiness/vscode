static CURLcode imap_state_fetch_final_resp(struct connectdata *conn,
                                            int imapcode,
                                            imapstate instate)
{
  CURLcode result = CURLE_OK;

  (void)instate; /* No use for this yet */

  if(imapcode != 'O')
    result = CURLE_FTP_WEIRD_SERVER_REPLY; /* TODO: Fix error code */
  else
    /* End of DONE phase */
    state(conn, IMAP_STOP);

  return result;
}