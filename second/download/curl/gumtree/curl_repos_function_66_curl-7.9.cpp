CURLcode Curl_SSL_InitSessions(struct SessionHandle *data, long amount)
{
  struct curl_ssl_session *session;

  if(data->state.session)
    /* this is just a precaution to prevent multiple inits */
    return CURLE_OK;

  session = (struct curl_ssl_session *)
    malloc(amount * sizeof(struct curl_ssl_session));
  if(!session)
    return CURLE_OUT_OF_MEMORY;

  /* "blank out" the newly allocated memory */
  memset(session, 0, amount * sizeof(struct curl_ssl_session));

  /* store the info in the SSL section */
  data->set.ssl.numsessions = amount;
  data->state.session = session;
  data->state.sessionage = 1; /* this is brand new */

  return CURLE_OK;
}