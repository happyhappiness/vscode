{
  struct curl_ssl_session *session;

  if(data->state.session)
    /* this is just a precaution to prevent multiple inits */
    return CURLE_OK;

  session = calloc(amount, sizeof(struct curl_ssl_session));
  if(!session)
    return CURLE_OUT_OF_MEMORY;

  /* store the info in the SSL section */
  data->set.general_ssl.max_ssl_sessions = amount;
  data->state.session = session;
  data->state.sessionage = 1; /* this is brand new */
  return CURLE_OK;
}