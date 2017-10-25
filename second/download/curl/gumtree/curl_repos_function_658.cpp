CURLcode Curl_ssl_initsessions(struct SessionHandle *data, long amount)
{
#ifdef USE_SSL
  struct curl_ssl_session *session;

  if(data->state.session)
    /* this is just a precaution to prevent multiple inits */
    return CURLE_OK;

  session = (struct curl_ssl_session *)
    calloc(sizeof(struct curl_ssl_session), amount);
  if(!session)
    return CURLE_OUT_OF_MEMORY;

  /* store the info in the SSL section */
  data->set.ssl.numsessions = amount;
  data->state.session = session;
  data->state.sessionage = 1; /* this is brand new */
#else
  /* without SSL, do nothing */
  (void)data;
  (void)amount;
#endif

  return CURLE_OK;
}