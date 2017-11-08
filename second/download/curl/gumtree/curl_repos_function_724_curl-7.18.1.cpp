static CURLcode do_init(struct connectdata *conn)
{
  struct SessionHandle *data = conn->data;
  struct SingleRequest *k = &data->req;

  conn->bits.done = FALSE; /* Curl_done() is not called yet */
  conn->bits.do_more = FALSE; /* by default there's no curl_do_more() to use */

  /* NB: the content encoding software depends on this initialization */
  Curl_easy_initHandleData(data);

  k->start = Curl_tvnow(); /* start time */
  k->now = k->start;   /* current time is now */
  k->header = TRUE; /* assume header */
  k->httpversion = -1; /* unknown at this point */

  k->bytecount = 0;

  k->buf = data->state.buffer;
  k->uploadbuf = data->state.uploadbuffer;
  k->hbufp = data->state.headerbuff;
  k->ignorebody=FALSE;

  Curl_pgrsTime(data, TIMER_PRETRANSFER);
  Curl_speedinit(data);

  Curl_pgrsSetUploadCounter(data, 0);
  Curl_pgrsSetDownloadCounter(data, 0);

  return CURLE_OK;
}