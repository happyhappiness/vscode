static CURLcode pop3_done(struct connectdata *conn, CURLcode status,
                          bool premature)
{
  CURLcode result = CURLE_OK;
  struct SessionHandle *data = conn->data;
  struct POP3 *pop3 = data->req.protop;

  (void)premature;

  if(!pop3)
    /* When the easy handle is removed from the multi interface while libcurl
       is still trying to resolve the host name, the POP3 struct is not yet
       initialized. However, the removal action calls Curl_done() which in
       turn calls this function, so we simply return success. */
    return CURLE_OK;

  if(status) {
    connclose(conn, "POP3 done with bad status");
    result = status;         /* use the already set error code */
  }

  /* Cleanup our per-request based variables */
  Curl_safefree(pop3->id);
  Curl_safefree(pop3->custom);

  /* Clear the transfer mode for the next request */
  pop3->transfer = FTPTRANSFER_BODY;

  return result;
}