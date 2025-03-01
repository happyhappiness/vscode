int Curl_SSL_Close_All(struct SessionHandle *data)
{
  int i;

  if(data->state.session) {    
    for(i=0; i< data->set.ssl.numsessions; i++)
      /* the single-killer function handles empty table slots */
      Kill_Single_Session(&data->state.session[i]);
    
    /* free the cache data */
    free(data->state.session);
  }
#ifdef HAVE_OPENSSL_ENGINE_H
  if (data->engine)
  {
    ENGINE_free(data->engine);
    data->engine = NULL;
  }
#endif
  return 0;
}