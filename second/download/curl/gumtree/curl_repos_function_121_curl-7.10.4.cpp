CURLcode Curl_posttransfer(struct SessionHandle *data)
{
#if defined(HAVE_SIGNAL) && defined(SIGPIPE)
  /* restore the signal handler for SIGPIPE before we get back */
  if(!data->set.no_signal)
    signal(SIGPIPE, data->state.prev_signal);
#endif  

  return CURLE_OK;
}