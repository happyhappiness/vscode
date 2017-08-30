{
#if defined(HAVE_SIGNAL) && defined(SIGPIPE)
  /* restore the signal handler for SIGPIPE before we get back */
  signal(SIGPIPE, data->state.prev_signal);
#endif  

  return CURLE_OK;
}

CURLcode Curl_perform(struct SessionHandle *data)
{
  CURLcode res;
  CURLcode res2;
  struct connectdata *conn=NULL;
  char *newurl = NULL; /* possibly a new URL to follow to! */

  res = Curl_pretransfer(data);
  if(res)
    return res;

  /*
   * It is important that there is NO 'return' from this function any any
   * other place than falling down the bottom! This is because we have cleanup
   * stuff that must be done before we get back, and that is only performed
   * after this do-while loop.
   */

  do {
