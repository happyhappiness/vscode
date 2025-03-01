static CURLcode smtp_done(struct connectdata *conn, CURLcode status,
                          bool premature)
{
  CURLcode result = CURLE_OK;
  struct SessionHandle *data = conn->data;
  struct SMTP *smtp = data->req.protop;
  struct pingpong *pp = &conn->proto.smtpc.pp;
  const char *eob;
  ssize_t len;
  ssize_t bytes_written;

  (void)premature;

  if(!smtp)
    /* When the easy handle is removed from the multi interface while libcurl
       is still trying to resolve the host name, the SMTP struct is not yet
       initialized. However, the removal action calls Curl_done() which in
       turn calls this function, so we simply return success. */
    return CURLE_OK;

  if(status) {
    conn->bits.close = TRUE; /* marked for closure */
    result = status;         /* use the already set error code */
  }
  else if(!data->set.connect_only && data->set.upload && data->set.mail_rcpt) {
    /* Calculate the EOB taking into account any terminating CRLF from the
       previous line of the email or the CRLF of the DATA command when there
       is "no mail data". RFC-5321, sect. 4.1.1.4. */
    eob = SMTP_EOB;
    len = SMTP_EOB_LEN;
    if(smtp->trailing_crlf || !conn->data->set.infilesize) {
      eob += 2;
      len -= 2;
    }

    /* Send the end of block data */
    result = Curl_write(conn, conn->writesockfd, eob, len, &bytes_written);
    if(result)
      return result;

    if(bytes_written != len) {
      /* The whole chunk was not sent so keep it around and adjust the
         pingpong structure accordingly */
      pp->sendthis = strdup(eob);
      pp->sendsize = len;
      pp->sendleft = len - bytes_written;
    }
    else
      /* Successfully sent so adjust the response timeout relative to now */
      pp->response = Curl_tvnow();

    state(conn, SMTP_POSTDATA);

    /* Run the state-machine

       TODO: when the multi interface is used, this _really_ should be using
       the smtp_multi_statemach function but we have no general support for
       non-blocking DONE operations, not in the multi state machine and with
       Curl_done() invokes on several places in the code!
    */
    result = smtp_block_statemach(conn);
  }

  /* Cleanup our per-request based variables */
  Curl_safefree(smtp->custom);

  /* Clear the transfer mode for the next request */
  smtp->transfer = FTPTRANSFER_BODY;

  return result;
}