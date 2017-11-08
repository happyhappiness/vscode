static CURLcode imap_perform_append(struct connectdata *conn)
{
  CURLcode result = CURLE_OK;
  struct IMAP *imap = conn->data->req.protop;
  char *mailbox;

  /* Check we have a mailbox */
  if(!imap->mailbox) {
    failf(conn->data, "Cannot APPEND without a mailbox.");
    return CURLE_URL_MALFORMAT;
  }

  /* Check we know the size of the upload */
  if(conn->data->state.infilesize < 0) {
    failf(conn->data, "Cannot APPEND with unknown input file size\n");
    return CURLE_UPLOAD_FAILED;
  }

  /* Make sure the mailbox is in the correct atom format */
  mailbox = imap_atom(imap->mailbox);
  if(!mailbox)
    return CURLE_OUT_OF_MEMORY;

  /* Send the APPEND command */
  result = imap_sendf(conn, "APPEND %s (\\Seen) {%" CURL_FORMAT_CURL_OFF_T "}",
                      mailbox, conn->data->state.infilesize);

  Curl_safefree(mailbox);

  if(!result)
    state(conn, IMAP_APPEND);

  return result;
}