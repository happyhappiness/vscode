void Curl_ssl_close_all(struct SessionHandle *data)
{
#ifdef USE_SSL
  int i;
  /* kill the session ID cache */
  if(data->state.session) {
    for(i=0; i< data->set.ssl.numsessions; i++)
      /* the single-killer function handles empty table slots */
      kill_session(&data->state.session[i]);

    /* free the cache data */
    free(data->state.session);
    data->state.session = NULL;
  }
#ifdef USE_SSLEAY
  Curl_ossl_close_all(data);
#else
#ifdef USE_GNUTLS
  Curl_gtls_close_all(data);
#endif /* USE_GNUTLS */
#endif /* USE_SSLEAY */
#else /* USE_SSL */
  (void)data;
#endif /* USE_SSL */
}